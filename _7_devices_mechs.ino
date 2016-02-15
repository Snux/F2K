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
//
//     ___                  _      __  __        _      _  _              _ _         
//    / __|___ _ _  ___ _ _(_)__  |  \/  |___ __| |_   | || |__ _ _ _  __| | |___ _ _ 
//   | (_ / -_) ' \/ -_) '_| / _| | |\/| / -_) _| ' \  | __ / _` | ' \/ _` | / -_) '_|
//    \___\___|_||_\___|_| |_\__| |_|  |_\___\__|_||_| |_||_\__,_|_||_\__,_|_\___|_|  
//                                                                                    
//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------

//scoring setup
const int sling_hit = 10;

const int spinner_hit = 1000;
const int exit_lane_score = 25000;



//----------------------------------------
//methods
//----------------------------------------

void left_flipper()
{
    //Serial.println(F("Left Flipper"));
    //rotate_blastoff_left();
    if (test_active)
        test_left();
    else
        left_flipper_coil.enable();
}

void left_flipper_cancel()
{
    //Serial.println(F("Left Flipper Cancel"));
    left_flipper_coil.cancel();
}

void right_flipper()
{
    //Serial.println(F("Right Flipper"));
    //rotate_blastoff_right();
    //Serial.print(F("Free Ram:"));
    //Serial.println(freeRam());
    if (test_active)
        test_right();
    else
        right_flipper_coil.enable();
}

void right_flipper_cancel()
{
    //Serial.println(F("Right Flipper Cancel"));
    right_flipper_coil.cancel();
}

void general_points()
{
    update_score(active_player_id, 100);
    sound_channel1.play(6);
}

void left_top_sling()
{
    if (game_started)
    {
        update_score(active_player_id, sling_hit);
        toggle_right_bank();
        top_left_slingshot_coil.pulse(25);
        sound_channel1.play(3);
    }
}

void right_top_sling()
{
    if (game_started)
    {
        update_score(active_player_id, sling_hit);
        toggle_right_bank();
        top_right_slingshot_coil.pulse(25);
        sound_channel1.play(3);
    }
}

void left_bottom_sling()
{
    if (game_started)
    {
        update_score(active_player_id, sling_hit);
        toggle_right_bank();
        bottom_left_slingshot_coil.pulse(25);
        sound_channel1.play(3);
    }
}

void right_bottom_sling()
{
    if (game_started)
    {
        update_score(active_player_id, sling_hit);
        toggle_right_bank();
        bottom_right_slingshot_coil.pulse(25);
        sound_channel1.play(3);
    }
}

void outlane()
{

    // Increment bonus
    bonus_inc();
    spot_lit_target();
    update_score(active_player_id, exit_lane_score);
    sound_channel1.play(5);
}

