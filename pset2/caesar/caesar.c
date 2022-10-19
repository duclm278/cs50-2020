#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Prevent malicious users
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    int key = atoi(argv[1]);
    
    // Prompt user for plaintext
    string s = get_string("plaintext: ");
    
    // Encipher plaintext
    printf("ciphertext: ");
    int alpha_i;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isupper(s[i]))
        {
            // Covert ASCII to alphabetical index
            alpha_i = s[i] - 65;
            
            // Shift alphabetical index using fomula
            alpha_i = (alpha_i + key) % 26;
            
            // Conver result back to ASCII
            s[i] = (char)(alpha_i + 65);
        }
        else if (islower(s[i]))
        {
            // Covert ASCII to alphabetical index
            alpha_i = s[i] - 97;
            
            // Shift alphabetical index using fomula
            alpha_i = (alpha_i + key) % 26;
            
            // Conver result back to ASCII
            s[i] = (char)(alpha_i + 97);
        }
        printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}