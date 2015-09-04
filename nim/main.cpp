#include <iostream>
#include <ctime>
#include <stdlib.h>
//Drew Barrett
using namespace std;

int pilesize;
int turn = 0;
int computerIsSmart = 0;//false

int startPlayerTurn();

int startComputerTurn(int smart){
    int marbles;
    if (smart == 0){
        marbles = rand() % (pilesize/2) + 1;
        cout << "The easy computer takes " << marbles << " marbles from the pile\n";
        pilesize = pilesize - marbles;
        cout << "The remaining pile size is: " << pilesize << endl;
    }
    if(pilesize <= 1){
        cout << "The computer wins!\n";
        return 0;
    }
    startPlayerTurn();
    return 0;
}

int startPlayerTurn(){
    int marbles;
    cout << "Enter value between 1 and " << pilesize/2 << ": ";
    cin >> marbles;

    if(pilesize <= 1){
        cout << "You win!\n";
        return 0;
    }
    startComputerTurn(computerIsSmart);
    return 0;
}

int main()
{
    srand(time(0));
    pilesize = rand() % 91 + 10;
    turn = rand() % 2;
    //computerIsSmart = rand() % 2;
    cout << "DEBUG: ENTER COMPUTER DIFFICULTY: ";
    cin >> computerIsSmart;
    cout << "Welcome to Nim" << endl;
    cout << "The pile size starts at: " << pilesize << endl;
    if(turn == 0){
        cout << "The computer goes first.\n";
        startComputerTurn(computerIsSmart);
    }else{
        cout << "You go first.\n";
        startPlayerTurn();
    }
    system("PAUSE");
    return 0;
}
