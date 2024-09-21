#include <stdio.h>
#include <string.h>

void create_account();          // Function to create a new account
void deposit_money();           // Function to deposit money into an account
void withdraw_money();          // Function to withdraw money from an account
void check_balance();           // Function to check the balance of an account

const char *ACCOUNT_FILE = "account.dat"; // File to store account data

// Structure to represent an account
typedef struct
{
    char name[50];   // Account holder's name
    int acc_no;      // Account number
    float balance;   // Account balance
} Account;

int main()
{
    // Print welcome message
    printf("\n*** Welcome to the Bank Management System ***");
    printf("\n*** Developed By: Neeraj Kumar ***\n");

    while (1)
    {
        int choice;
        // Menu options
        printf("\n\n*** Bank Management System Menu ***");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account(); // Call function to create an account
            break;
        case 2:
            deposit_money(); // Call function to deposit money
            break;
        case 3:
            withdraw_money(); // Call function to withdraw money
            break;
        case 4:
            check_balance(); // Call function to check account balance
            break;
        case 5:
            printf("\nClosing the Bank, Thanks for your visit.\n");
            return 0; // Exit the program
            break;
        default:
            printf("\nInvalid choice!\n"); // Handle invalid input
            break;
        }
    }
}

void create_account()
{
    Account acc; // Declare an account structure
    FILE *file = fopen(ACCOUNT_FILE, "ab+"); // Open the account file in append mode
    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return; // Exit if file cannot be opened
    }

    // Clear input buffer
    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);

    // Get account holder's name
    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n"); // Remove newline character from name
    acc.name[ind] = '\0';
    printf("Enter your account number: ");
    scanf("%d", &acc.acc_no); // Get account number
    acc.balance = 0; // Initialize balance to 0

    fwrite(&acc, sizeof(acc), 1, file); // Write account data to file
    fclose(file); // Close the file
    printf("\nAccount created successfully!"); // Confirmation message
}

void deposit_money()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+"); // Open the account file in read-write mode
    if (file == NULL)
    {
        printf("Unable to open account file!!");
        return; // Exit if file cannot be opened
    }

    int acc_no;
    float money;
    Account acc_r; // Structure to read account data
    printf("Enter your account number: ");
    scanf("%d", &acc_no); // Get account number
    printf("Enter amount to deposit: ");
    scanf("%f", &money); // Get deposit amount

    // Read accounts from file
    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if (acc_r.acc_no == acc_no) // Match the account number
        {
            acc_r.balance += money; // Update balance
            fseek(file, -sizeof(acc_r), SEEK_CUR); // Move file pointer back to update record
            fwrite(&acc_r, sizeof(acc_r), 1, file); // Write updated account data back to file
            fclose(file); // Close the file
            printf("Successfully deposited Rs.%.2f. New balance is Rs.%.2f", money, acc_r.balance);
            return; // Exit function after successful deposit
        }
    }

    fclose(file); // Close the file if account not found
    printf("Money could not be deposited as the Account no %d was not found in records.", acc_no);
}

void withdraw_money()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+"); // Open the account file in read-write mode
    if (file == NULL)
    {
        printf("\nUnable to open the account file!!!.\n");
        return; // Exit if file cannot be opened
    }

    int acc_no;
    float money;
    Account acc_r; // Structure to read account data
    printf("Enter your account number: ");
    scanf("%d", &acc_no); // Get account number
    printf("Enter the amount you wish to withdraw: ");
    scanf("%f", &money); // Get withdrawal amount

    // Read accounts from file
    while (fread(&acc_r, sizeof(acc_r), 1, file) != EOF)
    {
        if (acc_r.acc_no == acc_no) // Match the account number
        {
            if (acc_r.balance >= money) // Check for sufficient balance
            {
                acc_r.balance -= money; // Update balance
                fseek(file, -sizeof(acc_r), SEEK_CUR); // Move file pointer back to update record
                fwrite(&acc_r, sizeof(acc_r), 1, file); // Write updated account data back to file
                printf("Successfully withdrawn Rs.%.2f. Remaining balance is Rs.%.2f", money, acc_r.balance);
            }
            else
            {
                printf("Insufficient balance!"); // Notify insufficient funds
            }
            fclose(file); // Close the file
            return; // Exit function after withdrawal
        }
    }

    fclose(file); // Close the file if account not found
    printf("Money could not be withdrawn as the Account no %d was not found in records.", acc_no);
}

void check_balance()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb"); // Open the account file in read mode
    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return; // Exit if file cannot be opened
    }

    int acc_no;
    Account acc_read; // Structure to read account data
    printf("Enter your account number: ");
    scanf("%d", &acc_no); // Get account number

    // Read accounts from file
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no) // Match the account number
        {
            printf("\nYour current balance is Rs.%.2f", acc_read.balance); // Display balance
            fclose(file); // Close the file
            return; // Exit function after displaying balance
        }
    }
    fclose(file); // Close the file if account not found
    printf("\nAccount No:%d was not found.\n", acc_no); // Notify account not found
}
