#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head_struct.h"
#include "model.h"

const char *getfield(char *line, int num)
{
    const char *tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int main()
{
    FILE *fp;

    fp = fopen("file.txt", "w+");
    fputs("This is tutorialspoint.com ae tot bar phit lal", fp);

    fseek(fp, 7, SEEK_SET);
    fputs(" C Programming Language", fp);
    fclose(fp);
    return 0;
}