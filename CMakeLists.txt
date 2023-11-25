cmake_minimum_required(VERSION 3.24)
project(chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess main.cc ChessBoard.cc ChessBoard.h Cell.cc Cell.h ChessPiece.cc ChessPiece.h Player.cc Player.h ChessGame.cc ChessGame.h Display.cc Display.h King.cc King.h Queen.cc Queen.h Bishop.cc Bishop.h Rook.cc Rook.h Knight.cc Knight.h Pawn.cc Pawn.h Position.cc Position.h Move.cc Move.h)
