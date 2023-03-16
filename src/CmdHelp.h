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

#include "Cmd.h"

class CmdHelp: public Cmd {

 public:

  static std::string & getName();

  bool execute(const std::vector<std::string> & args, IPlayer & iplayer) override;

  void displayHelp() override;

 private:

  static std::string name;
};

