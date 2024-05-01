#include<cs50.h>
#include<ctype.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
// index = 0.0588 * L - 0.296 * S - 15.8
// 其中L是文本中每 100 个单词的平均字母数，S是文本中每 100 个单词的平均句子数。
//L =字母数/单词数*100  S=句子数/单词数*100
int main(void){
  //prompt the user for some text
  string text = get_string("Text: ");
   //Count the number if letters 字母, words单词, and sentences句子 in the text
   float letters=count_letters(text);
   float words=count_words(text);
   float sentences=count_sentences(text);
   //Compute the Coleman-Liau index
 float L = (letters/words)*100;
 float S=(sentences/words)*100;

   int index =round(0.0588*L-0.296*S-15.8);

//  printf("%i\n",index);
 if(index<1){
  printf("Before Grade 1\n");
 }else if(index>16){
  printf("Grade 16+\n");
 }else{
  printf("Grade %i\n",index);
 }

}

int count_letters(string text){
  //Return the number of letters in text;
  // Consider letters to be uppercase or lowercase alphabetical character, not punctuation, digits, or other symbols 字母应该是大小写字母而不是标点符号数字或者其他
// isalpha 
    int count =0;
    for(int i=0,n=strlen(text);i<n;i++){
      if(isalpha(text[i])){
        count++;
      }

    }
    return count;
   }
int count_words(string text){
  //Retrun the number of words in text
  //我们将把任何由空格分隔的字符序列视为一个单词
  int count=1;
  for(int i=0,n=strlen(text);i<n;i++){
    if(isspace(text[i])){
       count++;
    }
  }
    return count;
}

int count_sentences(string text){
 // Retrun the number of sentences in text
 //  "? ! ."
   int count=0;
  for(int i=0,n=strlen(text);i<n;i++){
    if(text[i]=='.' ||text[i]=='?'||text[i]=='!'){
       count++;
    }
  }

  return count;
}
