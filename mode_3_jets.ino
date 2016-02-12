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

