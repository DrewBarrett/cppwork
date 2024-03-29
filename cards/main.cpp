#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <ctime>
//#include "hand.h"
#include "deck.h"
#include "Button.h"
#include "allegro5/allegro_font.h"
#define ScreenWidth 1024
#define ScreenHeight 768
using namespace std;
//Drew Barrett
int init();
int setup(Deck &);
int transferToHand(vector<Card> *, int);
int transferToPile();
int drawPile(vector<Card> &, ALLEGRO_MOUSE_STATE &, int, int, int ,int, int, bool);
void restart(Deck &);

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_MOUSE_STATE state;


CONST INT MAINPILEY = 200;
CONST INT FOUNDATIONY = 50;


bool clicked = false;
bool hoverFoundation;
bool won = false;
bool cheat = false;
int xOffset = 10;
int cardx = 71;
int cardy = 96;
int turn = 0;
vector<Card> table[7];
vector<Card> foundation[4];
vector<Card> topDeck;
vector<Card> hand;
vector<Card> *source;
vector<Card> *hover;
int main()
{
	init();
	ALLEGRO_FONT *font = al_load_font("comic.ttf", 20, 0);
    if (!font) {
        fprintf(stderr, "Could not load 'comic.ttf'.\n");
        return -1;
    }
    ALLEGRO_BITMAP *rules = al_load_bitmap("rules.png");
    Deck game;
	//ALLEGRO_BITMAP *bmp = al_create_bitmap(1280, 640);
	//Card a('c', "Ace", 14, "c1.bmp");

	//while (!key[KEY_ESC])

		//Lets view the deck first in order:

	//for (int i = 0; i < 13; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		//blit(game.deal().getImg(), bmp, 0, 0, x + i * 75, y + j * 100, 71, 96);
	//		al_set_target_bitmap(bmp);
	//
	//		//al_draw_bitmap(game.deal().getImg(),x + i * 75, y + j * 100,0);
	//		//textout_ex(bmp, font, game.deal().getFileDir().c_str(),x + j * 12 , y + i*100, -1, 0);
	//	}
	//}
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	timer = al_create_timer(1.0 / 60);
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	bool redraw = true;
	bool title = true;
	Card c;
	setup(game);
	int clicktime = 0;
	Button btnRestart = Button(ScreenWidth/2, ScreenHeight - 100, "Restart");
	while (1) {
        if(!clicked){
            clicktime--;
        }
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		//al_get_next_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (title){
                title = false;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_A)
                cheat = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				break;
			//game.deal();
		}
		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if(title){
                title = false;
			}
			clicked = true;
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			clicked = false;
			transferToPile();
			al_get_mouse_state(&state);
			if(won && btnRestart.checkMouse(state) == 2){
                restart(game);
			}
		}
		if (redraw && al_is_event_queue_empty(queue)) {
            if(title){
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "Solitaire!");
                al_draw_bitmap(rules, (ScreenWidth / 2) - (al_get_bitmap_width(rules)/2) , 100, 0);
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, ScreenHeight - 150, ALLEGRO_ALIGN_CENTRE,
					"Press any key to continue or ESC to exit...");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, ScreenHeight - 100, ALLEGRO_ALIGN_CENTRE,
					"Created by Drew Barrett");
            }else{

                hover = NULL;
                hoverFoundation = false;
                al_get_mouse_state(&state);
                al_set_target_bitmap(al_get_backbuffer(display));
                al_clear_to_color(al_map_rgb(0, 0, 0));
                if (won){
                    al_draw_text(font, al_color_name("white"), ScreenWidth / 2, ScreenHeight - 50, ALLEGRO_ALIGN_CENTRE, "You Won!");
                    btnRestart.draw(state);
                }
                //al_draw_bitmap(bmp, bx, 0, 0);
                int x1 = 100 + xOffset;
                int y1 = 10;
                int x2 = x1 + cardx;
                int y2 = y1 + cardy;
                drawPile(topDeck,state,x1,y1,x2,y2,20,false);
                al_draw_textf(font, al_color_name("white"), 0, 120, ALLEGRO_ALIGN_LEFT, "Turn: %d", turn);
                x1 = 10 + xOffset;
                y1 = 10;
                x2 = x1 + cardx;
                y2 = y1 + cardy;
                int deckSize = 10;
                if(game.size()<10){
                    deckSize = game.size();
                }
                for (int i = 0; i < deckSize; i += 2) {
                    al_draw_bitmap(c.getImg(), i + 10, i + 10, 0);
                }
                if(state.x >= x1 && state.x <= x2 && state.y >= y1 && state.y <= y2){
                    al_draw_rectangle(x1, y1, x2, y2, al_color_name("cyan"), 1);
                    if(clicked && hand.size() == 0 && game.size() > 0 && clicktime < 0){
                        turn++;
                        clicktime = 5;
                        if(topDeck.size() > 0){
                            game.insert(topDeck.front());
                            topDeck.pop_back();
                        }
                        topDeck.push_back(game.deal());
                        topDeck[0].flip();
                    }
                }

                for (int i = 0; i < 7; i++) {
                    int x1 = i*(cardx + 20) + xOffset;
                    int y1 = MAINPILEY;
                    int x2 = x1 + cardx;
                    int y2 = y1 + cardy;
                    /*if (table[i].size() == 0) {
                        al_draw_rectangle(x1, y1, x2, y2, al_color_name("white"), 1);
                    }*/
                    /*if (state.y >= MAINPILEY && state.y <= y2) {
                        //al_draw_rectangle(x1,y1,x2,y2,al_color_name("white"),1);
                    }*/
                    /*for (int k = 0; k < table[i].size(); k++) {
                        al_draw_bitmap(table[i][k].getImg(), x1, y1 + k * 20, 0);
                    }*/
                    drawPile(table[i],state,x1,y1,x2,y2,20,false);
                }
                /*for (int i = 0; i < 7; i++) {
                    int x1 = i*(cardx + 20) + xOffset;
                    int y1 = MAINPILEY;
                    int x2 = x1 + cardx + 1;
                    int y2 = y1 + cardy + 1;
                    for (int k = table[i].size()-1; k >= 0; k--) {
                        if (table[i][k].isFlipped()) {
                            if ((state.y >= y1 + k * 20 && state.y <= y2 + (table[i].size() - 1) * 20)
                                && (state.x >= x1 && state.x <= x2)) {
                                al_draw_rectangle(x1, y1 + k * 20, x2, y2 + (table[i].size() - 1) * 20, al_color_name("cyan"), 1);
                                hover = &table[i];
                                transferToHand(&table[i], k);
                                break;
                            }
                        }
                    }
                }*/
                for (int i = 0; i < 4; i++) {
                    int x1 = i*(cardx + 20) + xOffset + 250;
                    int y1 = FOUNDATIONY;
                    int x2 = x1 + cardx + 1;
                    int y2 = y1 + cardy + 1;
                    /*if (foundation[i].size() == 0) {
                        al_draw_rectangle(x1, y1, x2, y2, al_color_name("white"), 1);
                    }
                    else {
                        al_draw_bitmap(foundation[i].back().getImg(), x1, y1, 0);
                        if ((state.y >= y1 && state.y <= y2)
                            && (state.x >= x1 && state.x <= x2)) {
                            al_draw_rectangle(x1, y1, x2, y2, al_color_name("cyan"), 1);
                            hover = &foundation[i];
                            transferToHand(&foundation[i], foundation[i].size() - 1);
                        }
                    }
                    //for (int k = 0; k < foundation[i].size(); k++) {
                    //	al_draw_bitmap(foundation[i][k].getImg(), x1, y1 + k * 20, 0);
                    //}

                    if ((state.y >= y1&& state.y <= y2)
                        && (state.x >= x1 && state.x <= x2)) {
                        al_draw_rectangle(x1, y1, x2, y2, al_color_name("cyan"), 1);
                        hover = &foundation[i];
                    }*/
                    drawPile(foundation[i],state,x1,y1,x2,y2,0,true);
                }

                for (int i = 0; i < hand.size(); i++) {
                    int x1 = state.x - (cardx/2);
                    int y1 = state.y;
                    int x2 = x1 + cardx;
                    int y2 = y1 + cardy;
                    al_draw_bitmap(hand[i].getImg(), x1, y1 + i * 20, 0);
                }
                //game.deal();
                //al_draw_bitmap(c.getImg(),30,30,0);
            }
			al_flip_display();
			redraw = false;
		}
	}

	al_destroy_display(display);
	return 0;
}

