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
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static long current_attract_store;
static long previous_attract_store;
static byte attract_repeat_timer = 10;
static long high_score;
//static String message_data[4] = {"SUPERSONIC", "GAME OVER ", "PRESS START ", "HI SCORE - " + String(high_score) + " "};
//static boolean message_pause_flag[4] = {false, true, true, false};
//static byte message_id = 0;
static boolean attract_lamps_setup = false;
static boolean attract_display_hs_flag = false;

//----------------------------------------
//methods
//----------------------------------------

void attract()
{

    if (use_original_displays)
    {
        //run the scroll
        current_attract_store = millis();

        if ((current_attract_store - previous_attract_store) > (attract_repeat_timer * 2000)) //is it time alter the driver state
        {
            // save the last time attract display info was changed
            previous_attract_store = current_attract_store;
            if (!attract_display_hs_flag)
            {
                show_high_scores(high_score);
                lamp_hstd.on(0);
                attract_display_hs_flag = true;
            }
            else
            {
                show_last_game_scores();
                lamp_hstd.off();
                attract_display_hs_flag = false;
            }
        }

    }


}

void attract_lamps()
{
    //turn on gameover lamp
    lamp_game_over.on(0);

    //start lamp attract patterns
    if (!attract_lamps_setup)
    {
        lamp_effect_set1.strobe(50, 0, 1, 16, 4);
        lamp_effect_set2.strobe(50, 0, 1, 16, 4);
        lamp_effect_set3.strobe(50, 0, 1, 16, 4);
        lamp_effect_set4.strobe(50, 0, 1, 8, 4);
        attract_lamps_setup = true;
    }

}

void add_credit()
{
    credits += 1;
    update_credit_display();
    sound_channel1.play(1);
    Serial.print(F("Credits Now :"));
    Serial.println(credits);
}

void subtract_credit()
{
    credits -= 1;
    update_credit_display();
    Serial.print(F("Credits Now :"));
    Serial.println(credits);
}

