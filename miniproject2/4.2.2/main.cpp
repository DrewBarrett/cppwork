#include <allegro.h>

void init();
void deinit();
//drew barrett
int main() {
	init();
    BITMAP *bmp = create_bitmap(640, 480);
    int circley = 0;
    int circlex = 10;
    bool right = true;
	while (!key[KEY_ESC]) {
        clear_bitmap(bmp);
		line(bmp, 0, 0, 200, 200, makecol(0,225,0));
        ellipsefill(bmp, 40, 40, 10, 20, makecol(0,225,0));
        rect(bmp, 60, 60, 20, 20, makecol(0,225,0));
        triangle(bmp, 90,90, 80,90, 85,10,makecol(0,225,0));
        int points[12] = { 50, 50,   100, 100,  100, 150,
         50, 200,  0,   150,  0,   100 };
        polygon(bmp, 6, points, makecol(0, 225, 0));
        textout_centre_ex(bmp, font, "TEXT OUTPUT",
        SCREEN_W / 2, SCREEN_H / 2, makecol(255, 0, 0), makecol(0, 255, 0));
        circlefill(bmp,300,circley,10,makecol(0,225,0));
        circley+=1;
        if (circley > 490){
           circley = -10;
        }
        circlefill(bmp,circlex,240,10,makecol(0,225,0));
        if (circlex > 630){
                    right = false;
        }
        if (circlex < 10){
                    right = true;
        }
        if(right){
                  circlex++;
        }else{
              circlex--;
        }
        blit(bmp, screen, 0,0,0,0,640,480);
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
