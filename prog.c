#include <stdio.h>

// This test programm create a text file containing a success message 

int main(){
    FILE *fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "Process run successfully!");
    fclose(fp);
}