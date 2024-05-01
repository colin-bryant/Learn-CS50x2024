#include <cs50.h>
#include <stdio.h>
#include <string.h>
// 多数选举 plurality election
// Max number of candidates（候选人）
#define MAX 9

// Candidates have name and vote count（选票）
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates  定义为一个数组
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    //至少要有一个候选人 argc>2
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    //初始化
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    //Iterate over each candidates
    for(int i=0;i<candidate_count;i++){
        if(strcmp(candidates[i].name,name)==0){
            candidates[i].votes++;
          return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    //Find the maximum number of votes
    int max=candidates[0].votes;
    for(int i=1;i<candidate_count;i++){
        if(candidates[i].votes>max){
            max=candidates[i].votes;
        }
    }
   for(int i=0;i<candidate_count;i++){
         if(candidates[i].votes==max){
            printf("%s\n",candidates[i].name);
         }
    }



    return;
}
