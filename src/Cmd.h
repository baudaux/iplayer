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

#pragma once

#include <string>
#include <vector>

#include "IPlayer.h"

#define MIN_WIDTH 12

/*! \class Cmd
   * \brief Represents an abstract class that is derived for each command
   */

class Cmd {

 public:

  virtual ~Cmd() = default;
  
  virtual bool execute(const std::vector<std::string> & args, IPlayer & iplayer) = 0; // false is returned by this function for exiting the player (i.e CmdExit)
  virtual void displayHelp() = 0;
};

