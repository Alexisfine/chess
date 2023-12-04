#include "TwoPlayerChessBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
void TwoPlayerChessBoard::setupBoard() {
    for (int row = 1; row <= dimension; row++) {
        for (int col = 1; col <= dimension; col++) {
            remove({row, col});
        }
    }
    chessPieces.clear();

    for (int col = 1; col <= dimension; col++) {
        addTo({2, col}, ChessColor::WHITE, ChessType::PAWN);
    }
    for (int col = 1; col <= dimension; col++) {
        addTo({7, col}, ChessColor::BLACK, ChessType::PAWN);
    }
    addTo({1, 1}, ChessColor::WHITE, ChessType::ROOK);
    addTo({1, 2}, ChessColor::WHITE, ChessType::KNIGHT);
    addTo({1, 3}, ChessColor::WHITE, ChessType::BISHOP);
    addTo({1, 4}, ChessColor::WHITE, ChessType::QUEEN);
    addTo({1, 5}, ChessColor::WHITE, ChessType::KING);
    addTo({1, 6}, ChessColor::WHITE, ChessType::BISHOP);
    addTo({1, 7}, ChessColor::WHITE, ChessType::KNIGHT);
    addTo({1, 8}, ChessColor::WHITE, ChessType::ROOK);

    addTo({8, 1}, ChessColor::BLACK, ChessType::ROOK);
    addTo({8, 2}, ChessColor::BLACK, ChessType::KNIGHT);
    addTo({8, 3}, ChessColor::BLACK, ChessType::BISHOP);
    addTo({8, 4}, ChessColor::BLACK, ChessType::QUEEN);
    addTo({8, 5}, ChessColor::BLACK, ChessType::KING);
    addTo({8, 6}, ChessColor::BLACK, ChessType::BISHOP);
    addTo({8, 7}, ChessColor::BLACK, ChessType::KNIGHT);
    addTo({8, 8}, ChessColor::BLACK, ChessType::ROOK);

}

TwoPlayerChessBoard::TwoPlayerChessBoard(int dimension) : ChessBoard{dimension} {
    setupBoard();
}

