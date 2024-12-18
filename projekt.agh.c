#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 30

typedef struct {
    int id;
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int available;
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

// --- Pomocnicze funkcje ---
void clearInputBuffer() {
    while (getchar() != '\n');
}

void getInput(char *prompt, char *input, int length) {
    printf("%s", prompt);
    fgets(input, length, stdin);
    input[strcspn(input, "\n")] = '\0'; // Usuwa now¹ liniê
}

// --- Funkcje zarz¹dzania ksi¹¿kami ---
Book *findBookById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) return &library[i];
    }
    return NULL;
}

void addBook(int id, const char *title, const char *author) {
    if (bookCount >= MAX_BOOKS) {
        printf("The library is full!\n");
        return;
    }
    if (findBookById(id)) {
        printf("ID already exists! Please use a unique ID.\n");
        return;
    }
    library[bookCount] = (Book) {id, "", "", 1}; // Tworzy now¹ ksi¹¿kê
    strncpy(library[bookCount].title, title, TITLE_LENGTH);
    strncpy(library[bookCount].author, author, AUTHOR_LENGTH);
    bookCount++;
}

void listBooks() {
    printf("\nList of books in the library:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Available: %s\n",
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].available ? "Yes" : "No");
    }
}

void borrowBook(int id) {
    Book *book = findBookById(id);
    if (book) {
        if (book->available) {
            book->available = 0;
            printf("The book '%s' has been borrowed.\n", book->title);
        } else {
            printf("The book '%s' is already borrowed.\n", book->title);
        }
    } else {
        printf("The book with ID %d does not exist.\n", id);
    }
}

void returnBook(int id) {
    Book *book = findBookById(id);
    if (book) {
        if (!book->available) {
            book->available = 1;
            printf("The book '%s' has been returned.\n", book->title);
        } else {
            printf("The book '%s' is already in the library.\n", book->title);
        }
    } else {
        printf("The book with ID %d does not exist.\n", id);
    }
}

void updateBook(int id) {
    Book *book = findBookById(id);
    if (book) {
        getInput("Enter new title: ", book->title, TITLE_LENGTH);
        getInput("Enter new author: ", book->author, AUTHOR_LENGTH);
        printf("The book has been updated.\n");
    } else {
        printf("The book with ID %d does not exist.\n", id);
    }
}

void addNewBookToLibrary() {
    int id;
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];

    printf("Enter the ID for the new book: ");
    scanf("%d", &id);
    clearInputBuffer();

    if (findBookById(id)) {
        printf("ID already exists! Please use a unique ID.\n");
        return;
    }

    getInput("Enter the title of the new book: ", title, TITLE_LENGTH);
    getInput("Enter the author of the new book: ", author, AUTHOR_LENGTH);

    addBook(id, title, author);
    printf("The book '%s' by %s has been added to the library.\n", title, author);
}

void removeBook(int id) {
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            found = 1;
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            printf("The book with ID %d has been removed from the library.\n", id);
            break;
        }
    }
    if (!found) {
        printf("The book with ID %d does not exist.\n", id);
    }
}

// --- Funkcja g³ówna i obs³uga menu ---
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. List books\n");
    printf("2. Borrow a book\n");
    printf("3. Return a book\n");
    printf("4. Add a new book\n");
    printf("5. Remove a book\n");
    printf("6. Update a book\n");
    printf("7. Exit\n");
}

void handleMenuChoice(int choice) {
    int id;
    switch (choice) {
        case 1:
            listBooks();
            break;
        case 2:
            printf("Enter the ID of the book to borrow: ");
            scanf("%d", &id);
            borrowBook(id);
            break;
        case 3:
            printf("Enter the ID of the book to return: ");
            scanf("%d", &id);
            returnBook(id);
            break;
        case 4:
            addNewBookToLibrary();
            break;
        case 5:
            printf("Enter the ID of the book to remove: ");
            scanf("%d", &id);
            removeBook(id);
            break;
        case 6:
            printf("Enter the ID of the book to update: ");
            scanf("%d", &id);
            clearInputBuffer();
            updateBook(id);
            break;
        case 7:
            printf("Goodbye!\n");
            exit(0);
        default:
            printf("Invalid option!\n");
    }
}

int main() {
    addBook(1, "Agresywne Szachy", "Jacob Aagaard");
    addBook(2, "Steve Jobs", "Walter Isaacson");
    addBook(3, "Rok 1984", "George Orwell");
    addBook(4, "W pustyni i w puszczy", "Henryk Sienkiewicz");
    addBook(5, "Ogniem i mieczem", "Henryk Sienkiewicz");
    addBook(6, "Potop", "Henryk Sienkiewicz");
    addBook(7, "Zbrodnia i kara", "Fiodor Dostojewski");
    addBook(8, "Przedwiosnie", "Stefan Zeromski");
    addBook(9, "Antygona", "Sofokles");
    addBook(10, "Pan Tadeusz", "Adam Mickiewicz");

    int choice;
    while (1) {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);
        handleMenuChoice(choice);
    }
}
