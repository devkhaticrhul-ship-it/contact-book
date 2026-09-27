
#ifndef CONTACTS_H
#define CONTACTS_H

#define MAX_CONTACTS 500

typedef struct
{
    int id;
    char name[100];
    char phone[20];
    char email[100];
    char address[200];
} Contact;

/* Load and save contacts */
void loadContacts(void);
void saveContacts(void);

/* Contact operations */
void addContact(void);
void viewContacts(void);
void searchContact(void);
void updateContact(void);
void deleteContact(void);

/* Display utility */
void displayContact(Contact c);

#endif