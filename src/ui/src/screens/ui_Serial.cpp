// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Serial_screen_init(void)
{
ui_Serial = lv_obj_create(NULL);
lv_obj_add_event_cb(ui_Serial, ui_event_ResetInactivity, LV_EVENT_ALL, NULL);
lv_obj_clear_flag( ui_Serial, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Serial, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Serial, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SerialBackToMain = lv_imgbtn_create(ui_Serial);
lv_imgbtn_set_src(ui_SerialBackToMain, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_123003138, NULL);
lv_imgbtn_set_src(ui_SerialBackToMain, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_684857571, NULL);
lv_obj_set_height( ui_SerialBackToMain, 49);
lv_obj_set_width( ui_SerialBackToMain, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_SerialBackToMain, 2 );
lv_obj_set_y( ui_SerialBackToMain, 8 );

ui_TextSerial = lv_textarea_create(ui_Serial);
lv_obj_set_width( ui_TextSerial, 210);
lv_obj_set_height( ui_TextSerial, 99);
lv_obj_set_x( ui_TextSerial, -18 );
lv_obj_set_y( ui_TextSerial, -58 );
lv_obj_set_align( ui_TextSerial, LV_ALIGN_CENTER );
lv_textarea_set_placeholder_text(ui_TextSerial,"TX...");
lv_obj_set_style_radius(ui_TextSerial, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( ui_TextSerial, &ui_img_1744207828, LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_img_opa(ui_TextSerial, 180, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_TextSerial, lv_color_hex(0x267FB5), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_TextSerial, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_TextSerial, 3, LV_PART_MAIN| LV_STATE_DEFAULT);



ui_SerialSend = lv_imgbtn_create(ui_Serial);
lv_imgbtn_set_src(ui_SerialSend, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_1653814786, NULL);
lv_imgbtn_set_src(ui_SerialSend, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_946281160, NULL);
lv_obj_set_height( ui_SerialSend, 48);
lv_obj_set_width( ui_SerialSend, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_SerialSend, 121 );
lv_obj_set_y( ui_SerialSend, -53 );
lv_obj_set_align( ui_SerialSend, LV_ALIGN_CENTER );

ui_TextSerialRx = lv_textarea_create(ui_Serial);
lv_obj_set_width( ui_TextSerialRx, 210);
lv_obj_set_height( ui_TextSerialRx, 116);
lv_obj_set_x( ui_TextSerialRx, -18 );
lv_obj_set_y( ui_TextSerialRx, 58 );
lv_obj_set_align( ui_TextSerialRx, LV_ALIGN_CENTER );
lv_textarea_set_placeholder_text(ui_TextSerialRx,"RX...");
lv_obj_set_style_text_font(ui_TextSerialRx, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_TextSerialRx, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_TextSerialRx, lv_color_hex(0x2781B6), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_TextSerialRx, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_TextSerialRx, 3, LV_PART_MAIN| LV_STATE_DEFAULT);



ui_SerialDelete = lv_imgbtn_create(ui_Serial);
lv_imgbtn_set_src(ui_SerialDelete, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_538929268, NULL);
lv_imgbtn_set_src(ui_SerialDelete, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_1714323774, NULL);
lv_obj_set_height( ui_SerialDelete, 48);
lv_obj_set_width( ui_SerialDelete, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_SerialDelete, 121 );
lv_obj_set_y( ui_SerialDelete, 55 );
lv_obj_set_align( ui_SerialDelete, LV_ALIGN_CENTER );

ui_RateSelect = lv_dropdown_create(ui_Serial);
lv_dropdown_set_options( ui_RateSelect, "9600\n" );
lv_dropdown_set_text( ui_RateSelect, "Rate");
lv_obj_set_width( ui_RateSelect, 70);
lv_obj_set_height( ui_RateSelect, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_RateSelect, 124 );
lv_obj_set_y( ui_RateSelect, -3 );
lv_obj_set_align( ui_RateSelect, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_RateSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_set_style_border_color(ui_RateSelect, lv_color_hex(0x207DB4), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_RateSelect, 255, LV_PART_MAIN| LV_STATE_DEFAULT);



ui_KeyboardSerial = lv_keyboard_create(ui_Serial);
lv_obj_set_width( ui_KeyboardSerial, 300);
lv_obj_set_height( ui_KeyboardSerial, 120);
lv_obj_set_align( ui_KeyboardSerial, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_KeyboardSerial, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_set_style_radius(ui_KeyboardSerial, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_KeyboardSerial, lv_color_hex(0x00B3FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_KeyboardSerial, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_SerialBackToMain, ui_event_SerialBackToMain, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_TextSerial, ui_event_TextSerial, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SerialSend, ui_event_SerialSend, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SerialDelete, ui_event_SerialDelete, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_RateSelect, ui_event_RateSelect, LV_EVENT_ALL, NULL);
lv_keyboard_set_textarea(ui_KeyboardSerial,ui_TextSerial);
lv_obj_add_event_cb(ui_KeyboardSerial, ui_event_KeyboardSerial, LV_EVENT_ALL, NULL);

}