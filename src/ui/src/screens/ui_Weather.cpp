// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Weather_screen_init(void)
{
ui_Weather = lv_obj_create(NULL);
lv_obj_add_event_cb(ui_Weather, ui_event_ResetInactivity, LV_EVENT_ALL, NULL);
lv_obj_clear_flag( ui_Weather, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_TabWeather = lv_tabview_create(ui_Weather, LV_DIR_RIGHT, 40);
lv_obj_set_width( ui_TabWeather, 305);
lv_obj_set_height( ui_TabWeather, 234);
lv_obj_set_x( ui_TabWeather, 6 );
lv_obj_set_y( ui_TabWeather, 0 );
lv_obj_set_align( ui_TabWeather, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_TabWeather, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_text_font(ui_TabWeather, &ui_font_AlimamaShuHeiFont16Bpp4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_t *TabWeatherBtn =lv_tabview_get_tab_btns(ui_TabWeather);
lv_obj_set_style_border_width(TabWeatherBtn, 0, LV_PART_ITEMS| LV_STATE_CHECKED);


ui_TabToday = lv_tabview_add_tab(ui_TabWeather, "天气实况");

ui_Location = lv_img_create(ui_TabToday);
lv_img_set_src(ui_Location, &ui_img_886925217);
lv_obj_set_width( ui_Location, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Location, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Location, -105 );
lv_obj_set_y( ui_Location, -50 );
lv_obj_set_align( ui_Location, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Location, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Location, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Code = lv_img_create(ui_TabToday);
lv_img_set_src(ui_Code, &ui_img_1248718756);
lv_obj_set_width( ui_Code, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Code, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Code, -105 );
lv_obj_set_y( ui_Code, 10 );
lv_obj_set_align( ui_Code, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Code, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Code, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Temp = lv_img_create(ui_TabToday);
lv_img_set_src(ui_Temp, &ui_img_1653150344);
lv_obj_set_width( ui_Temp, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Temp, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Temp, -105 );
lv_obj_set_y( ui_Temp, 70 );
lv_obj_set_align( ui_Temp, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Temp, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Temp, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_LabelLocation = lv_label_create(ui_TabToday);
lv_obj_set_width( ui_LabelLocation, 180);
lv_obj_set_height( ui_LabelLocation, 20);
lv_obj_set_x( ui_LabelLocation, 30 );
lv_obj_set_y( ui_LabelLocation, -50 );
lv_obj_set_align( ui_LabelLocation, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelLocation,"地点:初始化中,请稍等");
lv_obj_set_style_text_font(ui_LabelLocation, &ui_font_AlimamaShuHeiFont16Bpp4, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LabelCode = lv_label_create(ui_TabToday);
lv_obj_set_width( ui_LabelCode, 180);
lv_obj_set_height( ui_LabelCode, 20);
lv_obj_set_x( ui_LabelCode, 30 );
lv_obj_set_y( ui_LabelCode, 10 );
lv_obj_set_align( ui_LabelCode, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelCode,"天气:初始化中,请稍等");

ui_LabelTemp = lv_label_create(ui_TabToday);
lv_obj_set_width( ui_LabelTemp, 180);
lv_obj_set_height( ui_LabelTemp, 20);
lv_obj_set_x( ui_LabelTemp, 30 );
lv_obj_set_y( ui_LabelTemp, 70 );
lv_obj_set_align( ui_LabelTemp, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelTemp,"气温:初始化中,请稍等");

ui_LabelUpdateTime = lv_label_create(ui_TabToday);
lv_obj_set_width( ui_LabelUpdateTime, 180);
lv_obj_set_height( ui_LabelUpdateTime, 20);
lv_obj_set_align( ui_LabelUpdateTime, LV_ALIGN_TOP_MID );
lv_label_set_long_mode(ui_LabelUpdateTime,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_LabelUpdateTime,"上次更新时间:");

ui_TabFuture = lv_tabview_add_tab(ui_TabWeather, "天气预报");

ui_LabelAllWeather = lv_label_create(ui_TabFuture);
lv_obj_set_width( ui_LabelAllWeather, 180);
lv_obj_set_height( ui_LabelAllWeather, 20);
lv_obj_set_align( ui_LabelAllWeather, LV_ALIGN_TOP_MID );
lv_label_set_long_mode(ui_LabelAllWeather,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_LabelAllWeather,"初始化中,请稍等 初始化中,请稍等...");

ui_RollerWeather = lv_roller_create(ui_TabFuture);
lv_roller_set_options( ui_RollerWeather, "初始化中,请稍等", LV_ROLLER_MODE_NORMAL );
lv_obj_set_width( ui_RollerWeather, 251);
lv_obj_set_height( ui_RollerWeather, 175);
lv_obj_set_x( ui_RollerWeather, -6 );
lv_obj_set_y( ui_RollerWeather, 16 );
lv_obj_set_align( ui_RollerWeather, LV_ALIGN_CENTER );
lv_obj_set_style_text_font(ui_RollerWeather, &ui_font_AlimamaShuHeiFont16Bpp4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_RollerWeather, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_RollerWeather, lv_color_hex(0xACACAC), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_RollerWeather, 225, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_RollerWeather, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_RollerWeather, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_RollerWeather, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_outline_opa(ui_RollerWeather, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(ui_RollerWeather, lv_color_hex(0x4F4F4F), LV_PART_SELECTED | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_RollerWeather, 255, LV_PART_SELECTED| LV_STATE_DEFAULT);

ui_UpdateWeather = lv_imgbtn_create(ui_Weather);
lv_imgbtn_set_src(ui_UpdateWeather, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_1416457588, NULL);
lv_imgbtn_set_src(ui_UpdateWeather, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_1416456565, NULL);
lv_obj_set_height( ui_UpdateWeather, 32);
lv_obj_set_width( ui_UpdateWeather, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_UpdateWeather, 240 );
lv_obj_set_y( ui_UpdateWeather, 8 );

ui_WeatherBackToMain = lv_imgbtn_create(ui_Weather);
lv_imgbtn_set_src(ui_WeatherBackToMain, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_123003138, NULL);
lv_imgbtn_set_src(ui_WeatherBackToMain, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_684857571, NULL);
lv_obj_set_height( ui_WeatherBackToMain, 64);
lv_obj_set_width( ui_WeatherBackToMain, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_WeatherBackToMain, 2 );
lv_obj_set_y( ui_WeatherBackToMain, 8 );

ui_LabelNoWiFI = lv_label_create(ui_Weather);
lv_obj_set_width( ui_LabelNoWiFI, 202);
lv_obj_set_height( ui_LabelNoWiFI, 80);
lv_obj_set_align( ui_LabelNoWiFI, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelNoWiFI,"无网络,请连接网络后查看...");
lv_obj_add_flag( ui_LabelNoWiFI, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_set_style_text_font(ui_LabelNoWiFI, &ui_font_AlimamaFont32Bpp4, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_UpdateWeather, ui_event_UpdateWeather, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WeatherBackToMain, ui_event_WeatherBackToMain, LV_EVENT_ALL, NULL);

}