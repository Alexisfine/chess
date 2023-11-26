//
// Created by 薛景帝 on 2023/11/24.
//

#include "Bishop.h"

Bishop::Bishop(ChessBoard& board, Player& owner):
    ChessPiece(ChessType::BISHOP, board, owner) {}

bool Bishop::isMovePossiblyValid(const Move& move) const {
    std::vector<Move> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move == validMove) return true;
    }
    return false;
}


std::vector<Move> Bishop::getAvailableMoves(const Position& curPosition) const {
    std::vector<Move> moves;
    const int MAX = 8;
    int curRow = curPosition.getRow();
    int curCol = curPosition.getCol();
    //maximum number of moves, without considering blocks
    int RX = MAX - curCol - 1;
    int LX = -curCol + 1;
    int upY = MAX - curRow - 1;
    int downY = -curRow + 1;
    //diagonal moves
    int UR = std::min(RX, upY); //up-right direction
    int UL = std::min(LX, upY); //up-left direction
    int DR = std::min(RX, downY); //down-right direction
    int DL = std::min(LX, downY); //down-left direction
    //1. Up-right diagonal moves
    for (int ur = 0; ur < UR; ur++) {
        Position newPosition {curRow + ur, curCol + ur};
        const Cell& cell = board.getCellAtPos(newPosition);
        if (cell.isOccupied()) {
            if (!cell.isOccupiedByMe(owner)) {
                Move possibleMove {curPosition, newPosition, this};
                moves.emplace_back(possibleMove);
            }
            break; //cannot move pass another chesspiece
        }
        //if the cell is not occupied
        Move possibleMove {curPosition, newPosition, this};
        moves.emplace_back(possibleMove);
    }
    //2. Up-left diagonal moves
    for (int ul = 0; ul < UL; ul++) {
        Position newPosition {curRow + ul, curCol - ul};
        const Cell& cell = board.getCellAtPos(newPosition);
        if (cell.isOccupied()) {
            if (!cell.isOccupiedByMe(owner)) {
                Move possibleMove {curPosition, newPosition, this};
                moves.emplace_back(possibleMove);
            }
            break; //cannot move pass another chesspiece
        }
        //if the cell is not occupied
        Move possibleMove {curPosition, newPosition, this};
        moves.emplace_back(possibleMove);
    }
    //3. Down-right diagonal moves
    for (int dr = 0; dr < DR; dr++) {
        Position newPosition {curRow - dr, curCol + dr};
        const Cell& cell = board.getCellAtPos(newPosition);
        if (cell.isOccupied()) {
            if (!cell.isOccupiedByMe(owner)) {
                Move possibleMove {curPosition, newPosition, this};
                moves.emplace_back(possibleMove);
            }
            break; //cannot move pass another chesspiece
        }
        //if the cell is not occupied
        Move possibleMove {curPosition, newPosition, this};
        moves.emplace_back(possibleMove);
    }
    //4. Down-left diagonal moves
    for (int dl = 0; dl < DL; dl++) {
        Position newPosition {curRow - dl, curCol - dl};
        const Cell& cell = board.getCellAtPos(newPosition);
        if (cell.isOccupied()) {
            if (!cell.isOccupiedByMe(owner)) {
                Move possibleMove {curPosition, newPosition, this};
                moves.emplace_back(possibleMove);
            }
            break; //cannot move pass another chesspiece
        }
        //if the cell is not occupied
        Move possibleMove {curPosition, newPosition, this};
        moves.emplace_back(possibleMove);
    }

    return moves;
}

