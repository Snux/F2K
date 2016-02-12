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
//    ___      _                     _  _              _ _         
//   / __|_ __(_)_ _  _ _  ___ _ _  | || |__ _ _ _  __| | |___ _ _ 
//   \__ \ '_ \ | ' \| ' \/ -_) '_| | __ / _` | ' \/ _` | / -_) '_|
//   |___/ .__/_|_||_|_||_\___|_|   |_||_\__,_|_||_\__,_|_\___|_|  
//       |_|                                                       

//----------------------------------------
//define includes
//----------------------------------------


//----------------------------------------
//define global variables
//----------------------------------------
static int right_spinner_value[max_players];


//----------------------------------------
//methods
//----------------------------------------

// The right spinner is worth whatever the lit value is

void right_spinner()
{
    update_score(active_player_id, right_spinner_value[active_player_id]);
    sound_channel1.play(8);

}

// The left spinner is worth either 200, or if the lamp is lit it scores 500
// per lit blastoff letter

void left_spinner()
{
    if (left_spinner_lit[active_player_id])
    {
        update_score(active_player_id, 500 * blastoff_count[active_player_id]);
    }
    else
    {
        update_score(active_player_id, 200);
    }
}

// Light the correct lamps related to spinner values

void update_spinner_lamps()
{
    reset_spinner_lamps();

    if (left_spinner_lit[active_player_id])
    {
        lamp_left_spinner.on(0);
    }
    if (right_spinner_value[active_player_id] >= 2000)
    {
        lamp_spinner2000.on(0);
    }
    if (right_spinner_value[active_player_id] >= 3500 || right_spinner_value[active_player_id] == 1500)
    {
        lamp_spinner1500.on(0);
    }
    if (right_spinner_value[active_player_id] >= 4500 || right_spinner_value[active_player_id] == 3000 ||
            right_spinner_value[active_player_id] == 1000)
    {
        lamp_spinner1000.on(0);
    }
    if (right_spinner_value[active_player_id] == 5000 || right_spinner_value[active_player_id] == 4000 ||
            right_spinner_value[active_player_id] == 2500 || right_spinner_value[active_player_id] == 500)
    {
        lamp_spinner500.on(0);
    }
}

// Increment the value of the right spinner

void right_spinner_value_inc()
{
    if (right_spinner_value[active_player_id] < 5000)
    {
        right_spinner_value[active_player_id] += 500;
    }
    Serial.println(F("Increase right spinner value"));
    update_spinner_lamps();
}

// Switch the spinner value lamps off

void reset_spinner_lamps()
{

    //reset spinner value lamps
    lamp_spinner500.off();
    lamp_spinner1000.off();
    lamp_spinner1500.off();
    lamp_spinner2000.off();
    lamp_left_spinner.off();
}
