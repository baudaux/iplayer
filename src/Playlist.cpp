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
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>

#include "Playlist.h"
#include "IPlayer.h"

Playlist::Playlist() {

  // Initiliaze the random number generator for the random mode
  std::srand(std::time(nullptr));
}

void Playlist::clear() {

  tracks.clear();
}

bool Playlist::addTrack(std::string file) {

  std::ifstream track_file(file);

  if (track_file.is_open()) {

    std::string line, duration, codec, title, artist;

    int line_number = 0;

    // track details are on 4 lines for: duration, coder, title and artist
    
    while (std::getline(track_file, line)) {

      ++line_number;

      switch (line_number) {

      case 1:
	duration = line;
	break;

      case 2:
	codec = line;
	break;
	  
      case 3:
	title = line;
	break;

      case 4:
	artist = line;
	break;

      default:

	break;
      }
    }

    track_file.close();

    // Track is added at the end of the playlist
    tracks.push_back(Track(file, duration, codec, title, artist));
  }
  else {

    return false;
  }

  return true;
}

bool Playlist::delTrack(IPlayer & iplayer, unsigned long track_index) {

  // Check if track_index is out of range
  if ( (track_index < 1) || (track_index > tracks.size()) )
    return false;

  // After track is being played, play another one
  if (tracks[track_index-1].getState() != Track::STOPPED) {
    
    after(iplayer, true); // Force the next track to be different from the deleted one
  }

  // Remove the track from the list of tracks
  tracks.erase(tracks.begin() + (track_index-1));
  
  return true;
}

Track * Playlist::getCurrentTrack(unsigned long * index) {

  unsigned long i = 0;
  
  for (auto& it: tracks) {

    if ( (it.getState() == Track::PLAYING) || ((it.getState() == Track::PAUSED)) ) {

      // Return the track being played or paused
      
      if (index)
	*index = i;
      
      return &it;
    }

    ++i;
  }

  return nullptr;
}

void Playlist::play(IPlayer & iplayer) {

  if (tracks.size() == 0) {

    std::cout << "The playlist is empty. Use the command 'add_track' for adding a track or 'load' for loading a playlist." << std::endl;
    return;
  }

  Track * current = getCurrentTrack(nullptr);

  if (current) {

    // Resume the track if it is paused or let the playback continue
    current->play(iplayer);
  }
  else if ( (getPlayMode() == ONCE) || (getPlayMode() == LOOP) ) {

    // Play the first track of the playlist
    tracks[0].play(iplayer);
  }
  else if (getPlayMode() == RANDOM) {

    // Play an random track
    tracks[std::rand()%tracks.size()].play(iplayer);
  }
}

void Playlist::pause(IPlayer & iplayer) {

  Track * current = getCurrentTrack(nullptr);

  if (current) {

    current->pause(iplayer);
  }
  else  {

    std::cout << "No track is being played." << std::endl;
    
  }
}

void Playlist::stop(IPlayer & iplayer) {

  Track * current = getCurrentTrack(nullptr);

  if (current) {

    current->stop(iplayer);
  }
  else  {

    std::cout << "No track is being played." << std::endl;
    
  }
}

void Playlist::next(IPlayer & iplayer) {

  unsigned long i;

  Track * current = getCurrentTrack(&i);

  if (current) {

    current->stop(iplayer);
    
    if (i < (tracks.size()-1)) {
      
      tracks[i+1].play(iplayer);
    }
    else {

      tracks[0].play(iplayer);
    }
  }
  else {
    
    tracks[0].play(iplayer);
  }
}

void Playlist::previous(IPlayer & iplayer) {

  unsigned long i;

  Track * current = getCurrentTrack(&i);

  if (current) {

    current->stop(iplayer);

    if (i > 0) {
      
      tracks[i-1].play(iplayer);
    }
    else {

      tracks[tracks.size()-1].play(iplayer);
    }
  }
  else {
    
    tracks[0].play(iplayer);
  }
}

void Playlist::after(IPlayer & iplayer, bool different) {

  if (tracks.size() == 0) {

    std::cout << "The playlist is empty. Use the command 'add_track' for adding a track or 'load' for loading a playlist." << std::endl;
    return;
  }
  
  unsigned long index = tracks.size();
  
  Track * current = getCurrentTrack(&index);
  
  if (current) {
    
    current->stop(iplayer, false);
  }

  if ( ( (getPlayMode() == ONCE) && (index < (tracks.size()-1)) ) || (getPlayMode() == LOOP) ) {

    if (!different || ((index+1)%tracks.size() != index) ) {

      tracks[(index+1)%tracks.size()].play(iplayer);
    }
  }
  else if (getPlayMode() == RANDOM) {

    if (different && (tracks.size() == 1))
	 return;

    unsigned long i = std::rand()%tracks.size();
    
    if (different && (i == index)) {

      i = (i+1)%tracks.size();
    }
    
    tracks[i].play(iplayer);
  }
  else {

    std::cout << "Playback stopped. End of playlist." << std::endl;
  }
}

void Playlist::delDuplicates() {

  std::string current_file;
  Track::State current_state;

  Track * current = getCurrentTrack(nullptr);

  if (current) {
    current_file = current->getFile();
    current_state = current->getState();
  }

  std::set<std::string> files;

  for (auto it = tracks.begin(); it != tracks.end();) {

    if (files.find(it->getFile()) != files.end()) {

      it = tracks.erase(it);
    }
    else {

      if (it->getFile() == current_file) {

	it->setState(current_state);
      }

      files.insert(it->getFile());
      ++it;
    }
  }
}