MoveResult TwoPlayerChessBoard::makeMove(Move move, ChessColor color) {
    // check if move is legal
    MoveResult res = isMoveLegal(move, color);
    if (!res.success) return res;

    // if new position contains a chess from the opponent, remove it
    if (!isPositionEmpty(move.getEnd()) && isPositionOccupiedByColor(move.getEnd(),color)) return {false, false};

    // capture this chess
    ChessPiece* capturedChess = board[move.getEnd().getRow()][move.getEnd().getCol()].getChessPiece();
    if (capturedChess) {
        remove(move.getEnd());
    }

    //castling
    if (move.getChessPiece()->getType() == ChessType::KING && abs(move.getStart().getCol() - move.getEnd().getCol()) == 2) {
        Position kingStart = move.getStart();
        Position kingEnd = move.getEnd();
        // Determine rook's start and end positions based on king's move
        bool isKingSide = kingEnd.getCol() > kingStart.getCol();
        int rookStartCol = isKingSide ? 8 : 1;
        int rookEndCol = isKingSide ? kingEnd.getCol() - 1 : kingEnd.getCol() + 1;
        Position rookStart(kingStart.getRow(), rookStartCol);
        Position rookEnd(kingStart.getRow(), rookEndCol);
        //move Rook to new position
        board[rookEnd.getRow()][rookEnd.getCol()].addChessPiece(board[rookStart.getRow()][rookStart.getCol()].getChessPiece());
        remove(rookStart);
        //increment Rook's moves
        board[rookEnd.getRow()][rookEnd.getCol()].getChessPiece()->incrementTotalMoves();
        //TextDisplay and Graphic Display of Rook's move
        textDisplay.notify(board[rookStart.getRow()][rookStart.getCol()]);
        textDisplay.notify(board[rookEnd.getRow()][rookEnd.getCol()]);
        if (graphicalDisplay) {
            graphicalDisplay->notify(board[rookStart.getRow()][rookStart.getCol()]);
            graphicalDisplay->notify(board[rookEnd.getRow()][rookEnd.getCol()]);
        }
    }

    // en passant
    // update pawn's state
    if (move.getChessPiece()->getType() == ChessType::PAWN) {
        if ((move.getStart().getRow() == 7 && move.getEnd().getRow() == 5)
        || (move.getStart().getRow() == 2 && move.getEnd().getRow() == 4)) {
            Pawn* pawn = dynamic_cast<Pawn*>(move.getChessPiece());
            pawn->setJustMadeDoubleStep(true);
        }
    }
    for (int row = 1; row <= dimension; row++) {
        for (int col = 1; col <= dimension; col++) {
            if (!isPositionEmpty({row, col})) {
                auto cur = board[row][col].getChessPiece();
                if (cur != move.getChessPiece() && cur->getType() == ChessType::PAWN) {
                    Pawn* curPawn = dynamic_cast<Pawn*>(cur);
                    curPawn->setJustMadeDoubleStep(false);
                }
            }
        }
    }

    if (move.getChessPiece()->getType() == ChessType::PAWN
    && move.getEnd().getCol() != move.getStart().getCol() && !capturedChess) {
        remove({move.getStart().getRow(), move.getEnd().getCol()});
    }

    // move chess to new position
    board[move.getEnd().getRow()][move.getEnd().getCol()].addChessPiece(move.getChessPiece());
    remove(move.getStart());


    textDisplay.notify(board[move.getStart().getRow()][move.getStart().getCol()]);
    textDisplay.notify(board[move.getEnd().getRow()][move.getEnd().getCol()]);
    if (graphicalDisplay) {
        graphicalDisplay->notify(board[move.getStart().getRow()][move.getStart().getCol()]);
        graphicalDisplay->notify(board[move.getEnd().getRow()][move.getEnd().getCol()]);
    }

    move.getChessPiece()->incrementTotalMoves();
    return res;
}

MoveResult TwoPlayerChessBoard::isMoveLegal(const Move& move, ChessColor color) {
    // check if the starting and ending position are valid
    if (!isValidPos(move.getStart()) || !isValidPos(move.getEnd())) return {false, false};
    // check if the player has a chess at the starting position
    const Cell& cell = board[move.getStart().getRow()][move.getStart().getCol()];
    if (!cell.isOccupiedByColor(color)) return {false, false};
    ChessPiece* chessPiece = cell.getChessPiece();
    return chessPiece->isMovePossiblyValid(*this, move);
}

bool TwoPlayerChessBoard::isValidPos(const Position& pos) const {
    return pos.getRow() >= 1 && pos.getRow() <= dimension && pos.getCol() >= 1 && pos.getCol() <= dimension;
}

TwoPlayerChessBoard::~TwoPlayerChessBoard() {
}


void TwoPlayerChessBoard::refresh() {
    setupBoard();
}

