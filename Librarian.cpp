#define _CRT_SECURE_NO_WARNINGS
//header files
#include "Librarian.h"
#include <Member.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Book.h>
#include <ctime>
#include <IssueHistory.h>

using namespace std;
//helper function defines below in the code
string input_pass();
//defualt construrctor 
Librarian::Librarian()
{

}
//getter
string Librarian::getUsername(){
    return username;
}

//array of securoty questions
string security_quests[3]={
    "What was your first shool name?",
    "What is your pet name?",
    "What is the name of your favourite teacher?"
};

bool Librarian::register_user(){
    cout << endl;
    //stores password
    string p1, p2;
    cin.ignore();
    cout << "Enter user name: ";
    getline(cin, username);

    cout << "Enter email: ";
    cin >> email;
    //if record already exists
    if(findRec(email)!=NULL){
        int choice;
        cout << "An account with this email already exist. \n"
             << "1: Login\n"
             << "2: Forgot Password\n"
             << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
            return login();
        else return forgot_pass();
    }

    cout << endl;
    //for loop to print array of questions
    for(int i=0; i<3; ++i)
        cout <<i+1 << " " <<security_quests[i] << endl;
    //chooses security question
    int choice;
    cout << "Choose your security question :  ";
    cin >> choice;
    security_quest= security_quests[choice-1];
    //print answer of security questions
    cin.ignore();
    cout << "Enter answer of the question: ";

    getline(cin, security_ans);




    //entering password twice
    do{
        cout << "ONLY CHARACTER AND NUMBERS ARE ALLOWED IN PASSWORD." << endl;
        cout << "Enter password :";
        p1= input_pass();

        cout << "Enter password again:";
        p2=input_pass();
        if(p1!=p2)
            cout << "Password mismatch. Enter again." << endl;
    }while(p1!=p2);
    password=p1;





    // writinng file
    ofstream o_accounts("accounts.txt", ios::app);
    o_accounts << username+"\t"+email+"\t"+password+"\t"+security_quest+"\t"+security_ans+"\n";
    o_accounts.close();
    //account has been created
    cout << "Your account has been created. You are now logged in as \"" << username << "\""<< endl;
    return true;
}
//printing password in ****
string input_pass(){
    string p;

    char temp;
    do{

        temp= _getch();
        if( ( temp>='a' && temp <='z') || (temp>='A' && temp <='Z') || (temp>='0' && temp <='9')){
            p+=temp;
            _putch('*');
        }
        if( int(temp) == 8 && p.size()>0 ){
            cout << "\b \b";
            p= p.substr(0, p.size()-1);
        }
    }while( temp!= '\r');

    cout << endl;

    return p;
}
string* split_string( string str, char c, int& length){
    string temp=str;
    temp+=c;
    length = 0;
    while(temp.find(c)!=string::npos){
        length++;
        temp= temp.substr(temp.find(c)+1);
    }

    string *words= new string[length];

    for( int i=0;i< length; ++i){
        words[i]= str.substr(0, str.find(c));
        str= str.substr(str.find(c)+1);
    }


    return words;
}

bool Librarian::forgot_pass(){
    cout << endl;
    string email;
    cout << "Enter your email address : ";
    cin >> email;

    Librarian* rec= findRec(email);

    string answer;
    cout << rec->security_quest << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin,answer);


    if(rec->security_ans== answer){
        string p1, p2;
        do{
            cout << "ONLY CHARACTER AND NUMBERS ARE ALLOWED IN PASSWORD." << endl;

            cout << "Enter new password: ";
            p1= input_pass();

            cout << "Enter new password again: ";
            p2= input_pass();

            if(p1!=p2)
                cout << "Password did not match. Enter again. " << endl;
        }while(p1!=p2);

        rec->password= p1;
        update(email, *rec);
        cout << "Your password has been updated successfully. You can now login. " << endl;
        return login();

    }

    cout << "Your entered the wrong answer. " << endl;
    return false;

}


