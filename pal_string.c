#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter to check if palindrome: %s\n",argv[0]);
        return 1;
    }
    char* word = argv[1];
    char* orig = word;
    int len = strlen(word);
    char rev[100];

    for(int i = 0; i < len; i++) 
    {
        rev[i] = word[len - 1 - i];
    }
    rev[len] = '\0';

    if (strcmp(word, rev) == 0)
        printf("%s is a Palindrome\n", word);
    else
        printf("%s is NOT a Palindrome\n", word);
    
    return 0;
}

