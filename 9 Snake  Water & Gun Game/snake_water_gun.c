#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Initialize random number generator
    srand(time(0));
    int player, computer = (rand() % 3);

    /*
     0 -- > Sanke
     1 -- > Water
     2 -- > Gun
    */
    printf("\n **WELCOME TO SNAKE, WATER, GUN GAME** ");
    printf("\n Developed By:NEERAJ KUMAR \n");
    printf("========================================== \n");

    printf("Choose 0 for Snake,1 for Water and 2 for Gun \n");
    scanf("%d", &player);
    printf("Computer Choose:%d\n", computer);

    if (player == 0 && computer == 0)
    {
        printf("It's a Draw! \n");
    }
    else if (player == 0 && computer == 1)
    {
        printf(" Congrats!! \n");
        printf(" You Win! \n");
    }
    else if (player == 0 && computer == 2)
    {
        printf(" You Loose! \n");
        printf(" Better Luck Next Time!! \n");
    }
    else if (player == 1 && computer == 0)
    {
        printf(" You Loose! \n");
        printf(" Better Luck Next Time!! \n");
    }
    else if (player == 1 && computer == 1)
    {
        printf("It's a Draw! \n");
    }
    else if (player == 1 && computer == 2)
    {
        printf(" Congrats!! \n");
        printf(" You Win! \n");
    }
    else if (player == 2 && computer == 0)
    {
        printf(" Congrats!! \n");
        printf(" You Win! \n");
    }
    else if (player == 2 && computer == 1)
    {
        printf(" You Loose! \n");
        printf(" Better Luck Next Time!! \n");
    }
    else if (player == 2 && computer == 2)
    {
        printf("It's a Draw! \n");
    }
    else
    {
        printf("Something Went Wrong!");
    }
    getch();
    return 0;
}