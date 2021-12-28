#ifndef MEMBER_H
#define MEMBER_H
#include <string>

using namespace std;

class Member
{
    private:
        string regNo;
        double CNIC;
        string name;
        int n;


    public:
        Member();
        double getCNIC();
        bool add_member();
        bool remove_member();
        void list_all();
        static Member* findRec(double CNIC);
        static void update(double, Member);
        void decrement_n(){
            n--;
        }
        void increment_n(){
            n++;
        }

        int getN(){
            return n;
        }
        string getName(){
            return name;
        }



        ~Member();

};

#endif // MEMBER_H
