#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Prevent malicious users
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");
    if (!raw)
    {
        printf("Cannot open the forensic image for reading!\n");
        return 1;
    }
    
    int check_end = 1, img_count = 0;
    char filename[8];
    FILE *img = NULL;
    while (check_end != 0)
    {
        BYTE buffer[512];
        check_end = fread(buffer, 512, 1, raw);
        
        // Check if there is no more bytes
        if (check_end == 0)
        {
            fclose(img);
            break;
        }
        
        // Check the first four bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not first JPEG, close the previous one before opening and writing the new one
            if (img_count != 0)
            {
                fclose(img);
            }
            
            // Open and write
            img_count++;
            sprintf(filename, "%03i.jpg", img_count - 1);
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
        }
        else if (img_count > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    
    fclose(raw);
    
    return 0;
}
