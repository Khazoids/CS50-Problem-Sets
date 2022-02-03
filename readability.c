#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int word = 0;
    int sentence = 0;
    int letter = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letter++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentence++;
        }
        else if (isspace(text[i]))
        {
            word++;
        }
    }

    float avg_letter = ((float)letter / (word + 1)) * 100;
    float avg_sentence = ((float)sentence / (word + 1)) * 100;
    float index = 0.0588 * avg_letter - 0.296 * avg_sentence - 15.8;

    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}
