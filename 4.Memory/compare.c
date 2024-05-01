#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(void){
  char *s =get_string("s: ");
  // char *t =get_string("t: ");

  // if(strcmp(s,t)==0){
  //   printf("Same\n");
  // }else{
  //   printf("Different\n");
  // }
  printf("%p\n",&s);
  printf("%p\n",s);
  //&s 打印了变量 s 的地址，即指向指针 s 的指针的地址。
  // s 打印了指针 s 所指向的地址，也就是指针 s 存储的值，该值是字符串的首地址。


}
