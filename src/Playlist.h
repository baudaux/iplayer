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

#include <vector>

#include "Track.h"

class IPlayer;

/*! \class Playlist
   * \brief Represents the playlist
   */

class Playlist {
  
 public:

  /*!
   * \brief Represents the mode of playback
   */
  enum PlayMode
   {
     ONCE,     // all tracks are played sequentially til the end of the playlist
     LOOP,     // all tracks are played sequentially til the end of the playlist and then it restarts from the first element
     RANDOM    // all tracks are played randomly endlessly til user stops the playback or changes the playback mode
   };

  Playlist();

  void clear();
  bool addTrack(std::string file);
  bool delTrack(IPlayer & iplayer, unsigned long track_index);

  void delDuplicates();

  std::vector<Track> & getTracks() { return tracks; }

  Track * getCurrentTrack(unsigned long * index);

  void play(IPlayer & iplayer);
  void pause(IPlayer & iplayer);
  void after(IPlayer & iplayer, bool different = false);
  void stop(IPlayer & iplayer);
  void next(IPlayer & iplayer);
  void previous(IPlayer & iplayer);
  
  void setPlayMode(PlayMode pm) { play_mode = pm; }
  PlayMode getPlayMode() { return play_mode; }
  
 private:

  /*!
   * \brief Represents the tracks contained in the playlist
   */
  std::vector<Track> tracks;

  PlayMode play_mode = ONCE;
};

