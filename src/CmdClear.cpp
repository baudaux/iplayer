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

#include "CmdClear.h"

std::string CmdClear::name = "clear";

std::string & CmdClear::getName() {

  return name;
}

bool CmdClear::execute(const std::vector<std::string> & args, IPlayer & iplayer) {

  (void)args;

  Track * current = iplayer.getPlaylist().getCurrentTrack(nullptr);

  if (current) {

    // Stop the track current being played before clearing the list
    current->stop(iplayer);
  }
    
  iplayer.getPlaylist().getTracks().clear();
  
  return true;
}

void CmdClear::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Clear the playlist." << std::endl;
}
