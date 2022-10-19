#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check whether there is a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    // Check whether the key contains 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        // Check whether the key contains only alphabetic characters
        if (isalpha(argv[1][i]) == false)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        
        // Convert lowercase letters to uppercase
        argv[1][i] = toupper(argv[1][i]);
    }
    
    // Check whether the key contains repeated characters
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    
    string s = get_string("plaintext: ");
    printf("ciphertext: ");
    
    // Use this to access the corresponding uppercase cipher character
    int j;
    
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Encipher and print lowercase characters
        if (islower(s[i]))
        {
            j = toupper(s[i]) - 65;
            printf("%c", tolower(argv[1][j]));
        }
        
        // Encipher and print uppcase characters
        else if (isupper(s[i]))
        {
            j = s[i] - 65;
            printf("%c", argv[1][j]);
        }
        
        // Ignore and print non-alphabetic characters
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}