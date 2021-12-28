#include "IssueHistory.h"
#include <fstream>
#include <Book.h>
#include <iostream>
#include <iomanip>
#include <Librarian.h>
#include <Member.h>


using namespace std;

IssueHistory::IssueHistory(){
}

IssueHistory::IssueHistory(string i, double b, double ISBN, string d, string return_d)
{
    issuer=i;
    borrower=b;
    isbn= ISBN;
    issue_date=d;
    return_date= return_d;

    //ctor
}

void IssueHistory::add_to_file(){
    ofstream file("issue_history.txt", ios::app);

    string s_isbn= to_string(isbn);
    s_isbn= s_isbn.substr(0, s_isbn.find('.'));

    string s_borrower= to_string(borrower);
    s_borrower= s_borrower.substr(0, s_borrower.find('.'));
    file << endl;
    file << issuer + '\t' + s_borrower + '\t' + s_isbn +'\t'+issue_date+'\t'+return_date;
}

void IssueHistory::display(double cnic){
    ifstream file("issue_history.txt");

    while(!file.eof()){
        file >> issuer >> borrower >> isbn >> issue_date >> return_date;
        if(cnic==0 || borrower==cnic){
            Book *b=Book::findRec(isbn);
            Librarian *l=Librarian::findRec(issuer);
            Member *m= Member::findRec(borrower);

            string heading="BOOK DETAILS";
            cout << string(60-heading.size()/2, ' ')  << heading << endl;
            cout << string(120,'-') << endl;
            cout << setw(35) << left << "Title"
                 << setw(45) << left << "Authors"
                 << setw(20) << left << "ISBN"
                 << setw(8)  << left << "Quantity" << endl;
            cout << string(120,'-') << endl;
            b->display_row();

            cout << endl;
            cout << endl;
            cout << string(120,'_') << endl;

            heading="ISSUER/BORROWER DETAILS";
            cout << string(60-heading.size()/2, ' ')  << heading << endl;
            cout << string(120,'-') << endl;
            cout << setw(20) << left << "Issuer Name"
                 << setw(20) << left << "Issuer Email"
                 << setw(20) << left << "Borrower Name"
                 << setw(20) << left << "Borrower CNIC"
                 << setw(20) << left << "Issue Date"
                 << setw(20) << left << "Return Date" << endl;
            cout << string(120,'-') << endl;

            cout << setw(20) << left << l->getUsername()
                 << setw(20) << left << l->getEmail()
                 << setw(20) << left << m->getName()
                 << setw(20) << left << m->getCNIC()
                 << setw(20) << left << issue_date
                 << setw(20) << left << return_date << endl;

            cout << string(120, '=') << endl;
            cout << endl;
            cout << endl;
        }




    }

}

bool IssueHistory::remove_from_file(double i_isbn, double i_borrower){


    string newContent="";
    ifstream file("issue_history.txt");
    bool found=false;

    while(!file.eof()){
        file >> issuer >> borrower >> isbn >> issue_date >> return_date;
        if(borrower==i_borrower && i_isbn==isbn && !found)
            found=true;
        else{
            string s_borrower= to_string(borrower);
            s_borrower= s_borrower.substr(0, s_borrower.find('.'));
            string s_isbn= to_string(isbn);
            s_isbn= s_isbn.substr(0, s_isbn.find('.'));

            newContent+=issuer+'\t'+s_borrower+'\t'+s_isbn+'\t'+issue_date+'\t'+return_date+'\n';
        }


    }
    if(!found){
        cout << "No record with this ISBN and CNIC." << endl;
        return false;
    }


    ofstream o_file("issue_history.txt");

    o_file<< newContent.substr(0, newContent.size()-1);

    return true;

}


IssueHistory* IssueHistory::findRec(double i_isbn, double i_borrower){
    string newContent="";
    ifstream file("issue_history.txt");
    while(!file.eof()){
        file >> issuer >> borrower >> isbn >> issue_date >> return_date;
        if(borrower==i_borrower && i_isbn==isbn)
            return this;
    }

    return NULL;

}
IssueHistory::~IssueHistory()
{
    //dtor
}
