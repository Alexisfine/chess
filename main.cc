#include <iostream>
#include "ChessGame.h"
#include <string>
#include <sstream>
#include "Position.h"

using namespace std;

Position strToPos(string str) {
    char a = str[0];
    char b = str[1];
    int row = b - '0';
    int col = a - 'a' + 1;
    return {row, col};
}

ChessType strToType(string str) {
    ChessType type;
    switch (str[0]) {
        case 'K':
            type = ChessType::KING;
            break;
        case 'k':
            type = ChessType::KING;
            break;
        case 'Q':
            type = ChessType::QUEEN;
            break;
        case 'q':
            type = ChessType::QUEEN;
            break;
        case 'B':
            type = ChessType::BISHOP;
            break;
        case 'b':
            type = ChessType::BISHOP;
            break;
        case 'N':
            type = ChessType::KNIGHT;
            break;
        case 'n':
            type = ChessType::KNIGHT;
            break;
        case 'R':
            type = ChessType::ROOK;
            break;
        case 'r':
            type = ChessType::ROOK;
            break;
        default:
            type = ChessType::PAWN;
            break;
    }
    return type;
}

ChessColor strToColor(string str) {
    if ('a' <= str[0] && str[0] <= 'z') {
        return ChessColor::BLACK;
    }
    return ChessColor::WHITE;
}

int main() {
    string command, aux;
    ChessGame* game;

    while (cin >> command) {
        if (command == "game") {
            int playerOneType;
            int playerTwoType;
            cin >> playerOneType;
            cin >> playerTwoType;
            // for now, just use two human players
            game = new ChessGame {8};
        } else if (command == "resign") {
            ChessColor color = game->getCurrentColor();
            game->resign();
            if (color == ChessColor::WHITE) {
                cout << "Black wins!" << endl;
            } else {
                cout << "White wins!" << endl;
            }
        } else if (command == "move") {
            string from;
            string to;
            cin >> from;
            cin >> to;
            Position fromPos = strToPos(from);
            Position toPos = strToPos(to);
            bool success = game->move(fromPos, toPos);
            if (!success) {
                cout << "Invalid Move" << endl;
                continue;
            }
            cout << *game << endl;
            auto isCheckMate = game->getIsChecked();
            for (const auto& [player, check] : isCheckMate) {
                if (check) {
                    if (player->getColor() == ChessColor::WHITE) {
                        cout << "White is in check." << endl;
                    } else {
                        cout << "Black is in check." << endl;
                    }
                }
            }

            // game has ended
            if (!game->hasStarted()) {
                if (game->getResult() == GameResult::WHITE_WON) {
                    cout << "Checkmate! White wins!" << endl;
                } else if (game->getResult() == GameResult::BLACK_WON) {
                    cout << "Checkmate! Black wins!" << endl;
                } else {
                    cout << "Stalemate" << endl;
                }
                game->displayScore();
            }

        } else if (command == "setup") {
            if (game->hasStarted()) {
                cout << "Invalid Command, the game has already started" << endl;
                cin.ignore();
                cin.clear();
                continue;
            }
            bool setUpMode = true;
            while (setUpMode) {
                cin >> aux;
                if (aux == "+") {
                    string type;
                    string position;
                    cin >> type;
                    cin >> position;
                    ChessType chessType = strToType(type);
                    Position pos = strToPos(position);
                    game->addChess(pos, strToColor(type), chessType);
                    cout << *game << endl;
                } else if (aux == "-") {
                    string position;
                    cin >> position;
                    game->removeChess(strToPos(position));
                    cout << *game << endl;
                } else if (aux == "=") {
                    string color;
                    cin >> color;
                    ChessColor c;
                    if (color == "white") c = ChessColor::WHITE;
                    else c = ChessColor::BLACK;
                    game->setCurrentTurn(c);
                } else if (aux == "done") {
                    bool isValid = game->verifySetup();
                    if (isValid) setUpMode = false;
                    else std::cout << "Setup is not valid" << std::endl;
                    if (isValid) {
                        game->start();
                        std::cout << "Game begins" << std::endl;
                    }
                } else {
                    std::cout << "Invalid command" << std::endl;
                    cin.ignore();
                    cin.clear();
                }
            }
        } else {
            std::cout << "Invalid command" << std::endl;
            cin.ignore();
            cin.clear();
        }
    }

    delete game;
}
