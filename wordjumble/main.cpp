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
    const int NUM_WORDS = 5;
    const string WORDS[NUM_WORDS][NUM_FIELDS] =
    {
        {"wall", "Do you feel you're banging your head against something?"},
        {"glasses", "These might help you see the answer."},
        {"labored", "Going slowly, is it?"},
        {"persistent", "Keep at it."},
        {"jumble", "It's what the game is all about."}
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

The jumble is: ujbelm

Your guess: jumble

That's it!  You guessed it! 6 points awarded!
Score: 6
4 words remaining!
The jumble is: lalw

Your guess: wall

That's it!  You guessed it! 4 points awarded!
Score: 10
3 words remaining!
The jumble is: rtpssietne

Your guess: persistent

That's it!  You guessed it! 10 points awarded!
Score: 20
2 words remaining!
The jumble is: albeord

Your guess: hint
Going slowly, is it?
3 points deducted for using hint
Score: 17

Your guess: labored

That's it!  You guessed it! 7 points awarded!
Score: 24
1 words remaining!
The jumble is: gassles

Your guess: glassess
Sorry, that's not it.

Your guess: glasses

That's it!  You guessed it! 7 points awarded!
Score: 31
0 words remaining!

Thanks for playing.

Process returned 0 (0x0)   execution time : 28.289 s
Press any key to continue.
*/
