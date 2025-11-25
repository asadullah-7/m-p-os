#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // for tolower()

// Function to convert string to lowercase
void toLowerCase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// Function to sort characters in a string (simple bubble sort)
void sortString(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (str[i] > str[j])
            {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main()
{
    char word1[100], word2[100];

    printf("Enter the first word: ");
    scanf("%99s", word1);

    printf("Enter the second word: ");
    scanf("%99s", word2);

    // Convert both words to lowercase for case-insensitive comparison
    toLowerCase(word1);
    toLowerCase(word2);

    if (strlen(word1) != strlen(word2))
    {
        printf("Not anagrams! (Different lengths)\n");
        return 0;
    }

    sortString(word1);
    sortString(word2);

    if (strcmp(word1, word2) == 0)
        printf("They are ANAGRAMS (case-insensitive)!\n");
    else
        printf("They are NOT anagrams.\n");

    return 0;
}
