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
void print_winner(void);
bool have_cycle(int pair_index);
int search_cycle(int original, int current, int cycle);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    for (int i = 0; i < pair_count; i++)
    {
        int highest = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[highest].winner][pairs[highest].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                highest = j;
            }
        }
        temp = pairs[i];
        pairs[i] = pairs[highest];
        pairs[highest] = temp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /*
    pairs[0].winner = 0;
    pairs[0].loser = 1;

    pairs[1].winner = 1;
    pairs[1].loser = 2;

    pairs[2].winner = 2;
    pairs[2].loser = 0;
    */

    for (int i = 0; i < pair_count; i++)
    {
        if (have_cycle(i) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int false_count;
    for (int i = 0; i < candidate_count; i++)
    {
        false_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
            }
        }

        if (false_count == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool have_cycle(int pair_index)
{
    int original = pair_index;
    int current = pair_index;
    int cycle = 0;

    if (search_cycle(original, current, cycle) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int search_cycle(int original, int current, int cycle)
{
    int new_current;
    for (int i = 0; i < pair_count; i++)
    {
        if (pairs[current].loser == pairs[i].winner && locked[pairs[i].winner][pairs[i].loser] == true)
        {
            if (pairs[i].loser == pairs[original].winner)
            {
                cycle = 1;
                break;
            }
            else
            {
                new_current = i;
                if (search_cycle(original, new_current, cycle) == 1)
                {
                    cycle = 1;
                    break;
                }
                else
                {
                    // Keep looping
                }
            }
        }
        else
        {
            // Keep looping
        }
    }
    return cycle;
}