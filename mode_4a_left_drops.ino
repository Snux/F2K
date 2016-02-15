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
//    ___ _ _ _______ _   ___                  
//   | __| | |__ /_  ) | |   \ _ _ ___ _ __ ___
//   |__ \_  _|_ \/ /| | | |) | '_/ _ \ '_ (_-<
//   |___/ |_|___/___|_| |___/|_| \___/ .__/__/
//                                    |_|      
//
// Handles the left side drop targets with 5-4-3-2-1 on them
//
// The targets are supposed to be hit in the sequence from 5 down to 1
// The next target to be hit is indicated by a flashing arrow.  If a target
// is hit which is not the next one in sequence, a score of 500 is given.
// If the next in sequence is hit, 5000 is scored.
// If the next target to be hit is already dropped, then the bank will reset
// so the target becomes available again.
// A number of playfield shots also drop the lit target (as if it had been hit)


//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------

static byte next_left_drop[max_players]; // For each player, the next target which should be dropped (1-5)
static boolean is_left_dropped[5]; // For each target, is it currently dropped (true) or raised (false)


//----------------------------------------
//methods
//----------------------------------------


// Called to reset (raise) the left target bank.  Specifying force=true will reset
// regardless of whether the next target to be hit is already up or not.  This is typically
// done at the start of a new ball

void left_drop_target_reset(boolean force = false)
{
    // So we only need to do something with the reset, if the next target the player is supposed to hit (in 5-4-3-2-1) sequence
    // is already dropped.
    if (is_left_dropped[next_left_drop[active_player_id] - 1] || force)
    {
        left_target_reset_coil.pulse_delay(40, 0, left_drops_callback);

    }


}

// This routine gets called shortly after the drop targets have all been reset (raised)
// It takes care of dropping the targets back down again to the right of the one the player
// needs to hit next.  So if the next target for the player is number 3, this code will
// drop targets 4 and 5

void left_drops_callback()
{
    // sort out the lamps, get the correct one flashing
    update_left_drop_lamps();

    // reset the status of each target
    for (byte i = 0; i < 5; i++)
    {
        is_left_dropped[i] = false;
    }
    // Drop the targets to the right of the next one to be hit.
    // Note - deliberately not using break() inside the switch statement
    Serial.print(F("In callback - next_left_drop is 0"));
    Serial.println(next_left_drop[active_player_id]);

    switch (next_left_drop[active_player_id]) {
        case 1:
            reset_drop(2);
        case 2:
            reset_drop(3);
        case 3:
            reset_drop(4);
        case 4:
            reset_drop(5);
        default:
            break;
    }
}

// A number of shots in the game will spot the next target in the 54321 bank
// So we'll call the reset_drop routine for that next target and then the switch
// for that target will get seen by regular code.

void spot_lit_target()
{
    reset_drop(next_left_drop[active_player_id]);
}


// Switch off the target lamps

void reset_left_drop_lamps()
{
    lamp_drop1.off();
    lamp_drop2.off();
    lamp_drop3.off();
    lamp_drop4.off();
    lamp_drop5.off();
}

// Flash the lamp to show the next target in sequence

void update_left_drop_lamps()
{
    // First switch them all off
    reset_left_drop_lamps();

    // Then flash the correct one
    if (next_left_drop[active_player_id] == 1) lamp_drop1.flash(100, 0);
    else if (next_left_drop[active_player_id] == 2) lamp_drop2.flash(100, 0);
    else if (next_left_drop[active_player_id] == 3) lamp_drop3.flash(100, 0);
    else if (next_left_drop[active_player_id] == 4) lamp_drop4.flash(100, 0);
    else lamp_drop5.flash(100, 0);
}

// The next 5 are called by the related switch on the drop target

void drop1()
{
    handle_left_drop(1);
}

void drop2()
{
    handle_left_drop(2);
}

void drop3()
{
    handle_left_drop(3);
}

void drop4()
{
    handle_left_drop(4);
}

void drop5()
{
    handle_left_drop(5);
}

// Routine called when a target is dropped, the parameter passed in is the target number 1-5

void handle_left_drop(byte num)
{
    Serial.print(F("Left drops      :"));
    Serial.print(num);
    Serial.print(F(" next_left_drop is "));
    Serial.println(next_left_drop[active_player_id]);
    Serial.print(F("Left drops      : multiball stage is currently "));
    Serial.println(multiball_stage[active_player_id], DEC);

    // Flag that the target is down
    is_left_dropped[num - 1] = true;

    // This routine will also be called if the machine automatically drops a target
    // during the reset of the bank.  If the target being handled here is one of those
    // then we don't actually want to do anything
    if (num <= next_left_drop[active_player_id])
    {
        if (next_left_drop[active_player_id] != num)
        {
            sound_channel1.play(17);
            update_score(active_player_id, 500);
        }
            // If the target hit was the one flashing in sequence, give the score and check the next one
        else
        {
            // Only speak the numbers if we are actually in the countdown phase of multiball prep
            if (multiball_stage[active_player_id] == 3) switch (num) {
                case 1: sound_channel1.play(324);
                    break; //One
                case 2: sound_channel1.play(301);
                    break; //Two
                case 3: sound_channel1.play(302);
                    break; //Three
                case 4: sound_channel1.play(303);
                    break; //Four
                case 5: sound_channel1.play(304);
                    break; //Five
            }

            update_score(active_player_id, 5000);
            // If we got the last target in the 54321 sequence, what happens next depends on 
            // how far along we are to getting multiball
            if (num == 1)
            {
                next_left_drop[active_player_id] = 5;
                switch (multiball_stage[active_player_id]) {
                        // Nowhere close to multiball
                    case 0:
                        break;
                        // Apollo 1 is lit - score 10000 and lite stage 1
                    case 1:
                        stage_lit[active_player_id] = 1;
                        update_score(active_player_id, 10000);
                        break;
                        // Apollo 2 is lit - score 20000 and lite stage 2
                    case 2:
                        stage_lit[active_player_id] = 2;
                        update_score(active_player_id, 20000);
                        break;
                        // Lite all systems go is lit.  Score 30,000 and lite all systems go (multiball stage 4)
                    case 3:
                        update_score(active_player_id, 30000);
                        multiball_stage[active_player_id] = 4;
                        stage_lit[active_player_id] = 2;
                        sound_channel1.play(339); //All systems go
                        break;
                    case 4:
                    case 5:
                    case 6:
                        break;
                }
                update_apollo_lamps();
            }
            else
            {
                next_left_drop[active_player_id] = next_left_drop[active_player_id] - 1;
            }
            update_left_drop_lamps();
        }

        left_drop_target_reset();
    }
    Serial.print(F("Left Drops      : multiball stage is now "));
    Serial.println(multiball_stage[active_player_id], DEC);

}

// Helper routine - will drop a specified left drop target

void reset_drop(byte num)
{
    Serial.print(F("Drop number  "));
    Serial.println(num);
    switch (num) {
        case 1:
            target_1_coil.pulse_delay(30, 240, null_routine);
            break;
        case 2:
            target_2_coil.pulse_delay(30, 240, null_routine);
            break;
        case 3:
            target_3_coil.pulse_delay(30, 240, null_routine);
            break;
        case 4:
            target_4_coil.pulse_delay(30, 240, null_routine);
            break;
        case 5:
            target_5_coil.pulse_delay(30, 240, null_routine);
            break;

    }
}

void null_routine()
{
}