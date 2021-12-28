#include "Member.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Member::Member(){

}          

double Member::getCNIC(){
    return CNIC;
}

bool Member::add_member(){
    cout << endl;

    do{
        cout << "Enter the CNIC: ";
        cin >> CNIC;
        if(!(CNIC>=1000000000000 && CNIC<=9999999999999))
            cout << "CNIC must be 13 digits. Enter again." << endl;
    }while(!(CNIC>=1000000000000 && CNIC<=9999999999999));

    if(findRec(CNIC)!=NULL){
        char choice;
        cout << "A member with this CNIC already exist.Do you want to enter again(y/n): ";
        cin >> choice;

        if(choice=='y' || choice=='Y')
            return add_member();

        return false;
    }

    cout << "ONLY ALPHANUMERIC CHARACTERS AND \"/\" IS ALLOWED" << endl;

    cout << "Enter the reg no (i.e 1234/FBAS/BSSE/F20): ";
    cin.ignore();
    getline(cin,regNo);

    for(int i=0; i<regNo.size(); ++i){
        char temp= regNo[i];
        if(!(( temp>='a' && temp <='z') || (temp>='A' && temp <='Z') || (temp>='0' && temp <='9') || temp=='/')){
            cout << "Invalid reg no. Enter again."<< endl;
            add_member();
        }

    }



    cout << "Enter the name: ";
    cin.ignore();
    getline(cin, name);

    // setting n to zero as number of books issued in start will be zero
    n=0;

    ofstream file("members.txt", ios::app);
    string s_cnic=to_string(CNIC);
    s_cnic= s_cnic.substr(0, s_cnic.find('.'));
    file << regNo+"\t"+s_cnic+"\t"+name+"\t"+to_string(n) << endl;
    cout << "Record has been added successfully." << endl;
    return true;
}
string* split_string( string str, char c, int& length);

bool Member::remove_member(){

    cout << "Enter the CNIC of member you want to remove: ";
    cin >> CNIC;

    if(findRec(CNIC)==NULL){
        char choice;
        cout << "No record with CNIC. Try again(y/n): " << endl;
        cin >> choice;
        if(choice=='y' || choice=='Y')
            return remove_member();
        return false;
    }
    ifstream file("members.txt");
    string newContent;
    string line;

     while(getline(file, line)){

        int l=0;
        string *fields= split_string(line, '\t', l);
        if(CNIC!=stod(fields[1]))
                newContent+=line+"\n";
        delete [] fields;
    }


    ofstream o_books("members.txt");
    o_books << newContent;

    cout << "Member record has been deleted successfully." << endl;
    return true;
}
void Member::list_all(){
    cout << endl;
    cout << setw(20)<< left << "RegNO"
         << setw(20)<< left << "CNIC"
         << setw(20)<< left << "Name"
         << setw(30)<< left << "Total Books Issued" << endl;
    cout << string(90, '-') << endl;
    cout << endl;
    Member* rec= new Member();
    ifstream file;
    file.open("members.txt");


    string line;

    while(getline(file, line)){

        int l=0;

        string *fields= split_string(line, '\t', l);

        cout << setw(20)<< left << fields[0]
             << setw(20)<< left << fields[1]
             << setw(20)<< left << fields[2]
             << setw(30)<< left << fields[3] << endl;

        delete [] fields;

    }
}


Member* Member::findRec(double CNIC){
    cout << endl;
    Member* rec= new Member();
    ifstream file;
    file.open("members.txt");


    string line;

    while(getline(file, line)){

        int l=0;

        string *fields= split_string(line, '\t', l);

        rec->regNo  = fields[0];
        rec->CNIC  = stod(fields[1]);
        rec->name     = fields[2];
        rec->n = stoi(fields[3]);

        delete [] fields;
        if(CNIC==rec->CNIC)
            return rec;
    }
    return NULL;

}

void Member::update(double CNIC, Member d){
    string newContent="";
    ifstream file;
    file.open("members.txt");


    string line;

    while(getline(file, line)){
        int l;
        string *fields= split_string(line, '\t', l);
        double f_CNIC= stod(fields[1]);

        if(CNIC==f_CNIC)
            line= d.regNo+"\t"+fields[1]+"\t"+d.name+"\t"+to_string(d.n);


        delete [] fields;


        newContent+=line+'\n';


    }

    ofstream o_accounts("members.txt");

    o_accounts << newContent;

}

Member::~Member()
{
    //dtor
}
