#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Constants
const int BAR_LENGTH = 20;  // Length of the progress bar
const int MAX_TASKS = 10;   // Number of tasks

// Task structure representing a task with an ID, progress, and step size
typedef struct
{
    int id;        // Task ID
    int progress;  // Current progress percentage (0-100)
    int step;      // Step size indicating how much progress is made in each iteration
} Task;

// Function prototypes
void print_bar(Task task);   // Prints the progress bar for a task
void clear_screen();         // Clears the terminal screen for smoother output

int main()
{
    Task tasks[MAX_TASKS];    // Array to hold multiple tasks
    srand(time(NULL));        // Seed for random number generator (used for random step sizes)

    // Task initialization
    for (int i = 0; i < MAX_TASKS; i++)
    {
        tasks[i].id = i + 1;                  // Assign task IDs (1 to MAX_TASKS)
        tasks[i].progress = 0;                // Initialize all task progress to 0
        tasks[i].step = rand() % 5 + 1;       // Assign a random step size (1 to 5)
    }

    int tasks_incomplete = 1;  // Flag to check if there are incomplete tasks
    while (tasks_incomplete)
    {
        tasks_incomplete = 0;  // Assume all tasks are complete, will check below
        clear_screen();        // Clear the screen for smooth progress update

        // Update and display each task's progress
        for (int i = 0; i < MAX_TASKS; i++)
        {
            tasks[i].progress += tasks[i].step;  // Increase progress by task's step size

            // Ensure progress doesn't exceed 100%
            if (tasks[i].progress > 100)
            {
                tasks[i].progress = 100;
            }

            // Check if any task is still incomplete
            else if (tasks[i].progress < 100)
            {
                tasks_incomplete = 1;  // If any task is incomplete, continue the loop
            }

            print_bar(tasks[i]);  // Print progress bar for the current task
        }

        sleep(1);  // Wait for 1 second before updating progress again
    }

    printf("All tasks completed!\n");  // Message displayed when all tasks are complete
    printf("Developed by Neeraj Kumar\n");  // Print developed by message
    return 0;
}

// Function to clear the terminal screen (cross-platform compatibility)
void clear_screen()
{
#ifdef _WIN32
    system("cls");    // Windows command to clear screen
#else
    system("clear");  // Unix/Linux/Mac command to clear screen
#endif
}

// Function to print the progress bar for a given task
void print_bar(Task task)
{
    int bars_to_show = (task.progress * BAR_LENGTH) / 100;  // Calculate how many bars to fill

    // Print task ID and opening bracket of the progress bar
    printf("Task %d: [", task.id);

    // Print the progress bar
    for (int i = 0; i < BAR_LENGTH; i++)
    {
        if (i < bars_to_show)
        {
            printf("=");  // Filled part of the progress bar
        }
        else
        {
            printf(" ");  // Empty part of the progress bar
        }
    }

    // Print the closing bracket and the percentage of progress
    printf("] %d%%\n", task.progress);
}
