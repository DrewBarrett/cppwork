#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "Button.h"
//Dynamic Link
//Drew Barrett
#define ScreenWidth 1024
#define ScreenHeight 768
int init();
bool checkForWall(int, int, int, int);
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_MOUSE_STATE state;
ALLEGRO_BITMAP *bg;

int main(int argc, char **argv)
{
    init();
    bg = al_load_bitmap("bg.png");
    ALLEGRO_FONT *font = al_load_font("comic.ttf", 20, 0);
    if (!font) {
        fprintf(stderr, "Could not load 'comic.ttf'.\n");
        return -1;
    }
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
	timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    bool redraw = true;
    bool title = false;
    int cx = ScreenWidth/2;
    int cy = ScreenHeight/2;
    int cr = 20;
    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                break;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_D){
                right = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_A){
                left = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_W){
                up = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_S){
                down = true;
            }
        }
        if (event.type == ALLEGRO_EVENT_KEY_UP){
            std::cout << "key up" << std::endl;
            std::cout << al_keycode_to_name(event.keyboard.keycode) << std::endl;
            std::cout << cx << ", " << cy << std::endl;
            if (event.keyboard.keycode == ALLEGRO_KEY_D){
                right = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_A){
                left = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_W){
                up = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_S){
                down = false;
            }
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if(title){
                title = false;
			}
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			al_get_mouse_state(&state);
		}
        if (event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(bg,0,0,0);
            if(title){
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "Solitaire!");
                //al_draw_bitmap(rules, (ScreenWidth / 2) - (al_get_bitmap_width(rules)/2) , 100, 0);
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, ScreenHeight - 150, ALLEGRO_ALIGN_CENTRE,
					"Press any key to continue or ESC to exit...");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, ScreenHeight - 100, ALLEGRO_ALIGN_CENTRE,
					"Created by Drew Barrett");
            }else{
                if(right){
                    if(!checkForWall(cx+cr,cy-cr,cx+cr,cy+cr)){
                        cx+=2;
                    }
                }
                if(left){
                    if(!checkForWall(cx-cr,cy-cr,cx-cr,cy+cr)){
                        cx-=2;
                    }
                }
                if(up){
                    if(!checkForWall(cx-cr,cy-cr,cx+cr,cy-cr)){
                        cy-=2;
                    }
                }
                if(down){
                    cy+=2;
                }
                al_draw_filled_circle(cx, cy, cr, al_color_name("white"));
            }
            al_flip_display();
        }
    }
    al_destroy_display(display);
    return 0;
}

bool checkForWall(int startx, int starty, int stopx, int stopy){
    if(startx == stopx){
        for(int i = starty; i < stopy; i+= stopy-starty-1){
            ALLEGRO_COLOR pixel = al_get_pixel(bg, startx, i);
            //std::cout << pixel.r << pixel.b << pixel.g;
            if(pixel.r == al_color_name("white").r && pixel.g == al_color_name("white").g && pixel.b == al_color_name("white").b){
                return true;
            }
        }
    }
    if(starty == stopy){
        for(int i = startx; i < stopx; i+= stopx-startx-1){
            ALLEGRO_COLOR pixel = al_get_pixel(bg, i, starty);
            //std::cout << pixel.r << pixel.b << pixel.g;
            if(pixel.r == al_color_name("white").r && pixel.g == al_color_name("white").g && pixel.b == al_color_name("white").b){
                return true;
            }
        }
    }
    return false;
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
}
