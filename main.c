#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void printhelp(); int catfile(FILE *fin, FILE *fout); void boo();

int main(int argc, char *argv[])
{
    int opt = 0, num_opts;
    FILE *fin = NULL, *fout = NULL;
    const char *dev_null_path = "/dev/null";
    const char *options = "hbm:";

    // Handle options
    while((opt = getopt(argc, argv, options)) != -1) 
    {
        num_opts++;
        switch(opt)
        {
            case 'h':
                printhelp();
                exit(EXIT_SUCCESS);
            case 'b':
                boo();
                exit(EXIT_SUCCESS);
            case 'm':
                break;
            default:
                fprintf(stderr, "Usage: %s [-b]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Open input file
    if(argc - num_opts < 2)
         fin = stdin;
    else
    {
         if ((fin = fopen(argv[argc-1], "r")) == NULL)
              perror("Failed to open input file\n");
    }

    // Open output file
    if((fout = fopen(dev_null_path, "w")) == NULL)
        perror("Failed to open /dev/null for writing\n");


    return catfile(fin, fout);
}

void printhelp()
{
    printf("Usage: ghostcat [OPTION]... [FILE]...\n");
    printf("Concatenate FILE, or standard input, to /dev/null\n");
    printf("\n");
    printf("  -h    Seriously? How else did you get this printout?\n");
    printf("  -b    Boo! The Ghost Cat appears\n");
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

void boo()
{
    printf("           ____________________ \n");
    printf("          /  __    ___    ___  \\            \n");
    printf("         |  |  \\  /   \\  /   \\  |            \n");
    printf("         |  |__/  |   |  |   |  |       \n");
    printf("         |  |  \\  |   |  |   |  |          \n");
    printf("         |  |__/  \\___/  \\___/  |               \n");
    printf("          \\_______       ______/               \n");
    printf("                  \\    /              \n");
    printf("                   \\  /               \n");
    printf("                    \\/                \n");
    printf("                                        \n");
    printf("                 |\\   |\\              \n");
    printf("                 | \\__| \\             \n");
    printf("                /  x  x  \\             \n");
    printf("                \\  >Y<    \\           \n");
    printf("                 \\__^      \\          \n");
    printf("                ___/   ___  \\          \n");
    printf("               ((( \\  ((( \\  \\       \n");
    printf("                  \\_\\    \\_\\  \\    \n");
    printf("                     \\         \\      \n");
    printf("                      ~~~~~    /        \n");
    printf("                          /   /         \n");
    printf("                          \\  /         \n");
    printf("                          / /           \n");
    printf("                          \\/           \n");
}
