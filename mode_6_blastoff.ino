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
//    ___ _         _        __  __ 
//   | _ ) |__ _ __| |_ ___ / _|/ _|
//   | _ \ / _` (_-<  _/ _ \  _|  _|
//   |___/_\__,_/__/\__\___/_| |_|  
//                                  
//
// The ball lock (top left lane) contains inserts for the words BLAST OFF
// These are spotted by rolling over the related switches on the playfield (top lanes and inlanes)
// Completing the full BLAST OFF letters is one of the requirements for starting multiball
//----------------------------------------
//define includes
//----------------------------------------


//----------------------------------------
//define global variables
//----------------------------------------


static boolean blastoff_spot_flags[max_players][8] = {false, false, false, false, false, false, false, false};


//----------------------------------------
//methods
//----------------------------------------


// This is called from the switch specific handlers further down.  It gets passed the number of
// the blastoff switch hit, BLASTOFF mapping to 12345678

void spot_blastoff(byte num)
{
    // Increment bonus
    bonus_inc();

    // If this letter hasn't been spotted yet
    if (!blastoff_spot_flags[active_player_id][num - 1])
    {
        // Then spot it
        blastoff_spot_flags[active_player_id][num - 1] = true;

        // and the lamp
        spot_blastoff_lamp(num);

        sound_channel1.play(9);

        // increment the count for this player
        blastoff_count[active_player_id] += 1;
        Serial.print(F("BLASTOFF counter is : "));
        Serial.println(String(blastoff_count[active_player_id]));
        // Hitting 8 means we got all of them.
        if (blastoff_count[active_player_id] == 8)
        {
            completed_blastoff();

        }
    }
        // Otherwise the letter is already spotted
    else
    {
        bonus_inc();
        sound_channel1.play(10);
    }
}

// The rotate_blastoff routines are supposed to work a little like lane change
// but not working properly at the moment so not called, need to debug this.

void rotate_blastoff_right()
{
    int top = blastoff_spot_flags[active_player_id][7];
    for (byte i = 7; i > 0; i--)
    {
        blastoff_spot_flags[active_player_id][i] = blastoff_spot_flags[active_player_id][i - 1];
    }
    blastoff_spot_flags[active_player_id][0] = top;
    update_blastoff_lamps();

}

void rotate_blastoff_left()
{
    int bottom = blastoff_spot_flags[active_player_id][0];
    for (byte i = 0; i < 6; i++)
    {
        blastoff_spot_flags[active_player_id][i] = blastoff_spot_flags[active_player_id][i + 1];
    }
    blastoff_spot_flags[active_player_id][7] = bottom;
    update_blastoff_lamps();

}


// This is the target in the small lane in the centre of the playfield.
// Scores 25000, increases bonus multiplier and spots a BLASTOFF target 

void spot_blast()
{
    update_score(active_player_id, 25000);
    bonus_mult_inc();

    // Loop through the targets and see if there is still one waiting to be spotted
    byte x = 0;
    for (byte i = 0; i < 9 and x == 0; i++)
    {
        if (blastoff_spot_flags[active_player_id][i] == false)
        {
            x = i + 1;
            spot_blastoff(x);
        }
    }

}

//Each of the blastoff switches calls one of the routines below.  BLASTOFF is 12345678 
//Each then adds the appropriate number of points and then calls the generic handler passing
//in the parameter of the letter spotted

void spot_blastoff1()
{
    update_score(active_player_id, 3000);
    spot_blastoff(1);
}

void spot_blastoff2()
{
    update_score(active_player_id, 5000);
    spot_blastoff(2);
}

void spot_blastoff3()
{
    update_score(active_player_id, 5000);
    spot_blastoff(3);
}

void spot_blastoff4()
{
    update_score(active_player_id, 5000);
    spot_blastoff(4);
}

void spot_blastoff5()
{
    update_score(active_player_id, 5000);
    spot_blastoff(5);
}

void spot_blastoff6()
{
    update_score(active_player_id, 5000);
    spot_blastoff(6);
}

void spot_blastoff7()
{
    update_score(active_player_id, 5000);
    spot_lit_target();
    spot_blastoff(7);
}

void spot_blastoff8()
{
    update_score(active_player_id, 5000);
    spot_lit_target();
    spot_blastoff(8);
}



