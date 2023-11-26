//
// Created by 薛景帝 on 2023/11/24.
//

#include "Rook.h"

Rook::Rook(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::ROOK, board, owner} {}

bool Rook::isMovePossiblyValid(const Move& move) const {
    std::vector<Move> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move == validMove) return true;
    }
    return false;
}


std::vector<Move> Rook::getAvailableMoves(const Position& curPosition) const {
    std::vector<Move> moves;
    const int MAX = 8;
    int curRow = curPosition.getRow();
    int curCol = curPosition.getCol();
    //maximum number of moves, without considering blocks
    int RX = MAX - curCol - 1;
    int LX = -curCol + 1;
    int upY = MAX - curRow - 1;
    int downY = -curRow + 1;
    //move right
    for (int dx = 1; dx <= RX; ++dx) {
        Position newPosition {curRow, curCol + dx};
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
    //move left
    for (int dx = -1; dx >= LX; --dx) {
        Position newPosition {curRow, curCol + dx};
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
    //move up
    for (int dy = 1; dy <= upY; ++dy) {
        Position newPosition {curRow + dy, curCol};
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
    //move down
    for (int dy = -1; dy >= downY; --dy) {
        Position newPosition {curRow + dy, curCol};
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
