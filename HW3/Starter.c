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

int main(int argc, char *argv[]){
    if(argc == 0 || argc < 2 || argc > 2){
        printf("Error: incorrect number of arguments. Expected: 2   Entered: %d\n", argc);
        return 1;
    }
    int fd[2];                                           //fd is the array will hold the 2-way pipe
    char tmp[16];
    char number[10];
    //int stat;

    if(pipe(fd) == -1){                                  //checks if the pipe failed
        printf("Pipe failed.\n");
        return -1;
    }
    sprintf(tmp, "%d", fd[1]);

    pid_t cPID = fork();                       
    if(cPID < 0){                                        //fork will return either 0 for 
        printf("Fork failed.\n");                        //child process or greater than 0
        return -1;                                       //for parent process
    }
    if(cPID == 0){                                       //child process
        close(fd[0]);
        execlp("./CharacterReader", "./CharacterReader", argv[1], tmp, NULL);
    }
    else{                                                //parent process
        close(fd[1]);                                    //close the write end since parent doesn't need it
        read(fd[0], number, sizeof(number));
        close(fd[0]);                                    //close read end
        printf("Starter[%u]: contents read from the read end pipe: %s\n", getpid(), number);
    }

    /* Shared Memory Part */

    char *names[3] = {"FIBB", "PRIME", "TOTAL"};                   //original names would not compile "SHM_Fibb, etc."
    char *executables[3] = {"./Fibb", "./Prime", "./Total"};       //created executables to use in execlp

    char SHM_Fibb[] = "FIBB";                                      //created the names FIBB, PRIME, and TOTAL
    char SHM_Prime[] = "PRIME";
    char SHM_Total[] = "TOTAL";

    int shm_fd = shm_open(SHM_Fibb, O_CREAT | O_RDWR, 0666);       //open shared memory for each child
    int shm_fd1 = shm_open(SHM_Prime, O_CREAT | O_RDWR, 0666);
    int shm_fd2 = shm_open(SHM_Total, O_CREAT | O_RDWR, 0666);

    int SIZE = 32;                                                 //size will be 32 bytes

    ftruncate(shm_fd, SIZE);                                       //truncated size of the memory
    ftruncate(shm_fd1, SIZE);
    ftruncate(shm_fd2, SIZE);

    void *shmPtr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);     //pointer to the memory that was opened for each
    void *shmPtr1 = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd1, 0);   //child process
    void *shmPtr2 = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd2, 0);

    printf("Starter[%u]: Created shared memory \"SHM_Fibb\" with FD: %d\n", getpid(), shm_fd);
    printf("Starter[%u]: Created shared memory \"SHM_Prime\" with FD: %d\n", getpid(), shm_fd1);
    printf("Starter[%u]: Created shared memory \"SHM_Total\" with FD: %d\n", getpid(), shm_fd2);

    int cPIDs[3];                                           //will be used to keep track of parent pid for each process

    for(int i = 0; i < 3; i++){                             //fork and exec in one for loop for each process
        pid_t share = fork();
        if(share < 0){
            printf("Fork failed.\n");
            return -1;
        }
        else if(share == 0){                                //child process
            execlp(executables[i], executables[i], names[i], number, NULL);
        }
        else{
            cPIDs[i] = share;                               //keep track of parent
        }
    }

    int status;
    for(int k = 0; k < 3; k++){                              //wait() in a separate for loop since we are running
        waitpid(cPIDs[k], &status, 0);                       //concurrently
    } 

    int fibb_result = atoi(shmPtr);                          //store last number of each process into results
    int prime_result = atoi(shmPtr1);
    int total_result = atoi(shmPtr2);

    shm_unlink(names[0]);                                    //unlink all of the shared memory
    shm_unlink(names[1]);
    shm_unlink(names[2]);

    printf("Starter[%u]: Fibb last number: %d\n", getpid(), fibb_result);
    printf("Starter[%u]: Prime last number: %d\n", getpid(), prime_result);
    printf("Starter[%u]: Total last number: %d\n", getpid(), total_result);

    return 0;                                                //successful program
}
