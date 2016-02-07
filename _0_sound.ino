//----------------------------------------
//----------------------------------------
//Sound Controller

//Version 1.0
//Feb 2015

//Orange Cloud Software Ltd Copyright 2015
//----------------------------------------
//----------------------------------------


//----------------------------------------
//define includes
//----------------------------------------
#include "PinballSound.h"
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static boolean sound_enabled = false; //sound enabled flag


//----------------------------------------
//define sound channels
//----------------------------------------
PinballSound sound_channel1 = PinballSound(1, true);
//PinballSound sound_channel2 = PinballSound(2,true);

