#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int check_arg_count(int argc);
int main(int argc, string argv[1])
{
//Initialize variables
    string command_input = argv[1];
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//Check to make sure that the user inputs correct amount of strings
    if (argc != 2)
    {
        printf("Usage: ./substitution 'key'\n");
        return 1;
    }
//Check to make sure there are enough characters in the string that the user provides
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
    //For loop to initialize an empty array which is called in the loop below to check for duplicate characters.
        char duplicate[26];
        for (int i = 0; i < 26; i++)
        {
            duplicate[i] = 0;
        }
    //Set argv to check so it becomes a string.
        string check = argv[1];
    // Loop will run the other for loop inside to check if any characters already exist in duplicate[] which would be a duplicate. If it's not a duplicate, the character is placed in duplicate[] to refer to future characters in the string.
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
        //For loop that checks the character in argv[] (or check[]).
            for (int j = 0; j < n; j++)
            {
                if (duplicate[j] == check[i])
                {
                    printf("Key must not contain any duplicate characters.\n");
                    return 1;
                }
            }
            duplicate[i] = check[i];
        }
    }


//Check to ensure that there aren't any numbers. COME BACK TO THIS TO INCLUDE EVERYTHING THAT'S NOT AN ALPHABET.
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if(isalpha(argv[1][i]))
        {
        }
        else
        {
            printf("Key must only contain alphabetical characters.\n");
            return 1;
        }
    }
string user_input = get_string("plaintext: ");
string cipher = argv[1];
printf("ciphertext: ");

        for (int j = 0; j < strlen(user_input); j++)
        {
            for (int k = 0; k < strlen(alphabet); k++)
            {
                if(tolower(alphabet[k]) == user_input[j])
                {
                    if(islower(user_input[j]))
                    {
                        printf("%c", tolower(cipher[k]));
                    }
                }
                else if(alphabet[k] == user_input[j])
                {
                    printf("%c", toupper(cipher[k]));
                }
            }
            if(isalpha(user_input[j]))
            {
            }
            else
            {
                printf("%c", user_input[j]);
            }
        }

printf("\n");

}
