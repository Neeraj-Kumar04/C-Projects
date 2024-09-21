#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Initialize random number generator
    srand(time(0));

    // Gnerate random number between 1 to 100
    int randomNumber = (rand() % 100) + 1;
    int no_of_guesses = 0;
    int guessed_number;

    // Print the random number
    // printf("Random Number:%d\n", randomNumber);
    printf("** WELCOME TO THE WORLD OF GUESSING NUMBER GAME **\n");
    printf("==================================================\n");

    do
    {
        printf("Guess the number between (1 to 100):");
        scanf("%d", &guessed_number);
        if (guessed_number > randomNumber)
        {
            printf("Guess a Smaller Number Please!\n");
        }
        else if (guessed_number < randomNumber)
        {
            printf("Guess a Larger Number Please!\n");
        }
        else
        {
            printf("Congrats!!\n");
            printf("You Guessed the Number in %d guesses\n", no_of_guesses);
        }
        no_of_guesses++;
    } while (guessed_number != randomNumber);

    printf("Bye Bye,Thanks for Playing.\n");
    printf("Developed By: NEERAJ KUMAR");

    getch();
    return 0;
}