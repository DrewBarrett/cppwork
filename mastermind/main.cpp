#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

enum color { RED, BLUE, YELLOW, GREEN, WHITE, ORANGE };
int pattern[4];

int guess(){

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
    cout << "Welcome to Mastermind.\n "
    guess();
    return 0;
}
