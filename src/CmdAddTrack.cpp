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

#include "CmdAddTrack.h"

std::string CmdAddTrack::name = "add_track";

std::string & CmdAddTrack::getName() {

  return name;
}

bool CmdAddTrack::execute(const std::vector<std::string> & args, IPlayer & iplayer) {

  if (args.size() > 0) {

    if (iplayer.getPlaylist().addTrack(args[0])) {

      std::cout << "Track added into the playlist: " << args[0] << std::endl;
    }
    else {

      std::cout << "Cannot open file: " << args[0] << std::endl;
    }
  }
  else {

    std::cout << "Missing argument" << std::endl;
  }
  
  return true;
}

void CmdAddTrack::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Add a track to the playlist (syntax: " << name << " <file name>)." << std::endl;
}
