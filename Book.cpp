#include <iostream>
#include <string>

using namespace std;

// -----------------------------
// Book Class
// -----------------------------
class Book
{
public:
  int id;
  string title, author;
  bool available;

  Book(int id, string title, string author)
      : id(id), title(title), author(author), available(true) {}

  bool borrow()
  {
    if (!available)
      return false;
    available = false;
    return true;
  }

  void returnBack()
  {
    available = true;
  }
};

// -----------------------------
// Book Node and List
// -----------------------------
class BookNode
{
public:
  Book *book;
  BookNode *next;

  BookNode(Book *book) : book(book), next(nullptr) {}
};

class BookList
{
private:
  BookNode *head;

public:
  BookList() : head(nullptr) {}

  void add(Book *book)
  {
    BookNode *newNode = new BookNode(book);
    newNode->next = head;
    head = newNode;
  }

  void remove(int id)
  {
    BookNode *current = head, *prev = nullptr;
    while (current)
    {
      if (current->book->id == id)
      {
        if (prev)
          prev->next = current->next;
        else
          head = current->next;
        delete current->book;
        delete current;
        return;
      }
      prev = current;
      current = current->next;
    }
  }

  Book *find(int id)
  {
    for (BookNode *current = head; current; current = current->next)
    {
      if (current->book->id == id)
        return current->book;
    }
    return nullptr;
  }

  void search(const string &term)
  {
    for (BookNode *current = head; current; current = current->next)
    {
      if (current->book->title.find(term) != string::npos ||
          current->book->author.find(term) != string::npos)
      {
        cout << "Found Book:\n"
             << "ID: " << current->book->id << "\n"
             << "Title: " << current->book->title << "\n"
             << "Author: " << current->book->author << "\n\n";
      }
    }
  }

  ~BookList()
  {
    while (head)
    {
      BookNode *temp = head;
      head = head->next;
      delete temp->book;
      delete temp;
    }
  }
};

// -----------------------------
// User Node and List
// -----------------------------
class UserNode
{
public:
  int id;
  string name;
  UserNode *next;

  UserNode(int id, string name) : id(id), name(name), next(nullptr) {}
};

class UserList
{
private:
  UserNode *head;

public:
  UserList() : head(nullptr) {}

  void add(int id, const string &name)
  {
    UserNode *newNode = new UserNode(id, name);
    newNode->next = head;
    head = newNode;
  }

  UserNode *find(int id)
  {
    for (UserNode *current = head; current; current = current->next)
    {
      if (current->id == id)
        return current;
    }
    return nullptr;
  }

  ~UserList()
  {
    while (head)
    {
      UserNode *temp = head;
      head = head->next;
      delete temp;
    }
  }
};

// -----------------------------
// Queue (Waiting List)
// -----------------------------
class Queue
{
private:
  struct QueueNode
  {
    int id;
    string name;
    QueueNode *next;

    QueueNode(int id, string name) : id(id), name(name), next(nullptr) {}
  };

  QueueNode *front;
  QueueNode *rear;

public:
  Queue() : front(nullptr), rear(nullptr) {}

  void enqueue(int id, const string &name)
  {
    QueueNode *newNode = new QueueNode(id, name);
    if (!rear)
      front = rear = newNode;
    else
    {
      rear->next = newNode;
      rear = newNode;
    }
  }

  void dequeue()
  {
    if (!front)
      return;
    QueueNode *temp = front;
    front = front->next;
    if (!front)
      rear = nullptr;
    delete temp;
  }

  bool isEmpty() const
  {
    return front == nullptr;
  }

  ~Queue()
  {
    while (front)
      dequeue();
  }
};

// -----------------------------
// Stack (Borrow History)
// -----------------------------
class Stack
{
private:
  struct StackNode
  {
    Book *book;
    StackNode *next;

    StackNode(Book *book) : book(book), next(nullptr) {}
  };

  StackNode *top;

public:
  Stack() : top(nullptr) {}

  void push(Book *book)
  {
    StackNode *newNode = new StackNode(book);
    newNode->next = top;
    top = newNode;
  }

  Book *pop()
  {
    if (!top)
      return nullptr;
    StackNode *temp = top;
    Book *book = temp->book;
    top = top->next;
    delete temp;
    return book;
  }

  bool isEmpty() const
  {
    return top == nullptr;
  }

  ~Stack()
  {
    while (top)
    {
      StackNode *temp = top;
      top = top->next;
      delete temp;
    }
  }
};

// -----------------------------
// Library System
// -----------------------------
class Library
{
private:
  BookList books;
  UserList users;
  Queue waitingList;

public:
  void addBook(int id, const string &title, const string &author)
  {
    books.add(new Book(id, title, author));
  }

  void deleteBook(int id)
  {
    books.remove(id);
  }

  void searchBook(const string &term)
  {
    books.search(term);
  }

  void registerUser(int id, const string &name)
  {
    users.add(id, name);
  }

  UserNode *findUser(int id)
  {
    return users.find(id);
  }
};

// -----------------------------
// Main Function
// -----------------------------
int main()
{
  Library library;
  int choice;

  while (true)
  {
    cout << "\n===== Library Menu =====\n";
    cout << "1. Add Book\n";
    cout << "2. Delete Book\n";
    cout << "3. Search Book\n";
    cout << "4. Register User\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      int id;
      string title, author;
      cout << "Enter Book ID: ";
      cin >> id;
      cin.ignore(); // Clear input buffer
      cout << "Enter Book Title: ";
      getline(cin, title);
      cout << "Enter Author: ";
      getline(cin, author);
      library.addBook(id, title, author);
      cout << "Book added successfully.\n";
      break;
    }

    case 2:
    {
      int id;
      cout << "Enter Book ID to delete: ";
      cin >> id;
      library.deleteBook(id);
      cout << "Book deleted if found.\n";
      break;
    }

    case 3:
    {
      string term;
      cin.ignore(); // Clear input buffer
      cout << "Enter search term (title or author): ";
      getline(cin, term);
      library.searchBook(term);
      break;
    }

    case 4:
    {
      int id;
      string name;
      cout << "Enter User ID: ";
      cin >> id;
      cin.ignore(); // Clear input buffer
      cout << "Enter User Name: ";
      getline(cin, name);
      library.registerUser(id, name);
      cout << "User registered successfully.\n";
      break;
    }

    case 5:
    {
      cout << "Exiting program.\n";
      return 0;
    }

    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}
