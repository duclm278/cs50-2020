#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Promp user for text
    string s = get_string("Text: ");
    int letters = 0, words = 1, sentences = 0;
    
    // Analyze text
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            letters++;
        }
        else if (s[i] == ' ')
        {
            words++;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    
    // Prevent malicious users
    if (letters == 0)
    {
        words = 0;
        sentences = 0;
    }
    
    // Caculate index
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    // Print the result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}