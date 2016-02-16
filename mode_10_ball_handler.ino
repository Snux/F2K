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
//    ___       _ _   _____                  _      _  _              _ _         
//   | _ ) __ _| | | |_   _| _ ___ _  _ __ _| |_   | || |__ _ _ _  __| | |___ _ _ 
//   | _ \/ _` | | |   | || '_/ _ \ || / _` | ' \  | __ / _` | ' \/ _` | / -_) '_|
//   |___/\__,_|_|_|   |_||_| \___/\_,_\__, |_||_| |_||_\__,_|_||_\__,_|_\___|_|  
//                                     |___/                                      
//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------


//----------------------------------------
//methods
//----------------------------------------

// As the trough switches can be a bit bouncy as balls run through, this routine will read the 
// switch states directly for the 3 trough switches (51,52,53)and determine how many balls are stored
byte balls_in_trough()
{
    //left_trough = getSwitchState(5, 3);
    //middle_trough = getSwitchState(5, 2);
    //right_trough = getSwitchState(5, 1);
    //rial.print(F("Balls in trough :")); Serial.println(trough_ball_count, DEC);
    
    return getSwitchState(5, 3) + getSwitchState(5, 2) + getSwitchState(5, 1);
}

// This routine is called whenever any of the trough switches do something

void trough_switch_handler()
{
    static byte previous_ball_count = 0;
    
    trough_ball_count = balls_in_trough();
    Serial.print(F("Outhole process : Balls in trough is currently "));Serial.println(trough_ball_count, DEC);
    Serial.print(F("                : Balls in trough was "));Serial.println(previous_ball_count, DEC);

    

    // We only want to do something here if the game is actually in progress, otherwise we'll react to the initial read
    // of switch states at power on.

    if (game_started && ball_in_play)
    {

        // We really only want to do something if we've got more balls in the trough now than we had before
        // otherwise we're either here because a ball got kicked out (who cares) or we're still settling down.
        
        if (trough_ball_count > previous_ball_count)
        {
            // If the number of balls in the trough and the number locked is the number in the game, then 
            // then there are no balls in play so call the trough handler with ball drain
            if (trough_ball_count + balls_in_walker == balls_in_game)
            {
                Serial.println(F("Outhole process : Last ball drained"));
                trough_mech_handler(2); // 2 is ball drain
            }
                // If a ball left the playfield, and now only 1 is in play, see if multiball needs to end
            else if (trough_ball_count + balls_in_walker == balls_in_game - 1)
            {
                Serial.println(F("Outhole process : Multiball check"));
                check_multiball_end();

            }
        }

    }
    else
        Serial.println(F("Outhole process : No game in progress, ignoring"));
    
    previous_ball_count = trough_ball_count;
}
//Test
// Parameter passed in determines what should be done
// 0 = normal ball start
// 1 = kick new ball after ball locked.
// 2 = ball drained

void trough_mech_handler(byte request)
{
    Serial.print(F("Trough handler: method called with param "));
    Serial.println(request, DEC); //debug

    
    if (request == 0)
    {
        mhs_delay(1000);
        ball_launcher_coil.pulse(30);
        Serial.println(F("Trough handler: Ball Launched!"));
        ball_save_enabled = true; //enable the ball save logic, disable here to turn off ball save

    }
    else if (request == 1)
    {
        Serial.println(F("Trough handler: Kicking ball in following lock"));
        ball_launcher_coil.pulse(30);
    }
    else if (request == 2)
    {
        if (ball_save_active_flag)
        {
            ball_launcher_coil.pulse_delay(30, 500, drain_ballsave_callback);
        }

        else
        {
            end_ball();
        }
    }
}

void drain_ballsave_callback()
{
    Serial.println(F("Ball Saved!"));
    sound_channel1.play(10); //needs new sound for ball save
    ball_save_disable();
}

void drain_balllaunch_callback()
{
    Serial.println(F("Ball Launched!"));
    ball_save_enabled = true; //enable the ball save logic, disable here to turn off ball save
}

// Add an extra ball, to be played after the current one.  At the moment only allow
// one extra, but might change later.

void add_extra_ball()
{
    if (extra_balls == 0)
    {
        extra_balls += 1;
        lamp_shoot_again.on(0);
    }
}

// Use up an extra ball - called from start_ball

void use_extra_ball()
{
    extra_balls -= 1;
    if (extra_balls == 0)
        lamp_shoot_again.off();
}

// When the machine is powered on, it's possible that balls are locked somewhere in ball walker path, either in
// positions where there is a switch or where there isn't.  The power_up routine counts how many balls are in the
// trough and sets the ball_search value to true.  The main game loop will call this loop here until the variable is
// cleared.  Basically the only thing we need to do is cycle the ball walker until we end up with 3 balls in the
// trough.  The other methods in the game code should take care of getting the ball through the rest of the locks.

void ball_search_loop()
{
    static long last_kick = 0;
    if (last_kick == 0 || millis() - last_kick > 1000)
    {
        walker_coil.pulse(240);
        last_kick = millis();
        if (balls_in_trough() == 3)
        {
            ball_search = false;
        }
    }
}