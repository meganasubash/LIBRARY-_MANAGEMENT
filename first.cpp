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