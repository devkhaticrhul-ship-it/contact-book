 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "contacts.h"

#define DATA_FILE "contacts.txt"

static Contact contacts[MAX_CONTACTS];
static int contactCount = 0;
static int nextID = 1;

/* Read a complete line safely */
static void readLine(const char *prompt, char *buffer, int size)
{
    int ch;
    size_t len;

    printf("%s", prompt);

    if (fgets(buffer, size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            /* Clear extra input */
        }
    }
}

/* Convert text to lowercase and compare */
static int containsIgnoreCase(const char *text, const char *pattern)
{
    int i, j;

    if (pattern[0] == '\0')
        return 1;

    for (i = 0; text[i] != '\0'; i++)
    {
        for (j = 0; pattern[j] != '\0'; j++)
        {
            if (text[i + j] == '\0')
                break;

            if (tolower((unsigned char)text[i + j]) !=
                tolower((unsigned char)pattern[j]))
                break;
        }

        if (pattern[j] == '\0')
            return 1;
    }

    return 0;
}

/* Check for characters that would break our file format */
static int validField(const char *text)
{
    int i;

    if (text[0] == '\0')
        return 0;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '|' || text[i] == '\n' || text[i] == '\r')
            return 0;
    }

    return 1;
}

/* Validate phone number */
static int validPhone(const char *phone)
{
    int i, digits = 0;

    for (i = 0; phone[i] != '\0'; i++)
    {
        if (isdigit((unsigned char)phone[i]))
        {
            digits++;
        }
        else if (phone[i] != '+' &&
                 phone[i] != '-' &&
                 phone[i] != ' ' &&
                 phone[i] != '(' &&
                 phone[i] != ')')
        {
            return 0;
        }
    }

    return digits >= 7 && digits <= 15;
}

/* Basic email validation */
static int validEmail(const char *email)
{
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    return at != NULL &&
           dot != NULL &&
           at != email &&
           dot > at + 1 &&
           dot[1] != '\0';
}

/* Find contact by ID */
static int findIndexByID(int id)
{
    int i;

    for (i = 0; i < contactCount; i++)
    {
        if (contacts[i].id == id)
            return i;
    }

    return -1;
}

/* Find contact by phone */
static int findIndexByPhone(const char *phone)
{
    int i;

    for (i = 0; i < contactCount; i++)
    {
        if (strcmp(contacts[i].phone, phone) == 0)
            return i;
    }

    return -1;
}

/* Find next available ID */
static int getNextID(void)
{
    while (findIndexByID(nextID) != -1)
        nextID++;

    return nextID++;
}

/* Load contacts from file */
void loadContacts(void)
{
    FILE *fp = fopen(DATA_FILE, "r");
    char line[600];
    char *token;

    contactCount = 0;
    nextID = 1;

    if (fp == NULL)
        return;

    while (fgets(line, sizeof(line), fp) != NULL &&
           contactCount < MAX_CONTACTS)
    {
        Contact c;

        token = strtok(line, "|\r\n");
        if (token == NULL)
            continue;
        c.id = atoi(token);

        token = strtok(NULL, "|\r\n");
        if (token == NULL)
            continue;
        strcpy(c.name, token);

        token = strtok(NULL, "|\r\n");
        if (token == NULL)
            continue;
        strcpy(c.phone, token);

        token = strtok(NULL, "|\r\n");
        if (token == NULL)
            continue;
        strcpy(c.email, token);

        token = strtok(NULL, "|\r\n");
        if (token == NULL)
            continue;
        strcpy(c.address, token);

        contacts[contactCount++] = c;

        if (c.id >= nextID)
            nextID = c.id + 1;
    }

    fclose(fp);
}

/* Save contacts to file */
void saveContacts(void)
{
    FILE *fp = fopen(DATA_FILE, "w");
    int i;

    if (fp == NULL)
    {
        printf("\nError: Could not save contacts!\n");
        return;
    }

    for (i = 0; i < contactCount; i++)
    {
        fprintf(fp, "%d|%s|%s|%s|%s\n",
                contacts[i].id,
                contacts[i].name,
                contacts[i].phone,
                contacts[i].email,
                contacts[i].address);
    }

    fclose(fp);
}

/* Display one contact */
void displayContact(Contact c)
{
    printf("\n----------------------------------------\n");
    printf("Contact ID : %d\n", c.id);
    printf("Name       : %s\n", c.name);
    printf("Phone      : %s\n", c.phone);
    printf("Email      : %s\n", c.email);
    printf("Address    : %s\n", c.address);
    printf("----------------------------------------\n");
}

