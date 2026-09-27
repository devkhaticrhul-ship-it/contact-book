
# CONTACT//VAULT
### Your Contacts. Organized.

CONTACT//VAULT is a console-based Contact Management
System developed using the C programming language.

It allows users to store, search, update, view, and
delete contacts through a simple interactive interface.

## Features

- Add contacts with name, phone, email, and address
- View all saved contacts
- Search contacts by name or phone number
- Update existing contact details
- Delete contacts with confirmation
- Persistent local storage using file handling
- Input validation and duplicate phone prevention
- Automatically assigns contact IDs

## Technologies Used

- C Programming Language
- GCC Compiler
- Standard C Libraries
- File Handling
- Structures and Arrays

## Project Structure

main.c       - Main menu and program entry
contacts.c   - Contact management functions
contacts.h   - Structure and function declarations
contacts.txt - Local contact database (generated at runtime)

## How to Compile

Install GCC and open the project folder in your terminal.

Compile the program:

```bash
gcc main.c contacts.c -o contactvault.exe
```

Run on Windows:

```cmd
contactvault.exe
```

## Data Storage

Contacts are stored locally in contacts.txt.
The file is created automatically when the program runs.

The personal database is excluded from version control
to prevent accidental publication of private contacts.

## Author

Rahul Kumar

## License

This project is available under the MIT License.