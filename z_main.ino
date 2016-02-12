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
//    __  __      _         ___         _           _ 
//   |  \/  |__ _(_)_ _    / __|___ _ _| |_ _ _ ___| |
//   | |\/| / _` | | ' \  | (__/ _ \ ' \  _| '_/ _ \ |
//   |_|  |_\__,_|_|_||_|  \___\___/_||_\__|_| \___/_|
//                                                    

//--------------------------------------------
// Main Hardware Setup & Init
//--------------------------------------------

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200); //comms to sound controller
    Serial2.begin(115200); //comms to display controller
    Serial.println(game_name);
    Serial.print(F("Free Ram:"));
    Serial.println(freeRam());
    Serial.println(F("Beginning System Setup"));

    //setup switch matrix
    setup_switches();
    //setup lamps
    setup_lamps();
    //setup the rgb lamp strip
    //setup_rgb_lamps();
    //setup driver board
    setup_driver();
    //config driver board
    config_driver();

    //configure library debug
    driver_debug();
    lamp_debug();
    //switch_debug();

    //init system
    power_up();

    //setup players
    setup_players();

    // Clear walker if we don't have 3 balls in the trough
    if (balls_in_trough() != 3)
    {
        ball_search = true;
    }
    //wait before continuing
    delay(2000);
}

void power_up()
{

    //Serial.print(F("v"));Serial.print(pu_version_major);Serial.print(F("."));+Serial.print(pu_version_minor1);Serial.print(pu_version_minor2);Serial.println(F(" OCS Ltd"));

    //test the sound hardware for operation
    sound_channel1.play(99);

    // Get the high score from NV memory
    high_score = EEPROMReadlong(0);
}


//GAME LOOP
//-----------------------

void loop()
{
    //check switches for presses
    check_switches();


    if (num_of_players > 0)
    {
        //update_player_scores();
        //update_display();
        ball_save_loop(); //run the ball save loop

    }
    else //game over
    {
        if (test_active) //test mode is active otherwise attract
        {
            test_mode();
        }
        else
        {
            attract();
            attract_lamps();
        }
    }

    if (ball_search)
    {
        ball_search_loop();
    }
    //update the drivers
    driver_loop();
    //update lamps
    lamp_loop();
    lamp_effect_loop();
    health_led.update();
}

//-----------------------


//general function section
//------------------------

void mhs_delay(int timer) //create a custom delay method that allows loop method to be still updated
{
    delay_start_timer_store = millis();
    delay_current_timer_store = delay_start_timer_store;

    while (delay_current_timer_store < (delay_start_timer_store + timer)) // is it time to update the display scroll?
    {
        delay_current_timer_store = millis();
        loop();
    }
}
//------------------------


