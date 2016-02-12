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

//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------
static byte max_test_size;

static byte test_counter;
static byte last_test_counter;
static long test_current_timer_store = 0;
static long test_previous_timer_store = 0;
static boolean test_started = false;


//-------------------------------------------------------
//methods
//-------------------------------------------------------

// test_left and test_right are called from the flipper button activation
// if the test mode is active (instead of actually firing the flippers)

void test_left()
{
    test_counter -= 1;
    if (test_counter == 0)
        test_counter = max_test_size;
}

void test_right()
{
    test_counter += 1;
    if (test_counter > max_test_size)
        test_counter = 1;
}

void test()
{
    if (!test_active)
    {
        reset_displays();
        reset_lamp_effects();
        reset_lamps();
        test_active = true; //set flag
    }
    else
    {
        test_id += 1;
        test_started = false;
    }
    Serial.print(F("Test ID:"));
    Serial.println(String(test_id));
}

void test_mode()
{
    //test main menu
    if (test_id == 0)
    {
        reset_lamps();
        set_display(0, "TEST");
        test_sw.read();
    }
        //test 1 - All Lamps
    else if (test_id == 1)
    {
        if (!test_started)
        {
            test_started = true;
            set_display(0, "TEST");
            set_display(1, String(1));
            int timer = 400;

            test_lamps(timer);
        }
    }

        // test 2 - single lamps
    else if (test_id == 2)
    {

        int timer = 400;
        if (!test_started)
        {
            max_test_size = 64;
            reset_lamps();
            test_counter = 1;
            last_test_counter = 0;
            test_started = true;
            set_display(0, "TEST");
            set_display(1, String(2));

        }
        if (last_test_counter != test_counter)
        {
            reset_lamps();
            set_display(2, String(test_counter));
            test_lamp(test_counter, timer);
            last_test_counter = test_counter;
        }


    }
        //test 3 - Drivers
    else if (test_id == 3)
    {
        if (!test_started)
        {
            reset_lamps(); //cancel lamps from previosu test
            max_test_size = 20;
            test_counter = 1;
            set_display(0, "TEST");
            set_display(1, String(3));
            test_previous_timer_store = millis();
            test_started = true;
        }
        byte pulse_length = 30;
        int wait = 1000;
        boolean enabled = false;

        test_current_timer_store = millis();

        if ((test_current_timer_store - test_previous_timer_store) > wait) //is it time to test next in series?
        {
            test_previous_timer_store = test_current_timer_store;
            enabled = true;
        }



        if (enabled)
        {
            set_display(2, String(test_counter));
            if (test_counter == 1)
            {
                top_right_slingshot_coil.pulse(pulse_length);
            }
            else if (test_counter == 2)
            {
                top_left_slingshot_coil.pulse(pulse_length);
            }
            else if (test_counter == 3)
            {
                bottom_left_slingshot_coil.pulse(pulse_length);
            }
            else if (test_counter == 4)
            {
                bottom_right_slingshot_coil.pulse(pulse_length);
            }
            else if (test_counter == 5)
            {
                top_jet_coil.pulse(pulse_length);
            }
            else if (test_counter == 6)
            {
                bottom_jet_coil.pulse(pulse_length);
            }
            else if (test_counter == 7)
            {
                left_target_reset_coil.pulse(pulse_length);
            }
            else if (test_counter == 8)
            {
                target_5_coil.pulse(pulse_length);
            }
            else if (test_counter == 10)
            {
                ball_launcher_coil.pulse(pulse_length);
            }
            else if (test_counter == 9)
            {
                walker_coil.pulse(pulse_length);
            }
            else if (test_counter == 11)
            {
                target_4_coil.pulse(pulse_length);
            }
            else if (test_counter == 12)
            {
                target_3_coil.pulse(pulse_length);
            }
            else if (test_counter == 13)
            {
                target_1_coil.pulse(pulse_length);
            }
            else if (test_counter == 14)
            {
                target_2_coil.pulse(pulse_length);
            }
            else if (test_counter == 15)
            {
                right_target_reset_coil.pulse(pulse_length);
            }
            else if (test_counter == 16)
            {
                right_top_kicker_coil.pulse(pulse_length);
            }
            else if (test_counter == 17)
            {
                coin_lockout_coil.pulse(pulse_length);
            }
            else if (test_counter == 18)
            {
                left_top_kicker_coil.pulse(pulse_length);
            }
            else if (test_counter == 19)
            {
                left_flipper_coil.pulse(pulse_length);
            }
            else if (test_counter == 20)
            {
                right_flipper_coil.pulse(pulse_length);
            }

            enabled = false;
        }

        test_sw.read();
    }

        //test 4 - switches
        //the switch matrix handler will just put the switch number on the display if
        //test_active is true, instead of calling the switch handlers.
    else if (test_id == 4)
    {
        if (!test_started)
        {
            set_display(0, "TEST");
            set_display(1, String(4));
            test_started = true;
        }

    }
        //test 5 - sounds
    else if (test_id == 5)
    {
        set_display(0, "TEST");
        set_display(1, String(5));
        int wait = 2500;
        boolean enabled = false;

        test_current_timer_store = millis();

        if ((test_current_timer_store - test_previous_timer_store) > wait) //is it time to test next in series?
        {
            test_previous_timer_store = test_current_timer_store;
            enabled = true;
        }

        if (enabled)
        {
            sound_channel1.play(1);
        }
    }
        //reset
    else if (test_id == 6)
    {
        test_id = 0;
        test_active = false;
    }
}

