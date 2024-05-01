// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles(等位基因)
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;
// generations 几代人
// INDENT_LENGTH 代码块的缩进长度
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
   // 这段代码用于种子随机数生成器。在C语言中，srand()函数用于设置随机数生成器的种子值，而time()函数通常用于获取当前时间，返回的是从某一固定时间点到现在所经过的秒数。
//    是的，srand(time(0)); 这行代码的作用是设置 rand() 函数的种子。在没有调用 srand() 函数的情况下，rand() 函数每次都会使用相同的默认种子，因此生成的随机数序列是固定的，与时间无关。这意味着在同一次运行中多次调用 rand() 会得到相同的随机数序列。
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate（分配） memory for new person
    person *new_person=malloc(sizeof(person));
    // If there are still generations left to create
    // 是否还有剩余的世代需要创建 就创建当前person的父母
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        new_person ->parents[0]=parent0;
        new_person ->parents[1]=parent1;
        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        new_person ->alleles[0]=parent0->alleles[rand()%2];
        new_person ->alleles[1]=parent1->alleles[rand()%2];
    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        new_person->parents[0]=NULL;
        new_person->parents[1]=NULL;
        // TODO: Randomly assign alleles
        new_person->alleles[0]=random_allele();
        new_person->alleles[1]=random_allele();
    }

    // TODO: Return newly created person
    return new_person;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case 基本情况 或者说递归终止条件
    if(p==NULL){
        return;
    }
    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);
    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generati on
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
