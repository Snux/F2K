//----------------------------------------
//----------------------------------------
//Display Controller

//Version 1.0
//Feb 2015

//Orange Cloud Software Ltd Copyright 2015
//----------------------------------------
//----------------------------------------


//----------------------------------------
//define includes
//----------------------------------------
//#include "LedControl.h"
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
//display setup
const byte num_of_displays = 5;
//LedControl lc = LedControl(44, 40, 42, num_of_displays); //data,clk,load,num of display
/* we always wait a bit between updates of the display */
unsigned long delaytime = 250;
//boolean flag = false;
static String display_data[num_of_displays];
static boolean display_text_set = false;

//scroll message setup
static int display_scroll_posn = 0;
static boolean display_scroll_active = false;
static long display_scroll_current_timer_store;
static long display_scroll_previous_timer_store;
static int display_scroll_wait = 100;

//original display setup
//char blank = 63;//15+48;
String blank = "0";


//----------------------------------------
//methods
//----------------------------------------

void reset_displays()
{
    Serial2.println(9); //special reset command

}

void set_display(byte display_id, String data)
{
    Serial2.print(1);
    Serial2.print(":");
    Serial2.print(display_id + 1);
    Serial2.print(":");
    Serial2.println(data);
    //Serial.print(1); Serial.print(":");Serial.print(display_id); Serial.print(":"); Serial.println(data);
}

void flash_display(byte display_id)
{
    Serial2.print(2);
    Serial2.print(":");
    Serial2.println(display_id + 1);
}

void blank_display(byte display_id)
{
    Serial2.print(3);
    Serial2.print(":");
    Serial2.println(display_id + 1);
}

void update_display()
{
    for (int i = 0; i < max_players; i++)
    {
        if (num_of_players > i)
        {
            set_display(i, display_data[i]);

            //    Serial.print(F("Display Num: "));
            //    Serial.print(i);
            //    Serial.print(F(" Display Data: "));
            //    Serial.println(display_data[i]);
            //    Serial.print(F(" Player Score Data: "));
            //    Serial.println(player_score[i]);
            //    Serial.print(F(" Formatted Player Score Data: "));
            //    Serial.println(format_digit_score(player_score[i]));
        }
        else
        {
            blank_display(i);
        }
    }
}

void update_credit_display()
{
    set_display(4, String(credits) + blank + blank + blank + String(ball_num[active_player_id]));
}

void update_match_display(byte num)
{
    set_display(4, String(credits) + blank + blank + String(num));
}

void show_high_scores(long score)
{
    for (int i = 0; i < max_players; i++)
    {
        set_display(i, String(score));
    }

    set_display(4, String(credits) + blank + blank + blank + blank);
}

void show_last_game_scores()
{
    for (int i = 0; i < max_players; i++)
    {
        set_display(i, format_digit_score(player_score[i]));
    }

    set_display(4, String(credits) + blank + blank + blank + blank);
}

void update_player_scores()
{
    if (!display_text_set)
    {
        for (byte i = 0; i < max_players; i++)
        {
            if (player_active_flag[i])
            {
                display_data[i] = format_digit_score(player_score[i]);
            }
        }
    }
}

void update_score(byte player_id, int value)
{
    player_score[player_id] += value;
    update_player_scores();
    update_display();

    //  check_score_threshold_awards();
}

/*
void check_score_threshold_awards()
{
  //process score_threshold settings
  if ((player_score[active_player_id] >= setting_score_level1.getScoreValue() || player_score[active_player_id] >= setting_score_level2.getScoreValue()) && score_threshold_counter < 2)
  {
    switch (setting_replay_type.getNumValue())
    {
      case 1: //replay
        credits += 1;
      case 2: //extra ball
        extra_ball_handler(1);
      case 3: //points
        update_score(active_player_id, 25000);
    }
    score_threshold_counter += 1;
  }
}

 */
String format_digit_score(long score)
{
    if (score == 0)
    {
        return "00";
    }
    else
    {
        return String(score, DEC);
    }
}


