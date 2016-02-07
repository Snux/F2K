//----------------------------------------
//----------------------------------------
//Attract Mode

//Version 1.0
//Feb 2015

//Orange Cloud Software Ltd Copyright 2015
//----------------------------------------
//----------------------------------------


//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static long current_attract_store;
static long previous_attract_store;
static byte attract_repeat_timer = 10;
static long high_score;
//static String message_data[4] = {"SUPERSONIC", "GAME OVER ", "PRESS START ", "HI SCORE - " + String(high_score) + " "};
//static boolean message_pause_flag[4] = {false, true, true, false};
//static byte message_id = 0;
static boolean attract_lamps_setup = false;
static boolean attract_display_hs_flag = false;

//----------------------------------------
//methods
//----------------------------------------

void attract()
{

    if (use_original_displays)
    {
        //run the scroll
        current_attract_store = millis();

        if ((current_attract_store - previous_attract_store) > (attract_repeat_timer * 2000)) //is it time alter the driver state
        {
            // save the last time attract display info was changed
            previous_attract_store = current_attract_store;
            if (!attract_display_hs_flag)
            {
                show_high_scores(high_score);
                lamp_hstd.on(0);
                attract_display_hs_flag = true;
            }
            else
            {
                show_last_game_scores();
                lamp_hstd.off();
                attract_display_hs_flag = false;
            }
        }

    }


}

void attract_lamps()
{
    //turn on gameover lamp
    lamp_game_over.on(0);

    //start lamp attract patterns
    if (!attract_lamps_setup)
    {
        lamp_effect_set1.strobe(50, 0, 1, 16, 4);
        lamp_effect_set2.strobe(50, 0, 1, 16, 4);
        lamp_effect_set3.strobe(50, 0, 1, 16, 4);
        lamp_effect_set4.strobe(50, 0, 1, 8, 4);
        attract_lamps_setup = true;
    }

}

void add_credit()
{
    credits += 1;
    update_credit_display();
    sound_channel1.play(1);
    Serial.print(F("Credits Now :"));
    Serial.println(credits);
}

void subtract_credit()
{
    credits -= 1;
    update_credit_display();
    Serial.print(F("Credits Now :"));
    Serial.println(credits);
}

