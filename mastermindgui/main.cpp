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
enum { red, blue, yellow, green, white, orange };
ALLEGRO_COLOR colors[10][8] = {};
int pattern[4];
std::vector<int> patternGuess;
bool won = false;
bool lost = false;

int incrementcol();
int hint();

int main(int argc, char **argv)
{
	init();
	double const CIRCLE_RADIUS = 15;
	double const CIRCLE_Y = 40;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 8; j++) {
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
	int circlepos[] = { 50 - 20, 100 - 20, 150 - 20, 200 - 20, 250 - 20, 300 - 20 };
	int code;
	srand(time(0));
	for (int i = 0; i < 4; i++) {
		code = rand() % 6;
		pattern[i] = code;
		std::cout << pattern[i] << std::endl;//debug
	}
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
			if (title) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 0, ALLEGRO_ALIGN_CENTRE, "Mastermind!");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 50, ALLEGRO_ALIGN_CENTRE, "...");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 100, ALLEGRO_ALIGN_CENTRE, "...");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 150, ALLEGRO_ALIGN_CENTRE,
					"...");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 200, ALLEGRO_ALIGN_CENTRE,
					"...");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, 250, ALLEGRO_ALIGN_CENTRE,
					"Press any key to continue or ESC to exit...");
				al_draw_text(font, al_color_name("white"), ScreenWidth / 2, ScreenHeight - 100, ALLEGRO_ALIGN_CENTRE,
					"Created by Drew Barrett");
			}
			else {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				if (mouse && !(won || lost)) {
					std::cout << state.x << ", " << state.y << std::endl;
					if (state.y >= CIRCLE_Y - CIRCLE_RADIUS && state.y <= CIRCLE_Y + CIRCLE_RADIUS) {
						if (state.x >= circlepos[red] - CIRCLE_RADIUS && state.x <= circlepos[red] + CIRCLE_RADIUS) {
							colors[row][column] = al_color_name("red");
							patternGuess.push_back(red);
							incrementcol();
						}
						if (state.x >= circlepos[blue] - CIRCLE_RADIUS && state.x <= circlepos[blue] + CIRCLE_RADIUS) {
							colors[row][column] = al_color_name("blue");
							patternGuess.push_back(blue);
							incrementcol();
						}
						if (state.x >= circlepos[yellow] - CIRCLE_RADIUS && state.x <= circlepos[yellow] + CIRCLE_RADIUS) {
							colors[row][column] = al_color_name("yellow");
							patternGuess.push_back(yellow);
							incrementcol();
						}
						if (state.x >= circlepos[green] - CIRCLE_RADIUS && state.x <= circlepos[green] + CIRCLE_RADIUS) {
							colors[row][column] = al_color_name("green");
							patternGuess.push_back(green);
							incrementcol();
						}
						if (state.x >= circlepos[white] - CIRCLE_RADIUS && state.x <= circlepos[white] + CIRCLE_RADIUS) {
							colors[row][column] = al_color_name("white");
							patternGuess.push_back(white);
							incrementcol();
						}
						if (state.x >= circlepos[orange] - CIRCLE_RADIUS && state.x <= circlepos[orange] + CIRCLE_RADIUS) {
							colors[row][column] = al_color_name("orange");
							patternGuess.push_back(orange);
							incrementcol();
						}
					}
					//colors[0][0] = al_color_name("white");
					mouse = false;
				}
				if (won) {
					al_draw_text(font, al_color_name("white"), circlepos[red], CIRCLE_Y + 50, 0, "You win!");
				}
				if (lost) {
					al_draw_text(font, al_color_name("white"), circlepos[red], CIRCLE_Y + 50, 0, "You lose!");
				}
				if (won || lost) {
					al_draw_text(font, al_color_name("white"), circlepos[red], CIRCLE_Y + 100, 0, "Press ESC to quit...");
				}
				al_draw_filled_circle(circlepos[red], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("red"));
				al_draw_filled_circle(circlepos[blue], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("blue"));
				al_draw_filled_circle(circlepos[yellow], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("yellow"));
				al_draw_filled_circle(circlepos[green], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("green"));
				al_draw_filled_circle(circlepos[white], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("white"));
				al_draw_filled_circle(circlepos[orange], CIRCLE_Y, CIRCLE_RADIUS, al_color_name("orange"));
				for (int j = 0; j < 10; j++) {
					for (int i = 0; i < 4; i++) {
						al_draw_filled_circle(350 + i * 40, CIRCLE_Y + j * 40, CIRCLE_RADIUS, colors[j][i]);
					}
					for (int i = 4; i < 8; i++) {
						al_draw_filled_circle(450 + i * 20, CIRCLE_Y + j * 40, CIRCLE_RADIUS / 3, colors[j][i]);
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
}

int incrementcol()
{
	column++;
	if (column == 4) {
		hint();
		column = 0;
	}
	return 0;
}

int hint() {
	int correct = 0;
	int wrongspot = 0;
	int status[] = { 0, 0, 0, 0 };
	for (int i = 0; i < 4; i++) {
		if (patternGuess[i] == pattern[i]) {
			correct++;
			status[i] = 1;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (status[i] != 1) {
			for (int k = 0; k < 4; k++) {
				if (status[k] == 0) {
					if (patternGuess[i] == pattern[k]) {
						wrongspot++;
						status[k] = 2;
					}
				}
			}
		}
	}

	column = 4;
	std::cout << "Hint: ";
	for (int i = 0; i < 4; i++) {
		if (status[i] == 1) {
			std::cout << "Red ";
			colors[row][column] = al_color_name("red");
			column++;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (status[i] == 2) {
			std::cout << "White ";
			colors[row][column] = al_color_name("white");
			column++;
		}
	}
	if (status[0] == 1 && status[1] == 1 && status[2] == 1 && status[3] == 1) {
		std::cout << "You win!\n";
		won = true;
		return 0;
	}

	if (status[0] == 0 && status[1] == 0 && status[2] == 0 && status[3] == 0) {
		std::cout << "All incorrect";
	}
	patternGuess.clear();
	if (row < 9) {
		row++;
	}
	else {
		lost = true;
	}
	return 0;
}