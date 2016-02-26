#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "Button.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
using namespace std;
//Dynamic Link
//Drew Barrett
#define ScreenWidth 1024
#define ScreenHeight 768
int init();
void drawMan(int);
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_MOUSE_STATE state;
ALLEGRO_BITMAP *bg;

int main(int argc, char **argv)
{
    init();
    bg = al_load_bitmap("bg.png");
    if(!bg){
        cout << "bg failed";
        return -1;
    }
    ALLEGRO_FONT *font = al_load_font("comic.ttf", 20, 0);
    if (!font) {
        fprintf(stderr, "Could not load 'comic.ttf'.\n");
        return -1;
    }
    ALLEGRO_SAMPLE *sndWrong = al_load_sample("Cave_Johnson_cave_laugh04.wav");
    if(!sndWrong) {
        cout << "sndWrong failed to load";
        return -1;
    }
    ALLEGRO_SAMPLE *sndCorrect = al_load_sample("Cave_Johnson_yes.wav");
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
	timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    bool redraw = true;
    bool title = true;
     // set-up
    const int MAX_WRONG = 8;  // maximum number of incorrect guesses allowed

    vector<string> words;  // collection of possible words to guess
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");
    words.push_back("APERTURE");
    words.push_back("SCIENCE");
    words.push_back("PORTAL");
    words.push_back("TEST");
    words.push_back("ASBESTOS");

    srand(time(0));
    random_shuffle(words.begin(), words.end());
    string THE_WORD = words[0];            // word to guess
    int wrong = 0;
    int incorrect = 0;
    int correct = 0;                              // number of incorrect guesses
    string soFar(THE_WORD.size(), '-');          // word guessed so far
    string used = "";                            // letters already guessed
    bool keyPressed = false;
    int key = 0;
    bool printStuff = true;
    bool won = false;
    string message = "";
    cout << "Welcome to Hangman.  Good luck!\n";
    Button btnRestart = Button(ScreenWidth/2, ScreenHeight - 100, "Restart");
    Button btnNext = Button(ScreenWidth/2, ScreenHeight - 100, "Next Word");
    Button btnFinish = Button(ScreenWidth/2, ScreenHeight - 100, "Finish Game");
    Button btnQuit = Button(ScreenWidth/2, ScreenHeight - 50, "Quit Early");
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
            //cout << event.keyboard.keycode << endl;
            if(title){
                title = false;
            }else{
                keyPressed = true;
                key = event.keyboard.keycode;
                cout << al_keycode_to_name(event.keyboard.keycode) << endl;
            }
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if(title){
                title = false;
			}
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			al_get_mouse_state(&state);
			if((wrong == MAX_WRONG || won) && btnRestart.checkMouse(state) == 2){
                words.clear();
                words.push_back("GUESS");
                words.push_back("HANGMAN");
                words.push_back("DIFFICULT");
                words.push_back("APERTURE");
                words.push_back("SCIENCE");
                words.push_back("PORTAL");
                words.push_back("TEST");
                words.push_back("ASBESTOS");
                random_shuffle(words.begin(), words.end());
                THE_WORD = words[0];            // word to guess
                wrong = 0;
                incorrect = 0;
                correct = 0;                              // number of incorrect guesses
                soFar = "";
                soFar.resize(THE_WORD.size(), '-');         // word guessed so far
                used = "";                            // letters already guessed
                keyPressed = false;
                key = 0;
                printStuff = true;
                won = false;
                message = "";
                title = true;
			}
			if(soFar == THE_WORD && btnNext.checkMouse(state) == 2 && words.size() > 1){
                //if(words.size() >= 1){
                words.erase(words.begin());
                //}
                if(words.size() > 0){
                    THE_WORD = words[0];
                    soFar = "";
                    soFar.resize(THE_WORD.size(), '-');
                    //wrong = 0;
                    used = "";
                    message = "";
                    printStuff = true;
                    keyPressed = false;
                    correct++;
                }
			}
			if(soFar == THE_WORD && btnFinish.checkMouse(state) == 2 && words.size()== 1){
                won = true;
			}
			if(btnQuit.checkMouse(state) == 2 && won != true){
                won = true;
			}
		}
        if (event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue)) {
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(bg,0,0,0);
            if(title){
                //al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "Hang Man!");
                al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 30, ALLEGRO_ALIGN_CENTRE,
                             "You have to guess the correct word by guessing letters in it with your keyboard");
                al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 60, ALLEGRO_ALIGN_CENTRE,
                             "If you guess incorrectly too many times you will lose!");
                al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 90, ALLEGRO_ALIGN_CENTRE,
                             "The more words you guess completely the better you have done!");
                //al_draw_bitmap(rules, (ScreenWidth / 2) - (al_get_bitmap_width(rules)/2) , 100, 0);
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, ScreenHeight - 150, ALLEGRO_ALIGN_CENTRE,
					"Press any key to continue or ESC to exit...");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, ScreenHeight - 100, ALLEGRO_ALIGN_CENTRE,
					"Created by Drew Barrett");
            }else if(won){
                al_get_mouse_state(&state);
                if(soFar == THE_WORD){
                    al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "You win!");
                }else{
                    al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "You lose!");
                }
                al_draw_textf(font, al_color_name("white"), ScreenWidth / 2, 30, ALLEGRO_ALIGN_CENTRE,
                              "You guessed %d words correctly. You missed %d words", correct, words.size());
                btnRestart.draw(state);
                drawMan(wrong);
            }else{
                //al_clear_to_color(al_map_rgb(0, 0, 0));
                //if ((wrong < MAX_WRONG) && (soFar != THE_WORD))
                //{
                drawMan(wrong);
                if(printStuff){
                    cout << "\n\nYou have " << (MAX_WRONG - wrong) << " incorrect guesses left.\n";
                    cout << "\nYou've used the following letters:\n" << used << endl;
                    cout << "\nSo far, the word is:\n" << soFar << endl;
                }
                al_draw_textf(font, al_color_name("white"), ScreenWidth / 2, 30, ALLEGRO_ALIGN_CENTRE,
                              "You have %d incorrect guesses left.", (MAX_WRONG - wrong));
                al_draw_textf(font, al_color_name("white"), ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE,
                              "You have guessed %d words correctly. There are %d left.", correct, words.size());
                al_draw_textf(font, al_color_name("white"), ScreenWidth / 2, 60, ALLEGRO_ALIGN_CENTRE,
                              "You've used the following letters: %s", used.c_str());
                al_draw_textf(font, al_color_name("white"), ScreenWidth / 2, 90, ALLEGRO_ALIGN_CENTRE,
                              "So far, the word is: %s", soFar.c_str());
                al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 120, ALLEGRO_ALIGN_CENTRE,
                              message.c_str());
                printStuff = false;
                char guess;
                //cout << "\n\nEnter your guess: ";
                al_get_mouse_state(&state);
                btnQuit.draw(state);
                if (wrong == MAX_WRONG){
                    cout << "\nYou've been hanged!";
                    message = "";
                    message = "You've been hanged! The word was " + THE_WORD;
                    btnRestart.draw(state);
                }else if(soFar == THE_WORD){
                    cout << "\nYou guessed it!";
                    message = "";
                    message = "You guessed it! The word was " + THE_WORD;

                    if(words.size()>1){
                        btnNext.draw(state);
                    }else{
                        btnFinish.draw(state);
                    }
                }else{
                    al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 150, ALLEGRO_ALIGN_CENTRE, "Type your guess!");
                    //cin >> guess;keyPressed = false;
                    if(keyPressed){
                        printStuff = true;
                        string keyName = al_keycode_to_name(key);
                        guess = keyName[0];
                        keyPressed = false;
                        if(used.find(guess) == string::npos){
                            used += guess;
                            if (THE_WORD.find(guess) != string::npos)
                            {
                                al_play_sample(sndCorrect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                cout << "That's right! " << guess << " is in the word.\n";
                                message = "";
                                message += "That's right! ";
                                message += guess;
                                message += " is in the word.";
                                //message = 'That\'s right! ' + guess + 'is in the word.';
                                cout << message;

                                // update soFar to include newly guessed letter
                                for (int i = 0; i < THE_WORD.length(); ++i)
                                    if (THE_WORD[i] == guess)
                                        soFar[i] = guess;
                            }
                            else
                            {
                                al_play_sample(sndWrong, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                cout << "Sorry, " << guess << " isn't in the word.\n";
                                //message = 'Sorry, ' + guess + 'isn\'t in the word.';
                                message = "";
                                message += "Sorry, ";
                                message += guess;
                                message += " isn't in the word.";
                                ++wrong;
                            }
                        }
                    }
                }

                //}

                //cout << "\nThe word was " << THE_WORD << endl;
            }
            al_flip_display();
        }
    }
    al_destroy_display(display);
    return 0;
}

