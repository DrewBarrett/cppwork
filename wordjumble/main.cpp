// Word Jumble
// The classic word jumble game where the player can ask for a hint

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
//Drew Barrett
using namespace std;

int score = 0;

int main()
{
    enum fields {WORD, HINT, NUM_FIELDS};
    const int NUM_WORDS = 10;
    const string WORDS[NUM_WORDS][NUM_FIELDS] =
    {
        {"wall", "Do you feel you're banging your head against something?"},
        {"glasses", "These might help you see the answer."},
        {"labored", "Going slowly, is it?"},
        {"persistent", "Keep at it."},
        {"jumble", "It's what the game is all about."},
        {"mumble", "Speak up."},
        {"fumble", "Don't drop it!"},
        {"crumbles", "And thats the way the cookie..."},
        {"rumble", "When your stomach does this you're hungry."},
        {"humble", "It's what you are until you get the top score in this amazing game."}
    };

    cout << "\t\t\tWelcome to Word Jumble!\n\n";
    cout << "Unscramble the letters to make a word.\n";
    cout << "Enter 'hint' for a hint.\n";
    cout << "Enter 'quit' to quit the game.\n\n";
    int remainingWords = NUM_WORDS;
    vector<int> used;
    do{
        srand(time(0));
        int valid = true;
        int choice;
        do{
            valid = true;
            choice = (rand() % NUM_WORDS);
            for(int i=0; i<used.size(); i++){
                //cout << used[i];
                if (choice == used[i])
                    valid = false;
            }
        }while(valid == false);
        used.push_back(choice);
        string theWord = WORDS[choice][WORD];  // word to guess
        string theHint = WORDS[choice][HINT];  // hint for word

        string jumble = theWord;  // jumbled version of word
        int length = jumble.size();
        for (int i=0; i<length; ++i)
        {
            int index1 = (rand() % length);
            int index2 = (rand() % length);
            char temp = jumble[index1];
            jumble[index1] = jumble[index2];
            jumble[index2] = temp;
        }
        cout << "The jumble is: " << jumble;

        string guess;
        cout << "\n\nYour guess: ";
        cin >> guess;

        while ((guess != theWord) && (guess != "quit"))
        {
            if (guess == "hint"){
                cout << theHint << endl;
                score -= (theWord.length() / 2);
                cout << (theWord.length() / 2) << " points deducted for using hint\nScore: " << score;
            }
            else
                cout << "Sorry, that's not it.";

            cout <<"\n\nYour guess: ";
            cin >> guess;
        }

        if (guess == theWord){
            cout << "\nThat's it!  You guessed it! " << theWord.length() << " points awarded!\n";
            score += theWord.length();
            cout << "Score: " << score << endl;
            remainingWords--;
            cout << remainingWords << " words remaining!\n";
        }
    }while(remainingWords>0);


    cout << "\nThanks for playing.\n";

    return 0;
}
/*
                        Welcome to Word Jumble!

Unscramble the letters to make a word.
Enter 'hint' for a hint.
Enter 'quit' to quit the game.

The jumble is: mlefub

Your guess: hint
Don't drop it!
3 points deducted for using hint
Score: -3

Your guess: fumble

That's it!  You guessed it! 6 points awarded!
Score: 3
9 words remaining!
The jumble is: mrlube

Your guess: rumble

That's it!  You guessed it! 6 points awarded!
Score: 9
8 words remaining!
The jumble is: ssagles

Your guess: gklassles
Sorry, that's not it.

Your guess: glasses

That's it!  You guessed it! 7 points awarded!
Score: 16
7 words remaining!
The jumble is: wlla

Your guess: wall

That's it!  You guessed it! 4 points awarded!
Score: 20
6 words remaining!
The jumble is: bcuemlsr

Your guess: hint
And thats the way the cookie...
4 points deducted for using hint
Score: 16

Your guess: crumbles

That's it!  You guessed it! 8 points awarded!
Score: 24
5 words remaining!
The jumble is: ulmhbe

Your guess: humble

That's it!  You guessed it! 6 points awarded!
Score: 30
4 words remaining!
The jumble is: redabol

Your guess: hint
Going slowly, is it?
3 points deducted for using hint
Score: 27

Your guess: laboreds
Sorry, that's not it.

Your guess: labored

That's it!  You guessed it! 7 points awarded!
Score: 34
3 words remaining!
The jumble is: pessentrit

Your guess: persistent

That's it!  You guessed it! 10 points awarded!
Score: 44
2 words remaining!
The jumble is: mlbeju

Your guess: jumble

That's it!  You guessed it! 6 points awarded!
Score: 50
1 words remaining!
The jumble is: bmumle

Your guess: mumble

That's it!  You guessed it! 6 points awarded!
Score: 56
0 words remaining!

Thanks for playing.

Process returned 0 (0x0)   execution time : 94.877 s
Press any key to continue.
*/
