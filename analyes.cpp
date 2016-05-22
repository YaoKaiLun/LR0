#include<iostream>
#include"data.h"
#include<list>
#include<sstream>
#include<iomanip>
using namespace std;

list<string> stateStack;
list<string> symbolStack;
string input;
int input_point;
string checkActionTable(string state,string _vt);
string checkGotoTable(string state,string _vn);
int flag;
const int WIDTH=30;
void printTable();
void init();
void analyes();
void printProcess();
int main(){
    for(int i=0;i<grammar_length;i++){
        cout<<"("<<i<<") "<<x_grammars[i].left<<"->"<<x_grammars[i].right<<endl;
    }
    printTable();
    while(1){
        init();
        cout<<"please input the sentence to check:";
        cin>>input;
        input+="#";
        cout<<std::left<<setw(WIDTH)<<"stateStack"<<setw(WIDTH)<<"symbolStack"<<setw(WIDTH)<<"input"<<endl;
        analyes();
        if(flag==1){
            cout<<"success!"<<endl;
        }
        else{
            cout<<"fail!"<<endl;
        }
    }
}

void init(){
    input_point=0;
    flag=0;
    stateStack.clear();
    symbolStack.clear();
    stateStack.push_back("0");
    symbolStack.push_back("#");

}

void printTable(){
    cout<<"table:"<<endl;
    cout<<"state"<<'\t';
    for(int i=0;i<vt_length;i++){
        cout<<vt[i]<<'\t';    
    }
    for(int i=0;i<vn_length;i++){
        cout<<vn[i]<<'\t';    
    }
    cout<<endl;
    for(int i=0;i<vn_length;i++){

    }
    for(int i=0;i<item_set_length;i++){
        cout<<i<<'\t';
        for(int j=0;j<vt_length;j++){
            cout<<actionTable[i][j]<<'\t';
        }
        for(int r=0;r<vn_length;r++){
            cout<<gotoTable[i][r]<<'\t';
        }
        cout<<endl;
    }
}
string checkActionTable(string state,string _vt){
    int st;
    stringstream ss;
    ss<<state;
    ss>>st;
    for(int i=0;i<vt_length;i++){
        if(_vt==vt[i]){
            //cout<<"actionTable["<<st<<"]["<<i<<"]"<<endl;
            return actionTable[st][i];
        }
    }
    return "";
}

string checkGotoTable(string state,string _vn){
    int st;
    stringstream ss;
    ss<<state;
    ss>>st;
    for(int i=0;i<vn_length;i++){
        if(_vn==vn[i]){
            return gotoTable[st][i];
        }
    }
    return "";
}

void analyes(){
    printProcess();
    string stateStack_top=stateStack.back();
    string now_input=input.substr(input_point,1);
    string goal=checkActionTable(stateStack_top,now_input);
    if(goal=="acc"){
        flag=1;
    }
    else if(goal[0]=='s'){
        stateStack.push_back(goal.substr(1));
        symbolStack.push_back(now_input);
        input_point++;
        analyes();
    }
    else if(goal[0]=='r'){
        int state;
        stringstream ss;
        ss<<goal[1];
        ss>>state;
        int len=x_grammars[state].length;
        for(int i=0;i<len;i++){
            symbolStack.pop_back();
            stateStack.pop_back();
        }
        symbolStack.push_back(x_grammars[state].left);      
        stateStack_top=stateStack.back();
        string st=checkGotoTable(stateStack_top,x_grammars[state].left);
        stateStack.push_back(st);
        analyes();
    }
}

void printProcess(){
   list<string>::const_iterator pos;
   cout<<std::left<<setw(WIDTH);
   string str="";
   for(pos=stateStack.begin();pos!=stateStack.end();++pos){
      str+=*pos;
      str+=" ";      
   } 
   cout<<str;
   cout<<std::left<<setw(WIDTH);
   str="";
   for(pos=symbolStack.begin();pos!=symbolStack.end();++pos){
      str+=*pos;
      str+=" ";      
   } 
   cout<<str;
   cout<<std::left<<setw(WIDTH);
   str="";
   for(int i=input_point;i<input.length();i++){
       str+=input[i];
   }
   cout<<str;
   cout<<endl;
}