/* Add a new contact */
void addContact(void)
{
    Contact c;

    if (contactCount >= MAX_CONTACTS)
    {
        printf("\nContact book is full!\n");
        return;
    }

    printf("\n========== ADD CONTACT ==========\n");

    readLine("Enter full name: ", c.name, sizeof(c.name));

    if (!validField(c.name))
    {
        printf("Invalid name. Name cannot be empty or contain '|'.\n");
        return;
    }

    readLine("Enter phone number: ", c.phone, sizeof(c.phone));

    if (!validPhone(c.phone))
    {
        printf("Invalid phone number. Use 7-15 digits.\n");
        return;
    }

    if (findIndexByPhone(c.phone) != -1)
    {
        printf("This phone number already exists!\n");
        return;
    }

    readLine("Enter email: ", c.email, sizeof(c.email));

    if (!validField(c.email) || !validEmail(c.email))
    {
        printf("Invalid email address.\n");
        return;
    }

    readLine("Enter address: ", c.address, sizeof(c.address));

    if (!validField(c.address))
    {
        printf("Invalid address.\n");
        return;
    }

    c.id = getNextID();
    contacts[contactCount++] = c;

    saveContacts();

    printf("\nContact added successfully!\n");
    printf("Assigned Contact ID: %d\n", c.id);
}

/* View all contacts */
void viewContacts(void)
{
    int i;

    printf("\n========== ALL CONTACTS ==========\n");

    if (contactCount == 0)
    {
        printf("No contacts found. Add a contact first.\n");
        return;
    }

    printf("Total contacts: %d\n", contactCount);

    for (i = 0; i < contactCount; i++)
    {
        displayContact(contacts[i]);
    }
}

/* Search contacts by name or phone */
void searchContact(void)
{
    char query[100];
    int i, found = 0;

    printf("\n========== SEARCH CONTACT ==========\n");

    readLine("Enter name or phone to search: ",
             query, sizeof(query));

    if (query[0] == '\0')
    {
        printf("Search query cannot be empty.\n");
        return;
    }

    for (i = 0; i < contactCount; i++)
    {
        if (containsIgnoreCase(contacts[i].name, query) ||
            strstr(contacts[i].phone, query) != NULL)
        {
            displayContact(contacts[i]);
            found = 1;
        }
    }

    if (!found)
        printf("\nNo matching contacts found.\n");
}

/* Update an existing contact */
void updateContact(void)
{
    int id, index;
    char input[200];

    printf("\n========== UPDATE CONTACT ==========\n");

    printf("Enter Contact ID to update: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    index = findIndexByID(id);

    if (index == -1)
    {
        printf("Contact ID not found.\n");
        return;
    }

    displayContact(contacts[index]);

    printf("\nLeave a field blank to keep its current value.\n");

    readLine("New name: ", input, sizeof(input));

    if (input[0] != '\0')
    {
        if (!validField(input))
        {
            printf("Invalid name. Update cancelled.\n");
            return;
        }

        strcpy(contacts[index].name, input);
    }

    readLine("New phone: ", input, sizeof(input));

    if (input[0] != '\0')
    {
        int existing = findIndexByPhone(input);

        if (!validPhone(input) ||
            (existing != -1 && existing != index))
        {
            printf("Invalid or duplicate phone. Update cancelled.\n");
            return;
        }

        strcpy(contacts[index].phone, input);
    }

    readLine("New email: ", input, sizeof(input));

    if (input[0] != '\0')
    {
        if (!validField(input) || !validEmail(input))
        {
            printf("Invalid email. Update cancelled.\n");
            return;
        }

        strcpy(contacts[index].email, input);
    }

    readLine("New address: ", input, sizeof(input));

    if (input[0] != '\0')
    {
        if (!validField(input))
        {
            printf("Invalid address. Update cancelled.\n");
            return;
        }

        strcpy(contacts[index].address, input);
    }

    saveContacts();

    printf("\nContact updated successfully!\n");
}

/* Delete a contact */
void deleteContact(void)
{
    int id, index, i;
    char confirm[10];

    printf("\n========== DELETE CONTACT ==========\n");

    printf("Enter Contact ID to delete: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    index = findIndexByID(id);

    if (index == -1)
    {
        printf("Contact ID not found.\n");
        return;
    }

    displayContact(contacts[index]);

    readLine("Are you sure you want to delete? (y/n): ",
             confirm, sizeof(confirm));

    if (tolower((unsigned char)confirm[0]) != 'y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    for (i = index; i < contactCount - 1; i++)
    {
        contacts[i] = contacts[i + 1];
    }

    contactCount--;

    saveContacts();

    printf("\nContact deleted successfully!\n");
}