bool TwoPlayerChessBoard::isColorInCheck(ChessColor color) {
    ChessPiece* king = nullptr;
    int kingRow = 0;
    int kingCol = 0;
    // find king
    for (int row = 1; row <= dimension; row++) {
        for (int col = 1; col <= dimension; col++) {
            if (board[row][col].getState() == CellState::EMPTY) continue;
            if (board[row][col].getChessPiece()->getColor() == color &&
                    board[row][col].getChessPiece()->getType() == ChessType::KING) {
                king = board[row][col].getChessPiece();
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }
    if (!king) return false;

    // Check if any opponent's piece can attack the king
    for (int row = 1; row <= dimension; row++) {
        for (int col = 1; col <= dimension; col++) {
            if (board[row][col].getState() == CellState::EMPTY) continue;
            ChessPiece* piece = board[row][col].getChessPiece();
            if (piece && piece->getColor() != color) {
                // Generate potential moves for this piece
                // If any move can capture the king, return true
                Position pos {row, col};
                auto opponentMoves = piece->getAvailableMoves(*this, pos, false);
                for (auto move : opponentMoves) {
                    if (move.getEnd().getRow() == kingRow && move.getEnd().getCol() == kingCol) return true;
                }
            }
        }
    }
    return false;
}


bool TwoPlayerChessBoard::isColorInCheckMate(ChessColor color) {
    if (!isColorInCheck(color)) return false;

    for (int row = 1; row <= dimension; row++) {
        for (int col = 1; col <= dimension; col++) {
            ChessPiece* piece = board[row][col].getChessPiece();
            if (piece && piece->getColor() == color) {
                auto possibleMoves = piece->getAvailableMoves(*this, {row, col}, false);
                for (const auto& move : possibleMoves) {
                    if (!simulateMove(move, color)) {
                        return false; // Found a move that does not result in check
                    }
                }
            }
        }
    }
    return true; // No move found that gets the king out of check
}

// return true if one move still leads to check
bool TwoPlayerChessBoard::simulateMove(Move move, ChessColor color) {
    Position start = move.getStart();
    Position end = move.getEnd();
    if (isPositionEmpty(end)) {
        board[end.getRow()][end.getCol()].addChessPiece(move.getChessPiece());
        board[start.getRow()][start.getCol()].removeChessPiece();
        bool stillCheck = isColorInCheck(color);
        board[end.getRow()][end.getCol()].removeChessPiece();
        board[start.getRow()][start.getCol()].addChessPiece(move.getChessPiece());
        return stillCheck;
    } else {
        ChessPiece* curChess = board[end.getRow()][end.getCol()].getChessPiece();
        board[end.getRow()][end.getCol()].removeChessPiece();
        board[end.getRow()][end.getCol()].addChessPiece(move.getChessPiece());
        board[start.getRow()][start.getCol()].removeChessPiece();
        bool stillCheck = isColorInCheck(color);
        board[end.getRow()][end.getCol()].removeChessPiece();
        board[end.getRow()][end.getCol()].addChessPiece(curChess);
        board[start.getRow()][start.getCol()].addChessPiece(move.getChessPiece());
        return stillCheck;
    }
}

void TwoPlayerChessBoard::addTo(const Position& pos, ChessColor color, ChessType chessType) {
    std::unique_ptr<ChessPiece> newPiece;
    switch (chessType) {
        case ChessType::KING:
            newPiece = std::make_unique<King>(color);
            break;
        case ChessType::QUEEN:
            newPiece = std::make_unique<Queen>(color);
            break;
        case ChessType::BISHOP:
            newPiece = std::make_unique<Bishop>(color);
            break;
        case ChessType::ROOK:
            newPiece = std::make_unique<Rook>(color);
            break;
        case ChessType::KNIGHT:
            newPiece = std::make_unique<Knight>(color);
            break;
        case ChessType::PAWN:
            newPiece = std::make_unique<Pawn>(color);
            break;
    }
    board[pos.getRow()][pos.getCol()].addChessPiece(newPiece.get());
    chessPieces.emplace_back(std::move(newPiece));

    textDisplay.notify(board[pos.getRow()][pos.getCol()]);
    if (graphicalDisplay) {
        graphicalDisplay->notify(board[pos.getRow()][pos.getCol()]);
    }
}

void TwoPlayerChessBoard::remove(const Position& pos) {
    board[pos.getRow()][pos.getCol()].removeChessPiece();
    textDisplay.notify(board[pos.getRow()][pos.getCol()]);
    if (graphicalDisplay) {
        graphicalDisplay->notify(board[pos.getRow()][pos.getCol()]);
    }
}

bool TwoPlayerChessBoard::verifySetup() {
    int whiteKing = 0;
    int blackKing = 0;
    for (int row = 1; row <= dimension; row++) {
        for (int col = 1; col <= dimension; col++) {
            if (row == 1 || row == dimension) {
                if (board[row][col].isOccupied()
                && board[row][col].getChessPiece()->getType() == ChessType::PAWN) return false;
            }
            if (board[row][col].isOccupied()
                && board[row][col].getChessPiece()->getType() == ChessType::KING) {
                if (board[row][col].getChessPiece()->getColor() == ChessColor::WHITE) {
                    whiteKing++;
                } else {
                    blackKing++;
                }
            }
        }
    }
    if (whiteKing != 1 || blackKing != 1) return false;
    if (isColorInCheck(ChessColor::WHITE) || isColorInCheck(ChessColor::BLACK)) return false;
    return true;
}


std::vector<ValidMove> TwoPlayerChessBoard::getAllValidMoves(ChessColor color, bool check) {
    std::vector<ValidMove> moves;
    for (int row = 1; row <= dimension; row++) {
        for (int col = 1; col <= dimension; col++) {
            if (board[row][col].isOccupied() && board[row][col].isOccupiedByColor(color)) {
                auto chessMoves = board[row][col].getChessPiece()->getAvailableMoves(*this, {row, col}, check);
                for (auto move : chessMoves) moves.emplace_back(move);
            }
        }
    }
    return moves;
}

bool TwoPlayerChessBoard::simulateEnPassant(Move move, ChessColor color) {
    Position start = move.getStart();
    Position end = move.getEnd();
    board[end.getRow()][end.getCol()].addChessPiece(move.getChessPiece());
    board[start.getRow()][start.getCol()].removeChessPiece();
    ChessPiece* capturedPawn = board[start.getRow()][end.getCol()].getChessPiece();
    board[start.getRow()][end.getCol()].removeChessPiece();
    bool check = isColorInCheck(color);
    board[end.getRow()][end.getCol()].removeChessPiece();
    board[start.getRow()][start.getCol()].addChessPiece(move.getChessPiece());
    board[start.getRow()][end.getCol()].addChessPiece(capturedPawn);

    return check;
}

//return true if the piece can be captured by opponent's piece in the next move
CapturedInfo TwoPlayerChessBoard::simulateCapture(Move move, ChessColor color) {
    Position start = move.getStart();
    Position end = move.getEnd();
    ChessPiece* movedPiece = move.getChessPiece();

    // Store the original state
    ChessPiece* originalPieceAtEnd = board[end.getRow()][end.getCol()].getChessPiece();

    // Simulate the move
    board[start.getRow()][start.getCol()].removeChessPiece();
    board[end.getRow()][end.getCol()].addChessPiece(movedPiece);

    // Check if any opponent's piece can capture the moved piece
    bool canBeCaptured = false;
    int capturedScore = 0;
    for (int row = 1; row <= getDimension(); ++row) {
        for (int col = 1; col <= getDimension(); ++col) {
            Position pos(row, col);
            const Cell& cell = board[pos.getRow()][pos.getCol()];
            if (cell.isOccupied() && cell.getChessPiece()->getColor() != color) {
                // Check each of the opponent's piece's valid moves
                std::vector<ValidMove> opponentMoves = cell.getChessPiece()->getAvailableMoves(*this, pos, false);
                for (const ValidMove& oppMove : opponentMoves) {
                    if (oppMove.getEnd() == end) {
                        canBeCaptured = true;
                        capturedScore = min(capturedScore, -cell.getChessPiece()->getScore());
                    }
                }
            }
        }
    }

    // Undo the move
    board[start.getRow()][start.getCol()].addChessPiece(movedPiece);
    if (originalPieceAtEnd) {
        board[end.getRow()][end.getCol()].addChessPiece(originalPieceAtEnd);
    } else {
        board[end.getRow()][end.getCol()].removeChessPiece();
    }

    return {canBeCaptured, capturedScore};
}

