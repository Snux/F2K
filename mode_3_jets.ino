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
//       _     _     ___                             
//    _ | |___| |_  | _ )_  _ _ __  _ __  ___ _ _ ___
//   | || / -_)  _| | _ \ || | '  \| '_ \/ -_) '_(_-<
//    \__/\___|\__| |___/\_,_|_|_|_| .__/\___|_| /__/
//                                 |_|               
//
//  In the standard game, the jet bumpers don't do anything
//  more than kick the ball and score 1000 points.

//----------------------------------------
//define includes
//----------------------------------------
//----------------------------------------

//----------------------------------------
//define global variables
//----------------------------------------

//----------------------------------------
//methods
//----------------------------------------

//TO-DO - play around with some random sounds.

void bottom_jet()
{
    if (game_started)
    {
        update_score(active_player_id, 1000);
        sound_channel1.play(7);
        bottom_jet_coil.pulse(50);
    }
}

void top_jet()
{
    if (game_started)
    {
        update_score(active_player_id, 1000);
        sound_channel1.play(7);
        top_jet_coil.pulse(50);
    }
}

