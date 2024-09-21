#include <stdio.h>
#include <conio.h>
#include <windows.h>

// Function declarations
int getkey();
void display(int, int, int, int[]);
void calendar(int, int);

//-------------- GOTO function definition ----------------------
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//------------ Change color -------------------
// Function to change the color of the console text
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Fetching console attributes to keep the background unchanged
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        // Set the new foreground color while retaining the current background color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

// Month and week names
char *month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char *week[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

int main()
{
    int nmonth, nyr, ch;

    // Welcome message
    system("cls");
    SetColor(10);
    printf("Welcome to the Calendar Program\n");
    SetColor(14);
    printf("Developed by: Neeraj Kumar\n\n");
    SetColor(15);

enteryear: // Label for re-entering the year
    while (1)
    {
        printf("Enter year and month (number): ");
        scanf("%d%d", &nyr, &nmonth);

        // Year validation
        if (nyr < 1945)
        {
            printf("\n\tPlease enter a year above 1945\n");
            continue;
        }
        else
        {
            // Display calendar for the entered year and month
            calendar(nyr, nmonth);
        }

        // Calendar navigation loop
        while (1)
        {
            gotoxy(20, 20);
            printf("(*) Use LEFT, RIGHT, UP, and DOWN arrows.");
            gotoxy(20, 22);
            printf("(*) Press 'P' to go to a particular year and month.");
            gotoxy(20, 24);
            printf("(*) Press ESC to Exit.");
            ch = getkey();

            switch (ch)
            {
            case 80: // DOWN ARROW (Increase Month)
                if (nmonth == 12)
                {
                    nmonth = 1;
                    nyr++;
                }
                else
                {
                    nmonth++;
                }
                calendar(nyr, nmonth);
                break;

            case 77: // RIGHT ARROW (Increase Year)
                nyr++;
                calendar(nyr, nmonth);
                break;

            case 72: // UP ARROW (Decrease Month)
                if (nmonth == 1)
                {
                    nyr--;
                    nmonth = 12;
                }
                else
                {
                    nmonth--;
                }
                calendar(nyr, nmonth);
                break;

            case 75: // LEFT ARROW (Decrease Year)
                if (nyr == 1945)
                {
                    gotoxy(15, 2);
                    printf("Year below 1945 not available");
                }
                else
                {
                    nyr--;
                    calendar(nyr, nmonth);
                }
                break;

            case 27: // ESC KEY (Exit)
                system("cls");
                gotoxy(50, 14);
                printf("Exiting program.\n\n\n\n\n");
                exit(0);

            case 112: // 'P' KEY (Go to particular year and month)
                system("cls");
                goto enteryear; // Go back to year and month input
            }
        }
        break;
    }

    getch();
    return 0;
}

//============== DISPLAYING THE CALENDAR ===================
// Function to display the calendar
void display(int nyr, int nmonth, int tdays, int days[])
{
    int i, j, pos;

    // Heading: display month and year
    SetColor(12);
    gotoxy(56, 6);
    printf("%s %d", month[nmonth - 1], nyr);

    // Display week headers (Mon to Sun)
    for (i = 0, pos = 30; i < 7; i++, pos += 10)
    {
        if (i == 6)
            SetColor(9); // Sunday in blue
        else
            SetColor(10); // Other days in green
        gotoxy(pos, 8);
        printf("%s", week[i]);
    }

    // Reset color to white for days display
    SetColor(15);
    tdays++; // Increment tdays by 1 for day position calculation

    // Set the initial position based on tdays (0 = Sunday, 1 = Monday, etc.)
    switch (tdays)
    {
    case 0:
    case 7:
        pos = 91;
        break; // Sunday
    case 1:
        pos = 31;
        break; // Monday
    case 2:
        pos = 41;
        break; // Tuesday
    case 3:
        pos = 51;
        break; // Wednesday
    case 4:
        pos = 61;
        break; // Thursday
    case 5:
        pos = 71;
        break; // Friday
    case 6:
        pos = 81;
        break; // Saturday
    }

    // Display the days of the month
    for (i = 0, j = 10; i < days[nmonth - 1]; i++, pos += 10)
    {
        SetColor(pos == 91 ? 8 : 7); // Dark grey for Sundays, white for others
        gotoxy(pos, j);
        printf("%d", i + 1);
        if (pos == 91)
        {
            pos = 21; // Move to next row (Monday)
            j++;      // Move to the next line
        }
    }

    // Draw the border and navigation symbols
    SetColor(5);
    for (i = 22; i < 102; i++)
    {
        gotoxy(i, 4);
        printf("%c", 196); // Top border
        gotoxy(i, 17);
        printf("%c", 196); // Bottom border
    }

    gotoxy(21, 4);
    printf("%c", 218); // Top-left corner
    gotoxy(102, 4);
    printf("%c", 191); // Top-right corner
    gotoxy(21, 17);
    printf("%c", 192); // Bottom-left corner
    gotoxy(102, 17);
    printf("%c", 217); // Bottom-right corner

    for (i = 5; i < 17; i++)
    {
        gotoxy(21, i);
        printf("%c", 179); // Left border
        gotoxy(102, i);
        printf("%c", 179); // Right border
    }

    // Left and right navigation arrows
    SetColor(11);
    gotoxy(24, 11);
    printf("%c", 174); // Left arrow
    gotoxy(98, 11);
    printf("%c", 175); // Right arrow
}

//============== ARROW KEY HANDLER ===============
// Function to handle arrow and special keys
int getkey()
{
    int ch = getch();
    if (ch == 0)
    {
        ch = getch(); // Fetch the extended key
        return ch;
    }
    return ch; // Return the key pressed
}

//============ CALENDAR FUNCTION =============
// Function to calculate the first day of the month and display the calendar
void calendar(int nyr, int nmonth)
{
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Days per month
    int tdays = 0, k, myear;

    // Clear the screen for a fresh display
    system("cls");

    // Decrease the year by 1 to start calculating days from 1945
    myear = nyr - 1;
    if (myear >= 1945)
    {
        // Count total days from 1945 to the year before the entered year
        for (k = 1945; k <= myear; k++)
        {
            if (k % 4 == 0)   // Leap year check
                tdays += 366; // Add 366 for leap year
            else
                tdays += 365; // Add 365 for non-leap year
        }
    }

    // Adjust February for leap years
    if (nyr % 4 == 0)
        days[1] = 29; // Leap year
    else
        days[1] = 28; // Non-leap year

    // Add days of previous months of the current year
    for (k = 0; k < (nmonth - 1); k++)
    {
        tdays += days[k];
    }

    // Calculate the remainder to find the first day of the month
    tdays = tdays % 7;

    // Display the calculated calendar
    display(nyr, nmonth, tdays, days);
}
