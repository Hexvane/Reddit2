#include <pebble.h>
#include "main.h"

Window *title;
Window *menu;
Window *ask;
Window *questions;
Window *answers;

BitmapLayer *title_layer;
GBitmap *title_bitmap;

TextLayer *menu_text;
TextLayer *select_text;

int selected = 1;
int height = 10;


void menu_load(Window *menu)
{
	menu_text = text_layer_create(GRect(10,10,144,168));
	text_layer_set_text(menu_text, "Search\n\n\nAnswers\n\n\nQuestions\n\n\nHelp");
	text_layer_set_text_color(menu_text, GColorBlack);
	layer_add_child(window_get_root_layer(menu), text_layer_get_layer(menu_text));
	
	select_text = text_layer_create(GRect(0,height,10,168));
	text_layer_set_text(select_text, "*");
	text_layer_set_text_color(select_text, GColorBlack);
	layer_add_child(window_get_root_layer(menu), text_layer_get_layer(select_text));
}

void menu_unload(Window *menu)
{
	text_layer_destroy(menu_text);
}

void title_load(Window *title)
{
	title_bitmap = gbitmap_create_with_resource(RESOURCE_ID_REDDIT_TITLE_IMAGE);
	title_layer = bitmap_layer_create(GRect(0, 0, 144, 180));
	bitmap_layer_set_bitmap(title_layer, title_bitmap);
	layer_add_child(window_get_root_layer(title), bitmap_layer_get_layer(title_layer));
}

void title_unload(Window *title)
{
	
}

void title_click_handler(ClickRecognizerRef recognizer, void *context)
{
	window_stack_push(menu, true);
	window_set_click_config_provider(menu, menu_cfg_provider);
}

void menu_down_handler(ClickRecognizerRef recognizer, void *context)
{
	if(height+43 < 168)
		height += 43;
	if(selected < 4)
		selected++;
	layer_set_frame(text_layer_get_layer(select_text), GRect(0,height,10,168));
	APP_LOG(APP_LOG_LEVEL_INFO, "%d", selected);
}

void menu_up_handler(ClickRecognizerRef recognizer, void *context)
{
	if(height-43 > 0)
		height -= 43;
	if(selected > 1)
		selected--;
	layer_set_frame(text_layer_get_layer(select_text), GRect(0,height,10,168));
	APP_LOG(APP_LOG_LEVEL_INFO, "%d", selected);
}

void menu_select_handler(ClickRecognizerRef recognizer, void *context)
{
	
}

void menu_cfg_provider(void *context)
{
	window_single_click_subscribe(BUTTON_ID_DOWN, menu_down_handler);
	window_single_click_subscribe(BUTTON_ID_UP, menu_up_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, menu_select_handler);
}

void title_cfg_provider(void *context)
{
	window_single_click_subscribe(BUTTON_ID_DOWN, title_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, title_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, title_click_handler);
}

void app_init()
{
	window_set_click_config_provider(title, title_cfg_provider);
}

int main()
{
	title = window_create();
	menu = window_create();
	
	app_init();
	
	window_set_window_handlers(title, (WindowHandlers){.load = title_load, .unload = title_load});
	window_set_window_handlers(menu, (WindowHandlers){.load = menu_load, .unload = menu_load});
	
	window_stack_push(title, true);
	
	app_event_loop();
}