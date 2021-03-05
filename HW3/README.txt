Questions: (To be answered in README file.)

1. Name the function that is used to create a pipe. Which ends 
    denotes the read and the write ends of a pipe?  

Answer: We need to get an integer result back from
        CharacterReader.c so we must create a pipe in Starter.c
        that we can use to return that.

        In our assignment, Starter.c has no need of the write 
        end and CharacterReader.c has no need of the read end.
        Starter.c = read end fd[0]
        CharacterReader.c = write end fd[1]

2. Name the function used to map files or devices in to memory?

Answer: In this assignment we are using mmap() to map files
        into memory.

3. Name the function used to open a shared memory object? 
    What does it return?

Answer: In this assignment we are using shm_open() to open 
        the shared memory for Fibb.c, Prime.c, and Total.c.

        shm_open() returns a file descriptor that is associated
        with the shared memory object that is specified by the 
        name we created. If there is an error in the process,
        shm_open() will return a -1.

