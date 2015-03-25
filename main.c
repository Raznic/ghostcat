#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int catfile(FILE *fin, FILE *fout);

int main(int argc, char *argv[])
{
     FILE *fin = NULL, *fout = NULL;
     const char *dev_null_path = "/dev/null";

     // Open input file
     if(argc < 2)
          fin = stdin;
     else
     {
          if ((fin = fopen(argv[1], "r")) == NULL)
               perror("Failed to open input file\n");
     }

     // Open output file
     if((fout = fopen(dev_null_path, "w")) == NULL)
        perror("Failed to open /dev/null for writing\n");

     return catfile(fin, fout);
}

int catfile(FILE *fin, FILE *fout)
{
    int read = 0;
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, BUFFER_SIZE);  
    while((read = fread(buffer, sizeof(char), BUFFER_SIZE, fin)) != 0)
    {
        if(fwrite(buffer, sizeof(char), BUFFER_SIZE, fout) < read) 
        {
            if(ferror(fout))
                printf("Error writing to /dev/null");
        }
        memset(buffer, 0, BUFFER_SIZE);  
    }

    // Check to see if we ended because of error
    if(ferror(fin))
    {
        printf("Error reading from file");
        return -1;
    }

    return 0;
}
