#include "file_operation.hpp"

void HandleCommand(string command, task_manager& task_tracker)
{
    if(command.substr(0, 9)!="task-cli "){
        cout << "[ERROR] Please input 'task-cli'..." << endl;
        return;
    }
    switch(command[9]){

        case 'a': {
            if(command.length()<16){
                cout << "[ERROR] Please input 'add \"*task_name*\"'" << endl;
                return ;
            }
            if(command.substr(10,4)=="dd \"" && command[command.size()-1]=='"'){
                task_tracker.Add(command.substr(14, command.length()-15));
                WriteIntoJson(task_tracker);
            }
            else cout << "[ERROR] Input error when adding" << endl;
            return;
        }

        case 'u': {
            if(command.length()<21){
                cout << "[ERROR] Please input 'update \"task_id\"'" << endl;
                return ;
            }
            if(command.substr(10, 6) == "pdate "&& command[command.length()-1]=='"'){
                int i = 16, id=0;
                while(i<command.length() && '0'<=command[i]&&command[i]<='9'){
                    id = id*10 + (command[i++]-'0');
                }
                if(command[i++]!=' '){
                    cout << "[ERROR] Short of space" << endl;
                    return ;
                }
                if(command[i++]!='\"'){
                    cout << "[ERROR] Short of \"" << endl;
                    return ;
                }
                if(id>task_tracker.MaxId() || id<1){
                    cout << "[ERROR] Invalid id" << endl;
                    return ;
                }
                task_tracker.Update(id, command.substr(i, command.length()-i-1));
                WriteIntoJson(task_tracker);
                return ;
            }
            else{
                cout << "[ERROR] Input error when updating" << endl;
                return ;
            }
        }

        case 'd': {
            if(command.length()<16){
                cout << "[ERROR] Please input 'update \"task_name\"'" << endl;
                return ;
            }
            if(command.substr(10, 6)!="elete "){
                cout << "[ERROR] 'delete' spelling error" << endl;
                return ;
            }
            int i = 16, id=0;
            for(i; i<command.length(); ++i){
                if(!('0'<=command[i]&&command[i]<='9')){
                    cout << "[ERROR] Not number 1~9" << endl;
                    return ;
                }
                id = id*10 + (command[i]-'0');
            }
            if(id>task_tracker.MaxId() || id<1){
                cout << "[ERROR] Invalid id" << endl;
                return ;
            }
            task_tracker.Remove(id);
            WriteIntoJson(task_tracker);
            return ;
        }

        case 'm': {
            if(command.length()>=27 && command.substr(10, 16)=="ark-in-progress "){
                int i, id=0;
                for(i=26;i<command.length();++i){
                    if(!('0' <= command[i] && command[i]<='9')){
                        cout << "[ERROR] Not number 1~9" << endl;
                        return ;
                    }
                    id = id*10 + (command[i]-'0');
                }
                if(id>task_tracker.MaxId() || id<1){
                    cout << "[ERROR] Invalid id" << endl;
                    return ;
                }
                task_tracker.MarkInProgress(id);
                WriteIntoJson(task_tracker);
            }
            else if(command.length()>=20 && command.substr(10, 9)=="ark-done "){
                int i, id=0;
                for(i=19;i<command.length();++i){
                    if(!('0' <= command[i] && command[i]<='9')){
                        cout << "[ERROR] Not number 1~9" << endl;
                        return ;
                    }
                    id = id*10 + (command[i]-'0');
                }
                if(id>task_tracker.MaxId() || id<1){
                    cout << "[ERROR] Invalid id!" << endl;
                    return ;
                }
                task_tracker.MarkDone(id);
                WriteIntoJson(task_tracker);
            }
            else{
                cout << "[ERROR] Input error when marking" << endl;
            }
            return ;

        }

        case 'l': {
            if(command.length()==13 && command=="task-cli list") task_tracker.List();
            else if(command.length()==18 && command.substr(10, 8)=="ist done") task_tracker.ListDone();
            else if(command.length()==18 && command.substr(10, 8)=="ist todo") task_tracker.ListTodo();
            else if(command.length()==25 && command.substr(10, 15)=="ist in-progress") task_tracker.ListInProgress();
            return ;
        }

        default: {
            cout << "[ERRPR] Invalid input" << endl;
            return ;
        }
        
    }
}

int main()
{
    string user_command;
    task_manager task_tracker;
    ReadFromJson(task_tracker);
    while(true){
        getline(cin, user_command);
        HandleCommand(user_command, task_tracker);
    }
    return 0;
}