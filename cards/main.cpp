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

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;

int main()
{
    init();
    Deck game;
    int x = 10, y = 10;
    int bx = 0;
    ALLEGRO_BITMAP *bmp = al_create_bitmap(1280, 640);
    Card a('c', "Ace", 14, "c1.bmp");
    //while (!key[KEY_ESC])
    {
        //Lets view the deck first in order:

        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 4; j++) {
                //blit(game.deal().getImg(), bmp, 0, 0, x + i * 75, y + j * 100, 71, 96);
                al_set_target_bitmap(bmp);
                al_draw_bitmap(game.deal().getImg(),x + i * 75, y + j * 100,0);
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
        while (1) {
            ALLEGRO_EVENT event;
            al_wait_for_event(queue, &event);
            //al_get_next_event(queue, &event);

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                break;
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    break;
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                    bx+= 20;
                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT){
                    bx-= 20;
                }
            }
            if (event.type == ALLEGRO_EVENT_TIMER) {
                redraw = true;
            }
            if (redraw && al_is_event_queue_empty(queue)) {
                al_set_target_bitmap(al_get_backbuffer(display));
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(bmp, bx, 0, 0);
                al_flip_display();
                redraw = false;
            }
        }
    }
    al_destroy_display(display);
    return 0;
}

int init()
{
    /* add other initializations here */
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    display = al_create_display(640, 480);
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

