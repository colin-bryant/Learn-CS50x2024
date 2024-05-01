#include<stdio.h>
// #include<cs50.h>

int main(void){
  // int n =50;
  // int *p=&n;

  // printf("%i\n",*p);
  // string s! ="HI!";
  char *s ="HI!";
 // char *s =&"HI!";//clang 足够聪明 当它看到一系列字符周围有双引号 它希望该第一个字符的地址放入变量中
  // printf("%p\n",s);
  // printf("%p\n",&s[0]);
  // printf("%p\n",&s[1]);
  // printf("%p\n",&s[2]);
  // printf("%p\n",&s[3]);

//   printf("%c",s[0]);
//   printf("%c",s[1]);
//   printf("%c\n",s[2]);
// }
    printf("%c\n",*s);
    printf("%c\n",*(s+1));
    printf("%c\n",*(s+2));

}
