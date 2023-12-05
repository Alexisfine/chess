#include "CommandInterpreter.h"
#include <iostream>
#include <set>
#include <stdexcept>
using namespace std;

Position strToPos(string str) {
    if (str.length() != 2 || str[0] < 'a' || str[0] > 'h' || str[1] < '1' || str[1] > '8') {
        throw invalid_argument("Invalid position format");
    }
    char a = str[0];
    char b = str[1];
    int row = b - '0';
    int col = a - 'a' + 1;
    return {row, col};
}

ChessType strToType(string str) {
    if (str.empty()) {
        throw invalid_argument("Invalid chess type");
    }

    ChessType type;
    switch (str[0]) {
        case 'K': case 'k':
            type = ChessType::KING;
            break;
        case 'Q': case 'q':
            type = ChessType::QUEEN;
            break;
        case 'B': case 'b':
            type = ChessType::BISHOP;
            break;
        case 'N': case 'n':
            type = ChessType::KNIGHT;
            break;
        case 'R': case 'r':
            type = ChessType::ROOK;
            break;
        case 'P': case 'p':
            type = ChessType::PAWN;
            break;
        default:
            throw invalid_argument("Invalid chess type");
    }
    return type;
}


ChessColor strToColor(string str) {
    if ('a' <= str[0] && str[0] <= 'z') {
        return ChessColor::BLACK;
    }
    return ChessColor::WHITE;
}
CommandInterpreter::CommandInterpreter() {}

void CommandInterpreter::run() {
    set<string> validCommands = {"resign", "move", "game", "setup"};
    XWindow xw {};
    string command, aux;
    ChessGame game {8, xw};
    PlayerType pt1;
    PlayerType pt2;

    while (cin >> command) {
         if (validCommands.find(command) == validCommands.end()) {
            cout << "Invalid command" << endl;
            cin.ignore(100, '\n');
            cin.clear();
            continue;
        }
        if (game.hasStarted()) {
            if (command == "resign") {
                game.resign();
                game.init();
            } else if (command == "move") {
                if (game.getCurrentColor() == ChessColor::WHITE && pt1 == PlayerType::COMPUTER) {
                    game.autoMove(game.getCurrentColor());
                } else if (game.getCurrentColor() == ChessColor::BLACK && pt2 == PlayerType::COMPUTER) {
                    game.autoMove(game.getCurrentColor());

                } else {
                    try {
                    string from;
                    string to;
                    cin >> from;
                    cin >> to;
                    Position fromPos = strToPos(from);
                    Position toPos = strToPos(to);

                    MoveResult result = game.move(fromPos, toPos);
                    if (result.pawnPromotion) {
                        bool validInput = false;
                        char promotedChess;
                        ChessType newChess;
                        while (!validInput) {                       
                            cin >> promotedChess;                               
                            switch (promotedChess) {
                                case 'Q': case 'q':
                                    newChess = ChessType::QUEEN;
                                    validInput = true;
                                    break;
                                case 'R': case 'r':
                                    newChess = ChessType::ROOK;
                                    validInput = true;
                                    break;
                                case 'B': case 'b':
                                    newChess = ChessType::BISHOP;
                                    validInput = true;
                                    break;
                                case 'N': case 'n':
                                    newChess = ChessType::KNIGHT;
                                    validInput = true;
                                    break;
                                default:
                                    cout << "Invalid Chess Type. Choose from Queen, Rook, Bishop, or Knight" << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                            }
                        } 
                        game.promotePawn(newChess, toPos);
                    }
                    if (!result.success) {
                        cout << "Invalid Move" << endl;
                        continue;
                    }
                }
                catch (const std::invalid_argument& e) {
                    cout << "Error: " << e.what() << endl;
                    continue;
                }
            }
                game.postMove();
                cin.ignore();
                cin.clear();
            }
        } else {
            if (command == "game") {
                string playerOneType;
                string playerTwoType;
                int level1 = 1;
                int level2 = 1;
                cin >> playerOneType;
                cin >> playerTwoType;
                // Parse playerOne type and level
                if (playerOneType == "human") {
                    pt1 = PlayerType::HUMAN;
                } else if (playerOneType.find("computer") != string::npos) {
                    pt1 = PlayerType::COMPUTER;
                    level1 = playerOneType[9] - '0'; // Extract level from "computer[1-4]"
                }

                // Parse playerOne type and level
                if (playerTwoType == "human") {
                    pt2 = PlayerType::HUMAN;
                } else if (playerTwoType.find("computer") != string::npos) {
                    pt2 = PlayerType::COMPUTER;
                    level2 = playerTwoType[9] - '0'; // Extract level from "computer[1-4]"
                }

                game.start(pt1, pt2, level1, level2);

            } else if (command == "setup") {
                if (game.hasStarted()) {
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
                        try {
                            ChessType chessType = strToType(type);
                            Position pos = strToPos(position);
                            game.addChess(pos, strToColor(type), chessType);
                            cout << game << endl;
                        }
                        catch (const std::invalid_argument& e) {
                            cout << "Error: " << e.what() << endl;
                            continue;
                        }
                    } else if (aux == "-") {
                        string position;
                        cin >> position;
                        try{
                            game.removeChess(strToPos(position));
                            cout << game << endl;
                        }
                        catch (const std::invalid_argument& e) {
                            cout << "Error: " << e.what() << endl;
                            continue;
                        }
                    } else if (aux == "=") {
                        string color;
                        cin >> color;
                        ChessColor c;
                        if (color == "white") c = ChessColor::WHITE;
                        else c = ChessColor::BLACK;
                        game.setCurrentTurn(c);
                    } else if (aux == "done") {
                        bool isValid = game.verifySetup();
                        if (isValid) {
                            setUpMode = false;
                            cout << "Setup is completed" << endl;
                            game.completeSetup();
                        }
                        else cout << "Setup is not valid" << endl;

                    } else if (aux == "erase") {
                        game.erase();
                        cout << game << endl;
                    } else {
                        cout << "Invalid command" << endl;
                        cin.ignore();
                        cin.clear();
                    }
                }
            } else {
                cout << "Invalid command" << endl;
                cin.ignore();
                cin.clear();
            }
        }
    }
    game.displayScore();
}

