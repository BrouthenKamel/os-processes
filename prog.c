#include <stdio.h>

// This test programm create a text file containing a success message 

int main(){
    FILE *fp;

    fp = fopen("output.txt", "w");
    fprintf(fp, "[LIVE] Process ran successfully!\n");
    fclose(fp);

    printf("[LIVE OUTPUT] Process ran successfully!\n");

    return 0;
}