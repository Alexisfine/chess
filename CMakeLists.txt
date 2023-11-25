cmake_minimum_required(VERSION 3.24)
project(chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess main.cc ChessBoard.cc ChessBoard.h Cell.cc Cell.h ChessPiece.cc ChessPiece.h Player.cc Player.h ChessGame.cc ChessGame.h Display.cc Display.h)
