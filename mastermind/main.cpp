#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <vector>

using namespace std;
//Drew Barrett
enum color { RED, BLUE, YELLOW, GREEN, WHITE, ORANGE };
int pattern[4];
int guesses = 15;
string rawInput;
int patternGuess[4];
int guess();

int hint(){
    int correct = 0;
    int wrongspot = 0;
    int status[] = { 0, 0, 0, 0 };
    cout << "You guessed: ";
    for (int i=0; i < 4; i++){
        switch(patternGuess[i])
        {
            case RED:   cout << "red ";     break;
            case BLUE:  cout << "blue ";    break;
            case YELLOW:cout << "yellow ";  break;
            case GREEN: cout << "green ";   break;
            case WHITE: cout << "white ";   break;
            case ORANGE:cout << "orange ";  break;
        }
    }
    cout << endl;
    for (int i=0; i < 4; i++){
        if(patternGuess[i] == pattern[i]){
            correct++;
            status[i] = 1;
        }
    }
    for (int i=0; i < 4; i++){
        if(status[i] != 1){
            for (int k=0; k < 4; k++){
                if(status[k] == 0){
                    if(patternGuess[i] == pattern[k]){
                        wrongspot++;
                        status[k] = 2;
                    }
                }
            }
        }
    }

    //cout << correct << " " << wrongspot << endl;
    /*for (int i=0; i<4;i++){
        cout << status[i] << endl;
    }*/
    if(status[0] == 1 && status[1] == 1 && status[2] == 1 && status[3] == 1){
        cout << "You win!\n";
        return 0;
    }
    cout << "Hint: ";
    for (int i=0; i<4;i++){
        if(status[i] == 1){
            cout << "Red ";
        }
    }
    for (int i=0; i<4;i++){
        if(status[i] == 2){
            cout << "White ";
        }
    }

    if(status[0] == 0 && status[1] == 0 && status[2] == 0 && status[3] == 0){
        cout << "All incorrect";
    }
    cout << "\nRed means right color in right place and white means right color in wrong place\n";
    guesses--;
    guess();
    return 0;
}

int interpretInput(){
    string lowerInput;
    lowerInput = rawInput;
    transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
    lowerInput.erase(remove_if(lowerInput.begin(), lowerInput.end(), ::isspace), lowerInput.end());

    //cout << lowerInput << endl;//DEBUG
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
   // cout << lowerInput << endl;//DEBUG
    if (lowerInput.length() == 4){
        for (int i = 0 ; i < 4 ; i++)
        {
            patternGuess[i] = lowerInput.at(i) - '0';
        }
        //cout << patternGuess[0] << endl;//DEBUG
        return 0;
    }else{
        return 1;
    }
}

int guess(){
    bool valid = false;
    if(guesses <= 0){
        cout << "You are out of guesses! The pattern was: ";
        for (int i=0; i < 4; i++){
            switch(pattern[i])
            {
                case RED:   cout << "red ";     break;
                case BLUE:  cout << "blue ";    break;
                case YELLOW:cout << "yellow ";  break;
                case GREEN: cout << "green ";   break;
                case WHITE: cout << "white ";   break;
                case ORANGE:cout << "orange ";  break;
            }
        }
        return 0;
    }
    while(!valid){
        cout << "You have " << guesses << " guesses remaining.\nEnter your guess: ";
        getline(cin, rawInput);
        if(interpretInput())
        {
            cout << "Invalid input, try again. " << endl;
            valid = false;
        }else{
            valid = true;
        }
    }
    //cout << rawInput << endl;//DEBUG
    hint();
    return 0;
}

