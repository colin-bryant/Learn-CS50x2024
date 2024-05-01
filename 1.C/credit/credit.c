#include<cs50.h>
#include<stdio.h>
bool luhn_check(long numbers);
int even_digit(int n);

int main(void){

// 1. Prompt for input
  long numbers;
  do{
    numbers=get_long("Number: ");
  }while(numbers<1);
  bool is_valid=luhn_check(numbers);
  if(!is_valid){
    printf("INVALID\n");
    return 0;
  }
 // pass the luhn check
 // get the first two digit
 int digits =0;//获取位数
 while(numbers>=100){
   numbers=numbers/10;
   digits++;
 }
 if(digits+2==15){
  if(numbers==34 ||numbers==37){
    printf("AMEX\n");
  }else{
    printf("INVALID\n");
  }
 }
 else if(digits+2==16){
  if(numbers==51 ||numbers==52 || numbers==53  || numbers==54|| numbers==55 ){
    printf("MASTERCARD\n");
  }else{
    printf("INVALID\n");
  }
 }
 else if(digits + 2 ==13 ||digits + 2==16){
  if(numbers/10 ==4){
    printf("VISA\n");
  }else{
    printf("INVALID\n");
  }
 }



}
bool luhn_check(long numbers){
// 2. calculate checksum
  // odd_digit even_digit
  // 给numbers不断的除以“/” 10 取模 %
  int sum_odd=0;
  int sum_even=0;
  int digit=1;
  for(;numbers>0;numbers=numbers / 10,digit++){
    //n 表示每一次算出来的值
     int n = numbers %10;
     // 判断奇数项或者偶数项 用次数判断 digit
     if(digit % 2==1){
       sum_odd+=n;
     }else{
        //计算偶数项
     sum_even+=even_digit(n);
     }

  }
 int sum=sum_odd+sum_even;
 if(sum % 10 ==0){
  return true;
 }else{
  return false;
 }
}

int even_digit(int n){
  int middle= n*2;
  int sum=0;

  if(middle>=10){
    //个位
   int single=middle %10;
   int tens=middle/10;
   sum=single+tens;
  }else{
    sum=middle;
  }
  return sum;
}
