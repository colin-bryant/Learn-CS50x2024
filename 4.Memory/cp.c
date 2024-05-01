#include<stdio.h>
#include<stdint.h>
// 给我一个无符号的8位数
typedef uint8_t BYTE;

int main(int argc,char *argv[])
{
  FILE *src =fopen(argv[1],"rb");
  FILE *dst =fopen(argv[2],"wb");

  BYTE b;
// fread 函数返回值为 0，表示已经到达文件结尾，此时文件复制完成。
  while(fread(&b,sizeof(b),1,src) !=0)
  {
    fwrite(&b,sizeof(b),1,dst);
  }
  fclose(dst);
  fclose(src);
}
