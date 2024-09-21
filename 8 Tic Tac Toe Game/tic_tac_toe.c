#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

// Structure to hold scores for player, computer, and draws
typedef struct
{
    int player;
    int computer;
    int draw;
} Score;

int difficulty;                                        // Variable to hold the difficulty level
Score score = {.player = 0, .computer = 0, .draw = 0}; // Initialize scores

// Function prototypes
void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main()
{
    srand(time(NULL)); // Seed random number generator
    int choice;

    // Welcome message
    printf("\n\t\tWelcome to Tic-Tac-Toe Game!");
    printf("\n\t\tDeveloped By: Neeraj Kumar\n");
    printf("\nLet's Play!");

    input_difficulty(); // Get the difficulty level from the user

    // Main game loop
    do
    {
        play_game(); // Play a game
        printf("\nPlay again? (1 for yes, 0 for no): ");
        scanf("%d", &choice); // Ask if the player wants to play again
    } while (choice == 1);

    printf("\nBye Bye, thanks for playing.\n");
    return 0; // End of program
}

void play_game()
{
    // Initialize the game board
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
    };

    // Randomly choose the starting player
    char current_player = rand() % 2 == 0 ? X : O;

    print_board(board); // Print the initial board
    while (1)
    {
        if (current_player == X)
        { // Player's turn
            player_move(board);
            print_board(board);
            if (check_win(board, X))
            {
                score.player++; // Increment player score
                print_board(board);
                printf("Congratulations! You have won!!!\n");
                break;
            }
            current_player = O; // Switch to computer's turn
        }
        else
        { // Computer's turn
            computer_move(board);
            print_board(board);
            if (check_win(board, O))
            {
                score.computer++; // Increment computer score
                print_board(board);
                printf("I won!!! But you played well...\n");
                break;
            }
            current_player = X; // Switch to player's turn
        }

        if (check_draw(board))
        { // Check for a draw
            score.draw++;
            print_board(board);
            printf("\nIt's a draw!\n");
            break;
        }
    }
}

// Function to check if a move is valid
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    return !(row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE || board[row][col] != ' ');
}

// Function for player's move
void player_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    int count = 0, x, y;
    // Check for available moves
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                count++;
                x = i;
                y = j;
            }
        }
    }

    if (count == 1)
    { // If only one move is left
        board[x][y] = X;
        return;
    }

    int row, col;
    // Get valid input from player
    do
    {
        printf("\nPlayer X's turn.");
        printf("\nEnter row and column (1-3) for X: ");
        scanf("%d", &row);
        scanf("%d", &col);
        row--;
        col--; // Convert to zero-based indexing
    } while (!is_valid_move(board, row, col));
    board[row][col] = X; // Place player's move on the board
}

// Function for computer's move
void computer_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    // 1. Play for Immediate win
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                if (check_win(board, O))
                {
                    return; // Win found
                }
                board[i][j] = ' '; // Reset if not a win
            }
        }
    }

    // 2. Play for Immediate Block
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = X;
                if (check_win(board, X))
                {
                    board[i][j] = O; // Block player's win
                    return;
                }
                board[i][j] = ' '; // Reset if not a block
            }
        }
    }

    // GOD Mode
    if (difficulty == 2)
    {
        // 3. Play Center if available
        if (board[1][1] == ' ')
        {
            board[1][1] = O;
            return;
        }

        // 4. Play Corner if available
        int corner[4][2] = {
            {0, 0},
            {0, 2},
            {2, 0},
            {2, 2}};
        for (int i = 0; i < 4; i++)
        {
            if (board[corner[i][0]][corner[i][1]] == ' ')
            {
                board[corner[i][0]][corner[i][1]] = O;
                return;
            }
        }
    }

    // 5. Play first available move
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O; // Make move
                return;
            }
        }
    }
}

// Function to check for a win
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    // Check rows and columns for a win
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return 1; // Win found
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return 1; // Win found
        }
    }

    // Check diagonals for a win
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[2][0] == player && board[1][1] == player && board[0][2] == player))
    {
        return 1; // Win found
    }
    return 0; // No win
}

// Function to check for a draw
int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0; // Empty space found, not a draw
            }
        }
    }
    return 1; // All spaces filled, it's a draw
}

// Function to print the game board
void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    clear_screen(); // Clear the console screen
    // Print scores
    printf("Score - Player X: %d, Computer: %d, Draws: %d", score.player, score.computer, score.draw);
    printf("\nTic-Tac-Toe\n");

    // Print the board
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("\n");
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ", board[i][j]); // Print each cell
            if (j < BOARD_SIZE - 1)
            {
                printf("|"); // Print column separator
            }
        }
        if (i < BOARD_SIZE - 1)
        {
            printf("\n---+---+---"); // Print row separator
        }
    }
    printf("\n\n");
}

// Function to input the difficulty level
void input_difficulty()
{
    while (1)
    {
        printf("\nSelect difficulty level:");
        printf("\n1. Human (Standard)");
        printf("\n2. God (Impossible to win)");
        printf("\nEnter your choice: ");
        scanf("%d", &difficulty);

        if (difficulty != 1 && difficulty != 2)
        {
            printf("\nIncorrect choice! Please enter (1/2)!!\n");
        }
        else
        {
            break; // Valid choice, exit loop
        }
    }
}

// Function to clear the console screen
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
