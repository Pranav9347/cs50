#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

//__________________________________________________
int get_cents(void)
{
    int x;
    do{
    x =get_int("Change owed: ");
    }
    while(x<0);
    return x;
}
//___________________________________________________

int calculate_quarters(int cents)
{
    int z,y;
if (cents>24)
{
for (z=cents,y=0; z>24; y++)
{
z=z-25;
}
return y;
}
    else return 0;
}
//___________________________________________________

int calculate_dimes(int cents)
{
    int a,b;
    if (cents>9)
    {
        for(a=cents,b=0; a>9; b+=1)
       {
          a=a-10;
       }
       return b;
    }
  else return 0;
}
//____________________________________________________

int calculate_nickels(int cents)
{
    int c,d;
    if (cents>4)
    {
        for(c=cents,d=0; c>4; d++)
        {
          c=c-5;
        }
        return d;
    }
    else return 0;
}
//_____________________________________________________
int calculate_pennies(int cents)
{
    return cents;
}
//_____________________________________________________ 