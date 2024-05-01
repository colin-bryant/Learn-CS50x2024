#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int main(void){

  // string s =get_string("s: ");
  // string t =s;   这是赋值了地址  所以会相同  深拷贝

  // char *s =get_string("s: ");
  // char *t =s;


  char *s =get_string("s: ");
  if(s==NULL){
    return 1;
  }
  char *t =malloc(strlen(s)+1);  //浅拷贝 malloc返回该内存块的地址
  if(t==NULL){
    return 1;
  }
  //    for(int i= 0,n=strlen(s);i<=n;i++){
  //   t[i]=s[i];
  //  } //这里并没有完全把s复制给t  i<=n /0
 strcopy(t,s); s into t
  if(strlen(t)>0){

  t[0] =toupper(t[0]);
  }

  printf("%s\n",s);//hi
  printf("%s\n",t);//Hi
  //因为浅拷贝的是值 地址就不一样 改变t 不会改变s

  //释放内存
  free(t);
  return 0；
}
