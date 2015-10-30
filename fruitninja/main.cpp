#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <ctime>
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
bool click = false;
ALLEGRO_MOUSE_STATE state;
int generateFruit();
int lastFruit = 0;
std::vector<double> fruitx;
std::vector<double> fruity;

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
	ALLEGRO_BITMAP *bg = al_load_bitmap("bg.jpg");
	if (!bg) {
		fprintf(stderr, "error loading bg.jpg.\n");
		return -1;
	}
	ALLEGRO_BITMAP *apple = al_load_bitmap("apple.png");
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	timer = al_create_timer(1.0 / 60);
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	bool title = true;
	bool redraw = true;
	std::vector<double> tracerx;
	std::vector<double> tracery;
	srand(time(0));
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
			if (title) {
				title = false;
			}
			else {
				tracerx.clear();
				tracery.clear();
				click = true;
			}
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			click = false;
		}
		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		if (redraw && al_is_event_queue_empty(queue)) {
			al_set_target_bitmap(al_get_backbuffer(display));
			if (title) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, white, ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "Fruit Ninja!");
				al_draw_text(font, white, ScreenWidth / 2, 50, ALLEGRO_ALIGN_CENTRE, "...");
				al_draw_text(font, white, ScreenWidth / 2, 100, ALLEGRO_ALIGN_CENTRE, "...");
				al_draw_text(font, white, ScreenWidth / 2, 150, ALLEGRO_ALIGN_CENTRE,
					"...");
				al_draw_text(font, white, ScreenWidth / 2, 200, ALLEGRO_ALIGN_CENTRE,
					"...");
				al_draw_text(font, white, ScreenWidth / 2, 250, ALLEGRO_ALIGN_CENTRE,
					"Press any key to continue or ESC to exit...");
				al_draw_text(font, white, ScreenWidth / 2, ScreenHeight - 100, ALLEGRO_ALIGN_CENTRE,
					"Created by Drew Barrett");
			}
			else {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_scaled_bitmap(bg, 0, 0, 2560, 1600, 0, 0, ScreenWidth, ScreenHeight, 0);
				generateFruit();
				for (int i = 0; i < fruitx.size(); i++) {
					fruity[i]--;
					if (fruity[i] < 10) {
						fruity.erase(fruity.begin() + i);
						fruitx.erase(fruitx.begin() + i);
					}
					int const DWIDTH = 3172 / 50;
					int const DHEIGHT = 2709 / 50;
					al_draw_filled_circle(fruitx[i], fruity[i], 20, al_color_name("white"));
					al_draw_scaled_bitmap(apple, 0, 0, 3172, 2709, fruitx[i] - DWIDTH / 2, fruity[i] - DHEIGHT / 2, DWIDTH, DHEIGHT, 0);
				}
				if (click) {
					al_get_mouse_state(&state);
					tracerx.push_back(state.x);
					tracery.push_back(state.y);
					if (tracerx.size() > 8) {
						tracerx.erase(tracerx.begin());
						tracery.erase(tracery.begin());
					}
					float tracerfloat[8];
					if (tracerx.size() >= 8) {
						for (int i = 0; i < 8; i += 2) {
							tracerfloat[i] = tracerx[i];
							tracerfloat[i + 1] = tracery[i];
						}
						al_draw_spline(tracerfloat, al_color_name("white"), 2);
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

int generateFruit() {
	if (fruitx.size() < 10 && lastFruit < 0) {
		fruitx.push_back((rand() % (ScreenWidth - 40))+20);
		fruity.push_back(ScreenHeight + 10);
		lastFruit = 40;
	}
	lastFruit--;
	return 0;
}

int init()
{
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