int main()
{
    int colors;

    srand(time(0));
    for (int i=0; i < 4; i++){
        colors = rand() % 6;
        /*switch(colors)
        {
            case RED: cout << "red\n";  break;
            case BLUE: cout << "blue\n";  break;
            case YELLOW: cout << "yellow\n";   break;
            case GREEN: cout << "green\n"; break;
            case WHITE: cout << "white\n";   break;
            case ORANGE: cout << "orange\n";   break;
        }*/
        pattern[i] = colors;
    }
    //cout << "Hello world!" << pattern[0] << pattern[1] << pattern[2] << pattern[3] << endl;
    cout << "Welcome to Mastermind.\n";
    cout << "The pegs are red(R), blue(B), yellow(Y), green(G), white(W) and orange(O).\n";
    cout << "You have to guess what the color and order of the 4 pegs.\n";
    cout << "There can be multiple of the same color peg.\n";
    cout << "Good luck, code breaker.\n";

    guess();
    return 0;
}
/*
PLAYER WINS:

Welcome to Mastermind.
The pegs are red(R), blue(B), yellow(Y), green(G), white(W) and orange(O).
You have to guess what the color and order of the 4 pegs.
There can be multiple of the same color peg.
Good luck, code breaker.
You have 15 guesses remaining.
Enter your guess: RRRR
You guessed: red red red red
Hint: All incorrect
Red means right color in right place and white means right color in wrong place
You have 14 guesses remaining.
Enter your guess: BBBB
You guessed: blue blue blue blue
Hint: All incorrect
Red means right color in right place and white means right color in wrong place
You have 13 guesses remaining.
Enter your guess: YYYY
You guessed: yellow yellow yellow yellow
Hint: Red
Red means right color in right place and white means right color in wrong place
You have 12 guesses remaining.
Enter your guess: YYGG
You guessed: yellow yellow green green
Hint: Red White White
Red means right color in right place and white means right color in wrong place
You have 11 guesses remaining.
Enter your guess: ygww
You guessed: yellow green white white
Hint: Red White
Red means right color in right place and white means right color in wrong place
You have 10 guesses remaining.
Enter your guess: ggyy
You guessed: green green yellow yellow
Hint: Red Red White
Red means right color in right place and white means right color in wrong place
You have 9 guesses remaining.
Enter your guess: ggyw
You guessed: green green yellow white
Hint: Red Red White
Red means right color in right place and white means right color in wrong place
You have 8 guesses remaining.
Enter your guess: ggyo
You guessed: green green yellow orange
Hint: Red Red White White
Red means right color in right place and white means right color in wrong place
You have 7 guesses remaining.
Enter your guess: gygo
You guessed: green yellow green orange
Hint: White White White White
Red means right color in right place and white means right color in wrong place
You have 6 guesses remaining.
Enter your guess: ggoy
You guessed: green green orange yellow
Hint: Red White White White
Red means right color in right place and white means right color in wrong place
You have 5 guesses remaining.
Enter your guess: oygg
You guessed: orange yellow green green
Hint: Red Red White White
Red means right color in right place and white means right color in wrong place
You have 4 guesses remaining.
Enter your guess: gygo
You guessed: green yellow green orange
Hint: White White White White
Red means right color in right place and white means right color in wrong place
You have 3 guesses remaining.
Enter your guess: ygyo
You guessed: yellow green yellow orange
Hint: Red Red White
Red means right color in right place and white means right color in wrong place
You have 2 guesses remaining.
Enter your guess: yggo
You guessed: yellow green green orange
Hint: Red White White White
Red means right color in right place and white means right color in wrong place
You have 1 guesses remaining.
Enter your guess: ogyg
You guessed: orange green yellow green
You win!

Process returned 0 (0x0)   execution time : 277.695 s
Press any key to continue.

PLAYER LOSES + INPUT TESTS:
Welcome to Mastermind.
The pegs are red(R), blue(B), yellow(Y), green(G), white(W) and orange(O).
You have to guess what the color and order of the 4 pegs.
There can be multiple of the same color peg.
Good luck, code breaker.
You have 15 guesses remaining.
Enter your guess: rbgy
You guessed: red blue green yellow
Hint: Red Red White
Red means right color in right place and white means right color in wrong place
You have 14 guesses remaining.
Enter your guess: RBYG
You guessed: red blue yellow green
Hint: Red White White
Red means right color in right place and white means right color in wrong place
You have 13 guesses remaining.
Enter your guess: R B Y G
You guessed: red blue yellow green
Hint: Red White White
Red means right color in right place and white means right color in wrong place
You have 12 guesses remaining.
Enter your guess: red b yellow g
You guessed: red blue yellow green
Hint: Red White White
Red means right color in right place and white means right color in wrong place
You have 11 guesses remaining.
Enter your guess: red red red red
You guessed: red red red red
Hint: Red
Red means right color in right place and white means right color in wrong place
You have 10 guesses remaining.
Enter your guess: redredredred
You guessed: red red red red
Hint: Red
Red means right color in right place and white means right color in wrong place
You have 9 guesses remaining.
Enter your guess: redblueorangegreen
You guessed: red blue orange green
Hint: Red White White White
Red means right color in right place and white means right color in wrong place
You have 8 guesses remaining.
Enter your guess: RED BLUE PURPLE
Invalid input, try again.
You have 8 guesses remaining.
Enter your guess: 1234556
Invalid input, try again.
You have 8 guesses remaining.
Enter your guess: 1234
You guessed: blue yellow green white
Hint: Red White
Red means right color in right place and white means right color in wrong place
You have 7 guesses remaining.
Enter your guess: 4321
You guessed: white green yellow blue
Hint: Red White
Red means right color in right place and white means right color in wrong place
You have 6 guesses remaining.
Enter your guess: GREEEN g 1w
Invalid input, try again.
You have 6 guesses remaining.
Enter your guess: GREEN g 1w
You guessed: green green blue white
Hint: White White
Red means right color in right place and white means right color in wrong place
You have 5 guesses remaining.
Enter your guess: orangew5r
You guessed: orange white orange red
Hint: White White
Red means right color in right place and white means right color in wrong place
You have 4 guesses remaining.
Enter your guess: not a valid input
Invalid input, try again.
You have 4 guesses remaining.
Enter your guess: 123g
You guessed: blue yellow green green
Hint: Red White
Red means right color in right place and white means right color in wrong place
You have 3 guesses remaining.
Enter your guess: 1w34
You guessed: blue white green white
Hint: Red White
Red means right color in right place and white means right color in wrong place
You have 2 guesses remaining.
Enter your guess: 4444
You guessed: white white white white
Hint: All incorrect
Red means right color in right place and white means right color in wrong place
You have 1 guesses remaining.
Enter your guess: 4441
You guessed: white white white blue
Hint: Red
Red means right color in right place and white means right color in wrong place
You are out of guesses! The pattern was: red orange green blue
Process returned 0 (0x0)   execution time : 151.138 s
Press any key to continue.
*/
