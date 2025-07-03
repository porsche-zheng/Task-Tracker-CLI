#include"task_manager.hpp"
#include<fstream>
#include<iostream>

string filename = "../task.json";

void ReadFromJson(task_manager& tasks)
{
    if(tasks.MaxId()!=0) tasks.Clear();
    ifstream fin(filename);
    if(!fin.is_open()){
        ofstream fout(filename);
        fout << "[]" << endl;
        fout.close();
        tasks.Clear();
        cout << "New A Json File!" << endl;
    } // 新建 JSON 文件
    else{
        string line, description;
        int id, l, i;
        int cy, cm, cd, uy, um, ud;
        bool deleted;
        task_status status;
        getline(fin, line);
        getline(fin, line); // input pre 2 line first
        for(l=3; getline(fin, line); ++l){
            switch(l%8){
                case 3:{
                    id = 0;
                    for(i=10; i<line.length() && '0'<=line[i] && line[i]<='9';++i)
                        id = id*10 + (line[i]-'0');
                    break;
                }
                case 4:{
                    if(line.substr(15, 5)=="false") deleted = false;
                    if(line.substr(15, 4)=="true") deleted = true;
                    break;
                }
                case 5:{
                    description = line.substr(20, line.length()-22);
                    break;
                }
                case 6:{
                    if(line[14]=='0') status = task_status::todo;
                    else if(line[14]=='1') status = task_status::inprogress;
                    else status = task_status::done;
                    break;
                }
                case 7:{
                    cy = cm = cd = 0;
                    for(i=18; '0'<=line[i] && line[i]<='9'; ++i) cy = cy*10 + line[i] - '0';
                    for(i=i+1; '0'<=line[i] && line[i]<='9'; ++i) cm = cm*10+ line[i] - '0';
                    for(i=i+1; '0'<=line[i] && line[i]<='9'; ++i) cd = cd*10 + line[i] - '0';
                    break;
                }
                case 0:{
                    uy = um = ud = 0;
                    for(i=18; '0'<=line[i] && line[i]<='9'; ++i) uy = uy*10 + line[i] - '0';
                    for(i=i+1; '0'<=line[i] && line[i]<='9'; ++i) um = um*10+ line[i] - '0';
                    for(i=i+1; '0'<=line[i] && line[i]<='9'; ++i) ud = ud*10 + line[i] - '0';
                    break;
                }
                case 1:{
                    tasks.Add(id, deleted, description, status, Time(cy, cm, cd), Time(uy, um, ud));
                }
                case 2:{
                    id = 0, deleted = false, description = "", status = task_status::todo;
                    cy = cm = cd = uy = um = ud = 0;
                }
            }
        }
    }
    cout << "[INFO] [Read Fron Json] Succeed" << endl;
}

void WriteIntoJson(task_manager& tasks)
{
    ofstream fout(filename);
    fout << "[\n";
    for(int i=0; i<tasks.MaxId(); ++i){
        fout << "  {\n";
        fout << "    \"id\": " << tasks.GetId(i) << ",\n";
        fout << "    \"deleted\": " << tasks.GetDeleted(i) << ",\n";
        fout << "    \"description\": \"" << tasks.GetDesciption(i) << "\",\n";
        fout << "    \"status\": " << tasks.GetStatus(i) << ",\n";
        fout << "    \"createdAt\": \"" << tasks.GetCreateTime(i) << "\",\n";
        fout << "    \"updatedAt\": \"" << tasks.GetUpdateTime(i) << "\"\n";
        if(i==tasks.MaxId()-1) fout << "  }" << endl;
        else fout << "  }," << endl;
    }
    fout << "]\n";
    fout.close();
    cout << "[INFO] [Write Into Json] Succeed" << endl;
}