#ifndef ISSUEHISTORY_H
#define ISSUEHISTORY_H

#include <string>

using namespace std;


class IssueHistory
{
    private:
        string issuer;      // issuer email will be stored
        double borrower;    // borrower CNIC will be stored
        double isbn;
        string issue_date;
        string return_date;
    public:
        IssueHistory();
        IssueHistory(string i, double b, double ISBN, string d, string return_d);
        IssueHistory* findRec(double i_isbn, double i_borrower);
        void add_to_file();
        bool remove_from_file(double, double);
        string getReturnDate(){
            return return_date;
        }
        void display(double isbn=0);
        ~IssueHistory();

    protected:


};

#endif // ISSUEHISTORY_H
