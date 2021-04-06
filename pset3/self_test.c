#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

int pair_count;
int candidate_count;
// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int votes;
    int margin;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX];


// Function prototypes
// bool vote(int rank, string name, int ranks[]);
// void record_preferences(int ranks[]);
// void add_pairs(void);
// void sort_pairs(void);
void lock_pairs(void);
bool check_cycle(int winnerId, int loserId);
// void print_winner(void);
// string candidates[0] = "abc";
int main(void)
{
    candidate_count = 5;
    candidates[0] = "Alice";
    candidates[1] = "Bob";
    candidates[2] = "Charlie";
    candidates[3] = "David";
    candidates[4] = "Erin";
    pair_count = 5;
    pairs[0].winner = 2; pairs[0].loser = 0;
    pairs[1].winner = 4; pairs[1].loser = 1;
    pairs[2].winner = 1; pairs[2].loser = 3;
    pairs[3].winner = 3; pairs[3].loser = 4;
    pairs[4].winner = 4; pairs[4].loser = 2;

    lock_pairs();
    for (int i = 0; i < candidate_count; i++)
        for (int j = 0; j < candidate_count; j++)
            printf("%s ", locked[i][j] ? "true" : "false");
    // add_pairs();
    // printf("NUMBER OF PAIRS: %i\n", pair_count);
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("PAIR #%i - Winner: %i, Loser: %i, Votes: %i, Margin: %i\n", i, pairs[i].winner, pairs[i].loser, pairs[i].votes, pairs[i].margin);
    // }
    // sort_pairs();
    // for (int i = 0; i < 3; i++)
    //     printf("%i %i ", pairs[i].winner, pairs[i].loser);
}

void lock_pairs(void)
{
    // TODO

    for (int i = 0; i < pair_count; i++)
    {
        int winnerId = pairs[i].winner;
        int loserId = pairs[i].loser;
        // printf("================= START CHECK =======================\n");
        // printf("SOURCE: %i, DEST.: %i\n", winnerId, loserId);
        // for (int checkId = 0; checkId < peak_count; checkId++)
        // {
        //     printf("VISITED: %i\n", visited[checkId]);
        // }
        // for (int checkIdx = 0; checkIdx < peak_count; checkIdx++)
        // {
        //     printf("PEAK: %i\n", peak[checkIdx]);
        // }
        if (winnerId == 5 && loserId == 1)
            printf("================= HITSSSS =================\n");
        if (check_cycle(winnerId, loserId) == false)
        {
            printf("LOCKED: %i -> %i\n", winnerId, loserId);
            locked[winnerId][loserId] = true;
            // peak[i] = winnerId;
            // visited[i] = loserId;
            // peak_count ++;
        }
        // printf("AFTER LOCKED\n");
        //  printf("VISITED: ");
        // for (int checkId = 0; checkId < peak_count; checkId++)
        // {
        //     printf("%i, ", visited[checkId]);
        // }
        // printf("\nPEAK: ");
        // for (int checkIdx = 0; checkIdx < peak_count; checkIdx++)
        // {
        //     printf("%i, ", peak[checkIdx]);
        // }
        // printf("\n================= END CHECK =======================\n");
    }
    return;
}

bool check_cycle(int winnerId, int loserId)
{
    printf("CHECK CYCLE FOR: Winner - %i, Loser - %i\n", winnerId, loserId);
    if (winnerId == loserId)
    {
        return true;
    }
    for (int id = 0; id < candidate_count; id++)
    {
        // printf("TO BE CHECKED: %i -> %i\n", loserId, id);
        if (locked[id][winnerId])
        {
            printf("ALREADY LOCKED: %i -> %i\n", id, winnerId);
            return check_cycle(id, loserId);
        }
    }
    return false;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pairs[pair_count].votes = preferences[i][j];
                pairs[pair_count].margin = preferences[i][j] - preferences[j][i];
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pairs[pair_count].votes = preferences[j][i];
                pairs[pair_count].margin = preferences[j][i] - preferences[i][j];
                pair_count ++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair temp;
    for (int i = 0; i < pair_count - 1; i++)
    {
        int winnerId1 = pairs[i].winner;
        int loserId1 = pairs[i].loser;
        int margin1 = preferences[winnerId1][loserId1] - preferences[loserId1][winnerId1];
        for (int j = i + 1; j < pair_count; j++)
        {
            int winnerId2 = pairs[j].winner;
            int loserId2 = pairs[j].loser;
            int margin2 = preferences[winnerId2][loserId2] - preferences[loserId2][winnerId2];
            if (margin1 < margin2)
            {
                temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}
