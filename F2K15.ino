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
//    __  __      _        _  _             _         
//   |  \/  |__ _(_)_ _   | || |___ __ _ __| |___ _ _ 
//   | |\/| / _` | | ' \  | __ / -_) _` / _` / -_) '_|
//   |_|  |_\__,_|_|_||_| |_||_\___\__,_\__,_\___|_|  
//                                                    



//----------------------------------------
//define includes
//----------------------------------------
#include "Keypad.h"
#include "PinballStatus.h"
//----------------------------------------
//define global variables
//----------------------------------------
//game settings setup
//const String game_name = "HIGH VOLTAGE";
#define game_name "F2K15"
const boolean use_original_displays = true;
const boolean free_play = true;
const boolean no_bonus_flips = true;
static long delay_start_timer_store;
static long delay_current_timer_store;

//game logic setup
const byte balls_per_game = 3;
static byte credits = 0;
static boolean game_started = false;
static boolean ball_in_play = false;
static boolean test_active = false;
static byte test_id = 0;
const byte ball_save_time = 12;
static boolean ball_save_enabled = false;
static boolean ball_save_active_flag = false;
const byte balls_in_game = 3;
static byte locked_ball_count = 0;
static byte trough_ball_count = 0;
static byte lost_ball_count = 0;
static byte balls_in_play_count = 0;
static byte balls_in_walker = 0;
static boolean ball_search = false;



//player setup
const byte max_players = 4;
static byte num_of_players = 0;
static long player_score[max_players]; 
static boolean player_active_flag[max_players];
static byte ball_num[max_players];
static byte active_player_id = 0;
static byte blastoff_count[max_players];
static boolean left_spinner_lit[max_players];
static boolean lite_special_lit[max_players];
static byte extra_balls = 0;
static boolean blastoff_completed[max_players];


//setup health status LED
PinballStatus health_led = PinballStatus();