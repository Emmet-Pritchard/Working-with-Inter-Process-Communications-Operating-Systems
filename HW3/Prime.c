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

int prime(int num){
    //I chose to hardcode the prime values because it was strictly
    //between 1 and 25 inclusive. There is probably a better way but 
    //this seems to work just fine!
    int prime_numbers[30] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 
    29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 
    97, 101, 103, 107, 109, 113};
    int result;
    if(num == 0){
        return 0;
    }
    printf("%d", prime_numbers[0]);
    //simple for loop
    for(int i = 1; i < num; i++){
        printf(", %d", prime_numbers[i]);
        result = prime_numbers[i];
    }
    printf("\n");
    return result;
}

int main(int argc, char *argv[]){
    int arg1 = atoi(argv[2]);
    printf("Prime[%u] : First %u prime numbers are: ", getpid(), arg1);
    int result = prime(arg1);

    int SIZE = 32;
    int shm_fd = shm_open(argv[1], O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    void *shmPtr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sprintf(shmPtr, "%d", result);
    return result;
}