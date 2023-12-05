#include "Queen.h"

Queen::Queen(ChessColor color):
    ChessPiece(ChessType::QUEEN, color) {}

MoveResult Queen::isMovePossiblyValid(ChessBoard& board, const Move& move)  {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(board, move.getStart(), true);
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return {true, false};
    }
    return {false, false};
}

vector<ValidMove> Queen::addPossibleMoveByDirection(ChessBoard& board,
                                const Position& curPosition, int dy, int dx, int maxMoves, bool check) {
    vector<ValidMove> newMoves;
    int curRow = curPosition.getRow();
    int curCol = curPosition.getCol();
    for (int x = 0; x < maxMoves; x++) {
        Position newPosition {curRow + dy, curCol + dx};
        if (!board.isValidPos(newPosition)) return newMoves; // check if position is valid
        const Cell& cell = board.getCellAtPos(newPosition);
        bool canCapture = false;
        Move move {curPosition, newPosition, this};
        ChessColor opponentColor = color == ChessColor::WHITE ? ChessColor::BLACK : ChessColor::WHITE;
        bool canCheck = check && board.simulateMove(move, opponentColor);
        int beCapturedScore = check ? board.simulateCapture(move, color).score : 0;

        if (cell.isOccupied()) {
            canCapture = true;
            if (!cell.isOccupiedByColor(color)) {
                ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck,
                                        board.getCellAtPos(newPosition).getChessPiece()->getScore(), beCapturedScore};
                if (check) {
                    bool willCheck = board.simulateMove(possibleMove, color);
                    if (!willCheck) {
                        newMoves.emplace_back(possibleMove);
                    }
                } else newMoves.emplace_back(possibleMove);
            }
            break; //cannot move pass another chesspiece
        }
        //if the cell is not occupied
        ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck, 0, beCapturedScore};
        if (check) {
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) {
                newMoves.emplace_back(possibleMove);
            }
        } else newMoves.emplace_back(possibleMove);

        // update curRow, curCol
        curRow += dy;
        curCol += dx;
    }
    return newMoves;

}
std::vector<ValidMove> Queen::getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check)  {
    std::vector<ValidMove> moves;
    const int dimension = board.getDimension();
    int curRow = curPosition.getRow();
    int curCol = curPosition.getCol();
    //maximum number of moves, without considering blocks
    int RX = dimension - curCol;
    int LX = curCol - 1;
    int upY = dimension - curRow;
    int downY = curRow - 1;
    //move right
    auto rightMoves = addPossibleMoveByDirection(board, curPosition, 0, 1, RX, check);
    for (auto move : rightMoves) moves.emplace_back(move);

    //move left
    auto leftMoves = addPossibleMoveByDirection(board, curPosition, 0, -1, LX, check);
    for (auto move : leftMoves) moves.emplace_back(move);

    //move up
    auto upMoves = addPossibleMoveByDirection(board, curPosition, 1, 0, upY, check);
    for (auto move : upMoves) moves.emplace_back(move);

    //move down
    auto downMoves = addPossibleMoveByDirection(board, curPosition, -1, 0, downY, check);
    for (auto move : downMoves) moves.emplace_back(move);

    //diagonal moves
    int UR = std::min(RX, upY); //up-right direction
    int UL = std::min(LX, upY); //up-left direction
    int DR = std::min(RX, downY); //down-right direction
    int DL = std::min(LX, downY); //down-left direction
    //1. Up-right diagonal moves
    auto upRightMoves = addPossibleMoveByDirection(board, curPosition, 1, 1, UR, check);
    for (auto move : upRightMoves) moves.emplace_back(move);

    //2. Up-left diagonal moves
    auto upLeftMoves = addPossibleMoveByDirection(board, curPosition, 1, -1, UL, check);
    for (auto move : upLeftMoves) moves.emplace_back(move);

    //3. Down-right diagonal moves
    auto downRightMoves = addPossibleMoveByDirection(board, curPosition, -1, 1, DR, check);
    for (auto move : downRightMoves) moves.emplace_back(move);

    //4. Down-left diagonal moves
    auto DownLeftMoves = addPossibleMoveByDirection(board, curPosition, -1, -1, DL, check);
    for (auto move : DownLeftMoves) moves.emplace_back(move);

    return moves;
}
