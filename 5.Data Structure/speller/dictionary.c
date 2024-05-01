// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// 这是表中存储单独链表的数量
//例如，如果你的哈希函数只使用每个单词的第一个字母，你会将 N 设为 26，因为每个单词有 26 种不同的可能性
const unsigned int N = 1000000;

// Hash table
node *table[N];
//size of the dictionary
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //第一步是获取正在检查的单词的哈希值，并访问哈希表中相应索引处的链表。然后可以使用 strcasecomp()函数遍历链表并检查单词是否存在。如果存在，则返回 true，否则检查下一个节点，直到达到链表的末尾，然后返回 false。
    //Hash word to obtain hash value
    int hash_value=hash(word);
    //Access linked list at that index in hash table
    node *n =table[hash_value];
    //Traverse linked list,looking for word(strcasecomp)
    while(n!=NULL){
        if(strcasecmp(word,n->word)==0){
            return true;
        }
        n=n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    //这里我们定义了我们的哈希函数。对于此函数有无限的可能性，建议您在线上进行研究并找到您自己的方式。我选择了一个相当简单的方法，即将单词中每个字符的 ASCII 值相加。
    // 记得对哈希表中的桶数对哈希表输出的值进行模除，以获得在哈希表范围内的整数值。
    long sum =0;
    for(int i=0;i<strlen(word);i++){
        sum+=tolower(word[i]);
    }
    return sum % N;

}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //Open the dictionary file
    FILE *source=fopen(dictionary,"r");
    if(source==NULL){
        printf("Could not open %s\n",dictionary);
        return false;
    }
    //Initialise word array
    char next_word[LENGTH+1];
    //read each word in the file
    // bucket
    while(fscanf(source,"%s",next_word)!=EOF){
        //Create new node for each word
        node *n=malloc(sizeof(node));
        if(n==NULL){
            return false;
        }
        //copy word into node using strcopy  next_word 复制到n->word 指向的内存地址
        strcpy(n->word,next_word);
        // Hash word to obtain hash value
        int hash_value=hash(next_word);
        //Insert node into hash table at the location
        //当向链表添加节点时，我们首先将要插入的节点的指针设置为当前链表的头部，然后将节点设置为链表的新头部。
        n->next=table[hash_value];
        table[hash_value]=n;
        dict_size++;
    }

    //Close the dictional file
    fclose(source);
    return true;
}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
   for(int i=0;i<N;i++){
    node *cur =table[i];
    while(cur!=NULL){
        node *tmp=cur->next;
        free(cur);
        cur=tmp;
    }
   }
   return true;

}
