#include<cs50.h>
#include<stdio.h>

int main(void){
  // 25 10 5 1
  // 可以用贪心算法来做
// 1.Prompt the user for change owed, in cents.
  int cents;

  do{
   cents=get_int("Change Owed: ");
  }while(cents<1);
// 2.Calculate how many quarters you should give customer. Subtract the value of those quarters from cents.
    int quarters=0;
    while(cents>=25){
      quarters++;
      cents=cents-25;
   }
 
// 3.Calculate how/ many dimes you should give customer. Subtract the value of those dimes from remaining cents.
   int dimes=0;
   while(cents>=10){
    dimes++;
    cents=cents-10;
   }

// 4.Calculate how many nickels you should give customer. Subtract the value of those nickels from remaining cents.
  int nickels=0;
  while(cents>=5){
    nickels++;
    cents=cents-5;
  }

// 5.Calculate how many pennies you should give customer. Subtract the value of those pennies from remaining cents.
  int pennies=0;
  while(cents>0){
    pennies++;
    cents=cents-1;
  }
// 6.Sum the number of quarters, dimes, nickels, and pennies used.
  int owed=quarters+dimes+nickels+pennies;

  printf("%i\n",owed);
 }
