//即时决选系统 "Instant runoff system”
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates 选民和候选人的最大数量
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// 同一个选民  投了多少候选人
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status（是否被淘汰的状态）
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Array to keep track of whether a voter has voted for any candidate
bool voted[MAX_VOTERS][MAX_CANDIDATES] = {false};

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
    //提示用户输入选民的数量
    voter_count = get_int("Number of voters: ");

    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            // 提示用户投票
            string name = get_string("Rank %i: ", j + 1);



            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }


        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();

        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();

        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }

    return 0;
}

// Record preference if vote is valid  并且设置preferences
bool vote(int voter, int rank, string name)
{
    // TODO

    // Iterate over each candidate
    for(int i=0 ;i<candidate_count;i++){


        //Check if candidate's name macthes given name
        if(strcmp(candidates[i].name,name)==0){
              // Check if the voter has already voted for this candidate
            if(voted[voter][i]){
                printf("Voter %d has already voted for candidate %s.\n", voter , name);
                return false;
            }
            // preferences[0][0]=2 表示第一个选民的第一次投票（最喜欢的点候选人 是 2 坐标 也就是candidates的索引）可以用来判断投给谁了
            preferences[voter][rank]=i;
             // Mark the voter as voted for this candidate
            voted[voter][i] = true;
            return true;
        }
    }
    //If no match,return false
    return false;
}

// Tabulate（制表 表格化） votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    //Iterate over votes
    for(int i=0;i<voter_count;i++){
        //Iterate over ranks of votes[i]
        for(int j=0;j<candidate_count;j++){
            // 当前选民的第j次投票 投给哪个候选者
            int candidate_index=preferences[i][j];
            // 如果当前这个候选者已经被淘汰了 false表示没有被淘汰
            //！candidates[candidate_index].eliminated 为真的话 就表示没有被淘汰
            // Check candidate is eliminated
            if(!candidates[candidate_index].eliminated){
                //计算的是选民的第一偏好
                candidates[candidate_index].votes++;
                //如果被淘汰就就继续[0][1] [0][2]...
                break;
            }

        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int half =voter_count/2;
    for(int i=0;i<candidate_count;i++){
        if(candidates[i].votes>half){
            printf("%s is the winner of this election\n",candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min_votes=INT_MAX;
    for(int i =0;i<candidate_count;i++){
        if(!candidates[i].eliminated  && candidates[i].votes<min_votes){
            min_votes=candidates[i].votes;
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    //if evey uneliminated candidate has min votes ,it's tie
    for(int i=0;i<candidate_count;i++){
      if(!candidates[i].eliminated && candidates[i].votes>min){
        return false;
      }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for(int i=0;i<candidate_count;i++){
        if(candidates[i].votes==min){
            candidates[i].eliminated =true;
        }
    }
    return;
}
