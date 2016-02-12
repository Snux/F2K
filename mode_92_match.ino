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
//    __  __      _      _    
//   |  \/  |__ _| |_ __| |_  
//   | |\/| / _` |  _/ _| ' \ 
//   |_|  |_\__,_|\__\__|_||_|
//                            
//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static long current_match_store;
static long previous_match_store;
static byte chosen_match_num;

//----------------------------------------
//methods
//----------------------------------------

byte generate_numbers()
{
    byte num = random(10, 99);
    return num;
}

void match()
{
    //match mode
    reset_displays();

    byte i = 0;
    while (i < 20)
    {
        current_match_store = millis();

        if ((current_match_store - previous_match_store) > 150) //is it time to update the match numbers
        {
            previous_match_store = current_match_store;
            byte num = generate_numbers();
            update_match_display(num);
            chosen_match_num = num / 10;
            sound_channel1.play(8);
            i += 1;
        }
    }

    check_match();


    //Serial.println(F("Match"));

}

void check_match()
{
    for (int i = 0; i < max_players; i++)
    {
        if (player_active_flag[i] && player_score[i] == chosen_match_num)
        {
            add_credit();
            sound_channel1.play(15);
        }
    }
}
