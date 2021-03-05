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

//function that returns the fibb sequence n amount of times
int fibb(int num){
    //every fibb sequence begins with 0 and 1
    int n1 = 0;
    int n2 = 1;
    int result;
    if(num <= 0){
        return 0;
    }
    else{
        //formatted this way so there is no trailing comma
        printf("%d", n1);
        for(int i = 1; i < num; i++){
            printf(", %d", n2);
            //finding the sum of the two numbers and setting it as next
            int next = n1 + n2;
            n1 = n2;
            //keeping track of what to return from the fibb function
            result = n2;
            n2 = next;
        }
        printf("\n");
        return result;
    }
}

int main(int argc, char *argv[]){
    int arg1 = atoi(argv[2]);
    printf("Fibb[%u] : Number of terms in fibonacii series is %u\n", getpid(), arg1);
    printf("Fibb[%u] : The first %u numbers of the Fibonacii sequence are: ",
            getpid(), arg1);
    int result = fibb(arg1);

    int SIZE = 32;
    int shm_fd = shm_open(argv[1], O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    void *shmPtr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sprintf(shmPtr, "%d", result);
    return result;
}