//   ####################################################################################################
//   # Flight 3000 written by Mark Sunnucks (Snux) Copyright 2016                                       #
//   #                                                                                                  #
//   # Based on and expanded from example code supplied with the myPinballs Custom Controller Boardset  #
//   #                                                                                                  #
//   # This code will not compile or run on its own. It requires the myPinballs Custom Controller       #
//   # Boardset hardware and frameworks, which are available here:                                      #
//   # http://mypinballs.co.uk/electronics/store.jsp                                                    #  
//   #                                                                                                  #
//   # Boardset, All Frameworks & Code Structure/Design are Copyright Orange Cloud Software Ltd         #
//   ####################################################################################################
//
//   This file is part of Flight 3000.
//
//   Flight 3000 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
//   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//   Flight 3000 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.


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

// This is called when the second button in the coin door is pressed, will dump a whole load of
// game information to the serial monitor for debugging.
void game_status()
{
    Serial.print(F("Game Status     : balls in walker is "));Serial.println(balls_in_walker, DEC);
    Serial.print(F("Game Status     : multiball stage is "));Serial.println(multiball_stage[active_player_id], DEC);
    Serial.print(F("Game Status     : balls in trough is "));Serial.println(balls_in_trough());
    Serial.print(F("Game Status     : stage lit is "));Serial.println(stage_lit[active_player_id], DEC);
    Serial.print(F("Game Status     : extra ball count is "));Serial.println(extra_balls, DEC);
    Serial.print(F("Game Status     : extra ball count is "));Serial.println(extra_balls, DEC);
    Serial.print(F("Game Status     : free memory is  "));Serial.println(freeRam());
    //Serial.print(F("Free Ram:"));
    //Serial.println(freeRam());
}

