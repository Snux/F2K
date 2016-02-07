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
//    ___                    _  _              _ _         
//   | _ ) ___ _ _ _  _ ___ | || |__ _ _ _  __| | |___ _ _ 
//   | _ \/ _ \ ' \ || (_-< | __ / _` | ' \/ _` | / -_) '_|
//   |___/\___/_||_\_,_/__/ |_||_\__,_|_||_\__,_|_\___|_|  
//                                                         

//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static byte bonus_count[max_players];
static byte bonus_mult[max_players];

void bonus_inc()
{
    if (bonus_count[active_player_id] < 10)
    { // Was 55
        bonus_count[active_player_id] += 1;
        Serial.print(F("Increase bonus to: "));
        Serial.println(String(bonus_count[active_player_id]));
        update_bonus_lamps(bonus_count[active_player_id]);
    }
}

void bonus_mult_inc()
{
    if (bonus_mult[active_player_id] < 15)
    {
        bonus_mult[active_player_id] += 1;
        Serial.print(F("Increase bonus multipler to: "));
        Serial.println(String(bonus_mult[active_player_id]));
        update_bonus_mult_lamps(bonus_mult[active_player_id]);
    }
}

void reset_bonus_lamps()
{
    lamp_bonus1K.off();
    lamp_bonus2K.off();
    lamp_bonus3K.off();
    lamp_bonus4K.off();
    lamp_bonus5K.off();
    lamp_bonus6K.off();
    lamp_bonus7K.off();
    lamp_bonus8K.off();
    lamp_bonus9K.off();
    lamp_bonus10K.off();
}

void update_bonus_lamps(byte countback)
{
    reset_bonus_lamps();

    if (countback >= 10)
    {
        lamp_bonus10K.on(0);
        countback -= 10;
    }
    if (countback >= 9)
    {
        lamp_bonus9K.on(0);
        countback -= 9;
    }
    if (countback >= 8)
    {
        lamp_bonus8K.on(0);
        countback -= 8;
    }
    if (countback >= 7)
    {
        lamp_bonus7K.on(0);
        countback -= 7;
    }
    if (countback >= 6)
    {
        lamp_bonus6K.on(0);
        countback -= 6;
    }
    if (countback >= 5)
    {
        lamp_bonus5K.on(0);
        countback -= 5;
    }
    if (countback >= 4)
    {
        lamp_bonus4K.on(0);
        countback -= 4;
    }
    if (countback >= 3)
    {
        lamp_bonus3K.on(0);
        countback -= 3;
    }
    if (countback >= 2)
    {
        lamp_bonus2K.on(0);
        countback -= 2;
    }
    if (countback >= 1)
    {
        lamp_bonus1K.on(0);
        countback -= 1;
    }

}

void reset_bonus_mult_lamps()
{
    lamp_mult1X.off();
    lamp_mult2X.off();
    lamp_mult3X.off();
    lamp_mult4X.off();
    lamp_mult5X.off();
}

void update_bonus_mult_lamps(byte countback)
{

    reset_bonus_mult_lamps();
    if (countback >= 5)
    {
        lamp_mult5X.on(0);
        countback -= 5;
    }
    if (countback >= 4)
    {
        lamp_mult4X.on(0);
        countback -= 4;
    }
    if (countback >= 3)
    {
        lamp_mult3X.on(0);
        countback -= 3;
    }
    if (countback >= 2)
    {
        lamp_mult2X.on(0);
        countback -= 2;
    }
    if (countback >= 1)
    {
        lamp_mult1X.on(0);
        countback -= 1;
    }

}

void count_bonus()
{
    int between_delay = 200;

    for (byte mult = bonus_mult[active_player_id]; mult > 0; mult--)
    {
        update_bonus_mult_lamps(mult);
        for (byte count = bonus_count[active_player_id]; count > 0; count--)
        {
            sound_channel1.play(17);
            update_bonus_lamps(count);
            update_score(active_player_id, 1000);
            delay(max(between_delay, 50));
        }
        between_delay -= 50;
    }
}
