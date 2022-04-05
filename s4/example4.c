#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Este programa tiene suid como root

int main(int argc, char* argv[])
{
    FILE * f;
    //Comprueba si existe
    if (!access("/tmp/file.tmp", F_OK)) {
        printf external link("File exists!\n");
        return EXIT_FAILURE;
    }

    //Si no existe
    tmpFile = fopen(MY_TMP_FILE, "w");
 
    if (tmpFile == NULL) {
        return EXIT_FAILURE;
    }
 
    fputs("cuak\n", tmpFile);
 
    fclose(tmpFile);
 
    return EXIT_SUCCESS;
}
