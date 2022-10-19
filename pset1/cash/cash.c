#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    
    int cents = round(dollars * 100);
    
    int coins = 0;
    while (cents > 0)
    {
        if (cents >= 25)
        {
            coins += (cents - cents % 25) / 25;
            cents = cents % 25;
        }
        else if (cents >= 10 && cents < 25)
        {
            coins += (cents - cents % 10) / 10;
            cents = cents % 10;
        }
        else if (cents >= 5 && cents < 10)
        {
            coins += (cents - cents % 5) / 5;
            cents = cents % 5;
        }
        else
        {
            coins += cents;
            cents = 0;
        }
    }
    printf("%i\n", coins);
}