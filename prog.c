#include <stdio.h>

int main(){
    FILE *fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "Process run successfully!");
    fclose(fp);
}