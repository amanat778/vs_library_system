#include <iostream>
#include <Member.h>
#include <Librarian.h>
#include <Book.h>
#include <IssueHistory.h>


using namespace std;

Librarian l;
Book b;
Member m;
IssueHistory h;
int main()
{
    int choice = 0;

    cout << "1: Register\n"
        << "2: Login\n"
        << "3: Forgot Password\n"
        << "Enter your choice: ";
    cin >> choice;

    bool success = false;

    switch (choice) {
    case 1:
        success = l.register_user();
        break;
    case 2:
        success = l.login();
        break;
    case 3:
        success = l.forgot_pass();
        break;
    }

    if (!success)
        return 0;
    while (choice != 13) {
        cout << endl;
        cout << "1: Add new Books\n"
            << "2: Add new Members\n"
            << "3: Remove a book\n"
            << "4: Remove a member\n"
            << "5: Issue a book\n"
            << "6: Deposit a book\n"
            << "7: View members accounts\n"
            << "8: View Stock\n"
            << "9: List of books issued to a member\n"
            << "10: Search for a book\n"
            << "11: Update a book record\n"
            << "12: List all pending books\n"
            << "13: Exit"
            << endl;
        cout << "Enter your choice : ";
        cin >> choice;


        switch (choice) {
        case 1:
            b.add_book();
            break;

        case 2:
            m.add_member();
            break;

        case 3:
            b.remove_book();
            break;

        case 4:
            m.remove_member();
            break;

        case 5:
            l.issue_book();
            break;
        case 6:
            l.deposit_book();
            break;

        case 7:

            m.list_all();
            break;

        case 8:
            b.view_stock();
            break;

        case 9:
            double cnic;
            cout << "Enter the CNIC of member: ";
            cin >> cnic;
            h.display(cnic);
            break;

        case 10:
            b.search_book();
            break;

        case 11:
            b.update_book();
            break;
        case 12:
            h.display(0);
            break;

        }
    }





    return 0;
}