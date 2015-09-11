#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <math.h>
//Drew Barrett
using namespace std;

int pilesize;
int turn = 0;
int computerIsSmart = 0;//false

int startPlayerTurn();

int startComputerTurn(int smart){
    int marbles = 0;
    if (smart == 0){
        marbles = rand() % (pilesize/2) + 1;
        cout << "The easy computer takes " << marbles << " marbles from the pile.\n";
    }else{
        for(int i = 9; i > 0; i--){
            if((pow(2,i)-1) <= (pilesize)){
                marbles = pilesize - (pow(2,i)-1);
                i = 0;
            }
        }
        if (marbles == 0){
            marbles = rand() % (pilesize/2) + 1;
        }
        cout << "The hard computer takes " << marbles << " marbles from the pile.\n";
    }
    pilesize = pilesize - marbles;
    cout << "The remaining pile size is: " << pilesize << endl;
    if(pilesize <= 1){
        cout << "The computer wins!\n";
        return 0;
    }
    startPlayerTurn();
    return 0;
}

int startPlayerTurn(){
    int marbles;
    bool valid = false;

    while(!valid){
        cout << "Enter value between 1 and " << pilesize/2 << ": ";
        cin >> marbles;
        if(cin.fail() || marbles > (pilesize/2) || marbles < 1) //checks to see if the value in the cin stream is the correct type, if not it returns true,false otherwise.
        {
            cin.clear(); //This corrects the stream.
            cin.ignore(); //This skips the left over stream data.
            cout << "Invalid input, try again. " << endl;
            valid = false; //The cin was not an integer so try again.
        }else{
            valid = true;
        }
    }
    pilesize = pilesize - marbles;
    cout << "You take " << marbles << " marbles from the pile.\nThe remaining pile size is: " << pilesize << endl;

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
    computerIsSmart = rand() % 2;
    //cout << "DEBUG: ENTER COMPUTER DIFFICULTY: ";
    //cin >> computerIsSmart;
    cout << "Welcome to Nim" << endl;
    cout << "The pile size starts at: " << pilesize << endl;
    if(turn == 0){
        cout << "The computer goes first.\n";
        startComputerTurn(computerIsSmart);
    }else{
        if(computerIsSmart){
            cout << "You go first against a hard computer.\n";
        }else{
            cout << "You go first against an easy computer.\n";
        }
        startPlayerTurn();
    }
    system("PAUSE");
    return 0;
}

/*
EASY COMPUTER: PLAYER WIN
Welcome to Nim
The pile size starts at: 13
The computer goes first.
The easy computer takes 1 marbles from the pile.
The remaining pile size is: 12
Enter value between 1 and 6: 7
Invalid input, try again.
Enter value between 1 and 6: 0
Invalid input, try again.
Enter value between 1 and 6: k
Invalid input, try again.
Enter value between 1 and 6: 6
You take 6 marbles from the pile.
The remaining pile size is: 6
The easy computer takes 1 marbles from the pile.
The remaining pile size is: 5
Enter value between 1 and 2: 2
You take 2 marbles from the pile.
The remaining pile size is: 3
The easy computer takes 1 marbles from the pile.
The remaining pile size is: 2
Enter value between 1 and 1: 1
You take 1 marbles from the pile.
The remaining pile size is: 1
You win!
Press any key to continue . . .

EASY COMPUTER: COMPUTER WIN
Welcome to Nim
The pile size starts at: 32
You go first against an easy computer.
Enter value between 1 and 16: 16
You take 16 marbles from the pile.
The remaining pile size is: 16
The easy computer takes 2 marbles from the pile.
The remaining pile size is: 14
Enter value between 1 and 7: 1
You take 1 marbles from the pile.
The remaining pile size is: 13
The easy computer takes 4 marbles from the pile.
The remaining pile size is: 9
Enter value between 1 and 4: 1
You take 1 marbles from the pile.
The remaining pile size is: 8
The easy computer takes 1 marbles from the pile.
The remaining pile size is: 7
Enter value between 1 and 3: 1
You take 1 marbles from the pile.
The remaining pile size is: 6
The easy computer takes 3 marbles from the pile.
The remaining pile size is: 3
Enter value between 1 and 1: 1
You take 1 marbles from the pile.
The remaining pile size is: 2
The easy computer takes 1 marbles from the pile.
The remaining pile size is: 1
The computer wins!
Press any key to continue . . .

HARD COMPUTER: COMPUTER WINS GOING FIRST
Welcome to Nim
The pile size starts at: 76
The computer goes first.
The hard computer takes 13 marbles from the pile.
The remaining pile size is: 63
Enter value between 1 and 31: 32
Invalid input, try again.
Enter value between 1 and 31: 0
Invalid input, try again.
Enter value between 1 and 31: k
Invalid input, try again.
Enter value between 1 and 31: 30
You take 30 marbles from the pile.
The remaining pile size is: 33
The hard computer takes 2 marbles from the pile.
The remaining pile size is: 31
Enter value between 1 and 15: 4
You take 4 marbles from the pile.
The remaining pile size is: 27
The hard computer takes 12 marbles from the pile.
The remaining pile size is: 15
Enter value between 1 and 7: 5
You take 5 marbles from the pile.
The remaining pile size is: 10
The hard computer takes 3 marbles from the pile.
The remaining pile size is: 7
Enter value between 1 and 3: 1
You take 1 marbles from the pile.
The remaining pile size is: 6
The hard computer takes 3 marbles from the pile.
The remaining pile size is: 3
Enter value between 1 and 1: 1
You take 1 marbles from the pile.
The remaining pile size is: 2
The hard computer takes 1 marbles from the pile.
The remaining pile size is: 1
The computer wins!
Press any key to continue . . .

HARD COMPUTER: PLAYER WINS GOING FIRST
Welcome to Nim
The pile size starts at: 88
You go first against a hard computer.
Enter value between 1 and 44: 25
You take 25 marbles from the pile.
The remaining pile size is: 63
The hard computer takes 2 marbles from the pile.
The remaining pile size is: 61
Enter value between 1 and 30: 30
You take 30 marbles from the pile.
The remaining pile size is: 31
The hard computer takes 12 marbles from the pile.
The remaining pile size is: 19
Enter value between 1 and 9: 4
You take 4 marbles from the pile.
The remaining pile size is: 15
The hard computer takes 7 marbles from the pile.
The remaining pile size is: 8
Enter value between 1 and 4: 1
You take 1 marbles from the pile.
The remaining pile size is: 7
The hard computer takes 2 marbles from the pile.
The remaining pile size is: 5
Enter value between 1 and 2: 2
You take 2 marbles from the pile.
The remaining pile size is: 3
The hard computer takes 1 marbles from the pile.
The remaining pile size is: 2
Enter value between 1 and 1: 1
You take 1 marbles from the pile.
The remaining pile size is: 1
You win!
Press any key to continue . . .
*/
