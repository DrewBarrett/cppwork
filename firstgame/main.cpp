#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
//Dynamic Link
#define ScreenWidth 640
#define ScreenHeight 480
int init();
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;

int main(int argc, char **argv)
{
    init();
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_FONT *font = al_load_font("comic.ttf", 20, 0);
    if (!font) {
        fprintf(stderr, "Could not load 'comic.ttf'.\n");
        return -1;
    }
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());

    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    bool title = true;
    bool down = false;
    bool up = false;
    bool reset = true;
    bool gameover = false;
    bool roundwin = false;
    bool roundlose = false;
    const int PADDLESPEED = 5;
    int y1 = 10;
    int y2 = 10;
    int won = 0;
    int lost = 0;
    int recent = 0;
    double x = 2;
    double y = 2;
    double startx = ScreenWidth / 4;
    double starty = ScreenHeight / 4;
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
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                down = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                up = true;
            }
            if(!title)
                reset = false;
            title = false;
            roundlose = false;
            roundwin = false;
        }
        if (event.type == ALLEGRO_EVENT_KEY_UP) {
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                down = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                up = false;
            }
        }
        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue)) {
            al_set_target_bitmap(al_get_backbuffer(display));
            if(title) {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, white, ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "Pong!");
                al_draw_text(font, white, ScreenWidth / 2, 50, ALLEGRO_ALIGN_CENTRE, "Arrow keys to control paddle");
                al_draw_text(font, white, ScreenWidth / 2, 100, ALLEGRO_ALIGN_CENTRE, "You get a point for winning a match");
                al_draw_text(font, white, ScreenWidth / 2, 150, ALLEGRO_ALIGN_CENTRE,
                             "You win a match by having the ball go out of bounds on the right side");
                al_draw_text(font, white, ScreenWidth / 2, 200, ALLEGRO_ALIGN_CENTRE,
                             "Best of 3 wins the game!");
                al_draw_text(font, white, ScreenWidth / 2, 250, ALLEGRO_ALIGN_CENTRE,
                             "Press any key to continue or ESC to exit...");
                al_draw_text(font, white, ScreenWidth / 2, ScreenHeight - 100, ALLEGRO_ALIGN_CENTRE,
                             "Created by Drew Barrett");
            } else {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                if (reset || gameover) {
                    startx = ScreenWidth / 2;
                    starty = ScreenHeight / 2;

                    x = 2;
                    y = 2;
                    y1 = ScreenHeight / 2 - (50 / 2);
                    y2 = ScreenHeight / 2 - (50 / 2);
                    if(lost >= 2) {
                        al_draw_text(font, white, ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTRE, "Game Over - You lose...");
                        gameover = true;
                    } else if (won >= 2) {
                        al_draw_text(font, white, ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTRE, "Game Over - You win!");
                        gameover = true;
                    } else {
                        al_draw_text(font, white, ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTRE, "Press any key to start...");
                    }
                    if(roundlose) {
                        al_draw_text(font, white, ScreenWidth / 2, ScreenHeight / 2 - 50, ALLEGRO_ALIGN_CENTRE, "Round lost...");
                    }
                    if(roundwin) {
                        al_draw_text(font, white, ScreenWidth / 2, ScreenHeight / 2 - 50, ALLEGRO_ALIGN_CENTRE, "Round Won!");
                    }
                    al_draw_text(font, white, ScreenWidth / 2, ScreenHeight / 2 + 50, ALLEGRO_ALIGN_CENTRE, "Press ESC to quit...");
                }
                x *= 1.0005;//increase speed
                y *= 1.0005;

                if(down) {
                    if(y1 < ScreenHeight - 50)
                        y1 += PADDLESPEED;
                }
                if(up) {
                    if(y1 > 0)
                        y1 -= PADDLESPEED;
                }
                //second paddle
                if(y2 + (50 / 2) < starty && y2 + 50 <= ScreenHeight - PADDLESPEED - 1) {
                    if(starty - (y2 + (50 / 2)) >= PADDLESPEED) {
                        y2 += PADDLESPEED;
                    } else {
                        y2 += starty - (y2 + (50 / 2));
                    }
                }
                if(y2 + (50 / 2) > starty && y2 >= PADDLESPEED - 1) {
                    if((y2 + (50 / 2)) - starty > PADDLESPEED) {
                        y2 -= PADDLESPEED;
                    } else {
                        y2 -= (y2 + (50 / 2)) - starty;
                    }
                }
                std::cout << x << ", " << y << std::endl;

                al_draw_filled_rectangle(10, y1, 20, y1 + 50, yellow);
                al_draw_filled_rectangle(ScreenWidth - 10, y2, ScreenWidth - 20, y2 + 50, yellow);
                if(starty >= ScreenHeight - 5 || starty <= 5) {
                    //y *= -1.0001;
                    //y *= -.9999;
                    y *= -1;
                }
                if(startx <= 5) {
                    lost++;
                    reset = true;
                    roundlose = true;

                    //lose = true;
                }
                if(startx >= ScreenWidth - 5) {
                    won++;
                    reset = true;
                    roundwin = true;

                    //win = true;
                }
                if ((startx <= 25 && startx >= 10 && starty >= y1 && starty <= y1 + 50 ||
                        startx >= ScreenWidth - 25 && startx <= ScreenWidth - 10 && starty >= y2 && starty <= y2 + 50 ) && recent <= 0) {
                    x *= -1;
                    recent = 15;
                }
                recent--;
                startx += x;
                starty += y;
                al_draw_filled_circle(startx, starty, 5, yellow);
                al_draw_textf(font, white, 0 , 0, ALLEGRO_ALIGN_LEFT, "Player score: %d", won);
                al_draw_textf(font, white, ScreenWidth, 0, ALLEGRO_ALIGN_RIGHT, "Enemy score: %d", lost);
            }
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_display(display);

    return 0;
}

int init()
{
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    display = al_create_display(640, 480);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_init_image_addon();
    if(!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_install_keyboard();
}
