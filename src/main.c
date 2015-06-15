#include <pebble.h>

Window *my_window;
Layer *custom_layer;

int digits[10][7][5] = {
	{
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1}
	},
	{
		{1,1,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,1,1,1}
	},
	{
		{1,1,1,1,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{1,1,1,1,1},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,1,1,1,1}
	},
	{
		{1,1,1,1,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{1,1,1,1,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{1,1,1,1,1}
	},
	{
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{0,0,0,0,1}
	},
	{
		{1,1,1,1,1},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,1,1,1,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{1,1,1,1,1}
	},
	{
		{1,1,1,1,1},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1}
	},
	{
		{1,1,1,1,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
	},
	{
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1}
	},
	{
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1},
		{0,0,0,0,1},
		{0,0,0,0,1},
		{1,1,1,1,1}
	}
};

int hour_ten = 0, hour_one = 0, min_ten = 0, min_one = 0;

#define THEME 0
int theme = 1;
#define RED 0
#define PURPLE 1
#define BLUE 2
#define ORANGE 3
#define GREEN 4
#define BROWN 5
#define RAINBOW 9
	
GColor get_red_random_shade(){
	int shade = rand()%3;
	switch(shade){
		case 0: return GColorBulgarianRose;
		case 1: return GColorDarkCandyAppleRed;
		case 2: return GColorRed;
		default: return GColorRed;
	}
}

GColor get_purple_random_shade(){
	int shade = rand()%3;
	switch(shade){
		case 0: return GColorIndigo;
		case 1: return GColorVividViolet;
		case 2: return GColorPurple;
		default: return GColorPurple;
	}
}

GColor get_green_random_shade(){
	int shade = rand()%3;
	switch(shade){
		case 0: return GColorDarkGreen;
		case 1: return GColorMayGreen;
		case 2: return GColorIslamicGreen;
		default: return GColorIslamicGreen;
	}
}

GColor get_orange_random_shade(){
	int shade = rand()%3;
	switch(shade){
		case 0: return GColorWindsorTan;
		case 1: return GColorRed;
		case 2: return GColorOrange;
		default: return GColorOrange;
	}
}

GColor get_blue_random_shade(){
	int shade = rand()%3;
	switch(shade){
		case 0: return GColorBlueMoon;
		case 1: return GColorDukeBlue;
		case 2: return GColorCobaltBlue;
		default: return GColorCobaltBlue;
	}
}

GColor get_brown_random_shade(){
	int shade = rand()%3;
	switch(shade){
		case 0: return GColorBrass;
		case 1: return GColorLimerick;
		case 2: return GColorArmyGreen;
		default: return GColorArmyGreen;
	}
}

GColor get_thematic_random_color(int current_theme){
	switch(current_theme){
		case RED: return get_red_random_shade();
		case PURPLE: return get_purple_random_shade();
		case BLUE: return get_blue_random_shade();
		case ORANGE: return get_orange_random_shade();
		case GREEN: return get_green_random_shade();
		case BROWN: return get_brown_random_shade();
		case RAINBOW: return get_thematic_random_color(rand()%5);
		default: return GColorBlack;
	}
}

void tick(struct tm *tick_time, TimeUnits units){
	hour_ten = tick_time->tm_hour/10;
	hour_one = tick_time->tm_hour%10;
	if(!clock_is_24h_style()){
		if(tick_time->tm_hour == 0){ hour_ten = 1; hour_one = 2; }
		else if(tick_time->tm_hour > 12){ hour_ten -= 1; hour_one -= 2; }
	}
	min_ten = tick_time->tm_min/10;
	min_one = tick_time->tm_min%10;
	layer_mark_dirty(custom_layer);
}
	
bool is_digit(int x, int y){
	if(x == 0 || y == 0 || x == 120 || y == 160 || x == 60 || y == 80) return false;
	
	if(x >= 10 && x <= 50 && y >= 10 && y <= 70 && digits[hour_ten][y/10-1][x/10-1] == 1) return true;
	
	if(x >= 70 && x <= 110 && y >= 10 && y <= 70 && digits[hour_one][y/10-1][(x-60)/10-1] == 1) return true;
	
	if(x >= 10 && x <= 50 && y >= 80 && y <= 150 && digits[min_ten][(y-80)/10-1][x/10-1] == 1) return true;
	
	if(x >= 70 && x <= 110 && y >= 80 && y <= 150 && digits[min_one][(y-80)/10-1][(x-60)/10-1] == 1) return true;
	
	return false;
}

void draw(Layer *layer, GContext *ctx){
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, GRect(0,0,144,168),0,GCornerNone);
 
	 for(int x = 0; x < 130; x+=10){
		 for(int y = 0; y < 170; y+=10){
			if(is_digit(x,y))
			 graphics_context_set_fill_color(ctx, GColorWhite);
		     else
			  graphics_context_set_fill_color(ctx, get_thematic_random_color(theme));
			 graphics_fill_rect(ctx, GRect(8+x, y, 8, 8), 0, GCornerNone);
		 }
	 }
}

void inbox(DictionaryIterator *iter, void *context){
	Tuple *t = dict_read_first(iter);
	theme = atoi(t->value->cstring);
	time_t now = time(NULL);
	struct tm *tick_time = localtime(&now);
	tick(tick_time, MINUTE_UNIT);
	persist_write_int(THEME, theme);
}	

void handle_init(void) {
	if(persist_exists(THEME)) theme = persist_read_int(THEME);
	
	app_message_open(32,32);
	app_message_register_inbox_received(inbox);
	
	my_window = window_create();

  custom_layer = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(custom_layer, draw);
	layer_add_child(window_get_root_layer(my_window), custom_layer);
	window_stack_push(my_window, true);
	
	time_t seed = time(NULL);
	srand(seed);
	struct tm *now = localtime(&seed);
	tick(now, MINUTE_UNIT);
	
	tick_timer_service_subscribe(MINUTE_UNIT, tick);	
}

void handle_deinit(void) {
	tick_timer_service_unsubscribe();
	app_message_deregister_callbacks();
  layer_destroy(custom_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