void drawMan(int wrong){
    if(wrong>=1){
        al_draw_circle(ScreenWidth/2,(ScreenHeight/2) - 130, 30, al_color_name("white"), 2);
        if(wrong>=2){
            al_draw_line(ScreenWidth/2, (ScreenHeight/2)-100, ScreenWidth/2, ScreenHeight/2,al_color_name("white"),2);
            if(wrong >= 3){
                al_draw_line(ScreenWidth/2, (ScreenHeight/2) - 50, (ScreenWidth/2) - 60, (ScreenHeight/2) - 70,al_color_name("white"),2);
                if(wrong >= 4){
                    al_draw_line(ScreenWidth/2, (ScreenHeight/2) - 50, (ScreenWidth/2) + 60, (ScreenHeight/2) - 70,al_color_name("white"),2);
                    if(wrong >= 5){
                        al_draw_line(ScreenWidth/2, (ScreenHeight/2), (ScreenWidth/2) + 50, (ScreenHeight/2) + 80,al_color_name("white"),2);
                        if(wrong >= 6){
                            al_draw_line(ScreenWidth/2, (ScreenHeight/2), (ScreenWidth/2) - 50, (ScreenHeight/2) + 80,al_color_name("white"),2);
                            if(wrong >= 7){
                                al_draw_line(ScreenWidth/2+90, (ScreenHeight/2)-200, ScreenWidth/2+90, ScreenHeight/2 + 100,al_color_name("white"),2);
                                al_draw_line(ScreenWidth/2+60, (ScreenHeight/2)+100, ScreenWidth/2+120, ScreenHeight/2 + 100,al_color_name("white"),2);
                                if(wrong >= 8){
                                    al_draw_line(ScreenWidth/2, (ScreenHeight/2) - 160, ScreenWidth/2, ScreenHeight/2 -200,al_color_name("white"),2);
                                    al_draw_line(ScreenWidth/2,ScreenHeight/2 -200, ScreenWidth/2+90, ScreenHeight/2 -200,al_color_name("white"),2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

int init(){

    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    display = al_create_display(ScreenWidth, ScreenHeight);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    al_init_image_addon();
    if(!al_init_primitives_addon()){
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
}
