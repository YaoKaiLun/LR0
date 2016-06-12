#include<iostream>
#include<string>
#include"LR0.cpp"
using namespace std;

int main(){
    string filename="";
    cout<<"please input the grammar file name:";
    cin>>filename;
    LR0 lr0(filename);
    if(lr0.exec()){
        lr0.writeDataToFile();
        cout<<"compile the analyes.cpp file and run it."<<endl;
    }
    else {
        cout<<"fail!"<<endl;
    }
}
