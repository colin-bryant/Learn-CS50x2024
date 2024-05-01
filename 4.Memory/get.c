#include<stdio.h>

int main(void){
  // int n;
  // printf("n: ");
  // scanf("%i",&n);
  // printf("n: %i\n",n);
 // char *s;// error:Segmentation fault (core dumped)
  char s[4];
  printf("s: ");
  scanf("%s",s);//s已经是一个地址&s 表示的是指向指针 s 的指针，而不是指向字符串的指针，
  printf("s: %s\n",s);
  // clang -o get -Wno-uninitialized get.c 不要警告我们有些变量初始化
}
