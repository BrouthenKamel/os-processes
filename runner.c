// Modules
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FILE_NAME_SIZE 64


int main(int argc, char *argv[]){
    // Processes states and errors variables
    int p, p1, p2, p3, err, status;

    // Commands variables
    char file_name[FILE_NAME_SIZE] = "" ;
    char program_name[FILE_NAME_SIZE] = "" ;
    char object_module_name[FILE_NAME_SIZE] = "" ;
    char execution_name[FILE_NAME_SIZE] = "./" ;

    // file_name
    strcpy(file_name, argv[1]);

    // program_name: file_name.c
    strcpy(program_name, file_name);
    strcat(program_name, ".c");

    // object_module_name: file_name.o
    strcpy(object_module_name, argv[1]);
    strcat(object_module_name, ".o");

    // execution_name: ./file_name
    strcat(execution_name, argv[1]);

    printf("Input file: %s \n", argv[1]);

    /** Creating processes **/

    // 1st Child Creation 
    p = fork();

    //1st Child Operation --> Making the payload ready to create prog.o
    if (p == 0){
        printf("Process runs: gcc -c %s -o %s \n", program_name, object_module_name);
        err = execlp("gcc", "gcc", "-c", program_name, "-o", object_module_name, NULL);
        printf("Execution Error with code: %d \n", err);
        exit(err);
    }

    // Waiting for the completation of the 1st process without errors
    p1 = wait(NULL);

    // 2nd Child Creation 
    p = fork();

    //2nd Child Operation --> Making the payload ready to compile prog.o into an executable
    if (p == 0){
        printf("Process runs: gcc %s -o %s \n", object_module_name, file_name);
        err = execlp("gcc", "gcc", object_module_name, "-o", file_name, NULL);
        printf("Execution Error with code: %d \n", err);
        exit(err);
    }
// Waiting for the completation of the 1st process without errors
    p2 = wait(NULL);

    // 3rd Child Creation 
    p = fork();

    // 3rd Child Operation --> setting the 3rd Process to execute the compiled program
    //The Excepted result is : a text file with a success message
    // This proof of concept is useful because it show a concreat proof of the successed operation
    if (p == 0){
        printf("Process runs: ./%s \n", file_name);
        err = execlp(execution_name, file_name, NULL);
        printf("Execution Error with code: %d \n", err);
        exit(err);
    }

    //Getting the status to use in the in step 4 (macro analysis)
    p3 = wait(&status);

    // WIFEXITED : the macro verifying the normal termination of the process
    // The conditional bloc is added to check whether it is terminated with success or failure
    if(WIFEXITED(status)){
        if(WEXITSTATUS(status) == 0)
            printf("Process exited with no errors! \n");
        else
            printf("Process exited with status: %d \n", WEXITSTATUS(status));
    }

    // WIFESIGNLED : the macro checking the overflow (debordement) flag
    if(WIFSIGNALED(status)){
        printf("Process exited with signal number: %d \n", WTERMSIG(status));
    }

    // TO NOT DELETE : KEEPS THE PARENT PROCESS ON HOLD UNTIL THE TERMINATION OF ITS SONS
    while(wait(NULL) != -1);
}