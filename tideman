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

int main(int argc, string argv[])
{
    //Check for invalid usage
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

    //Check if the name that the user enters for a rank is valid. If it is, then update the ranks array to include the candidate according to what the user prefers.
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
    // TODO

    //Go through the votes and tally how many times candidate[i] is preferred over candidate[j]
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

    //Initialize a pair that will be used to record each iteration below which will be added to the pairs array.
    pair p;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                p.winner = i;
                p.loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                p.winner = j;
                p.loser = i;
            }

            //A pair is created only if there isn't a tie.
            if (!(preferences[i][j] == preferences[j][i]))
            {
                pairs[pair_count] = p;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Placeholders are initialized to allow a swap.
    pair placeholder_pair;
    int placeholder = 0;

    int victory_strength[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        victory_strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            //Run a selection sort.
            if (victory_strength[i] < victory_strength[j])
            {
                placeholder = victory_strength[j];
                victory_strength[j] = victory_strength[i];
                victory_strength[i] = placeholder;

                placeholder_pair = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = placeholder_pair;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    //initialize an int to use as a comparison for any potential cycles. A loser cannot equal a previous winner, otherwise there will be a cycle. The exception is usually the first two pairs (because there are not enough pairs to create a cycle.)
    int backtrace = 0;

    //int skip will be used to keep track of any pairs that cause a cycle. Once detected, will allow us to skip over the pair if it's a middle pair.
    //if the middle pair is not skipped over, then a cycle is created when backtracing and the second loop will never end.
    int skip = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        //Lock congruent pairs to false because the same candidate cannot be preferred over themselves.
        locked[i][i] = false;
        backtrace = pairs[i].winner;

        //Lock in pairs.
        locked[pairs[i].winner][pairs[i].loser] = true;
        locked[pairs[i].loser][pairs[i].winner] = false;

        for (int j = 0; j < i + 1; j++)
        {
            if (j == skip)
            {
                j++;
            }

            //Backtrack through the pairs.
            if (backtrace == pairs[j].loser)
            {
                backtrace = pairs[j].winner;
                j = 0;
            }

            //If the connecting candidate(AKA the loser) has previously appeared as a winner, then there is a cycle.
            if (backtrace == pairs[i].loser)
            {
                locked[pairs[i].winner][pairs[i].loser] = false;
                skip = i;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int loss_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                loss_count++;
            }
        }

        if (loss_count == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

