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

#include "Decoder.h"
#include "IPlayer.h"
#include "CmdAfter.h"

Decoder::~Decoder() {
  
  stop();
}

void Decoder::decoderTask() {

  int position = 0; // Position in the track in seconds
  
  state = Decoder::STARTED;

  // Loop til position reaches duration or if decoder is paused
  while ( ( (position < duration) && (state == Decoder::STARTED) ) || (state == Decoder::PAUSED) )  {
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    if (state == Decoder::STARTED) {

      // Increment position only when decoding is on-going
      ++position;
    }
  }
  
  if (state == Decoder::STARTED) {

    std::vector<std::string> dummy_args;
    
    iplayer->sendCmd(CmdAfter::getName(), dummy_args, true);
  }
}

bool Decoder::decode(Track & track) {

  // Stop previous decoding if any
  stop();

  // Duration of the track in seconds
  duration = track.getDuration();
  file = track.getFile();

  // Start decoder thread
  task = std::thread(&Decoder::decoderTask, this);

  return true;
}

bool Decoder::stop() {

  if (state != Decoder::STOPPED) {

    state = Decoder::STOPPED;
    
    if (task.joinable())
      task.join();
  }

  return true;
}

bool Decoder::pause() {

  if (state == Decoder::STARTED)
    state = Decoder::PAUSED;

  return true;
}

bool Decoder::resume() {
  
  if (state == Decoder::PAUSED)
    state = Decoder::STARTED;

  return true;
}
