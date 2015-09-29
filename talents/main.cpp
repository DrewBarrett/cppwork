#include <iostream>
#include <fstream>

using namespace std;
//Drew Barrett
string input1;
string input2;

int parseInput(string inputfile){
    input1 = "";
    input2 = "";
    ifstream infile(inputfile.c_str());
    string temp;
    while(!infile.eof()){
        temp = "";
        getline(infile,temp);
        if(input1 == ""){
            input1 = temp;
        }else if (input2 == ""){
            input2 = temp;
        }else{
            continue;
        }
    }
    cout << inputfile << " input: \n" << input1 << " and " << input2 << endl;
    infile.close();
    return 0;
}

int output(){

}

int main()
{
    parseInput("talent1.txt");
    output();
    return 0;
}
