#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //Variable declaration:
    int words = 1, sentences = 0, letters, i = 0, j, index;
    string s = get_string("Text: ");
    int n = strlen(s);

//To determine the number of words in the text input:
    while (i < n)
    {
        if (s[i] == 32)
        {
            words++;
        }
        i++;
    }

//To determine the number of sentences in the text input:

    for (j = 0; j < n; j++)
    {
        if (s[j] == 46 || s[j] == 63 || s[j] == 33)
        {
            sentences++;
        }
    }

//To determine the number of letters in the text:
    int apostrophe = 0, doublequotes = 0, k;
    for (k = 0; k < n; k++)
    {
        if (s[k] == 39)
        {
            apostrophe++;
        }
        if (s[k] == 34)
        {
            doublequotes++;
        }
    }
    letters = n - (words - 1) - sentences - apostrophe - doublequotes;

//Coleman-Liau index calculation:
    index = (0.0588 * (letters  * 100 / words)) - (0.296 * (sentences * 100 / words)) - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
//Printing the readability grade level:
        printf("Grade %i\n", index);
    }
}

