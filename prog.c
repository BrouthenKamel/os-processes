#include <stdio.h>

// This test programm create a text file containing a success message 

int main(){
    FILE *fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "[LIVE] Process run successfully!\n");
    fclose(fp);

    printf("[LIVE OUTPUT] Process run successfully!\n");

    return 0;
}