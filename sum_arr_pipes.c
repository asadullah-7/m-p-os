#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char*argv[])
{
    if(argc != 11)
    {
        printf("enter 10 numbers: %s", argv[0]);
        return 1;
    }

    int fd1[2];
    int fd2[2];

   

    if(pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("PIPE FAILED!!");
        exit(1);
    }

    pid_t id = fork();


    if(id < 0)
    {
        perror("FORK FAILDED!!");
        exit(1);
    }
    int arr[10] = {};
    for(int i = 0; i < 10; i++)
    {
        arr[i] = atoi(argv[i+1]);
    }

    if(id > 0) // PARENT
    {
        close(fd1[READ]);
        close(fd2[WRITE]);
        write(fd1[WRITE], arr, sizeof(arr));
        close(fd1[WRITE]);
        int recivedSum = 0;
        read(fd2[READ], &recivedSum, sizeof(recivedSum));
        close(fd2[READ]);
        printf("sum of array is : %d\n", recivedSum);

        wait(NULL);
    }

    if(id == 0)
    {
        close(fd1[WRITE]);
        close(fd2[READ]);
        read(fd1[READ], arr, sizeof(arr));
        close(fd1[READ]);

        int sum = 0;
        for(int i = 0 ; i < 10; i++)
        {
            sum += arr[i];
        }
        write(fd2[WRITE], &sum, sizeof(sum));
        close(fd2[WRITE]);

    }

    

    return 0;
}