/*
 * Copyright (C) 2023 Benoit Baudaux
 *
 * This file is part of iplayer.
 *
 * iplayer is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * iplayer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with iplayer. If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <iomanip>

#include "CmdShow.h"

std::string CmdShow::name = "show";

std::string & CmdShow::getName() {

  return name;
}

bool CmdShow::execute(const std::vector<std::string> & args, IPlayer & iplayer) {

  (void)args;

  int i = 1;

  for (auto& it: iplayer.getPlaylist().getTracks()) {
    
    std::cout << "(" ;

    if ( (it.getState() == Track::PLAYING) || (it.getState() == Track::PAUSED) ) {

      // Asterisk is used for identifying the track currently being played
      std::cout << "*";
    }
    else {

      std::cout << " ";
    }

    std::cout << i << ") " << it << std::endl;

    ++i;
  }

  if (iplayer.getPlaylist().getTracks().size() == 0) {

    std::cout << "The playlist is empty. Use the command 'add_track' for adding a track or 'load' for loading a playlist." << std::endl;
  }
  
  return true;
}

void CmdShow::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Show the content of the playlist." << std::endl;
}
