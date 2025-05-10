#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    int year;

    Book() : title(""), author(""), year(0) {}
    Book(string t, string a, int y) : title(t), author(a), year(y) {}
};

void printBooks(Book books[], int size, int index = 0) {
    if (index >= size)
        return;
    
    cout << "Title: " << books[index].title << ", Author: " << books[index].author << ", Year: " << books[index].year << endl;
    printBooks(books, size, index + 1);
}

int searchBook(Book books[], int size, const string& title) {
    for (int i = 0; i < size; ++i) {
        if (books[i].title == title)
            return i;
    }
    return -1;
}

void sortBooksByTitle(Book books[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (books[i].title > books[j].title) {
                swap(books[i], books[j]);
            }
        }
    }
}

int binarySearch(Book books[], int left, int right, const string& title) {
    if (left > right)
        return -1;
    
    int mid = left + (right - left) / 2;
    if (books[mid].title == title)
        return mid;
    else if (books[mid].title < title)
        return binarySearch(books, mid + 1, right, title);
    else
        return binarySearch(books, left, mid - 1, title);
}

void addBook(Book books[], int &size, const Book &newBook) {
    books[size++] = newBook;
}

void deleteBook(Book books[], int &size, const string &title) {
    int index = searchBook(books, size, title);
    if (index == -1) {
        cout << "Book not found." << endl;
        return;
    }
    for (int i = index; i < size - 1; ++i) {
        books[i] = books[i + 1];
    }
    --size;
    cout << "Book titled '" << title << "' has been deleted." << endl;
}

struct TreeNode {
    Book book;
    TreeNode* children[10];
    int childCount;

    TreeNode(const Book& b) : book(b), childCount(0) {}
};

void addBookToTree(TreeNode* root, const Book& book) {
    if (root->childCount < 10) {
        root->children[root->childCount++] = new TreeNode(book);
    }
}

void printTree(TreeNode* root) {
    if (!root) return;
    cout << "Title: " << root->book.title << ", Author: " << root->book.author << ", Year: " << root->book.year << endl;
    for (int i = 0; i < root->childCount; ++i) {
        printTree(root->children[i]);
    }
}

struct GraphNode {
    string location;
    string books[10];
    int bookCount;
    GraphNode* adjacent[10];
    int adjCount;

    GraphNode(const string& loc) : location(loc), bookCount(0), adjCount(0) {}
};

void addBookToGraph(GraphNode* node, const string& book) {
    if (node->bookCount < 10) {
        node->books[node->bookCount++] = book;
    }
}

void addEdge(GraphNode* node1, GraphNode* node2) {
    if (node1->adjCount < 10) {
        node1->adjacent[node1->adjCount++] = node2;
    }
    if (node2->adjCount < 10) {
        node2->adjacent[node2->adjCount++] = node1;
    }
}

void printGraph(GraphNode* node) {
    cout << "Location: " << node->location << endl;
    for (int i = 0; i < node->bookCount; ++i) {
        cout << "  Book: " << node->books[i] << endl;
    }
    cout << "Adjacent Locations: ";
    for (int i = 0; i < node->adjCount; ++i) {
        cout << node->adjacent[i]->location << " ";
    }
    cout << endl;
}

size_t hashFunction(const string& title, size_t tableSize) {
    size_t hash = 0;
    for (char ch : title)
        hash += ch;
    return hash % tableSize;
}

class TransactionManager {
public:
    string transactions[100];
    int transactionCount;

    TransactionManager() : transactionCount(0) {}

    void addTransaction(const string& transaction) {
        if (transactionCount < 100) {
            transactions[transactionCount++] = transaction;
        }
    }

    void printTransactions() {
        for (int i = 0; i < transactionCount; ++i) {
            cout << transactions[i] << endl;
        }
    }
};

int main() {
    Book books[100];
    int bookCount = 0;

    TreeNode* root = new TreeNode(Book("Root", "RootAuthor", 0));

    GraphNode* shelf1 = new GraphNode("Shelf1");
    GraphNode* shelf2 = new GraphNode("Shelf2");
    GraphNode* shelf3 = new GraphNode("Shelf3");

    addEdge(shelf1, shelf2);
    addEdge(shelf2, shelf3);

    const size_t tableSize = 10;
    string hashTable[tableSize][10];
    int hashCounts[tableSize] = {0};

    TransactionManager manager;

    while (true) {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Delete Book" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Display All Books" << endl;
        cout << "5. Display Tree" << endl;
        cout << "6. Display Graph" << endl;
        cout << "7. Display Transactions" << endl;
        cout << "8. Exit" << endl;
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string title, author;
            int year;
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter book year: ";
            cin >> year;

            Book newBook(title, author, year);
            addBook(books, bookCount, newBook);
            addBookToTree(root, newBook);
            addBookToGraph(shelf1, title); 

            size_t hashIndex = hashFunction(title, tableSize);
            if (hashCounts[hashIndex] < 10) {
                hashTable[hashIndex][hashCounts[hashIndex]++] = title;
            }

            manager.addTransaction("Added book titled '" + title + "'");
        }
        else if (choice == 2) {
            string title;
            cout << "Enter book title to delete: ";
            cin.ignore();
            getline(cin, title);

            deleteBook(books, bookCount, title);
            manager.addTransaction("Deleted book titled '" + title + "'");
        }
        else if (choice == 3) {
            string title;
            cout << "Enter book title to search: ";
            cin.ignore(); 
            getline(cin, title);

            int index = searchBook(books, bookCount, title);
            if (index != -1) {
                cout << "Book found: Title: " << books[index].title << ", Author: " << books[index].author << ", Year: " << books[index].year << endl;
            } else {
                cout << "Book not found." << endl;
            }
        }
        else if (choice == 4) {
            cout << "All Books in the Library:" << endl;
            sortBooksByTitle(books, bookCount);
            printBooks(books, bookCount);
        }
        else if (choice == 5) {
            cout << "Books in Tree:" << endl;
            printTree(root);
        }
        else if (choice == 6) {
            cout << "Books in Graph:" << endl;
            printGraph(shelf1);
            printGraph(shelf2);
            printGraph(shelf3);
        }
        else if (choice == 7) {
            cout << "Transaction History:" << endl;
            manager.printTransactions();
        }
        else if (choice == 8) {
            break;
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
