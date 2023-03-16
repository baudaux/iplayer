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

#include "CmdShowTrack.h"

std::string CmdShowTrack::name = "show_track";

std::string & CmdShowTrack::getName() {

  return name;
}

bool CmdShowTrack::execute(const std::vector<std::string> & args, IPlayer & iplayer) {

  (void)args;

  unsigned long i;
  
  Track * current = iplayer.getPlaylist().getCurrentTrack(&i);

  if (current) {

    std::cout << current->getStateString() << " (" << (i+1) << "/" << iplayer.getPlaylist().getTracks().size() << ") " << *current << std::endl;
  }
  else {

    std::cout << "No track is being played." << std::endl;
  }
  
  return true;
}

void CmdShowTrack::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name  << ": Show the current track." << std::endl;
}
