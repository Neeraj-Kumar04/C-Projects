#include <stdio.h>
#include <conio.h>

struct emp
{
    int empno;     // Employee number
    char name[50]; // Employee name
    int bpay;      // Basic pay
    int allow;     // Allowances
    int ded;       // Deductions
    int npay;      // Net pay
} e[10];

void main()
{
    int i, n;

    // Display the developer information
    printf("\n\t\tEmployee Payroll System\n");
    printf("\t\tDeveloped by: Neeraj Kumar\n\n");

    // Get the number of employees
    printf("Enter the number of employees (max 10): ");
    scanf("%d", &n);

    if (n > 10)
    {
        printf("Maximum number of employees is 10.\n");
        return;
    }

    // Input employee details
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the employee number: ");
        scanf("%d", &e[i].empno);
        printf("Enter the name: ");
        scanf("%s", e[i].name);
        printf("Enter the basic pay, allowances & deductions: ");
        scanf("%d %d %d", &e[i].bpay, &e[i].allow, &e[i].ded);
        e[i].npay = e[i].bpay + e[i].allow - e[i].ded; // Calculate net pay
    }

    // Display employee payroll details
    printf("\nEmp. No.\tName\t\tBpay\tAllow\tDed\tNpay\n");
    printf("------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%s\t\t%d\t%d\t%d\t%d\n", e[i].empno,
               e[i].name, e[i].bpay, e[i].allow, e[i].ded, e[i].npay);
    }

    getch(); // Pause the program to view the output
}
