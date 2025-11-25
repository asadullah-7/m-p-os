#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter a number to check if palindrome: %s\n",argv[0]);
        return 1;
    }
    int num = atoi(argv[1]);
    int rev = 0;
    int orig = num;
    while(num>0)
    {
        rev = rev * 10 + num % 10;
        num = num/10;
    }
    if ( rev == orig)
    {
        printf("%d is a Palindrome number\n",orig);
    }
    else 
    {
        printf("%d is a NOT Palindrome number\n",orig);
        
    }
    
    return 0;
}