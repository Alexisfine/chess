#include "King.h"

King::King(ChessColor color) :
        ChessPiece{ChessType::KING, color} {}

MoveResult King::isMovePossiblyValid(ChessBoard& board, const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(board, move.getStart(), true);
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return {true, false};
    }
    return {false, false};
}
std::vector<ValidMove> King::getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) {
    int possibleMoves[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};
    std::vector<ValidMove> moves;
    for (auto pos : possibleMoves) {
        Position newPosition {curPosition.getRow() + pos[0], curPosition.getCol() + pos[1]};
        if (!board.isValidPos(newPosition)) continue; // check if newPosition is within the grid
        // check if newPosition is occupied by myself
        if (!board.isPositionEmpty(newPosition) && board.isPositionOccupiedByColor(newPosition, color)) continue;
        bool canCheck = false; //  Implement Check Later
        bool canCapture = false;
        if (!board.isPositionEmpty(newPosition)) canCapture = true;
        ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
        if (check) {
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) {
                moves.emplace_back(possibleMove);

            }
        } else {
            moves.emplace_back(possibleMove);
        }

    }
    //castling
    if (totalMoves == 0) {
        int row = curPosition.getRow();
        // Positions for rooks
        Position rookPos1 = (color == ChessColor::WHITE) ? Position(1, 8) : Position(8, 8);
        Position rookPos2 = (color == ChessColor::WHITE) ? Position(1, 1) : Position(8, 1);

        // Check for Rook at rookPos1
        if (isCastlingAvailable(board, curPosition, rookPos1)) {
            Position newKingPos(row, curPosition.getCol() + 2);  // King's new position
            ValidMove possibleMove {curPosition, newKingPos, this, false, false};
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) {
                moves.emplace_back(possibleMove);
            }
        }

        // Check for Rook at rookPos2
        if (isCastlingAvailable(board, curPosition, rookPos2)) {
            Position newKingPos(row, curPosition.getCol() - 2);  // King's new position
            ValidMove possibleMove {curPosition, newKingPos, this, false, false};
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) {
                moves.emplace_back(possibleMove);
            }
        }
    }

    return moves;
}

bool King::isCastlingAvailable(ChessBoard& board,const Position& kingPos, const Position& rookPos) {
    ChessPiece* rook = board.getCellAtPos(rookPos).getChessPiece();
    if (rook && rook->getTotalMoves() == 0) { //check if rook is not removed
        // Check if spaces between King and Rook are empty
        int startCol = min(kingPos.getCol(), rookPos.getCol()) + 1;
        int endCol = max(kingPos.getCol(), rookPos.getCol());
        for (int col = startCol; col < endCol; ++col) {
            if (!board.isPositionEmpty(Position(kingPos.getRow(), col))) {
                return false;
            }
        }
        return true; // All conditions met
    }
    return false; // Rook has moved or does not exist
}
