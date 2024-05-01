//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
//https://api.openai.com/v1/chat/completions
// Condorcet winner
// https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9
#include <cs50.h>
#include <stdio.h>
#include <string.h>
//https://oneapi.xty.app/v1/chat/completions
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
// 整数 preferences[i][j] 将表示更喜欢候选人 i 而不是候选人 j 的选民数量。
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
//Pairwise comparison（两两比较)
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

//1. tally
//2. sort
//3. lock
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for(int i = 0; i<candidate_count;i++){
        if(strcmp(candidates[i],name)==0){
            //ranks[i] is the voter's ith preference
            //如果我们的候选人alice bob charlie 他们的索引是[0，1，2]
            //如果用户投票给Rank1:Alice Rank2:Charile Rank3:Bob
            //那么Ranks数组在第一个选民之后将是[0,2,1] int rank是j 也就是该选民的第几次投票
            ranks[rank]=i;
            return true;
        }
    }
    //如果name中没有候选人
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // preferences[i][j]是偏好候选人i超过j候选人的选民数量
    // 遍历排名列表
//     candidates
// Alice Bob Charlie

// voter preferences, n candidate is represented by n row
// Alice  [0 3 2]
// Bob    [2 0 3]
// Charlie[1 4 0]
// there is one preference array for each candidate
    for (int i = 0; i < candidate_count; i++) {

        // 对于候选人 i 之后的每一个候选人 j
        for (int j = i + 1; j < candidate_count; j++) {
            // 更新偏好，增加候选人 i 相对于候选人 j 的偏好数量
            //preferences[preferred_candidate][ranks[j]] 的值增加1，
            preferences[ranks[i]][ranks[j]]++;

        }
    }
    return ;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    // TODO
    //我们需要与之前函数相同的嵌套循环，因为我们不想将候选者与其自身进行比较，并且要防止重复检查。
    for(int i=0;i<candidate_count;i++){


        for(int j=i+1 ;j<candidate_count;j++){
            // 检查候选人 i的 是否 比 候选人 j 更受选民喜欢
            if(preferences[i][j]>preferences[j][i]){
                pairs[ pair_count].winner=i;
                pairs[ pair_count].loser=j;
                pair_count++;

            }else if(preferences[i][j]<preferences[j][i]){
                pairs[ pair_count].winner=j;
                pairs[ pair_count].loser=i;
                pair_count++;


            }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
     // 使用冒泡排序对 pairs 数组进行排序
    for(int i=0;i<pair_count -1 ;i++){
        for(int j=0;j<pair_count-i-1;j++){
        // 如果 pairs[j] 的胜利强度小于 pairs[j+1] 的胜利强度，则交换它们
           if(preferences[pairs[j].winner][pairs[j].loser]<preferences[pairs[j+1].winner][pairs[j+1].loser]){
            //交换 t=a; a=b;b=t
            pair temp =pairs[j];
            pairs[j]=pairs[j+1];
            pairs[j+1]=temp;

           }
        }
    }
    return;
}

bool is_cycle(int end , int cycle_start){
    //if strart ==end ,has a path
    //对于两个相同的候选值 意味着候选者指向自己 从而创建了一个循环 比如说0人觉得alice比alice好
    // end 是输家  cycle_start是每一个被检查的配对中的赢家
    // 如果一个箭头从end指向另一位候选者 那么久可能出现循环 如果没有就不可能出现循环 函数返回false
    // Sorted Pairs = [(d, a), (a, b), (b, c), (c, a), (d, b), (d, c)]
    //如果第一次检查返回true 那么cycle再次被调用 这次使用当前候选者最为end参数 这个过程重复进行 直到返回false，意味着链结束并且没有循环
    // 首先考虑第一对(d, a)，我们选择赢家d，并检查a在任何已锁定的对中是否能获胜。由于没有对是锁定的（这是我们的第一对），a永远不会赢。因此，我们可以锁定(d, a)。形成的链条如下。d->a
    // 第二对(a,b) ........
    //(c,a)的时候 发现存在a->b a战胜b的锁定对  进入递归 目的是为了检查b->c  然后 i=c return true  所以c->a 无法被锁定  c->a->b->c
    //(d,b)的时候  d->b->c   c->a没有被锁定
    //(d,c)的时候  d->c
    if(end==cycle_start){
        return true;
    }
    for(int i =0 ;i<candidate_count;i++){
       // 每次我们创建链表之前 我们必须再次检查所有的配对
            if(locked[end][i]){
                         if(is_cycle(i, cycle_start))
            {
                return true;
            }
            }
    }
    //如果没有找到路径 则返回false
    return false;

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for(int i=0;i<pair_count;i++){
        int winner =pairs[i].winner;
        int loser=pairs[i].loser;
        // If the addition of (A,B) forms a ring,it proves that there was a path from B to A before the addition.
        // The problem is transformed into: check if a path exists from B to A
         //如果这个环路不存在
        if(!is_cycle(loser,winner)){
            locked[winner][loser]=true;
        }
    }
    return;
}

// Print the winner of the election
// 赢家是没有被locked 为true的候选人
void print_winner(void)
{
    // TODO
//    获胜者是列中没有真值的候选人。在图形术语中，这意味着没有箭头指向他们。
//为了确定这一点，我们可以遍历每个候选人，声明一个整数来计算锁定中该候选人的列中的假值数量。然后，我们遍历每个候选人的列，如果找到假值，则递增false_count。如果false_count等于candidate_count，则整个列都是假的，并且可以宣布该候选人为图的源，并打印他们的名字。
    // Winner is the candidate with no arrows pointing to them
    for(int i=0;i<candidate_count;i++){
        int false_count=0;
      for(int j =0 ;j<candidate_count; j++){
        if(locked[j][i]==false){
            false_count++;
        }
     }
        //意味着在该候选人的列中没有任何箭头指向他们，也就是说该候选人在锁定图中没有任何假值，因此他们是图的源，也就是获胜者
            if(false_count==candidate_count){
                printf("%s\n",candidates[i]);
            }
    }               

    return;
}
