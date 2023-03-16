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
#include <map>
#include <queue>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "Playlist.h"
#include "Decoder.h"

class Cmd;

/*! \class Event
   * \brief Represents the event used for communicating between threads
   */

class Event {

  std::string cmd;
  std::vector<std::string> args;
  bool is_event;

 public:

  Event() {}
 Event(std::string _cmd, std::vector<std::string> _args, bool _is_event): cmd{_cmd}, args{_args}, is_event{_is_event} {}

  friend class IPlayer;
};

/*! \class IPlayer
   * \brief Represents the player itself
   */

class IPlayer {
  
 public:

  IPlayer();
  ~IPlayer();

  /*!
   * \brief Starts the player
   */
  int run(int argc, char * argv[]);
  
  Playlist & getPlaylist() { return playlist; };
  
  std::map<std::string, std::unique_ptr<Cmd>> & getCommands() { return commands; }
  
  bool play(Track & track);
  bool pause(Track & track);
  bool stop(Track & track, bool verbose);
  bool resume(Track & track);

  /*!
   * \brief Sends a command to the worker thread
   */
  bool sendCmd(std::string & cmd, std::vector<std::string> & args, bool isEvent = false);
  
 private:
  
  std::map<std::string, std::unique_ptr<Cmd>> commands;

  /*!
   * \brief Represents the playlist that stores the list of tracks to be played
   */
  Playlist playlist;

  /*!
   * \brief Represents the decoder that decodes the audio tracks
   */
  Decoder decoder;

  /*!
   * \brief Represents the mutex used for synchronizing the threads
   */
  std::mutex cmd_mutex;
  std::condition_variable cmd_cond;
  std::condition_variable res_cond;
  bool resCmd;
  bool cmd_processed{false};

  /*!
   * \brief Represents the event queue used for the communication between the threads
   */
  std::queue<Event> events;

  /*!
   * \brief Represents the worker thread that executes the commands
   */
  std::thread worker;
  
  void workerTask();
};

