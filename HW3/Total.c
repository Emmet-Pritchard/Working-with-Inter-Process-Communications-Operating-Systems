#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

//function that returns the sum of the numbers
//very simple for loop
int total(int input){
    int sum = 0;
    for(int i = 0; i <= input; i++){
        sum += i;
    }
    return sum;
}

int main(int argc, char *argv[]){
    int arg1 = atoi(argv[2]);   
    int sum = total(arg1);
    printf("Total[%u] : Sum = %u\n", getpid(), sum);

    int SIZE = 32;
    int shm_fd = shm_open(argv[1], O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    void *shmPtr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sprintf(shmPtr, "%d", sum);

    return sum;
}