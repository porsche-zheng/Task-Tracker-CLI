#include "task.hpp"
#include<vector>
#include<chrono>
#include<ctime>

class task_manager
{
    vector<task> task_list; // id-1 = index in `task_list`

public:
    task_manager() {}
    ~task_manager() {}

    void Add(string name){
        // get current time
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        tm* local_tm = localtime(&now_c);
        Time tm = Time(local_tm->tm_year+1900, local_tm->tm_mon+1, local_tm->tm_mday);
        // add in `task_list` vector
        task_list.emplace_back(task_list.size()+1,name, task_status::todo, tm, tm);
        cout << "[INFO] [Add] Succeed" << endl;
    }

    void Add(int i, bool del, string name, task_status sta, Time ct, Time ut){
        task_list.emplace_back(i, name, sta, ct, ut, del);
    }

    void Update(int id, string name){
        // get current time
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        tm* local_tm = localtime(&now_c);
        // find the task and update its time
        
        task_list[id-1].description = name;
        task_list[id-1].updatedAt = Time(local_tm->tm_year+1900, local_tm->tm_mon+1, local_tm->tm_mday);
        cout << "[INFO] [Update] Succeed" << endl ;
        return ;
    }

    void Remove(int id){
        task_list[id-1].deleted = true;
        cout << "[INFO] [Delete] Succeed" << endl;
    }

    void MarkInProgress(int id){
        task_list[id-1].status = task_status::inprogress;
        cout << "[INFO] [Mark In-Progress] Succeed" << endl;
        return ;
    }

    void MarkDone(int id){
        task_list[id-1].status = task_status::done;
        cout << "[INFO] [Mark Done] Succeed" << endl;
        return ;
    }

    void List(){
        cout << "[INFO] [List All Tasks]" << endl;
        for(int i=0;i<task_list.size();++i){
            if(!task_list[i].deleted) task_list[i].show();
        }
    }

    void ListDone(){
        cout << "[INFO] [List All Tasks Which Are Done]" << endl;
        for(int i=0;i<task_list.size();++i){
            if(task_list[i].status==task_status::done && !task_list[i].deleted) task_list[i].show();
        }
    }

    void ListTodo(){
        cout << "[INFO] [List All Tasks Which Are Todo]" << endl;
        for(int i=0;i<task_list.size();++i){
            if(task_list[i].status==task_status::todo && !task_list[i].deleted) task_list[i].show();
        }
    }

    void ListInProgress(){
        cout << "[INFO] [List All Tasks Which Are In-Progress]" << endl;
        for(int i=0;i<task_list.size();++i){
            if(task_list[i].status==task_status::inprogress && !task_list[i].deleted) task_list[i].show();
        }
    }

    int MaxId(){
        return task_list.size();
    }

    void Clear(){
        task_list.clear();
    }

    string GetId(int i){
        return to_string(task_list[i].id);
    }

    string GetDesciption(int i){
        return task_list[i].description;
    }

    string GetStatus(int i){
        if(task_list[i].status==task_status::todo) return "0";
        if(task_list[i].status==task_status::inprogress) return "1";
        if(task_list[i].status==task_status::done) return "2";
        return "0";
    }

    string GetDeleted(int i){
        if(task_list[i].deleted) return "true";
        else return "false";
    }

    string GetUpdateTime(int i){
        return task_list[i].updatedAt.time();
    }

    string GetCreateTime(int i){
        return task_list[i].createdAt.time();
    }
};