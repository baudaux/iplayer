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

#include "CmdSave.h"

std::string CmdSave::name = "save";

std::string & CmdSave::getName() {

  return name;
}

bool CmdSave::execute(const std::vector<std::string> & args, IPlayer & iplayer) {
  
  (void)iplayer;
  
  if (args.size() > 0) {

    std::ofstream playlist_file(args[0]);

    if (playlist_file.is_open()) {

      for (auto it: iplayer.getPlaylist().getTracks()) {

	playlist_file << it.getFile() << std::endl;
      }

      playlist_file.close();

      std::cout << "Playlist saved into " << args[0] << std::endl;
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

void CmdSave::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Save the playlist (syntax: " << name << " <playlist file>)." << std::endl;
}
