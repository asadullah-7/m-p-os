#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/wait.h>

#define READ 0
#define WRITE 1

int factorial(int num)
{
    if(num == 0 || num == 1)
    {
        return 1;
    }
    return num * factorial(num-1);
}

bool isPrime(int num)
{
    if(num <= 1)
    {
        return false;
    }

    for(int i = 2; i < num; i++)
    {
        if(num % i == 0)
        {
            return false;
        }       
    }
    return true;
    
}

int main(int argc, char*argv[])
{
    if(argc != 2)
    {
        printf("Enter the number: %s", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    int fd1[2]; // Parent -> child1
    int fd2[2]; // child1 -> parent
    int fd3[2]; // Parent -> child2
    int fd4[2]; // child2 -> parent

    if(pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1 || pipe(fd4) == -1)
    {
        perror("PIPE FAILED!");
        exit(1);
    }

    pid_t id1 = fork();

    
    if(id1 < 0)
    {
        perror("FORK FAILED!");
        exit(1);
    }

    

    if(id1 == 0) // CHILD 1
    {
        close(fd1[WRITE]);
        close(fd2[READ]);
        
        close(fd3[WRITE]); close(fd3[READ]);
        close(fd4[WRITE]); close(fd4[READ]);


        read(fd1[READ], &num, sizeof(num));

        int fac = factorial(num);

        write(fd2[WRITE], &fac, sizeof(fac));
        
        
        exit(0);

    }

    pid_t id2 = fork();

    if(id2 < 0) // CHILD 2
    {
        perror("FORK FAILED!");
        exit(1);
    }
    
    if(id2 == 0)
    {
        close(fd1[WRITE]); close(fd1[READ]);
        close(fd2[WRITE]); close(fd2[READ]);
        close(fd3[WRITE]);
        close(fd4[READ]);

        
        read(fd3[READ], &num, sizeof(num));
        

       int if_p = isPrime(num)? 1 : 0;
        
        write(fd4[WRITE], &if_p, sizeof(if_p));
        

        exit(0);
    }
    if(id1 > 0) // PARENT
    {
        close(fd1[READ]);
        close(fd2[WRITE]);
        close(fd3[READ]);
        close(fd4[WRITE]);

        write(fd1[WRITE], &num, sizeof(num));
        write(fd3[WRITE], &num, sizeof(num));

        close(fd1[WRITE]);
        close(fd3[WRITE]);


        int result_fac = 0;
        int result_prime = 0;

        read(fd2[READ], &result_fac, sizeof(result_fac));
        read(fd4[READ], &result_prime, sizeof(result_prime));
        close(fd2[READ]);
        close(fd4[READ]);

        wait(NULL);
        wait(NULL);

        printf("Factorial of %d is %d\n",num, result_fac);
        printf("%d is %s\n",num, (result_prime ? "PRIME" : "NOT PRIME"));

    }
    return 0;
}