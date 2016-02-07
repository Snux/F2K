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
//    ___ _      _   _     ___                 ___            _   
//   | _ (_)__ _| |_| |_  |   \ _ _ ___ _ __  | _ ) __ _ _ _ | |__
//   |   / / _` | ' \  _| | |) | '_/ _ \ '_ \ | _ \/ _` | ' \| / /
//   |_|_\_\__, |_||_\__| |___/|_| \___/ .__/ |___/\__,_|_||_|_\_\
//         |___/                       |_|                        
//----------------------------------------
// Handles the right side drop targets 
//
// Dropping all three targets increases the value of the right spinner
// and also increases the bonus (end of ball) multiplier.
// If all 3 are dropped at the same time and the related lamp is lit, also score 50000
// The 50,000 lamp is only lit when all 3 targets are raised, and is then toggled on and
// off by the slingshots.

//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static int right_drops_count; // Number of targets currently down 1-3
static int right_drops_completed[max_players]; // How many times a player has dropped all 3
static boolean right_bank_lit = false; // Is the bank currently worth 50,000



//----------------------------------------
//methods
//----------------------------------------

// Reset the bank (raise them all)

void right_drop_target_reset()
{
    right_target_reset_coil.pulse_delay(30, 0, right_drops_callback);
}


// All 3 of the right hand side drop targets call this code - there is no
// different action between any of them

void right_drop()
{
    static long first_hit; // The time the first of the 3 targets was dropped

    right_drops_count += 1;
    Serial.print(F("Right drops     : targets down is "));
    Serial.println(right_drops_count, DEC);
    right_bank_lit = false;
    update_right_bank_lamp();
    // If this was the first drop down, make a note of the time
    if (right_drops_count == 1)
    {
        first_hit = millis();
    }

    sound_channel1.play(17);
    update_score(active_player_id, 500); // Target down scores 500

    // If all three are down.....
    if (right_drops_count == 3)
    {
        bonus_mult_inc();
        right_spinner_value_inc();
        right_drops_completed[active_player_id] += 1;
        // This is the 3rd target dropped, so if the first went down less than a second ago
        // and the lamp was lit we score 50000
        if ((millis() - first_hit < 1000) && right_bank_lit)
        {
            Serial.println(F("Right drops     : dropped together, score 50000"));
            update_score(active_player_id, 50000);
        }
        else
        {
            Serial.println(F("Right drops     : dropped too slow"));
        }
        right_drop_target_reset();
    }
}

// Called a short time after the bank is reset (raised)

void right_drops_callback()
{
    right_drops_count = 0;
    right_bank_lit = true;
    update_right_bank_lamp();
}

// Set the lamp for the bank.

void update_right_bank_lamp()
{
    if (right_bank_lit)
        lamp_right_bank.on(0);
    else
        lamp_right_bank.off();
}

// The slingshots will toggle the right bank lamp on and off
// providing that all 3 targets are still raised.

void toggle_right_bank()
{
    Serial.print(F("Right toggle    : Drop count is  "));
    Serial.println(right_drops_count, DEC);
    if (right_bank_lit)
        Serial.println(F("Right toggle    : Bank is lit"));
    else
        Serial.println(F("Right toggle    : Bank is not lit"));
    // Only if all three targets are still raised
    if (right_drops_count == 0)
    {
        right_bank_lit = !right_bank_lit;
        update_right_bank_lamp();
    }
    if (right_bank_lit)
        Serial.println(F("Right toggle    : Bank is lit"));
    else
        Serial.println(F("Right toggle    : Bank is not lit"));

}

