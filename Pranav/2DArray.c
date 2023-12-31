#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(void)
{
    // UNDERSTANDING 2-D Arrays:
    // Declaring a 2-D array:
        int array[2][3];
for(int i=0; i<2; i++)
{
    for(int j=0; j<3; j++)
    {
        array[i][j]=get_int("Element position[%i][%i]:",i,j);
    }
}


// Printing the 2-D array:
printf("Your matrix:\n");
for(int i=0; i<2; i++)
{
    for(int j=0; j<3; j++)
    {
        printf("%i  ",array[i][j]);
    }
    printf("\n");
}

// Pointers in 2-D Arrays:
int *q=&array[0][0];
printf("%p\n",q);
int *r=&array[1][0];
printf("%p\n",r);
int *s=&array[0][2];
printf("%p\n",s);

printf("%i\n",*q);
printf("%i\n",*r);

}
