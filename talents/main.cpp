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
    if(!infile.is_open()){
        cout << inputfile << " not found... moving on...";
        return 0;
    }
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
    int length;
    int suffixlength = 0;
    if(input1.length() < input2.length()){
        length = input1.length();
    }else{
        length = input2.length();
    }
    cout << "Output: ";
    for(int i=1; i < length + 1; i++){
        //cout << input1.substr(0, i);
        if(input1.substr(0, i) == input2.substr(input2.length() - i)){
            suffixlength = i;
        }
    }
    cout << input1.substr(0,suffixlength) << " ";
    cout << suffixlength << endl << endl;
}

int main()
{
    parseInput("talent1.txt");
    output();
    parseInput("talent2.txt");
    output();
    parseInput("talent3.txt");
    output();
    parseInput("talent4.txt");
    output();
    parseInput("talent5.txt");
    output();
    parseInput("talent6.txt");
    output();
    parseInput("talent7.txt");
    output();
    parseInput("talent8.txt");
    output();
    parseInput("talent9.txt");
    output();
    parseInput("talent10.txt");
    output();
    parseInput("talent11.txt");
    output();
    parseInput("talent12.txt");
    output();
    return 0;
}
/*
talent1.txt input:
clinton and homer
Output:  0

talent2.txt input:
riemann and marjorie
Output: rie 3

talent3.txt input:
ababababab and abababababababab
Output: ababababab 10

talent4.txt input:
abababababababab and ababababab
Output: ababababab 10

talent5.txt input:
kdkdkdkdkdkd and kdkdkdkdkdkd
Output: kdkdkdkdkdkd 12

talent6.txt input:
ababcababdababcab and babacbabadbaababc
Output: ababc 5

talent7.txt input:
aaaaaaaaaa and aaaaaaaaaz
Output:  0

talent8.txt input:
zaaaaaaaaa and aaaaaaaaaa
Output:  0

talent9.txt not found... moving on...Output:  0

talent10.txt not found... moving on...Output:  0

talent11.txt input:
xxxxxxxxxx and yyyyyyyyyyyyyyy
Output:  0

talent12.txt input:
ababcabadaba and babaxxxababcabadabayyyadaba
Output: aba 3


Process returned 0 (0x0)   execution time : 0.076 s
Press any key to continue.
*/