bool Librarian::update(string email, Librarian d){
    string newContent="";
    ifstream accounts;
    accounts.open("accounts.txt");


    string account_info;

    while(getline(accounts, account_info)){
        char delimiter='\t';

        int l;
        string *fields= split_string(account_info, '\t', l);
        string f_email=fields[1];

        delete [] fields;
        if(email==f_email)
                account_info= d.username+"\t"+d.email+"\t"+d.password+"\t"+d.security_quest+"\t"+d.security_ans;



        newContent+=account_info+"\n";


    }

    ofstream o_accounts("accounts.txt");

    o_accounts << newContent;
    return true;
}
bool Librarian::login(){
    cout << endl;
    cout << "Enter email: ";
    cin >> email;


    cout << "ONLY CHARACTER AND NUMBERS ARE ALLOWED IN PASSWORD." << endl;
    cout << "Enter password: ";
    cin.ignore();
    //getline(cin, password);
    password= input_pass();

    Librarian* rec=findRec(email);




    if(rec && rec->password == password ){
        username= rec->username;
        security_quest= rec->security_quest;
        security_ans= rec->security_ans;
        cout << "You are now logged in as \"" << username << "\"" << endl;

        return true;
    };

    if(rec==NULL)
        cout << "This email is not registered. Login Again(y/n):  ";
    else if(rec->password!= password)
        cout << "Password did not match. Login Again(y/n): ";

    char choice;
    cin >> choice;
    if(choice=='y' || choice=='Y'){
        return login();
    }

    return false;
};


Librarian* Librarian::findRec(string email){
    Librarian* rec= new Librarian();
    ifstream accounts;
    accounts.open("accounts.txt");


    string account_info;

    while(getline(accounts, account_info)){
        int l=0;
        string *fields= split_string(account_info, '\t', l);
        rec->username= fields[0];
        rec->email=fields[1];
        rec->password=fields[2];
        rec->security_quest=fields[3];
        rec->security_ans= fields[4];
        delete [] fields;

        if(email==rec->email)
                return rec;


    }
    return NULL;

}

bool Librarian::issue_book(){
    double isbn, CNIC;
    cout << "Enter the ISBN number of book you want to issue: ";
    cin >> isbn;

    if (Book::findRec(isbn) == NULL) {
        cout << "Sorrry no book with this ISBN number exists. " << endl;
        return false;
    }

    cout << "Enter the CNIC of borrower: ";
    cin >> CNIC;


    Book *b   = Book::findRec(isbn);
    Member *m = Member::findRec(CNIC);

    if(b==NULL){
        char choice;
        cout << "No book with this ISBN number. Enter again(y/n): " << endl;
        cin >> choice;

        if(choice=='y' || choice=='Y')
            return issue_book();

        return false;
    }

    if(m==NULL){
        char choice;
        cout << "No Member with this CNIC number. Enter again(y/n): " << endl;
        cin >> choice;

        if(choice=='y' || choice=='Y')
            return issue_book();

        return false;
    }
    if(m->getN()>=5){
        cout << "This member already has five books issued." << endl;
        return false;
    }

    b->decrement_qty();
    m->increment_n();
    Book::update(isbn, *b);
    Member::update(CNIC, *m);

    time_t sec;
    time(&sec);     //filling sec variable
    tm *time;

    time=localtime(&sec);

    string issue_date = to_string(sec);

     
    sec+= 2;     // adding 30 days
    time= localtime(&sec);
    string return_date=to_string(time->tm_mon+1)+":";
    return_date+= to_string(time->tm_mday )+ ":";
    return_date+= to_string(time->tm_year+1900);

    IssueHistory h(email, CNIC, isbn, issue_date, to_string(sec));
    h.add_to_file();
    cout << "Return date is " << return_date << endl;
    cout << "Book has been issued successfully. " << endl;

    return true;
}


bool Librarian::deposit_book(){
    cout << endl;
    int fine_per_day= 100;
    double isbn, cnic;
    cout << "Enter the ISBN of book: ";
    cin >> isbn;

    cout << "Enter the CNIC of borrower: ";
    cin >> cnic;

    IssueHistory h;
    h.remove_from_file(isbn, cnic);
    IssueHistory *rec= h.findRec(isbn, cnic);

    if(rec==NULL){
        cout << "No such book was issued. " << endl;
        return false;
    }




    
    time_t sec = stod(rec->getReturnDate());

    time_t now;
    time(&now);
    double sec_per_day= 2;
    float late_days=(now-sec)/sec_per_day ;
    if(late_days<0) late_days=0;
    cout << "Fine is : " << late_days*fine_per_day << " rupees"<< endl;

    Book *b = Book::findRec(isbn);
    Member *m = Member::findRec(cnic);
    b->increment_qty();
    m->decrement_n();
    Book::update(isbn, *b);
    Member::update(cnic, *m);

    cout << "Book has been deposited successfully" << endl;
    return true;
}

Librarian::~Librarian()
{
    //dtor
}
