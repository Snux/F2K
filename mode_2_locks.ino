//    ___ _    ___ ___ _  _ _____   ___ _  ___ ___ 
//   | __| |  |_ _/ __| || |_   _| |_  ) |/ / | __|
//   | _|| |__ | | (_ | __ | | |    / /| ' <| |__ \
//   |_| |____|___\___|_||_| |_|   /___|_|\_\_|___/
//                                                                                                 
//   #############################################
//   # Flight 2K15                               #
//   #                                           #
//   # Written by Mark Sunnucks (Snux) for use   #
//   # with the myPinballs Pinball Controller    #
//   #                                           #
//   ############################################# 
//    _            _     __  __                             
//   | |   ___  __| |__ |  \/  |__ _ _ _  __ _ __ _ ___ _ _ 
//   | |__/ _ \/ _| / / | |\/| / _` | ' \/ _` / _` / -_) '_|
//   |____\___/\__|_\_\ |_|  |_\__,_|_||_\__,_\__, \___|_|  
//                                            |___/         
//
// Switch sequence for ball travelling through is
// ball_launch, left_kicker, right_kicker, release_rocket
// The ball "walker" lock mechanism only has a switch at the entrance (ball_launch)
// and another which is triggered when a ball drops out (left_kicker)
// This means that it's possible for up to 2 balls to be sitting in the walker
// and the game can't detect them as they don't sit on a switch.  So we have to keep
// a count of how many balls are in there.
//
// This code also handles the various Apollo/Stage lamps and will start multiball
// 

//----------------------------------------
//define includes
//----------------------------------------


//----------------------------------------
//define global variables
//----------------------------------------
static boolean ball_travelling = false; // Is the walker currently travelling the balls down?
static long ball_walker_fired;
static boolean multiball_in_progress = false;

// This variable controls how far we are progressed toward multiball
// 0 = no progress (initial state)
// 1 = Apollo 1 lit - by shooting a ball into the lock
// 2 = Apollo 1 and 2 lit - by shooting another into the lock
// 3 = Lite all systems go - Apollo 1 and 2 lit, and blastoff completed
// 4 = Multiball ready - lite all systems go complete and 54321 targets completed.
// 5 = Multiball launch in progress!!
// 6 = Multiball running
static byte multiball_stage[max_players];
static byte stage_lit[max_players];

//----------------------------------------
//methods
//----------------------------------------

// Helper routine to determine if multiball is running

boolean multiball_is_running()
{
    return (multiball_stage[active_player_id] == 6);
}

// The left_kicker is the one underneath the ball walker mechanism, so this
// switch closes when a ball drops out from the walker.
// Being kicked from here scores 10000 if stage 1 is lit plus 5000 per lit BLASTOFF if all systems go is lit.

void left_kicker()
{

    Serial.print(F("Left Kicker     : Balls in walker is currently "));
    Serial.println(balls_in_walker, DEC);
    Serial.print(F("Left Kicker     : multiball stage is currently "));
    Serial.println(multiball_stage[active_player_id], DEC);
    // This code could also get called when a ball search is happening on power up.  
    // If so, just kick the ball out without doing anything else
    if (ball_search)
    {
        left_top_kicker_coil.pulse(50);
    }
        // Otherwise we have a game running and need to do more
    else
    {

        // Decrease the count of balls held in the walker
        balls_in_walker -= 1;

        if (multiball_stage[active_player_id] >= 4)
        {
            update_score(active_player_id, 5000 * blastoff_count[active_player_id]);
            //TO-DO make this a fancy animation of adding the score, like the original.
        }
        if (multiball_stage[active_player_id] >= 1)
        {
            update_score(active_player_id, 10000);
        }
        // And kick the ball out
        left_top_kicker_coil.pulse(50);

        // If multiball is in progress, and there are still balls in the walker lock, then 
        // drop the next one out
        if (multiball_stage[active_player_id] == 5)
        {
            if (balls_in_walker > 0)
            {
                walker_coil.pulse(240);
            }
            else
            {
                Serial.println(F("Left Kicker     : walker now empty, multiball running!!"));
                clear_blastoff(active_player_id);
                stage_lit[active_player_id] = 0;
                multiball_stage[active_player_id] = 6;
            }

        }
    }
}

// Balls get kicked out of here when they arrive.
// If stage 2 is lit, score 10000

void right_kicker()
{
    if (multiball_stage[active_player_id] >= 2)
    {
        update_score(active_player_id, 10000);
    }
    // Fire the kicker out and then set the callback to check it really left :)
    right_top_kicker_coil.pulse_delay(50, 0, right_kicker_callback);

}

