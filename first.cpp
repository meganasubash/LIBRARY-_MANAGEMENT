#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <conio.h>
using namespace std;
class Lib
{
public:
    char bookname[100], auname[50], id[20], pub[50];
    int q, B, p;
    Lib()
    {
        strcpy(bookname, "NO Book Name");
        strcpy(auname, "No Author Name");
        strcpy(id, "No Book ID");
        strcpy(pub, "No Book ID");
        q = 0;
        B = 0;
        p = 0;
    }
    void get();
    void student();
    void pass();
    void librarian();
    void password();
    void getdata();     // to get information of book
    void show(int);     // to show information of book
    void booklist(int); // to read the books from a file
    void modify();
    void see(int);
    int branch(int);
    void issue();
    void der(char[], int, int);
    void fine(int, int, int, int, int, int);
};
void Lib::getdata()
{
    int i;
    fflush(stdin); // to remove input buffer
    cout << "\n\t\tEnter the details :-\n";
    cout << "\n\t\tEnter Book's Name : ";
    cin.getline(bookname, 100); // used to store with spaces
    for (i = 0; bookname[i] != '\0'; i++)
    {
        if (bookname[i] >= 'a' && bookname[i] <= 'z')
            bookname[i] -= 32; // converting all lowercase to uppercase
    }
    cout << "\n\t\tEnter Author's Name : ";
    cin.getline(auname, 50);
    cout << "\n\t\tEnter Publication name : ";
    cin.getline(pub, 50);
    cout << "\n\t\tEnter Book's ID : ";
    cin.getline(id, 20);
    cout << "\n\t\tEnter Book's Price : ";
    cin >> p;
    cout << "\n\t\tEnter Book's Quantity : ";
    cin >> q;
}
void Lib::show(int i)
{
    cout << "\n\t\tBook Name : " << bookname << endl;
    cout << "\n\t\tBook's Author Name : " << auname << endl;
    cout << "\n\t\tBook's ID : " << id << endl;
    cout << "\n\t\tBook's Publication : " << pub << endl;
    if (i == 2) // only for librarian
    {
        cout << "\n\t\tBook's Price : " << p << endl;
        cout << "\n\t\tBook's Quantity : " << q << endl;
    }
}
void Lib::booklist(int i)
{
    int b, r = 0;
    system("cls"); // to clear console screen
    // used library stdlib.h;
    b = branch(i);
    system("cls");
    ifstream intf("Booksdata.txt", ios::binary); // This is a C++ standard library class used for reading from files.
    // intf is an object created
    if (!intf)
        cout << "\n\t\tFile Not Found."; // if  if the file cannot be opened for any reason (such as if it does not exist or if there are permission issues), the stream object will be in a "fail" state.
    else
    {
        cout << "\n\t    ************ Book List ************ \n\n";
        intf.read((char *)this, sizeof(*this));
        while (!intf.eof()) // to read till end of book
        {
            if (b == B)
            {
                if (q == 0 && i == 1) // quantity of book is not zero
                {
                }
                else
                {
                    r++;
                    cout << "\n\t\t********** " << r << ". ********** \n";
                    show(i);
                }
            }
            intf.read((char *)this, sizeof(*this));
        }
    }
    cout << "\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    if (i == 1)
        student();
    else
        librarian();
}
void Lib::der(char st[], int b, int x)
{
    int i, cont = 0;
    fstream intf("Booksdata.txt", ios::in | ios::out | ios::ate | ios::binary); // Open a file stream for reading and writing
    intf.seekg(0);                                                              // Move the get pointer to the beginning of the file
    intf.read((char *)this, sizeof(*this));                                     // Read data from the file into the object
    while (!intf.eof())                                                         // Loop until the end of the file is reached
    {
        for (i = 0; b == B && id[i] != '\0' && st[i] != '\0' && st[i] == id[i]; i++)
            ; // Loop through characters of 'id' and 'st' until a mismatch is found or the end of the strings is reached
        if (id[i] == '\0' && st[i] == '\0')
        {
            cont++;
            if (x == 1)
            {
                q--;
            }
            else
            {
                q++;
            }
            intf.seekp(intf.tellp() - sizeof(*this)); // Move the put pointer to the position before the last read/write operation
            intf.write((char *)this, sizeof(*this));  // Write data from the object back to the file
            break;
        }
        intf.read((char *)this, sizeof(*this)); // Read the next record from the file into the object
    }
    if (cont == 0) // If no matching record was found
    {
        cout << "\n\t\tBook not found.\n";
        cout << "\n\n\t\tPress any key to continue.....";
        getch();       // Wait for a key press
        system("cls"); // Clear the screen
        issue();
    }
    intf.close(); // Close the file stream
}
//modify function
void Lib::modify()
{
    char ch, st1[100];
    int i = 0, b, cont = 0;
    system("cls");
    cout << "\n\t\t>>Please Choose one option :-\n";
    cout << "\n\t\t1.Modification In Current Books\n\n\t\t2.Add New Book\n\n\t\t3.Delete A Book\n\n\t\t4.Go back\n";
    cout << "\n\n\t\tEnter your choice : ";
    cin >> i;
    if (i == 1)
    {
        system("cls");
        b = branch(2);
        ifstream intf1("Booksdata.txt", ios::binary); // opening in binary

        if (!intf1)
        {
            cout << "\n\t\tFile Not Found\n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            librarian(); // shows options of librarian cause only librarian can modify books
        }
        intf1.close(); // close text file
        system("cls");
        cout << "\n\t\tPlease Choose One Option :-\n";
        cout << "\n\t\t1.Search By Book Name\n\n\t\t2.Search By Book's ID\n";
        cout << "\n\t\tEnter Your Choice : ";
        cin >> i;
        fflush(stdin);
        if (i == 1) // to search by book name
        {
            system("cls");
            cout << "\n\t\tEnter Book Name : ";
            cin.getline(st1, 100);
            system("cls");
            fstream intf("Booksdata.txt", ios::in | ios::out | ios::ate | ios::binary); // opens the file and the seeker is set to end
            intf.seekg(0);                                                              // seeker set to start of file
            intf.read((char *)this, sizeof(*this));
            while (!intf.eof())
            {
                for (i = 0; b == B && bookname[i] != '\0' && st1[i] != '\0' && (st1[i] == bookname[i] || st1[i] == bookname[i] + 32); i++)
                    ;
                if (bookname[i] == '\0' && st1[i] == '\0')
                {
                    cont++;
                    getdata();
                    intf.seekp(intf.tellp() - sizeof(*this));
                    intf.write((char *)this, sizeof(*this));
                    break;
                }
                intf.read((char *)this, sizeof(*this));
            }
            intf.close();
        }
        else if (i == 2) // to search by id
        {
            cout << "\n\t\tEnter Book's ID : ";
            cin.getline(st1, 100);
            system("cls");
            fstream intf("Booksdata.txt", ios::in | ios::out | ios::ate | ios::binary);
            intf.seekg(0);
            intf.read((char *)this, sizeof(*this));
            while (!intf.eof())
            {
                for (i = 0; b == B && id[i] != '\0' && st1[i] != '\0' && st1[i] == id[i]; i++)
                    ;
                if (id[i] == '\0' && st1[i] == '\0')
                {
                    cont++;
                    getdata();
                    intf.seekp(intf.tellp() - sizeof(*this));
                    intf.write((char *)this, sizeof(*this));
                    break;
                }
                intf.read((char *)this, sizeof(*this));
            }
            intf.close();
        }
        else
        {
            cout << "\n\t\tIncorrect Input.....:(\n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            modify();
        }
        if (cont == 0)
        {
            cout << "\n\t\tBook Not Found.\n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            modify();
        }
        else
            cout << "\n\t\tUpdate Successful.\n"; // end of option one i.e Adding a book
    }
    else if (i == 2)
    {
        system("cls");
        B = branch(2);
        system("cls");
        getdata();
        ofstream outf("Booksdata.txt", ios::app | ios::binary); // appends to end of file
        outf.write((char *)this, sizeof(*this));
        outf.close();
        cout << "\n\t\tBook added Successfully.\n"; // end of book add function
    }
    else if (i == 3)
    {
        system("cls");
        b = branch(2); // only librarian can add
        ifstream intf1("Booksdata.txt", ios::binary);
        if (!intf1)
        {
            cout << "\n\t\tFile Not Found\n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            intf1.close();
            system("cls");
            librarian(); // checking if file exists
        }
        intf1.close(); // closing anyway
        system("cls");
        cout << "\n\t\tPlease Choose One Option for deletion:-\n";
        cout << "\n\t\t1.By Book Name\n\n\t\t2.By Book's ID\n";
        cout << "\n\t\tEnter Your Choice : ";
        cin >> i;
        fflush(stdin);
        if (i == 1)
        {
            system("cls");
            cout << "\n\t\tEnter Book Name : ";
            cin.getline(st1, 100);
            ofstream outf("temp.txt", ios::app | ios::binary); // to duplicate the orignal file
            ifstream intf("Booksdata.txt", ios::binary);
            intf.read((char *)this, sizeof(*this));
            while (!intf.eof())
            {
                for (i = 0; b == B && bookname[i] != '\0' && st1[i] != '\0' && (st1[i] == bookname[i] || st1[i] == bookname[i] + 32); i++)
                    ;
                if (bookname[i] == '\0' && st1[i] == '\0')
                {
                    cont++;
                    intf.read((char *)this, sizeof(*this));
                }
                else
                {
                    outf.write((char *)this, sizeof(*this));
                    intf.read((char *)this, sizeof(*this));
                }
            }
            intf.close();
            outf.close();
            remove("Booksdata.txt");             // deleting orignal file
            rename("temp.txt", "Booksdata.txt"); // changing duplicate into orignal
        }
        else if (i == 2)
        {
            cout << "\n\t\tEnter Book's ID : ";
            cin.getline(st1, 100);
            ofstream outf("temp.txt", ios::app | ios::binary);
            ifstream intf("Booksdata.txt", ios::binary);
            intf.read((char *)this, sizeof(*this));
            while (!intf.eof())
            {
                for (i = 0; b == B && id[i] != '\0' && st1[i] != '\0' && st1[i] == id[i]; i++)
                    ;
                if (id[i] == '\0' && st1[i] == '\0')
                {
                    cont++;
                    intf.read((char *)this, sizeof(*this));
                }
                else
                {
                    outf.write((char *)this, sizeof(*this));
                    intf.read((char *)this, sizeof(*this));
                }
            }
            outf.close();
            intf.close(); // closing both files
            remove("Booksdata.txt");
            rename("temp.txt", "Booksdata.txt");
        }
        else
        {
            cout << "\n\t\tIncorrect Input.....:(\n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            modify();
        }
        if (cont == 0)
        {
            cout << "\n\t\tBook Not Found.\n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            modify();
        }
        else
            cout << "\n\t\tDeletion Successful.\n";
    }
    else if (i == 4) // go back to main menu
    {
        system("cls");
        librarian();
    }
    else
    {
        cout << "\n\t\tWrong Input.\n";
        cout << "\n\t\tPress any key to continue.....";
        getch();
        system("cls");
        modify();
    }
    cout << "\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    librarian(); // going back to librarian page
} // end of modify funciton