// This is called when the player has spotted all the BLASTOFF letters

void completed_blastoff()
{
    blastoff_completed[active_player_id] = true;
    sound_channel1.play(14);
    update_blastoff_lamps();
    if (multiball_stage[active_player_id] == 2)
    {
        multiball_stage[active_player_id] = 3;
        update_apollo_lamps();
    }
}

// Called to reset the blastoff status

void clear_blastoff(byte player)
{
    for (byte i = 0; i < 9; i++)
    {
        blastoff_spot_flags[player][i] = false;
    }
    blastoff_count[player] = 0;
    blastoff_completed[player] = false;
    update_blastoff_lamps();
}

void spot_blastoff_lamp(byte num)
{


    //set lamps for units
    if (num == 1)
    {
        lamp_blastoff_rollover1.timeout(25, 450);
        lamp_blastoff1.smarton(25, 450);
    }
    else if (num == 2)
    {
        lamp_blastoff_rollover2.timeout(25, 450);
        lamp_blastoff2.smarton(25, 450);
    }
    else if (num == 3)
    {
        lamp_blastoff_rollover3.timeout(25, 450);
        lamp_blastoff3.smarton(25, 450);
    }
    else if (num == 4)
    {
        lamp_blastoff_rollover4.timeout(25, 450);
        lamp_blastoff4.smarton(25, 450);
    }
    else if (num == 5)
    {
        lamp_blastoff_rollover5.timeout(25, 450);
        lamp_blastoff5.smarton(25, 450);
    }
    else if (num == 6)
    {
        lamp_blastoff_rollover6.timeout(25, 450);
        lamp_blastoff6.smarton(25, 450);
    }
    else if (num == 7)
    {
        lamp_blastoff_rollover7.timeout(25, 450);
        lamp_blastoff7.smarton(25, 450);
    }
    else if (num == 8)
    {
        lamp_blastoff_rollover8.timeout(25, 450);
        lamp_blastoff8.smarton(25, 450);
    }


}

void reset_blastoff_lamps()
{

    //reset blastoff lamps
    lamp_blastoff_rollover1.on(0);
    lamp_blastoff_rollover2.on(0);
    lamp_blastoff_rollover3.on(0);
    lamp_blastoff_rollover4.on(0);
    lamp_blastoff_rollover5.on(0);
    lamp_blastoff_rollover6.on(0);
    lamp_blastoff_rollover7.on(0);
    lamp_blastoff_rollover8.on(0);
    lamp_spot_blast.off();
    lamp_blastoff1.off();
    lamp_blastoff2.off();
    lamp_blastoff3.off();
    lamp_blastoff4.off();
    lamp_blastoff5.off();
    lamp_blastoff6.off();
    lamp_blastoff7.off();
    lamp_blastoff8.off();
}

void update_blastoff_lamps()
{
    reset_blastoff_lamps();
    if (blastoff_count[active_player_id] != 0)
    {
        lamp_spot_blast.on(0);
    }
    if (blastoff_spot_flags[active_player_id][0])
    {
        lamp_blastoff_rollover1.off();
        lamp_blastoff1.on(0);
    }

    if (blastoff_spot_flags[active_player_id][1])
    {
        lamp_blastoff_rollover2.off();
        lamp_blastoff2.on(0);
    }

    if (blastoff_spot_flags[active_player_id][2])
    {
        lamp_blastoff_rollover3.off();
        lamp_blastoff3.on(0);
    }

    if (blastoff_spot_flags[active_player_id][3])
    {
        lamp_blastoff_rollover4.off();
        lamp_blastoff4.on(0);
    }

    if (blastoff_spot_flags[active_player_id][4])
    {
        lamp_blastoff_rollover5.off();
        lamp_blastoff5.on(0);
    }

    if (blastoff_spot_flags[active_player_id][5])
    {
        lamp_blastoff_rollover6.off();
        lamp_blastoff6.on(0);
    }

    if (blastoff_spot_flags[active_player_id][6])
    {
        lamp_blastoff_rollover7.off();
        lamp_blastoff7.on(0);
    }

    if (blastoff_spot_flags[active_player_id][7])
    {
        lamp_blastoff_rollover8.off();
        lamp_blastoff8.on(0);
    }


}



