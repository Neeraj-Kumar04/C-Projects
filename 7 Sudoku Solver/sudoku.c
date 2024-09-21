#include <stdio.h>

// Initial Sudoku puzzle setup
int puzzle[9][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};

// Function prototypes
void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int col, int val);
int solve_puzzle(int puzzle[9][9], int row, int col);

int main()
{
    // Welcome message
    printf("\n\t\tWelcome to SUDOKU Solver !!!");
    printf("\n\t\t---------------------------");
    printf("\n\t\tDeveloped By: Neeraj Kumar");
    printf("\n\nOriginal Puzzle:");

    // Print the original puzzle
    print_puzzle(puzzle);

    // Attempt to solve the puzzle
    if (solve_puzzle(puzzle, 0, 0))
    {
        printf("\n The puzzle is solved: ");
        print_puzzle(puzzle); // Print solved puzzle
    }
    else
    {
        printf("\n This puzzle is not solvable\n");
    }

    return 0; // End of program
}

// Function to solve the Sudoku puzzle
int solve_puzzle(int puzzle[9][9], int row, int col)
{
    // Move to the next row when the end of a column is reached
    if (col == 9)
    {
        if (row == 8)
        {
            return 1; // Puzzle solved
        }
        row++;
        col = 0; // Reset column
    }

    // Skip filled cells
    if (puzzle[row][col] > 0)
    {
        return solve_puzzle(puzzle, row, col + 1);
    }

    // Try placing numbers 1 to 9
    for (int i = 1; i <= 9; i++)
    {
        if (valid_move(puzzle, row, col, i))
        {
            puzzle[row][col] = i; // Place number

            // Recursively attempt to solve the puzzle
            if (solve_puzzle(puzzle, row, col + 1))
            {
                return 1; // If successful, return
            }
            puzzle[row][col] = 0; // Reset if not successful
        }
    }
    return 0; // Backtrack
}

// Function to check if placing a number is valid
int valid_move(int puzzle[9][9], int row, int col, int val)
{
    // Check for duplicates in the row
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[row][i] == val)
        {
            return 0; // Invalid move
        }
    }

    // Check for duplicates in the column
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[i][col] == val)
        {
            return 0; // Invalid move
        }
    }

    // Check for duplicates in the 3x3 square
    int r = row - row % 3;
    int c = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[r + i][c + j] == val)
            {
                return 0; // Invalid move
            }
        }
    }

    return 1; // Valid move
}

// Function to print the Sudoku puzzle
void print_puzzle(int puzzle[9][9])
{
    printf("\n+-------+-------+-------+");
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf("\n|-------+-------+-------|");
        }
        printf("\n");
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
            {
                printf("| ");
            }
            if (puzzle[row][col] != 0)
            {
                printf("%d ", puzzle[row][col]); // Print filled cell
            }
            else
            {
                printf("  "); // Print empty cell
            }
        }
        printf("|");
    }
    printf("\n+-------+-------+-------+\n");
}
