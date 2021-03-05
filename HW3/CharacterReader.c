#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc , char *argv[]){
    int result = 0;                                         //must initialize to 0
    char buffer[10];                                        //create a file

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE* stream = fopen(argv[1], "r");                     //fopen to open the file

    while((read = getline(&line, &len, stream)) != -1) {    //reads in line by line and adds
        result += atoi(line);                               //the line converted to an int to result
    }
    int w_e = atoi(argv[2]);                                //write end is argv[2]
    sprintf(buffer, "%d", result);
    write(w_e, buffer, sizeof(buffer));
    fclose(stream);                                         //not necessary but good practice
    return result;
}   