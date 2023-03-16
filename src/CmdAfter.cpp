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

#include "CmdAfter.h"

std::string CmdAfter::name = "after";

std::string & CmdAfter::getName() {

  return name;
}

bool CmdAfter::execute(const std::vector<std::string> & args, IPlayer & iplayer) {

  (void)args;
  
  iplayer.getPlaylist().after(iplayer);

  return true;
}

void CmdAfter::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Play the following track, either the next one in the playlist or a random one depending on the play mode." << std::endl;
}
