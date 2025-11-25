#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    if(argc !=2 )
    {
        printf("Enter the number you want to find factorial %s\n",argv[0]);
        return 1;
    }
    int num = atoi(argv[1]);
    int fac = 1;
    for(int i = 1 ; i <= num; i++)
    {
        fac = fac*i;
    }
    printf("%d! = %d\n",num,fac);
    return 0;
}