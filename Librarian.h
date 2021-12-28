#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include <string>


using namespace std;

class Librarian
{
    private:
        //class data members
        string username;
        string email;
        string password;
        string security_quest;
        string security_ans;
    public:
        //constructor
        Librarian();
        //member functions that defines in librarian.cpp
        bool register_user();
        bool login();
        //udating old record and adding new record
        bool update(string email, Librarian d);
        static Librarian* findRec(string email);
        bool issue_book();
        bool deposit_book();

        
        bool forgot_pass();

        string getUsername();
        string getEmail(){
            //getter
            return email;
        }

        ~Librarian();





};

#endif // LIBRARIAN_H