int transferToHand(vector<Card> *pile, int start) {
	if (clicked && hand.size()==0) {
		int size = pile->size() - start;
		for (int i = start; i < pile->size(); i++) {
			hand.push_back(pile->at(i));
		}
		for (int i = 0; i < size; i++) {
			pile->pop_back();
		}
		source = pile;
	}
	return 0;
}

int transferToPile() {
	if (hand.size() > 0) {
		if (hover != NULL && source != NULL && hover != source){
            if((hover->size() != 0 && !hover->back().isInDeck())
                || (hover->size() == 0 && (hand.front().getValue() == 13 || hand.front().getValue() == 1))){
                cout << hand.front().getValue() << endl;
                if(!hoverFoundation && ((hover->size() == 0 && hand.front().getValue() == 13) || (hover->size() > 0 && hover->back().getValue() == hand.front().getValue()+1))){
                    if((((hover->back().getSuit() == 's' || hover->back().getSuit() == 'c')&&(hand.front().getSuit() != 's' && hand.front().getSuit() != 'c'))
                       || ((hover->back().getSuit() == 'd' || hover->back().getSuit() == 'h')&&(hand.front().getSuit() != 'd' && hand.front().getSuit() != 'h')))|| hover->size() == 0){
                        for (int i = 0; i < hand.size(); i++) {
                            hover->push_back(hand.at(i));
                            hover->back().leaveDeck();
                        }
                        if (source->size() > 0 && !source->back().isFlipped()) {
                            source->back().flip();
                        }
                        hand.clear();
                        turn++;
                    }
                }
                else if(hoverFoundation && ((hover->size() == 0 && hand.front().getValue() == 1) || (hover->size() > 0 && hover->back().getValue() == hand.front().getValue()-1))){
                    if(hand.front().getValue() == 1 || (hand.size() == 1 && hand.front().getSuit() == hover->back().getSuit())){
                        for (int i = 0; i < hand.size(); i++) {
                            hover->push_back(hand.at(i));
                            hover->back().leaveDeck();
                        }
                        if (source->size() > 0 && !source->back().isFlipped()) {
                            source->back().flip();
                        }
                        hand.clear();
                        turn++;
                    }
                }
            }
		}
	}
	if (hand.size() > 0){
        cout << hand.front().getValue() << endl;
        for (int i = 0; i < hand.size(); i++) {
            source->push_back(hand.at(i));
        }
        hand.clear();
	}
    if(cheat||(foundation[0].size()==13&&foundation[1].size()==13&&foundation[2].size()==13&&foundation[3].size()==13)){
        won = true;
    }
	return 0;
}

