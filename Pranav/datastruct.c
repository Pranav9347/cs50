#include <stdio.h>
#include <cs50.h>

int main (void)
{

typedef struct
{
    char x;
    int y;
}
intattribute;

intattribute z;
z.x = 'a';
z.y = 2;

printf("%i\n%c\n",z.y,z.x);
}