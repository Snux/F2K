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
//    ___              _      _      _  _              _ _         
//   / __|_ __  ___ __(_)__ _| |___ | || |__ _ _ _  __| | |___ _ _ 
//   \__ \ '_ \/ -_) _| / _` | (_-< | __ / _` | ' \/ _` | / -_) '_|
//   |___/ .__/\___\__|_\__,_|_/__/ |_||_\__,_|_||_\__,_|_\___|_|  
//       |_|                                                       

//----------------------------------------
//define includes
//----------------------------------------


//----------------------------------------
//define global variables
//----------------------------------------



//----------------------------------------
//methods
//----------------------------------------

void update_special_lamps()
{
    if (lite_special_lit[active_player_id])
        lamp_special_lane.on(0);
    else
        lamp_special_lane.off();
}

void lite_special_outlanes()
{

}