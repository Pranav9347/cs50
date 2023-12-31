#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x, i, s, c, d;
    printf("Program which creates 2 adjacent pyramids of desired height and width:--\n");

//This is to accept input between 1 and 8 only:
    do
    {
        x = get_int("What should the height be?(Type a number between 1 & 8):");
    }
    while (x < 1 || x > 8);



//Outer for-loop to print each row:
    for (i = 1; i < x + 1; i++)
    {

        //Alignment:
        for (s = 1; s < x - i + 1; s++)
        {
            printf(" ");
        }


        //Inner for-loop to print each column:
        for (c = 1; c < i + 1; c++)
        {
            printf("#");
        }
        printf("  ");
        for (d = 1; d < i + 1; d++)
        {
            printf("#");
        }
        printf("\n");

    }
}

