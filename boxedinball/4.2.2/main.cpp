#include <allegro.h>

void init();
void deinit();
//drew barrett
int main() {
	init();
    BITMAP *bmp = create_bitmap(640, 480);
    int circlex = 70;
    bool right = true;
	while (!key[KEY_ESC]) {
		clear_bitmap(bmp);
        rect(bmp, 60, 60, 400, 400, makecol(0,225,0));
        circlefill(bmp,circlex,240,10,makecol(0,225,0));
        if (circlex > 390){
                    right = false;
        }
        if (circlex < 70){
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
