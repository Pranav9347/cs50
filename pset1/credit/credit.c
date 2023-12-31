#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cc;
    bool b = true;
    int d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, sum1, sum2;
    printf("Proram to verify and determine the validity credit cards:--\n");

    cc = get_long("Enter your credit card number:");
// To get each digit of the obtained cc number:
    d1 = cc % 10;
    d2 = (cc % 100) / 10;
    d3 = (cc % 1000) / 100;
    d4 = (cc % 10000) / 1000;
    d5 = (cc % 100000) / 10000;
    d6 = (cc % 1000000) / 100000;
    d7 = (cc % 10000000) / 1000000;
    d8 = (cc % 100000000) / 10000000;
    d9 = (cc % 1000000000) / 100000000;
    d10 = (cc % 10000000000) / 1000000000;
    d11 = (cc % 100000000000) / 10000000000;
    d12 = (cc % 1000000000000) / 100000000000;
    d13 = (cc % 10000000000000) / 1000000000000;
    d14 = (cc % 100000000000000) / 10000000000000;
    d15 = (cc % 1000000000000000) / 100000000000000;
    d16 = (cc % 10000000000000000) / 1000000000000000;

    // Check if Luhn's algorithm is satisfied:
    sum1 = ((d2 * 2) % 10 + (d2 * 2) / 10) + ((d4 * 2) % 10 + (d4 * 2) / 10) + ((d6 * 2) % 10 + (d6 * 2) / 10) + ((d8 * 2) % 10 +
            (d8 * 2) / 10) + ((d10 * 2) % 10 + (d10 * 2) / 10) + ((d12 * 2) % 10 + (d12 * 2) / 10) + ((d14 * 2) % 10 + (d14 * 2) / 10) + ((
                        d16 * 2) % 10 + (d16 * 2) / 10);
    sum2 = d1 + d3 + d5 + d7 + d9 + d11 + d13 + d15;
//If Luhn's algorithm is not satisfied, then the cc number is invalid:
    if ((sum1 + sum2) % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {

        // Identify the credit card:
        while (b == true)
        {
            //Condition for it to be a VISA card:
            if (d16 == 4 || d13 == 4)
            {
                printf("VISA\n");
                b = false;
                break;
            }
//Condition for it to be a AMEX card:
            if ((d15 == 3 && (d14 == 4 || d14 == 7)) && d16 == 0)
            {
                printf("AMEX\n");
                b = false;
                break;
            }
//Condition for it to be a MASTERCARD:
            if (((d15 == 1 || d15 == 2 || d15 == 3 || d15 == 4 || d15 == 5) && d16 == 5))
            {
                printf("MASTERCARD\n");
                b = false;
                break;
            }
            else
            {
                //What if a given cc number satisfies Luhn's algorithm but actually is invalid?
                printf("INVALID\n");
                b = false;
            }
        }
    }
}