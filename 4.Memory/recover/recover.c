#include <stdio.h>
// #include <stdlib.h>
#include <stdint.h>
 // 恢复照片
int main(int argc, char *argv[])
{
  if(argc !=2){
    printf("Usage: ./recover FILE\n");
    return 1;
  }
  //Open the memory card
  FILE *card =fopen(argv[1],"r");
  if(card==NULL){
    printf("could not open %s.\n",argv[1]);
    return 2;
  }
  //create a buffer for a block of data
  // uint8_t buffer[512];
  uint8_t buffer[512];

  int count =0;
  //JEPG file
  FILE *img =NULL;
  //while there's still data left to read from the mermory card
  // buffer:存储读取数据的内存缓冲区的指针
  // 1：要读取的每个数据项的大小 以字节为单位
  //512:读取的数据项的数量
  //card：指向FILE结构的指针 它标识了要从中读取数据的文件
  while(fread(buffer,1,512,card)){
    //0xff 0xd8 0xff 0xe1
    if(buffer[0]==0xff && buffer[1]==0xd8  && buffer[2]==0xff && (buffer[3]& 0xff)==0xe0){
      //close previous img (if has)
      if(img){
        fclose(img);
        //update img numbers
        count++;
      }
      //create a new filename
      char filename[8]={'0'};
      sprintf(filename,"%03i.jpg",count);

      //open a new JPEG file
      img =fopen(filename,"w");
      if(img==NULL){
        fclose(img);
        printf("Could not create %s.\n",filename);
        return 3;
      }
    }
    if(img){
      //write 512 bytes until a new JPEG is found
    fwrite(buffer,1,512,img);
    }
  }
  fclose(img);
  fclose(card);
  return 0;
}
