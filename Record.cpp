#include "Record.h"

Record::Record()
{
    //ctor
}


string* split_string( string str, char c, int& length){
    string temp=str;
    temp+=c;

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


bool Record::update(int field, string target, string * fields, int l){
    string newContent="";
    ifstream books;
    books.open("books.txt");


    string rec;

    while(getline(books, rec)){
        int l;

        string *fields= split_string(rec, '\t', l);
        double f_isbn= stod(fields[2]);
        delete [] fields;

        rec+="\n";
        if(isbn==f_isbn){
            string s_isbn=to_string(d.isbn);
            s_isbn= s_isbn.substr(0, s_isbn.find('.'));
            rec=d.title+"\t"+d.authors+"\t"+s_isbn+"\t"+to_string(d.quantity)+"\n";
        }


        newContent+=rec;


    }

    ofstream o_books("books.txt");

    o_books << newContent;
    return true;
}


Book* Book::findRec(double isbn){
    cout << endl;
    Book* rec= new Book();
    ifstream file;
    file.open("books.txt");


    string line;

    while(getline(file, line)){

        int l=0;

        string *fields= split_string(line, '\t', l);

        rec->title    = fields[0];
        rec->authors  = fields[1];
        rec->isbn     = stod(fields[2]);
        rec->quantity = stoi(fields[3]);

        delete [] fields;
        if(isbn==rec->isbn)
                return rec;
    }
    return NULL;

}

bool Book::remove_book(){
   cout << "Enter the ISBN number of book you want to remove: ";
   cin >>isbn;
   ifstream file("books.txt");
   string newContent;
   string line;

   while(getline(file, line)){

        int l=0;
        string *fields= split_string(line, '\t', l);
        if(isbn!=stod(fields[2]))
                newContent+=line+"\n";
        delete [] fields;
    }


    ofstream o_books("books.txt");
    o_books << newContent;

    cout << "Book record has been deleted successfully." << endl;
    return true;
}

Record::~Record()
{
    //dtor
}
