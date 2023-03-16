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
#include <sstream>
#include <vector>

#include "IPlayer.h"

#include "CmdHelp.h"
#include "CmdExit.h"
#include "CmdAddTrack.h"
#include "CmdDelTrack.h"
#include "CmdClear.h"
#include "CmdDelDup.h"
#include "CmdShow.h"
#include "CmdShowTrack.h"
#include "CmdPlay.h"
#include "CmdPause.h"
#include "CmdStop.h"
#include "CmdLoad.h"
#include "CmdSave.h"
#include "CmdSetMode.h"
#include "CmdAfter.h"
#include "CmdNext.h"
#include "CmdPrevious.h"

#define VERSION    "1.0"
#define PROMPT     ">>> "

IPlayer::IPlayer(): decoder(this) {

  std::cout << "iplayer " << VERSION << " by Benoit Baudaux (2023)" << std::endl;

  // Register all the commands supported by iplayer
  commands[CmdHelp::getName()] = std::unique_ptr<Cmd>(new CmdHelp());
  commands[CmdExit::getName()] = std::unique_ptr<Cmd>(new CmdExit());
  commands[CmdAddTrack::getName()] = std::unique_ptr<Cmd>(new CmdAddTrack());
  commands[CmdDelTrack::getName()] = std::unique_ptr<Cmd>(new CmdDelTrack());
  commands[CmdClear::getName()] = std::unique_ptr<Cmd>(new CmdClear());
  commands[CmdDelDup::getName()] = std::unique_ptr<Cmd>(new CmdDelDup());
  commands[CmdShow::getName()] = std::unique_ptr<Cmd>(new CmdShow());
  commands[CmdShowTrack::getName()] = std::unique_ptr<Cmd>(new CmdShowTrack());
  commands[CmdPlay::getName()] = std::unique_ptr<Cmd>(new CmdPlay());
  commands[CmdPause::getName()] = std::unique_ptr<Cmd>(new CmdPause());
  commands[CmdStop::getName()] = std::unique_ptr<Cmd>(new CmdStop());
  commands[CmdLoad::getName()] = std::unique_ptr<Cmd>(new CmdLoad());
  commands[CmdSave::getName()] = std::unique_ptr<Cmd>(new CmdSave());
  commands[CmdSetMode::getName()] = std::unique_ptr<Cmd>(new CmdSetMode());
  commands[CmdAfter::getName()] = std::unique_ptr<Cmd>(new CmdAfter());
  commands[CmdNext::getName()] = std::unique_ptr<Cmd>(new CmdNext());
  commands[CmdPrevious::getName()] = std::unique_ptr<Cmd>(new CmdPrevious());
}

IPlayer::~IPlayer() {

  std::cout << "Exit iplayer" << std::endl;
}

int IPlayer::run(int argc, char * argv[]) {

  for (int i = 1; i < argc; ++i) {

    if (!strcmp(argv[i], "--help")) {  // List all the registered commands and exit

      std::vector<std::string> dummy_args;

      commands["help"]->execute(dummy_args, *this);
      return 0;
    }
  }

  // Create the worker thread
  worker = std::thread(&IPlayer::workerTask, this);

  while (1) {

    std::string line, token, cmd;
    std::vector<std::string> args;

    std::cout << PROMPT;

    // Read input line from stdin
    std::getline(std::cin, line);

    if (line == "")
      continue;
    
    // Extract command and arguments from input line
    std::stringstream ss(line);

    int token_index = 0;
    
    while (getline(ss, token, ' ')) {

      ++token_index;

      if (token_index == 1) { // First token is the command
	
	cmd = token;
      }
      else { // Next tokens are arguments

	args.push_back(token);
      }
    }

    if (commands.find(cmd) == commands.end()) { // Command not found in the commands map
      
      std::cout << cmd << ": Command not found. Type 'help' for having the list of commands." << std::endl;
    }
    else {
      
      if (!sendCmd(cmd, args)) // loop is exited when it is an exit command
	break;
    }
  }

  // Wait the end of the worker thread
  worker.join();
  
  return 0;
}

void IPlayer::workerTask() {
  
  while (1) {

    // Wait a command coming from main thread or decoder thread

    std::unique_lock<std::mutex> lk(cmd_mutex);
    cmd_cond.wait(lk, [this]{ return !events.empty(); });

    // Take the command/event from the event queue
    Event event = events.front();
    
    events.pop();

    // Execute the command
    resCmd = commands[event.cmd]->execute(event.args, *this);

    bool quit = !resCmd;

    lk.unlock();

    if (!event.is_event) { // Reply to the main thread only in case it is a command

      cmd_processed = true;
      res_cond.notify_one();
      
      if (quit) {

	decoder.stop();
	break;
      }
    }
  }
}

bool IPlayer::sendCmd(std::string & cmd, std::vector<std::string> & args, bool isEvent) {

  // Add the command in the event qeue
  {
    std::lock_guard<std::mutex> lk(cmd_mutex);
    events.push(Event{cmd, args, isEvent});
  }

  // Notify command to worker thread
  cmd_cond.notify_one();

  // Wait end of command from worker thread
  if (!isEvent) {
    std::unique_lock<std::mutex> lk(cmd_mutex);
    res_cond.wait(lk, [this]{ return cmd_processed; });
    cmd_processed = false;
  }

  return resCmd;
}

bool IPlayer::play(Track & track) {

  // Ask decoder to start decoding the track
  if (decoder.decode(track)) {

    std::cout << track.getStateString() << " " << track << std::endl;
    
    return true;
  }

  return false;
}

bool IPlayer::pause(Track & track) {

  // Ask decoder to pause the decoding of the track
  if (decoder.pause()) {

    std::cout << track.getStateString() << " " << track << std::endl;
    
    return true;
  }

  return false;
}

bool IPlayer::stop(Track & track, bool verbose) {

  // Ask decoder to stop decoding the track
  if (decoder.stop()) {

    if (verbose)
      std::cout << track.getStateString() << " " << track << std::endl;
    
    return true;
  }

  return false;
}

bool IPlayer::resume(Track & track) {

  // Ask decoder to resume the decoding of the track
  if (decoder.resume()) {

    std::cout << track.getStateString() << " " << track << std::endl;
    
    return true;
  }

  return false;
}

