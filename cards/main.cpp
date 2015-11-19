#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <ctime>
#include "hand.h"
#include "deck.h"
using namespace std;

int init();
int setup(Deck *);

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_MOUSE_STATE state;



CONST INT MAINPILEY = 200;
CONST INT FOUNDATIONY = 50;

int xOffset = 10;
int cardx = 71;
int cardy = 96;
vector<Card> table[7];
vector<Card> foundation[4];
vector<Card> hand;
int main()
{
    init();
    Deck game;
    ALLEGRO_BITMAP *bmp = al_create_bitmap(1280, 640);
    Card a('c', "Ace", 14, "c1.bmp");

    //while (!key[KEY_ESC])

        //Lets view the deck first in order:

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            //blit(game.deal().getImg(), bmp, 0, 0, x + i * 75, y + j * 100, 71, 96);
            al_set_target_bitmap(bmp);
            game.shuffleDeck();
            //al_draw_bitmap(game.deal().getImg(),x + i * 75, y + j * 100,0);
            //textout_ex(bmp, font, game.deal().getFileDir().c_str(),x + j * 12 , y + i*100, -1, 0);
        }
    }
    queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	timer = al_create_timer(1.0 / 60);
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	bool redraw = true;
	setup(&game);
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        //al_get_next_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
            //game.deal();
        }
        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){

        }
        if (redraw && al_is_event_queue_empty(queue)) {
            al_get_mouse_state(&state);
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //al_draw_bitmap(bmp, bx, 0, 0);
            Card c;
            for (int i = 0; i<10; i+=2){
                al_draw_bitmap(c.getImg(),i+10,i+10,0);
            }
            for (int i=0; i<7; i++){
                int x1 = i*(cardx+20)+xOffset;
                int y1 = MAINPILEY;
                int x2 = x1 + cardx;
                int y2 = y1 + cardy;
                if(table[i].size()==0){
                    al_draw_rectangle(x1,y1,x2,y2,al_color_name("white"),1);
                }
                if(state.y >= MAINPILEY && state.y <= y2){
                    //al_draw_rectangle(x1,y1,x2,y2,al_color_name("white"),1);
                }
                for(int k=0; k<table[i].size(); k++){
                    al_draw_bitmap(table[i][k].getImg(),x1,y1 + k*20,0);
                }

            }
            for(int i=0; i<7; i++){
                int x1 = i*(cardx+20)+xOffset;
                int y1 = MAINPILEY;
                int x2 = x1 + cardx+1;
                int y2 = y1 + cardy+1;
                for(int k=0; k<table[i].size(); k++){
                    if (table[i][k].isFlipped()){
                        if((state.y >= y1 + k*20 && state.y <= y2+(table[i].size()-1)*20)
                           &&(state.x >= x1 && state.x <= x2)){
                            al_draw_rectangle(x1,y1+k*20,x2,y2+k*20,al_color_name("white"),1);
                        }
                    }
                }
            }
            for (int i=0; i<4; i++){
                int x1 = i*(cardx+20)+xOffset+250;
                int y1 = FOUNDATIONY;
                int x2 = x1 + cardx;
                int y2 = y1 + cardy;
                al_draw_rectangle(x1,y1,x2,y2,al_color_name("white"),1);
                for(int k=0; k<foundation[i].size(); k++){
                    al_draw_bitmap(foundation[i][k].getImg(),x1,y1 + k*20,0);
                }
            }
            //game.deal();
            //al_draw_bitmap(c.getImg(),30,30,0);
            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_display(display);
    return 0;
}

int setup(Deck *d){
    for(int k = 0; k < 7; k++){
        for(int i = 6; i>=k; i--){
            table[i].push_back(d->deal());
        }
    }
    for(int i = 0; i<7;i++){
        table[i].back().flip();
    }
    return 0;
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

