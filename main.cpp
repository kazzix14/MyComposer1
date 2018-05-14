#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    ofstream outputfile("test.txt");
    outputfile<<"test";
    outputfile.close();
}