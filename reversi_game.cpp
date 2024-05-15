
#include <iostream>
#include <string>
#include <vector>
#include "reversi_helper.h"

using namespace std;

// on printed board, black is O, white is X

int main() {
    int dim;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    vector<int> num_flips;
    vector<int> B_valid;
    vector<int> W_valid;
    char opponent;

    cout << "Welcone to reversi!" << endl;

    while (opponent != 'H' && opponent != 'C') {
        cout << "Select playing against another human (H) or against the computer (C) ";
        cin >> opponent;
    }

    vector< vector<char> > board;

    while (true) {
        board = initialize_board(dim);
        print_board(board);

        cout << "Enter reset if you are not satisfied with the board configuration, else enter continue: ";
        string input;
        cin >> input;

        if (input == "reset") {
            continue;
        }
        
        break;
    }

    cout << "Board ready" << endl;
    valid_exist(board, dim, B_valid, W_valid);
    char color = 'W';

    while (!check_endgame(B_valid, W_valid)) {

        int row;
        int col;
        
        if (color == 'B' && W_valid.size() != 0) {
            color = 'W';
        } else if (color == 'W' && B_valid.size() != 0) {
            color = 'B';
        }

        if (color == 'B') {
            cout << "It's O's turn, please enter a coordinate: ";
        } else if (color == 'W' && opponent == 'H') {
            cout << "It's X's turn, please enter a coordinate: ";
        }

        if (!(color == 'W' && opponent == 'C')) {
            string input;
            cin >> input;

            while (!convert_input(input, row, col)) {
                cout << "Please enter a correctly formatted coordinate: ";
                cin >> input;
            }

            // at this step the input is definitely inbound

            while (!check_valid(board, row, col, color, dim, num_flips)) {
                cout << "The move you have requested is not possible" << endl;
                cout << "Please enter a valid coordinate: ";
                cin >> input; 
                convert_input(input, row, col);
            }

            // at this step the move is definitely valid

            place_piece(board, row, col, color);
            flip_pieces(board, row, col, color, num_flips);            
        } else {
            select_optimal(board, row, col, dim, num_flips);

            // reset num_flips by calling check_valid
            check_valid(board, row, col, color, dim, num_flips);
            place_piece(board, row, col, color);
            flip_pieces(board,row, col, color, num_flips);
            cout << "The AI played " << alphabet[row] << alphabet[col] << endl;
        }
     
        // finished changing the board, display newboard
        cout << endl;
        print_board(board);

        // print new available moves
        valid_exist(board, dim, B_valid, W_valid);
    }

    // exit the while loop when neithe player has a valid move

    declare_score(board, true);

    return 0;
}
