#include <stdio.h>
#include <cs50.h>
int main(void)
{
    string x = get_string("Please enter your name:");
//'get_string()' is a function which accepts input from the user. The input is then stored in the variable x declared as a string variable.
    printf("Hello,%s\n", x);
//'%s' is a format code which acts as a replacement for a string variable.
// a comma(,) is used to separate multiple inputs for the function printf().

}