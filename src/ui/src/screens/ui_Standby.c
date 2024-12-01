#include "../ui.h"

void ui_Standby_screen_init(void)
{
    ui_Standby = lv_obj_create(NULL);

    lv_obj_add_event_cb(ui_Standby, standby_screen_event_handler, LV_EVENT_CLICKED, NULL);
    ui_Face = lv_img_create(ui_Standby);
    lv_img_set_src(ui_Face, &ui_img_xiaodianshi_png);
    lv_obj_set_width(ui_Face, LV_SIZE_CONTENT);   /// 320
    lv_obj_set_height(ui_Face, LV_SIZE_CONTENT);    /// 240
    lv_obj_set_align(ui_Face, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Face, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Face, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
}