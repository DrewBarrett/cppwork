#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
//Drew Barrett
vector<string> hand;

int readInput(string inputfile){
    hand.clear();
    ifstream infile(inputfile.c_str());
    string temp;
    string input = "";// = "1 2 3 4 5 6 7\n1 2 3 4 6 7 8\n1 2 3 3 4 4 4\n11 1 5 4 12 2 3";
    //converts file to one line to be separated with \n in order to work with original way
    while(!infile.eof()){
        temp = "";
        getline(infile,temp);
        temp += '\n';
        if (temp != "\n"){//creates bug where it realizes \n already exists at the end of the line after you add \n
            input += temp;
        }
    }
    //cout << input;

    while(input.find('\n') != string::npos){
        hand.push_back(" " + input.substr(0,input.find('\n')) + " ");
        input.erase(0,input.find('\n')+1);
    }
    if (!input.empty()){//useless now that we always add \n to every line but will keep for testing manual input
        hand.push_back(" " + input + " ");
        input.erase();
    }
    cout << inputfile << ": \n";
    infile.close();
    return 0;
}

int output(){
    for(int i = 0; i < hand.size(); i++){
        cout << hand[i];
        if (hand[i].find(" 1 ") != string::npos &&
            hand[i].find(" 2 ") != string::npos &&
            hand[i].find(" 3 ") != string::npos &&
            hand[i].find(" 4 ") != string::npos &&
            hand[i].find(" 5 ") != string::npos){
            cout << "Bet\n";
        }else{
            cout << "Fold\n";
        }
    }
    return 0;
}

int main(){
    readInput("poker1.txt");
    output();
    readInput("poker2.txt");
    output();
    readInput("poker3.txt");
    output();
    readInput("poker4.txt");
    output();
    readInput("poker5.txt");
    output();
    return 0;
}
/*
poker1.txt:
 1 2 3 4 5 6 7 Bet
 1 2 3 4 6 7 8 Fold
 1 2 3 3 4 4 4 Fold
 11 1 5 4 12 2 3 Bet
 5 1 3 2 6 7 9 Fold
poker2.txt:
 12 12 12 12 11 11 11 Fold
 13 13 13 13 1 1 1  Fold
 1 1 1 1 2 2 2 Fold
 5 5 5 5 3 3 3 Fold
poker3.txt:
 1 2 1 2 3 4 5 Bet
 2 2 1 2 3 4 5 Bet
 3 2 1 2 3 4 5 Bet
 13 13 1 2 3 4 5 Bet
 12 12 1 2 3 4 5 Bet
poker4.txt:
 5 4 3 2 1 6 7 Bet
 5 4 3 2 1 13 12 Bet
 5 4 3 2 1 8 8 Bet
 8 5 4 3 2 1 8 Bet
 5 8 4 3 2 8 1  Bet
 8 2 5 4 3 13 1  Bet
poker5.txt:
 1 2 3 4 5 6 7 Bet
 2 3 4 6 7 8 9 Fold
 9 2 3 4 7 4 11 Fold
 11 13 5 4 8 2 3 Fold
 5 1 3 2 6 7 9 Fold

Process returned 0 (0x0)   execution time : 0.062 s
Press any key to continue.
*/
