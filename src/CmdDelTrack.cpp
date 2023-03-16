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

#include "CmdDelTrack.h"

std::string CmdDelTrack::name = "del_track";

std::string & CmdDelTrack::getName() {

  return name;
}

bool CmdDelTrack::execute(const std::vector<std::string> & args, IPlayer & iplayer) {

  if (args.size() > 0) {

    unsigned long track_index = stoi(args[0]);

    if (track_index > 0) {
      
      if (iplayer.getPlaylist().delTrack(iplayer, track_index)) {

	std::cout << "Track removed from playlist" << std::endl;
      }
      else {

	std::cout << "Cannot remove track from playlist" << std::endl;
      }
    }
  }
  else {

    std::cout << "Missing argument" << std::endl;
  }
  
  return true;
}

void CmdDelTrack::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Remove a track from the playlist (syntax: " << name << " <track index>)." << std::endl;
}
