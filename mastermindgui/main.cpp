#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_color.h>
//Dynamic Link
#define ScreenWidth 640
#define ScreenHeight 480
int init();
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_MOUSE_STATE state;
int row = 0;
int column = 0;

int incrementcol();

int main(int argc, char **argv)
{
    init();
    double const CIRCLE_RADIUS = 15;
    double const CIRCLE_Y = 40;
    ALLEGRO_COLOR colors[10][4] = { };
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 4; j++) {
            colors[i][j] = al_color_name("gray");
        }
    }
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
    bool title = true;
    bool redraw = true;
    bool mouse = false;
    int circlepos[] = {50 - 20, 100 - 20, 150 - 20, 200 - 20, 250 - 20, 300 - 20};
    enum {red, blue, yellow, green, white, orange};
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        //al_get_next_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
            title = false;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(title){
                title = false;
            }else{
                mouse = true;
                al_get_mouse_state(&state);
            }
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

        }
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {

        }
        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue)) {
            al_set_target_bitmap(al_get_backbuffer(display));
            if(title) {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_color_name("blue"), ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "Mastermind!");
                al_draw_text(font, al_color_name("blue"), ScreenWidth / 2, 50, ALLEGRO_ALIGN_CENTRE, "...");
                al_draw_text(font, al_color_name("blue"), ScreenWidth / 2, 100, ALLEGRO_ALIGN_CENTRE, "...");
                al_draw_text(font, al_color_name("blue"), ScreenWidth / 2, 150, ALLEGRO_ALIGN_CENTRE,
                             "...");
                al_draw_text(font, al_color_name("blue"), ScreenWidth / 2, 200, ALLEGRO_ALIGN_CENTRE,
                             "...");
                al_draw_text(font, al_color_name("blue"), ScreenWidth / 2, 250, ALLEGRO_ALIGN_CENTRE,
                             "Press any key to continue or ESC to exit...");
                al_draw_text(font, al_color_name("blue"), ScreenWidth / 2, ScreenHeight - 100, ALLEGRO_ALIGN_CENTRE,
                             "Created by Drew Barrett");
            } else {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                if(mouse) {
                    std::cout << state.x << ", " << state.y << std::endl;
                    if(state.y >= CIRCLE_Y - CIRCLE_RADIUS && state.y <= CIRCLE_Y + CIRCLE_RADIUS) {
                        if(state.x >= circlepos[red] - CIRCLE_RADIUS && state.x <= circlepos[red] + CIRCLE_RADIUS) {
                            colors[row][column] = al_color_name("red");
                            incrementcol();
                        }
                        if(state.x >= circlepos[blue] - CIRCLE_RADIUS && state.x <= circlepos[blue] + CIRCLE_RADIUS) {
                            colors[row][column] = al_color_name("blue");
                            incrementcol();
                        }
                        if(state.x >= circlepos[yellow] - CIRCLE_RADIUS && state.x <= circlepos[yellow] + CIRCLE_RADIUS) {
                            colors[row][column] = al_color_name("yellow");
                            incrementcol();
                        }
                        if(state.x >= circlepos[green] - CIRCLE_RADIUS && state.x <= circlepos[green] + CIRCLE_RADIUS) {
                            colors[row][column] = al_color_name("green");
                            incrementcol();
                        }
                        if(state.x >= circlepos[white] - CIRCLE_RADIUS && state.x <= circlepos[white] + CIRCLE_RADIUS) {
                            colors[row][column] = al_color_name("white");
                            incrementcol();
                        }
                        if(state.x >= circlepos[orange] - CIRCLE_RADIUS && state.x <= circlepos[orange] + CIRCLE_RADIUS) {
                            colors[row][column] = al_color_name("orange");
                            incrementcol();
                        }
                    }
                    //colors[0][0] = al_color_name("white");
                    mouse = false;
                }
                al_draw_filled_circle(circlepos[red], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("red"));
                al_draw_filled_circle(circlepos[blue], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("blue"));
                al_draw_filled_circle(circlepos[yellow], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("yellow"));
                al_draw_filled_circle(circlepos[green], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("green"));
                al_draw_filled_circle(circlepos[white], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("white"));
                al_draw_filled_circle(circlepos[orange], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("orange"));
                for(int j = 0; j < 10; j++) {
                    for(int i = 0; i < 4; i++) {
                        al_draw_filled_circle(400 + i * 40, CIRCLE_Y + j * 40, CIRCLE_RADIUS, colors[j][i]);
                    }
                }
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

int incrementcol()
{
    column++;
    if(column == 4) {
        column = 0;
        row++;
    }
}
