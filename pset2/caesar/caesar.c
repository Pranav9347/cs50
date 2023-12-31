#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //____________________________________________________________________________________________________________________________
    //To check if the key is valid:
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string s = argv[1];
    int n = strlen(s);
    for (int i = 0; i < n; i += 0)
    {
        if (s[i] == 48 || s[i] == 49 || s[i] == 50 || s[i] == 51 || s[i] == 52 || s[i] == 53 || s[i] == 54 || s[i] == 55 || s[i] == 56
            || s[i] == 57)
        {
            i++;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int k = atoi(s);
//_____________________________________________________________________________________________________________________________________

//Obtaining plaintext from the user:
    string plaintext = get_string("plaintext:  ");


// Conversion of plaintext to ciphertext:
    int l = strlen(plaintext);
    char ciphertext[l];

    while (k > 25)
    {
        k = k - 26;
    }

    for (int j = 0; j < l; j++)
    {
        //In case of a lowercase letter:
        if (islower(plaintext[j]) != 0)
        {
            //Ensuring k value is restored everytime:
            k = atoi(s);
            while (k > 25)
            {
                k = k - 26;
            }
            k = k - 26;
            ciphertext[j] = plaintext[j] + k;

            while (ciphertext[j] < 97)
            {
                ciphertext[j] = ciphertext[j] + 26;
            }
        }
        //In case of an uppercase letter:
        else if (isupper(plaintext[j]) != 0)
        {
            int g = atoi(s);
            while (g > 25)
            {
                g = g - 26;
            }
            ciphertext[j] = plaintext[j] + g;

            while (ciphertext[j] > 90)
            {
                ciphertext[j] = ciphertext[j] - 26;
            }
        }
        else
        {
            ciphertext[j] = plaintext[j];
        }

    }
    //Printing the ciphertext:
    printf("ciphertext: ");
    for (int m = 0; m < l; m++)
    {
        printf("%c", ciphertext[m]);
    }

    printf("\n");

}






