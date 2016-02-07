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
    Serial.print(F("Free Ram:"));
    Serial.println(freeRam());
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

