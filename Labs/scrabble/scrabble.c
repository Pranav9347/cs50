#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
// Compute and return score for string

    int l = strlen(word), worth[l], total = 0;

    for (int i = 0; i < l; i++)
    {
// If the character is not a letter, its point is 0:
        if (isupper(word[i]) == 0 && islower(word[i]) == 0)
        {
            worth[i] = 0;
        }
// Converting uppercase letters to corresponding lowercase letters:
        if (isupper(word[i]) != 0)
        {
            word[i] = tolower(word[i]);
        }
// Assigning points to each letter:
        for (int k = 97, x = 0; k < 123 && x < 26; k++, x++)
        {
            if (word[i] == k)
            {
                worth[i] = POINTS[x];
            }
        }

    }
// Adding the total points of each character:
    for (int i = 0; i < l; i++)
    {
        total = total + worth[i];
    }
    return total;


}
