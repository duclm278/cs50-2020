#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");
    int i = 0, sum = 0, digit_1st = 0, digit_2nd = 0;
    while (number > 0)
    {
        if (i % 2 == 1)
        {
            int product = (number % 10) * 2;
            if (product > 9)
            {
                // Add the digit in the ones place
                sum += (product % 10);
                // Add the digit in the tens place
                sum += (product - product % 10) / 10;
            }
            else
            {
                sum += product;
            }
            
        }
        else
        {
            sum += number % 10;  
        }
        digit_2nd = digit_1st;
        digit_1st = number % 10;
        number = (number - number % 10) / 10;
        i++;
    }
    
    /*
    printf("Sum: %i\n", sum);
    printf("Length: %i\n", i);
    printf("Digit 1st: %i\n", digit_1st);
    printf("Digit 2nd: %i\n", digit_2nd);
    */
    
    if (sum % 10 == 0)
    {
        // American Express
        if (i == 15 & digit_1st == 3)
        {
            switch (digit_2nd)
            {
                case 4:
                case 7:
                    printf("AMEX\n");
                    break;
                default:
                    printf("INVALID\n");
            }
        }
        
        // MasterCard
        else if (i == 16 & digit_1st == 5)
        {
            if (digit_2nd > 0 && digit_2nd < 6)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        
        // Visa
        else if ((i == 13 || i == 16) && digit_1st == 4)
        {
            printf("VISA\n");
        }
        
        // Others
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    
}