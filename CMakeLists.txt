cmake_minimum_required (VERSION 3.1)

project(iplayer)

set (CMAKE_CXX_STANDARD 11)

set (IPLAYER_SRCS src/main.cpp src/IPlayer.cpp src/Playlist.cpp src/Track.cpp src/Decoder.cpp src/CmdHelp.cpp src/CmdExit.cpp src/CmdAddTrack.cpp src/CmdDelTrack.cpp src/CmdShow.cpp src/CmdPlay.cpp src/CmdLoad.cpp src/CmdSave.cpp src/CmdSetMode.cpp src/CmdAfter.cpp src/CmdStop.cpp src/CmdPause.cpp src/CmdShowTrack.cpp src/CmdClear.cpp src/CmdNext.cpp src/CmdPrevious.cpp src/CmdDelDup.cpp)

if(MSVC)
    string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable (iplayer ${IPLAYER_SRCS})
