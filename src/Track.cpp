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

#include <regex>
#include <iostream>

#include "Track.h"
#include "IPlayer.h"

std::ostream& operator<<(std::ostream& os, const Track& track) {

  os << "[" << track.file << "] " << track.title << " - " << track.artist <<  " - " << track.duration << " - "  << track.codec;

  return os;
}

Track::State Track::play(IPlayer & iplayer) {

  if (state == Track::STOPPED) {
    
    state = Track::PLAYING;
  
    iplayer.play(*this);
  }
  else if (state == Track::PAUSED) {
    
    state = Track::PLAYING;
    
    iplayer.resume(*this);
  }
  
  return state;
}

Track::State Track::pause(IPlayer & iplayer) {

  if (state == Track::PLAYING) {
    
    state = Track::PAUSED;
  
    iplayer.pause(*this);
  }
  
  return state;
}

Track::State Track::stop(IPlayer & iplayer, bool verbose) {

  if (state != Track::STOPPED) {
    
    state = Track::STOPPED;
    
    iplayer.stop(*this, verbose);
  }
  
  return state;
}

int Track::getDuration() {

  // duration format is: HH:mm:ss or H:m:s or any combination of one or two digits

  std::regex expr ("(\\d?\\d):(\\d?\\d):(\\d?\\d)");
  std::smatch sm;
  
  std::regex_match (duration, sm, expr);

  if (sm.size() == 4) {

    return stoi(sm[1])*3600 + stoi(sm[2])*60 + stoi(sm[3]);
  }

  return 0;
}

std::string Track::getStateString() {

  std::string state= "Unknown";
  
  switch(getState()) {

  case Track::STOPPED:

    state = "STOPPED";
    break;

  case Track::PLAYING:

    state = "PLAYING";
    break;

  case Track::PAUSED:

    state = "PAUSED";
    break;
  }

  return state;
}
