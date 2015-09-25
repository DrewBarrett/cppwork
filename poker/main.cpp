#include <iostream>
#include <vector>
using namespace std;
//Drew Barrett
vector<string> hand;

int readInput(){
    string input = "1 2 3 4 5 6 7\n1 2 3 4 6 7 8\n1 2 3 3 4 4 4\n11 1 5 4 12 2 3";

    while(input.find('\n') != string::npos){
        hand.push_back(" " + input.substr(0,input.find('\n')) + " ");
        input.erase(0,input.find('\n')+1);
    }
    if (!input.empty()){
        hand.push_back(" " + input + " ");
        input.erase();
    }
    return 0;
}

int main(){
    readInput();
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
