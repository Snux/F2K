//----------------------------------------
//----------------------------------------
// Utilites 
// for use in modes and general housekeeping

// Version 1.0
// Feb 2015

// Orange Cloud Software Ltd Copyright 2015
//----------------------------------------
//----------------------------------------


//----------------------------------------
// define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
// define global variables
//----------------------------------------


//----------------------------------------
// methods
//----------------------------------------

int freeRam() //outputs the amount of free sram in bytes
{
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

