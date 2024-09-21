#include <stdio.h>
#include <string.h>
#include <conio.h>   // For _getch(), which allows reading characters without echoing
#include <windows.h> // For Windows-specific functions

#define MAX_USERS 10         // Maximum number of users supported
#define CREDENTIAL_LENGTH 30 // Maximum length for usernames and passwords

// Structure to represent a user with a username and password
typedef struct
{
    char username[CREDENTIAL_LENGTH]; // Username of the user
    char password[CREDENTIAL_LENGTH]; // Password of the user
} User;

User users[MAX_USERS]; // Array to hold registered users
int user_count = 0;    // Current count of registered users

// Function prototypes
void register_user();                                   // Function to register a new user
int login_user();                                       // Function to log in a user, returns the user index
void fix_fgets_input(char *);                           // Helper function to fix input from fgets
void input_credentials(char *username, char *password); // Function to input username and password
void print_welcome_message();                           // Function to print a welcome message

int main()
{
    int option;     // User's menu option
    int user_index; // Index of the logged-in user

    // Print the welcome message
    print_welcome_message();

    // Infinite loop to display the menu until the user exits
    while (1)
    {
        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Exit");
        printf("\nSelect an option: ");
        scanf("%d", &option);
        getchar(); // Consume extra newline character

        switch (option)
        {
        case 1:
            register_user(); // Call the registration function
            break;
        case 2:
            user_index = login_user(); // Call the login function
            if (user_index >= 0)
            {
                printf("\nLogin successful! Welcome, %s!\n", users[user_index].username);
            }
            else
            {
                printf("\nLogin failed! Incorrect username or password.\n");
            }
            break;
        case 3:
            printf("\nExiting Program.\n");
            return 0; // Exit the program
        default:
            printf("\nInvalid option. Please try again.\n");
            break;
        }
    }
    return 0; // Return success
}

void register_user()
{
    // Check if maximum user limit is reached
    if (user_count == MAX_USERS)
    {
        printf("\nMaximum %d users are supported! No more registrations allowed!\n", MAX_USERS);
        return;
    }

    int new_index = user_count; // Get the index for the new user
    printf("\nRegister a new user");
    input_credentials(users[new_index].username, users[new_index].password); // Input username and password
    user_count++;                                                            // Increment the user count
    printf("\nRegistration successful!\n");
}

int login_user()
{
    char username[CREDENTIAL_LENGTH]; // Buffer for the username
    char password[CREDENTIAL_LENGTH]; // Buffer for the password

    input_credentials(username, password); // Input credentials for login

    // Check entered credentials against registered users
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return i; // Return index if credentials match
        }
    }

    return -1; // Return -1 if login failed
}

void input_credentials(char *username, char *password)
{
    printf("\nEnter username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin); // Input username
    fix_fgets_input(username);                 // Clean up the input
    printf("Enter password (masking enabled): ");
    fflush(stdout); // Flush stdout to ensure the prompt appears immediately

    int i = 0;
    char ch;
    // Read password character by character without echo
    while ((ch = _getch()) != '\r')
    { // Use _getch() to read character without echo
        if (ch == '\b')
        { // Handle backspace
            if (i > 0)
            {
                i--;
                printf("\b \b"); // Move back, print space, move back again
            }
        }
        else
        {
            password[i++] = ch; // Store the character in password
            printf("*");        // Print asterisks for password
        }
    }
    password[i] = '\0'; // Null-terminate the password string
    printf("\n");       // Move to the next line after password entry
}

void fix_fgets_input(char *string)
{
    // Remove the newline character from fgets input
    int index = strcspn(string, "\n");
    string[index] = '\0';
}

// Function to print the welcome message
void print_welcome_message()
{
    printf("\n**********************************************\n");
    printf("**                                          **\n");
    printf("**           !! Welcome to UserHub !!        **\n");
    printf("**   Your gateway to secure user management! **\n");
    printf("**                                          **\n");
    printf("**********************************************\n");
    printf("         Developed By: Neeraj Kumar          \n");
    printf("**********************************************\n\n");
}
