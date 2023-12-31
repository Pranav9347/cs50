#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x, i, k, s;
    printf("Program which creates a pyramid of desired height and width:--\n");

//This is to accept input between 1 and 8 only:
    do
    {
        x = get_int("What should its height be?(Type a number between 1 & 8):");
    }
    while (x < 1 || x > 8);



//Outer for loop to print each row:
    for (i = 1; i < x + 1; i += 1)
    {
//Right alignment of the pyramid:
        for (s = 1; s < x-i + 1; s++)
        {
            printf(" ");
        }
        //Inner for loop to print each column:
        for (k = 1; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }

}

