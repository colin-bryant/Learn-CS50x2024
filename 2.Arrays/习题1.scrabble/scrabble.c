#include<cs50.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
int compute_score(string word);
int POINTS[]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

int main(void){
  //prompt the user for two words
  string word1=get_string("Player 1: ");
  string word2=get_string("Player 2: ");
  //Compute the score of each word
  int score1 = compute_score(word1);
  int score2 = compute_score(word2);
  //print the winner
  if(score1 > score2){
    printf("Player 1 wins!\n");
  }else if(score1<score2){
    printf("Player 2 wins!\n");

  }else{
    printf("Tie!\n");
  }
}
int compute_score(string word){
  // keep track of score 记录分数
  int score= 0;
  //Compute and return score for word
  //1. 如果是B 对应就是 POINTS[1] 也就是在数组中的第二位数
  //2. "1" 如何得知呢?  B：66  B-A =1 C-A=2
  //3. 如果是小写b  b:96  b-a=1
   // computer score of each character
   for(int i=0,n=strlen(word);i<n;i++){
    if(isupper(word[i])){
      score+=POINTS[word[i]-'A'];
    }else if(islower(word[i])){
      score+=POINTS[word[i]-'a'];
    }
   }
   return score;

}
