#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define READ 0
#define WRITE 1

// Function to calculate factorial
long long factorial(int n) {
    long long fac = 1;
    for(int i = 2; i <= n; i++)
        fac *= i;
    return fac;
}

// Function to check prime
bool isPrime(int n) {
    if(n <= 1) return false;
    for(int i = 2; i*i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    int fd_even[2], fd_prime[2], fd_fact[2];

    // Create pipes
    pipe(fd_even);
    pipe(fd_prime);
    pipe(fd_fact);

    // Child1: Even/Odd
    pid_t id1 = fork();
    if(id1 == 0) {
        close(fd_even[READ]);
        close(fd_prime[READ]); close(fd_prime[WRITE]);
        close(fd_fact[READ]); close(fd_fact[WRITE]);

        int even = (num % 2 == 0) ? 1 : 0;  // 1=even,0=odd
        write(fd_even[WRITE], &even, sizeof(even));
        close(fd_even[WRITE]);
        exit(0);
    }

    // Child2: Prime check
    pid_t id2 = fork();
    if(id2 == 0) {
        close(fd_prime[READ]);
        close(fd_even[READ]); close(fd_even[WRITE]);
        close(fd_fact[READ]); close(fd_fact[WRITE]);

        int prime = isPrime(num) ? 1 : 0;
        write(fd_prime[WRITE], &prime, sizeof(prime));
        close(fd_prime[WRITE]);
        exit(0);
    }

    // Child3: Factorial
    pid_t id3 = fork();
    if(id3 == 0) {
        close(fd_fact[READ]);
        close(fd_even[READ]); close(fd_even[WRITE]);
        close(fd_prime[READ]); close(fd_prime[WRITE]);

        long long fac = factorial(num);
        write(fd_fact[WRITE], &fac, sizeof(fac));
        close(fd_fact[WRITE]);
        exit(0);
    }

    // Parent
    close(fd_even[WRITE]);
    close(fd_prime[WRITE]);
    close(fd_fact[WRITE]);

    int even, prime;
    long long fac;

    read(fd_even[READ], &even, sizeof(even));
    read(fd_prime[READ], &prime, sizeof(prime));
    read(fd_fact[READ], &fac, sizeof(fac));

    close(fd_even[READ]);
    close(fd_prime[READ]);
    close(fd_fact[READ]);

    // Wait for all children
    wait(NULL); wait(NULL); wait(NULL);

    // Print results on console
    printf("Number: %d\n", num);
    printf("Even/Odd: %s\n", (even ? "Even" : "Odd"));
    printf("Prime/Not Prime: %s\n", (prime ? "Prime" : "Not Prime"));
    printf("Factorial: %lld\n", fac);

    // Write results to txt file
    FILE *fp = fopen("results.txt", "w");
    if(fp != NULL) {
        fprintf(fp, "Number: %d\n", num);
        fprintf(fp, "Even/Odd: %s\n", (even ? "Even" : "Odd"));
        fprintf(fp, "Prime/Not Prime: %s\n", (prime ? "Prime" : "Not Prime"));
        fprintf(fp, "Factorial: %lld\n", fac);
        fclose(fp);
    } else {
        perror("File write failed");
    }

    return 0;
}
