#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <ctype.h>

using namespace std;
//Drew Barrett
enum color { RED, BLUE, YELLOW, GREEN, WHITE, ORANGE };
int pattern[4];
int guesses = 15;
string rawInput;
int patternGuess[4];

int interpretInput(){
    string lowerInput;
    lowerInput = rawInput;
    transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
    lowerInput.erase(remove_if(lowerInput.begin(), lowerInput.end(), ::isspace), lowerInput.end());

    cout << lowerInput << endl;//DEBUG
    string guess;
    while (lowerInput.find("red") != string::npos){
        lowerInput.replace(lowerInput.find("red"), 3, "0");
    }
    while (lowerInput.find("blue") != string::npos){
        lowerInput.replace(lowerInput.find("blue"), 4, "1");
    }
    while (lowerInput.find("yellow") != string::npos){
        lowerInput.replace(lowerInput.find("yellow"), 6, "2");
    }
    while (lowerInput.find("green") != string::npos){
        lowerInput.replace(lowerInput.find("green"), 5, "3");
    }
    while (lowerInput.find("white") != string::npos){
        lowerInput.replace(lowerInput.find("white"), 5, "4");
    }
    while (lowerInput.find("orange") != string::npos){
        lowerInput.replace(lowerInput.find("orange"), 6, "5");
    }
    while (lowerInput.find("r") != string::npos){
        lowerInput.replace(lowerInput.find("r"), 1, "0");
    }
    while (lowerInput.find("b") != string::npos){
        lowerInput.replace(lowerInput.find("b"), 1, "1");
    }
    while (lowerInput.find("y") != string::npos){
        lowerInput.replace(lowerInput.find("y"), 1, "2");
    }
    while (lowerInput.find("g") != string::npos){
        lowerInput.replace(lowerInput.find("g"), 1, "3");
    }
    while (lowerInput.find("w") != string::npos){
        lowerInput.replace(lowerInput.find("w"), 1, "4");
    }
    while (lowerInput.find("o") != string::npos){
        lowerInput.replace(lowerInput.find("o"), 1, "5");
    }
    cout << lowerInput << endl;//DEBUG
    if (rawInput == "lol"){
        return 0;
    }else{
        return 1;
    }
}

int guess(){
    bool valid = false;

    while(!valid){
        cout << "You have " << guesses << " guesses remaining.\nEnter your guess: ";
        getline(cin, rawInput);
        if(interpretInput())
        {
            cout << "Invalid input, try again. " << endl;
            valid = false; //The cin was not an integer so try again.
        }else{
            valid = true;
        }
    }
    cout << rawInput << endl;//DEBUG
}

int main()
{
    int colors;

    srand(time(0));
    for (int i=0; i < 4; i++){
        colors = rand() % 6;
        switch(colors)
        {
            case RED: cout << "red\n";  break;
            case BLUE: cout << "blue\n";  break;
            case YELLOW: cout << "yellow\n";   break;
            case GREEN: cout << "green\n"; break;
            case WHITE: cout << "white\n";   break;
            case ORANGE: cout << "orange\n";   break;
        }
        pattern[i] = colors;
    }
    cout << "Hello world!" << pattern[0] << pattern[1] << pattern[2] << pattern[3] << endl;
    cout << "Welcome to Mastermind.\n";
    cout << "The pegs are colored red(R), blue(B), yellow(Y), green(G), white(W) and orange(O).\n";
    cout << "You have to guess what the color and order of the 4 pegs.\n";
    cout << "There can be multiple of the same color peg.\n";
    cout << "Good luck, code breaker.\n";

    guess();
    return 0;
}
