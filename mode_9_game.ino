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
//     ___         _            _    ___                   ___         _     
//    / __|___ _ _| |_ _ _ __ _| |  / __|__ _ _ __  ___   / __|___  __| |___ 
//   | (__/ -_) ' \  _| '_/ _` | | | (_ / _` | '  \/ -_) | (__/ _ \/ _` / -_)
//    \___\___|_||_\__|_| \__,_|_|  \___\__,_|_|_|_\___|  \___\___/\__,_\___|
//                                                                           

//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static long ball_save_current_timer_store;
static long ball_save_reference_timer_store;

//----------------------------------------
//methods
//----------------------------------------

void setup_players()
{
    for (int i = 0; i < max_players; i++)
    {
        player_score[i] = 0;
        player_active_flag[i] = false;
    }
}

void start_game()
{
    Serial.print(F("start_game called with ball in play as "));
    Serial.println(String(ball_in_play));
    if (credits > 0 or free_play)
    {
        if (!game_started)
        {
            //cancel any active lamp effects
            lamp_game_over.off();
            reset_lamp_effects();
            //clear displays
            reset_displays();
            sound_channel1.play(338);  //Prepare for mission
            //set the ball save reference
            //ball_save_reference_timer_store = millis(); - remove?
            trough_switch_handler();  // Initial call to set trough counts.
        }

        //set flag
        game_started = true;
        //log
        Serial.println(F("Game Started"));

        if (num_of_players < max_players && ball_num[active_player_id] <= 1)
        {
            num_of_players += 1;
            player_active_flag[num_of_players - 1] = true;
            player_score[num_of_players - 1] = 0; //reset score
            left_spinner_lit[num_of_players - 1] = false;
            next_left_drop[num_of_players - 1] = 5;
            stage_lit[num_of_players - 1] = 0;
            multiball_stage[num_of_players - 1] = 0;
            clear_blastoff(num_of_players - 1);
            blastoff_completed[num_of_players - 1] = false;

            //update credits
            if (!free_play)
            {
                subtract_credit();
            }

            //play sound
            sound_channel1.play(2);

            //log
            Serial.print(F("Player "));
            Serial.print(String(num_of_players));
            Serial.println(F(" Added"));
        }

        if (!ball_in_play)
        {
            start_ball();
        }

    }
}

void end_game()
{
    game_started = false;
    Serial.println(F("Game Ended"));

    //reset player vars and set high score if required
    for (int i = 0; i < num_of_players; i++)
    {
        ball_num[i] = 0;
        player_active_flag[i] = false;

        //update high score if needed
        if (player_score[i] > high_score);
        {
            high_score = player_score[i];
            EEPROMWritelong(0, high_score);
        }

        player_score[i] = 0;
    }

    num_of_players = 0;
    active_player_id = 0;
    attract_lamps_setup = false;

    //run match
    match();

    //delay 5 secs then enter attract
    mhs_delay(5000);
}

