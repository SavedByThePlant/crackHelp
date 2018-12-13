#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

// INITIATE VARIABLES

    string hashInfo="";
    char salt[3];
    // GET KEY AT COMMAND LINE ARGUMENT
    // if key not provided, message and exit
    // if more than one arg, message and exit
    if (argc != 2) {
        printf("No password entered.\nQuitting...\n");
        return 1;
    }
    else {

        hashInfo = argv[1];

        if (strlen(hashInfo) != 13)
        {
            printf("Up to 13 characters. Not zero.\nQuitting...\n");
            return 1;
        }
    }

    printf("---------------------------------------\n");
    printf("HashInfo: %s\n", hashInfo);
    printf("--------------------------------------------------\n");

    //printf("\nSTART CRACKING\n");

    // COPY NO SALT HASH TO HASHTOCOMPARE
    char origPepper[11];
    int origPepperLength = sizeof(origPepper);
    //printf("%i\n", origPepperLength);
    char tempHash[origPepperLength];
    int tempHashLength = sizeof(tempHash);

    printf("Salt: ");

    for (int s=0; s < 2; s++)
    {
        salt[s] = hashInfo[s];
        printf("%c", salt[s]);
    }

    printf("\tPepper: ");

    // SET ORIGPEPPER AD TEMPHASH
    for (int i=0; i < origPepperLength; i++)
    {
        origPepper[i] = hashInfo[i+2];
        //printf("%c\n", origPepper[i]);
    }

    for (int i = 0; i < tempHashLength; i++)
    {
        tempHash[i] = origPepper[i];
        printf("%c", tempHash[i]);
    }
    printf("\n----------------------------------------------------\n");

    char fullAlphabet[] = {"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"};
    int alphaLength = strlen(fullAlphabet);
    //printf("%i", alphaLength);

    // iterate over the alphabet and add characters
    // to make words from a to AAAAA.
    int maxChars = 5;
    int outerLoop = 0;

    while (outerLoop < maxChars)
    {
        char word[maxChars+1];
        int wordLength = strlen(word);

        //printf("Outer: %i", outerLoop);
        //printf("\n  Salt: %s\tPepper: %s\n", salt, tempHash);
        string hashed;
        int hashedLength;
        for (int a=0; a < alphaLength; a++)
        {
            char letter = fullAlphabet[a];
            word[wordLength] = letter;
            printf("word: %s\t", word);

           hashed = crypt(word, salt);
            hashedLength = strlen(hashed);
            printf("Hashed: %s\n", hashed);
        }
        printf("\n");
        outerLoop++;
        //printf("\n  Salt: %s\tPepper: %s\n", salt, tempHash);
        bool matchFound = false;
        int matchCount = 0;
        for (int c=0; c < 13 && !matchFound; c++)
        {
            if (hashed[c]==hashInfo[c]) {
                //printf("%i They are equal\n", c);
                matchFound = true;
                matchCount++;
            }
            else if (hashed[c] != hashInfo[c]) {
                //printf("%i They are not equal\n", c);
                matchFound = false;
                printf("Match not found. \n");
            }

            if (matchCount == hashedLength)
            {
                printf("They all match.\n");
            }
            else
            {
                printf("One or more did not match.\n");
            }
        }
    printf("---------------------------------------------\n");
    }
    printf("\n");
    return 0;
}
// 1. accept hashed password
// 2. if more than one argument, error and exit
// 3. crack pw, print pw in clear followed by \n
// 4. assume hashed with DES-baed crypt
// 5. assume pw no longer than 5 chars long
// 6. only alpha characters a-z A-Z
