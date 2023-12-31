#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    int voter;
    int rank;
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

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        voter = i;
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            rank = j;
            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
            //printf("Index of candidate: %i; Voter: %i; Rank: %i\n",preferences[voter][rank], voter, rank);
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

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int j = 0; j < voter_count; j++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (preferences[j][0] == k)
            {
                candidates[k].votes++;
            }
        }
    }
    //printf("Hey_votes:%i\n Irl_votes:%i\n Joe_votes%i\n", candidates[0].votes,candidates[1].votes,candidates[2].votes);
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2.0)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int x = candidates[0].votes;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (x < candidates[i + 1].votes)
        {
            x = x + 0;
        }
        else
        {
            x = candidates[i + 1].votes;
        }
    }
    return x;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int x = candidates[0].votes;
    int k = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == x)
        {
            k++;
        }
    }
    if (k == candidate_count)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidate_count = candidate_count - 1;
            int h = i;
            for (int k = 1; k < candidate_count - i; k++)
            {
                candidates[h].name = candidates[i + k].name;
                candidates[h].votes = candidates[i + k].votes;
                h = i + k;
            }

            for (int m = 0; m < voter_count; m++)
            {
                if (preferences[m][0] == i)
                {
                    preferences[m][0] = preferences[m][1];
                }
            }
            candidates[i].eliminated = true;
        }

    }

    return;
}