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
#include <fstream>
#include <iomanip>

#include "CmdSetMode.h"
#include "IPlayer.h"
#include "Playlist.h"

std::string CmdSetMode::name = "set_mode";

std::string & CmdSetMode::getName() {

  return name;
}

bool CmdSetMode::execute(const std::vector<std::string> & args, IPlayer & iplayer) {
  
  (void)iplayer;
  
  if (args.size() > 0) {
    
    if (args[0] == "once")
      iplayer.getPlaylist().setPlayMode(Playlist::ONCE);
    else if (args[0] == "loop")
      iplayer.getPlaylist().setPlayMode(Playlist::LOOP);
    else if (args[0] == "random")
      iplayer.getPlaylist().setPlayMode(Playlist::RANDOM);
    else {
      
      std::cout << "Unknown play mode" << std::endl;
      return true;
    }
    
    std::cout << "Play mode changed" << std::endl;
  }
  else {
    
    std::cout << "Missing argument <once or loop or random>" << std::endl;
  }
  
  return true;
}

void CmdSetMode::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Set playback mode (syntax: " << name << " <once or loop or random>)." << std::endl;
}