int drawPile(vector<Card> &pile, ALLEGRO_MOUSE_STATE &state, int x1, int y1, int x2, int y2, int space, bool foundation){
    if (pile.size() == 0) {
        al_draw_rectangle(x1, y1, x2, y2, al_color_name("white"), 1);
    }
    for (int k = 0; k < pile.size(); k++) {
        al_draw_bitmap(pile[k].getImg(), x1, y1 + k * space, 0);
    }
    if ((state.y >= y1&& state.y <= y2)
        && (state.x >= x1 && state.x <= x2)) {
        hover = &pile;
        if(foundation){
            hoverFoundation = true;
        }
    }
    for (int k = pile.size()-1; k >= 0; k--) {
        if (pile[k].isFlipped()) {
            if ((state.y >= y1 + k * space && state.y <= y2 + (pile.size() - 1) * space)
                && (state.x >= x1 && state.x <= x2)) {
                al_draw_rectangle(x1, y1 + k * space, x2, y2 + (pile.size() - 1) * space, al_color_name("cyan"), 1);
                hover = &pile;
                if(foundation){
                    hoverFoundation = true;
                }
                transferToHand(&pile, k);
                break;
            }
        }
    }
	return 0;
}

int setup(Deck &d) {
    d.shuffleDeck();
	for (int k = 0; k < 7; k++) {
		for (int i = 6; i >= k; i--) {
			table[i].push_back(d.deal());
			table[i].back().leaveDeck();
		}
	}
	for (int i = 0; i < 7; i++) {
		table[i].back().flip();
	}
	return 0;
}

void restart(Deck &d){
    d = Deck();
    won = false;
    cheat = false;
    turn = 0;
    for(int i = 0; i < 7; i++){
        table[i].clear();
    }
    for(int i = 0; i < 4; i++){
        foundation[i].clear();
    }
    topDeck.clear();
    hand.clear();
    setup(d);
}

int init()
{
	/* add other initializations here */
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	display = al_create_display(1024, 768);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_init_image_addon();
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();
	return 0;
}

