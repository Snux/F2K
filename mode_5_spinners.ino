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
