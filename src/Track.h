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
#include <ostream>

class IPlayer;

/*! \class Track
   * \brief Represents the audio track
   */

class Track {
  
 public:

  enum State
    {
     STOPPED,  // Track is not played nore paused
     PLAYING,  // Track is begin played
     PAUSED    // Track is paused
    };

 Track(std::string & file_, std::string & duration_, std::string & codec_, std::string & title_, std::string &  artist_): file{file_}, duration{duration_}, codec{codec_}, title{title_}, artist{artist_}, state(State::STOPPED) {}

  Track::State getState() { return state; }
  void setState(Track::State s) { state = s; }
  std::string & getFile() { return file; }

  int getDuration();
  std::string getStateString();

  Track::State play(IPlayer & iplayer);
  Track::State pause(IPlayer & iplayer);
  Track::State stop(IPlayer & iplayer, bool verbose = true);  // versbose is used for printing the status of the stop command (sometimes, we do not want)


  /*!
   * \brief Function for printing the track details
   */
  friend std::ostream& operator<<(std::ostream & os, const Track & track);

 private:

  std::string file;
  std::string duration; // format: HH:mm:ss
  std::string codec;
  std::string title;
  std::string artist;

  Track::State state;
};
