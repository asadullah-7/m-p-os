#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter the range %s: ",argv[0]);
        return 1;
    }
    int range = atoi(argv[1]);
    int first = 0 ; 
    int second = 1;
    int next = 0; 
    for (int i = 0 ; i < range; i++)
    {
        printf("%d , ",first);
        next = first + second;
        first = second;
        second = next;

    }
    return 0;
}