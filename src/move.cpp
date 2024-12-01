#include <move.h>


int action = 0;
int move_flag = false;
int mic_move_flag = false;

void getmove(void)
{
    if (move_flag)
    // if (1)
    {
        Serial.begin(9600); // here or out of if?
        unsigned char DM_Action[5] = { 0xff, 0x09, 0x00, (unsigned char)action, 0x00 }; 
        // unsigned char DM_Action[5] = { 0xff, 0x09, 0x00, 0x05, 0x00 }; 
        Serial.write(DM_Action, sizeof(DM_Action)); 
        move_flag = 0;
        vTaskDelay(100);
    }
}



