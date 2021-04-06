#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

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
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_cycle(int winnerId, int loserId);
void print_winner(void);

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
        // printf("VOTED RANK:\n");
        // for (int id = 0; id < candidate_count; id++)
        // {
        //     printf("%i", ranks[id]);
        // }
        // printf("\n");
        // printf("CHECK PREFERENCE:\n");
        // for (int id = 0; id < candidate_count; id++)
        // {
        //     for (int idx = 0; idx < candidate_count; idx++)
        //     {
        //         printf("%i", preferences[id][idx]);
        //     }
        //     printf("\n");
        // }
        // printf("============================================\n");

        printf("\n");
    }
    // candidate_count = 3;
    // pair_count = 3;

    // preferences[0][0] = 0;
    // preferences[0][1] = 6;
    // preferences[0][2] = 7;
    // preferences[1][0] = 3;
    // preferences[1][1] = 0;
    // preferences[1][2] = 4;
    // preferences[2][0] = 2;
    // preferences[2][1] = 5;
    // preferences[2][2] = 0;
    add_pairs();
    // printf("NUMBER OF PAIRS: %i\n", pair_count);
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("PAIR #%i - Winner: %i, Loser: %i, Margin: %i\n", i, pairs[i].winner, pairs[i].loser, pairs[i].margin);
    // }
    sort_pairs();
    // printf("PAIRS AFTER SORTED: %i\n", pair_count);
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("PAIR #%i - Winner: %i, Loser: %i, Margin: %i\n", i, pairs[i].winner, pairs[i].loser, pairs[i].margin);
    // }
    // for (int i = 0; i < 3; i++)
    //     printf("%i %i \n", pairs[i].winner, pairs[i].loser);
    lock_pairs();
    // printf("THIS IS LOCKED:\n");
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         printf("%i", locked[i][j]);
    //     }
    //     printf("\n");
    // }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int before = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int after = ranks[j];
            preferences[before][after] ++;
        }
    }
    return;
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
    for (int i = 0; i < pair_count; i++)
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

// Lock pairs into the candidate graph in order, without creating cycles
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
        if (check_cycle(winnerId, loserId) == false)
        {
            // printf("LOCKED: %i -> %i\n", winnerId, loserId);
            locked[winnerId][loserId] = true;
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
    if (winnerId == loserId)
    {
        return true;
    }
    for (int id = 0; id < candidate_count; id++)
    {
        if (locked[id][winnerId])
        {
            // printf("ALREADY LOCKED: %i -> %i\n", id, winnerId);
            return check_cycle(id, loserId);
        }
    }
    return false;
}
// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if locked[i][j] = 1?
            if (locked[j][i] == 1)
            {
                count ++;
            }
        }
        if (count == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

