#include<iostream>
#include<string>
using namespace std;

enum class task_status{todo,inprogress,done};
class task_manager;

class Time
{
    int year, month, day;
public:
    Time(int y, int m, int d): year(y), month(m), day(d) {}
    ~Time() {}
    void show(){
        cout << year << '/' << month << '/' << day << endl;
    }
    string time(){
        string y = std::to_string(year);
        string m = to_string(month);
        string d = to_string(day);
        return (y + '/' + m + '/' + d);
    }
};

class task
{
friend task_manager;
protected:
    int id;
    bool deleted;
    string description;
    task_status status;
    Time createdAt;
    Time updatedAt;
public:
    task(int i, string d, task_status s, Time ct, Time ut, bool del = false):
    id(i), deleted(del), description(d), status(s), createdAt(ct), updatedAt(ut){}
    void show(){
        cout << id << '\t' << description << '\t';
        switch (status){
            case task_status::done:
                cout << "done" << endl;
                break;
            
            case task_status::inprogress:
                cout << "in progress" << endl;
                break;
            
            case task_status::todo:
                cout << "to do" << endl;
                break;
            
        }
        cout << "created time: ";
        createdAt.show();
        cout << "updated time: ";
        updatedAt.show();
    }
    ~task() {}
};
