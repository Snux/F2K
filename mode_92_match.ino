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
//    __  __      _      _    
//   |  \/  |__ _| |_ __| |_  
//   | |\/| / _` |  _/ _| ' \ 
//   |_|  |_\__,_|\__\__|_||_|
//                            
//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static long current_match_store;
static long previous_match_store;
static byte chosen_match_num;

//----------------------------------------
//methods
//----------------------------------------

byte generate_numbers()
{
    byte num = random(10, 99);
    return num;
}

void match()
{
    //match mode
    reset_displays();

    byte i = 0;
    while (i < 20)
    {
        current_match_store = millis();

        if ((current_match_store - previous_match_store) > 150) //is it time to update the match numbers
        {
            previous_match_store = current_match_store;
            byte num = generate_numbers();
            update_match_display(num);
            chosen_match_num = num / 10;
            sound_channel1.play(8);
            i += 1;
        }
    }

    check_match();


    //Serial.println(F("Match"));

}

void check_match()
{
    for (int i = 0; i < max_players; i++)
    {
        if (player_active_flag[i] && player_score[i] == chosen_match_num)
        {
            add_credit();
            sound_channel1.play(15);
        }
    }
}
