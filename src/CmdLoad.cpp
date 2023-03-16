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

#include "CmdLoad.h"

std::string CmdLoad::name = "load";

std::string & CmdLoad::getName() {

  return name;
}

bool CmdLoad::execute(const std::vector<std::string> & args, IPlayer & iplayer) {
  
  (void)iplayer;
  
  if (args.size() > 0) {

    std::ifstream playlist_file(args[0]);

    if (playlist_file.is_open()) {

      std::string line;
      
      // Empty the playlist
      iplayer.getPlaylist().clear();

      // There is one track (file name) per line
      // File name is relative...
      while (std::getline(playlist_file, line)) {

	iplayer.getPlaylist().addTrack(line);
      }

      playlist_file.close();

      std::cout << "Playlist loaded from " << args[0] << std::endl;
    }
    else {

      std::cout << "Cannot open file: " << args[0] << std::endl;
    }
  }
  else {

    std::cout << "Missing argument <playlist file>" << std::endl;
  }
  
  return true;
}

void CmdLoad::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Load a playlist (syntax: " << name << " <playlist file>)." << std::endl;
}
