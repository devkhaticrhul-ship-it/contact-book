
#include <stdio.h>
#include <stdlib.h>
#include "contacts.h"

#ifdef _WIN32
#include <windows.h>
#endif

/* Display application banner */
void showBanner(void)
{
    printf("\n");
    printf("============================================\n");
    printf("              CONTACT//VAULT                \n");
    printf("        YOUR CONTACTS. ORGANIZED.           \n");
    printf("============================================\n");
}

/* Display main menu */
void showMenu(void)
{
    printf("\n");
    printf("============== MAIN MENU ==============\n");
    printf("  1. Add Contact\n");
    printf("  2. View All Contacts\n");
    printf("  3. Search Contact\n");
    printf("  4. Update Contact\n");
    printf("  5. Delete Contact\n");
    printf("  6. Exit\n");
    printf("=======================================\n");
    printf("Enter your choice: ");
}

/* Pause until user presses Enter */
void pauseScreen(void)
{
    printf("\nPress Enter to continue...");
    getchar();
}

int main(void)
{
    int choice;
    int ch;

    #ifdef _WIN32
    SetConsoleTitle("CONTACT//VAULT - Contact Management System");
    #endif

    loadContacts();

    showBanner();

    printf("\nWelcome to CONTACT//VAULT!\n");
    printf("Your personal contact management system.\n");

    while (1)
    {
        showMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
                /* Clear invalid input */
            }

            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            /* Clear extra input */
        }

        switch (choice)
        {
            case 1:
                addContact();
                pauseScreen();
                break;

            case 2:
                viewContacts();
                pauseScreen();
                break;

            case 3:
                searchContact();
                pauseScreen();
                break;

            case 4:
                updateContact();
                pauseScreen();
                break;

            case 5:
                deleteContact();
                pauseScreen();
                break;

            case 6:
                printf("\nSaving contacts...\n");
                saveContacts();

                printf("Thank you for using CONTACT//VAULT!\n");
                printf("Goodbye!\n");

                return 0;

            default:
                printf("\nInvalid choice! Select 1 to 6.\n");
                pauseScreen();
        }
    }

    return 0;
}