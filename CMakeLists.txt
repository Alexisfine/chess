cmake_minimum_required(VERSION 3.24)
project(chess)

set(CMAKE_CXX_STANDARD 20)
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})
add_executable(chess main.cc ChessBoard.cc ChessBoard.h Cell.cc Cell.h ChessPiece.cc ChessPiece.h Player.cc Player.h ChessGame.cc ChessGame.h XDisplay.h King.cc King.h Queen.cc Queen.h Bishop.cc Bishop.h Rook.cc Rook.h Knight.cc Knight.h Pawn.cc Pawn.h Position.cc Position.h Move.cc Move.h TwoPlayerChessBoard.cc TwoPlayerChessBoard.h HumanPlayer.cc HumanPlayer.h ComputerPlayer.cc ComputerPlayer.h ValidMove.cc ValidMove.h TextDisplay.cc XWindow.cc XWindow.h GraphicsDisplay.cc GraphicsDisplay.h)
target_link_libraries(chess ${X11_LIBRARIES})
