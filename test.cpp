#include<iostream>
#include"LR0.cpp"
using namespace std;

int main(){
    LR0 lr0("grammar2.txt");
    lr0.exec();
    lr0.writeDataToFile();
}
