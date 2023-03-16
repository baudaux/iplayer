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

#include "CmdExit.h"

std::string CmdExit::name = "exit";

std::string & CmdExit::getName() {

  return name;
}

bool CmdExit::execute(const std::vector<std::string> & args, IPlayer & iplayer) {

  (void)args;
  (void)iplayer;
  
  std::cout << "Bye bye" << std::endl;
  
  return false;
}

void CmdExit::displayHelp() {

  std::cout << std::setw(MIN_WIDTH) << std::left << name << ": Exit iplayer." << std::endl;
}