void start_ball()
{
    // If we're coming here with extra balls to play, then use one up
    // since the current player number won't have changed.
    // Otherwise the player number will have incremented, so we up the 
    // ball count for that player.
    if (extra_balls > 0)
    {
        use_extra_ball();
    }
    else
    {
        ball_num[active_player_id] += 1;
    }
    sound_channel1.play(338); // Prepare for mission
/*
    switch (active_player_id) {
                case 0: sound_channel1.play(342);  //Player one stand by
                    break; //One
                case 1: sound_channel1.play(343);
                    break; //Two
                case 2: sound_channel1.play(344);
                    break; //Three
                case 3: sound_channel1.play(345);
                    break; //Four
                
            }
  */  
    Serial.print(F("Ball Start  1   : Ball number is "));
    Serial.println(ball_num[active_player_id], DEC);
    Serial.print(F("Ball Start  1   : Balls per game is "));
    Serial.println(balls_per_game, DEC);
    Serial.print(F("Ball Start  1   : Extra balls is "));
    Serial.println(extra_balls, DEC);
    Serial.print(F("Ball Start  1   : Active player id is "));
    Serial.println(active_player_id, DEC);
    Serial.print(F("Ball Start  1   : Number of players is  "));
    Serial.println(num_of_players, DEC);
    trough_mech_handler(0); // Start ball
    right_drop_target_reset();
    //  Reset the left bank, using a parm of true will force the bank to reset
    left_drop_target_reset(true);


    right_spinner_value[active_player_id] = 500;
    bonus_mult[active_player_id] = 1;
    bonus_count[active_player_id] = 0;

    //flash current players score
    flash_display(active_player_id);
    //update bip to display
    update_credit_display();

    ball_in_play = true;
    Serial.print(F("Ball started, Player:"));
    Serial.print(String(active_player_id));
    Serial.print(F(", Ball in play:"));
    Serial.println(String(ball_num[active_player_id]));

    //start bgnd music
    //sound_channel1.play(50);

    //reset lamps
    reset_lamps();

    //update lamps for features

    update_blastoff_lamps();
    update_spinner_lamps();
    update_special_lamps();
    update_bonus_mult_lamps(bonus_mult[active_player_id]);
    update_bonus_lamps(bonus_count[active_player_id]);
    update_apollo_lamps();
    /* update_kickback_lamps();
     update_saucer_lamps();
     update_ramp_lamps();
     update_bonus_lamps();
     */
    //turn on ball in play lamp
    lamp_match.on(0);

}

void end_ball()
{
    Serial.print(F("Ball Ended  1   : Ball number is "));
    Serial.println(ball_num[active_player_id], DEC);
    Serial.print(F("Ball Ended  1   : Balls per game is "));
    Serial.println(balls_per_game, DEC);
    Serial.print(F("Ball Ended  1   : Extra balls is "));
    Serial.println(extra_balls, DEC);
    Serial.print(F("Ball Ended  1   : Active player id is "));
    Serial.println(active_player_id, DEC);
    Serial.print(F("Ball Ended  1   : Number of players is  "));
    Serial.println(num_of_players, DEC);
    ball_in_play = false; //update flag

    //play end of ball music
    sound_channel1.play(51);
    //turn off ball in play lamp
    lamp_match.off();

    left_flipper_coil.cancel();
    right_flipper_coil.cancel();

    //wait
    delay(2000);

    //run bonus
    count_bonus();

    //end of ball logic

    if (ball_num[active_player_id] == balls_per_game && num_of_players - 1 == active_player_id && extra_balls == 0) //all balls played, time to end game
    {
        end_game();
    }
    else //progress game to next ball
    {
        // Only move to the next player if we're not going to run an extra ball for the same player
        if (extra_balls == 0)
        {
            //update the active player
            if (num_of_players - 1 > active_player_id)
            {
                active_player_id += 1;
            }
            else if (num_of_players - 1 == active_player_id)
            {
                active_player_id = 0;
            }
        }

        Serial.print(F("Ball Ended  2   : Ball number is "));
        Serial.println(ball_num[active_player_id], DEC);
        Serial.print(F("Ball Ended  2   : Balls per game is "));
        Serial.println(balls_per_game, DEC);
        Serial.print(F("Ball Ended  2   : Extra balls is "));
        Serial.println(extra_balls, DEC);
        Serial.print(F("Ball Ended  2   : Active player id is "));
        Serial.println(active_player_id, DEC);
        Serial.print(F("Ball Ended  2   : Number of players is  "));
        Serial.println(num_of_players, DEC);

        start_ball();
    }
}

void ball_save_loop()
{
    if (ball_save_enabled and player_score[active_player_id] > 0)
    {

        if (!ball_save_active_flag) //first run , set the flags and lamp
        {
            ball_save_reference_timer_store = millis();
            ball_save_active_flag = true;
            lamp_shoot_again.flash(50, 0);
        }

        ball_save_current_timer_store = millis();


        if ((ball_save_current_timer_store - ball_save_reference_timer_store) > ball_save_time * 1000 and ball_save_active_flag) // check for ball save deactivation
        {
            ball_save_disable();
        }

    }
}

void ball_save_disable()
{

    Serial.println(F("Ball Save       : Disabled"));
    ball_save_active_flag = false;
    ball_save_enabled = false;
    lamp_shoot_again.off();
}



//------------------

