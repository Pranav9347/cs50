#include<stdio.h>
#include<string.h>
#include<cs50.h>
int main (void)
{
   string s=get_string("Enter the string:");
   int n=strlen(s);
    int k=0, l=0;
// If the number of letters in the word is even:
   if (n%2==0)
   {
    for(int i=0; i<(n/2); i++)
    {
        if (s[i]==s[n-1-i])
          {
            k++;
          }
    }
   }
// If the number of letters in the word is odd:
   else if (n%2!=0)
   {
    for(int j=0; j<((n-1)/2); j++)
    {
        if (s[j]==s[n-1-j])
        {
            l++;
        }
    }
   }
   if ((k==n/2)||(l==(n-1)/2))
   {
    printf("Yes, it's a palindrome!\n");
   }
   else
   {
    printf("No, its not a palindrome!\n");
   }

}