SET(SOURCES components/ui_comp_imagelab.c
    components/ui_comp.c
    screens/ui_Init.c
    screens/ui_Main.c
    screens/ui_Serial.c
    screens/ui_Set.c
    screens/ui_Weather.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_gooddog_png.c
    images/ui_img_dogmove_png.c
    images/ui_img_xiaodianshi_png.c
    images/ui_img_1481330059.c
    images/ui_img_1481322636.c
    images/ui_img_123003138.c
    images/ui_img_684857571.c
    images/ui_img_1974495044.c
    images/ui_img_1893424809.c
    images/ui_img_1760486568.c
    images/ui_img_1841556803.c
    images/ui_img_1248718756.c
    images/ui_img_1329788991.c
    images/ui_img_1744207828.c
    images/ui_img_1653814786.c
    images/ui_img_946281160.c
    fonts/ui_font_AlimamaFont32Bpp4.c
    fonts/ui_font_AlimamaShuHeiFont16Bpp4.c)

add_library(ui ${SOURCES})