// Sometimes the ball doesn't kick out properly and just sits on the switch, so this
// callback reads the switch state directly and kicks again if need be.

void right_kicker_callback()
{
    if (getSwitchState(2, 8) != 0)
        right_top_kicker_coil.pulse_delay(50, 250, right_kicker_callback);

}


// When a ball enters the lock, we need to get it moved down
// and increase the lock ball counter

void ball_launch()
{
    byte trough_ball_count = balls_in_trough();
    Serial.print(F("Lock Handler    : Ball entered lock, multiball stage is currently "));
    Serial.println(multiball_stage[active_player_id], DEC);

    // Increment the number of balls in the walker
    balls_in_walker += 1;
    Serial.print(F("Lock Handler    : Balls in walker is "));
    Serial.println(balls_in_walker, DEC);
    Serial.print(F("Lock Handler    : Balls in trough is "));
    Serial.println(trough_ball_count, DEC);
    // If there are 2 or less balls in the walker, then we should request a 
    // new ball to be kicked to the shooter lane, but only if we don't have any on the playfield
    // any more
    if (balls_in_walker <= 2 && (trough_ball_count + balls_in_walker == balls_in_game))
    {
        trough_mech_handler(1);
    }

    // If we are at multiball preparation stage 0 or 1, move it along.  See the left_drops code
    // for better explanation of the stages
    if (multiball_stage[active_player_id] <= 1)
    {
        multiball_stage[active_player_id]++;
        if (multiball_stage[active_player_id] == 1) sound_channel1.play(346); // First stage stand by
        else sound_channel1.play(347); // Second stage stand by
        update_apollo_lamps();
    }

    // If we are at stage 2, and BLASTOFF has been completed, then move to stage 3
    // Note that we might have come in at stage 1 and progress to 2 and 3 in one loop, if blastoff was
    // already lit
    if (multiball_stage[active_player_id] == 2 && blastoff_completed[active_player_id])
    {
        multiball_stage[active_player_id] = 3;
        update_apollo_lamps();
    }

    // If all systems go is lit (multiball_stage[active_player_id] is 4) then get the multiball under way
    if (multiball_stage[active_player_id] == 4)
    {
        multiball_stage[active_player_id] = 5;
        sound_channel1.play(341); //Commence count down
        left_spinner_lit[active_player_id] = true;
        lite_special_lit[active_player_id] = true;
        update_special_lamps();
        update_spinner_lamps();
        clear_blastoff(active_player_id);
        //TO-DO some fancy lamp show
    }

    if (lite_special_lit[active_player_id])
    {
        update_score(active_player_id, 40000);
        lite_special_lit[active_player_id] = false;
        update_special_lamps();
        lite_special_outlanes();
    }
    // Now we'll activate the walker mechanism.  If there were 3 balls in there, the bottom one 
    // should drop out and that will be picked up elsewhere
    walker_coil.pulse(240);

}

// TO-DO - work out what to do with this switch :)

void release_rocket()
{

}



// Switch off the various lamps

void reset_apollo_lamps()
{
    lamp_apollo1.off();
    lamp_apollo2.off();
    lamp_stage1_go.off();
    lamp_stage2_go.off();
    lamp_all_go_top.off();
    lamp_all_go_left.off();
}

// Handle the various lamps which indicate the readiness of multiball

void update_apollo_lamps()
{
    // First switch them all off
    reset_apollo_lamps();

    Serial.print(F("Update Apollo   : multiball stage is currently "));
    Serial.println(multiball_stage[active_player_id], DEC);
    Serial.print(F("Update Apollo   : stage lit is currently "));
    Serial.println(stage_lit[active_player_id], DEC);

    // Then light the lamps.  Deliberately not using the break; within each case
    switch (multiball_stage[active_player_id]) {
        case 4:
            lamp_all_go_top.on(0);
        case 3:
            lamp_all_go_left.on(0);
        case 2:
            lamp_apollo2.on(0);
            if (stage_lit[active_player_id] > 1) lamp_stage2_go.on(0);
        case 1:
            lamp_apollo1.on(0);
            if (stage_lit[active_player_id] > 0) lamp_stage1_go.on(0);
        default:
            break;
    }

}

// Called from the outhold handler if there is only one ball on the playfield.  If so,
// we can stop any multiball that might be running.

void check_multiball_end()
{
    Serial.print(F("Multiball check : multiball stage is currently "));
    Serial.println(multiball_stage[active_player_id], DEC);

    if (multiball_stage[active_player_id] == 6)
    {
        Serial.println(F("Multiball check : ending multiball"));
        multiball_stage[active_player_id] = 0;
        stage_lit[active_player_id] = 0;
        update_apollo_lamps();
    }

}