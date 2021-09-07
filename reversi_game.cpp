
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

    vector< vector<char> > board = initialize_board(dim);
    print_board(board);

    cout << "Enter reset if you are not satisfied with the board configuration, or enter anything else to continue: ";
    string input;
    cin >> input;

    while (input == "reset") {
        vector< vector<char> > board = initialize_board(dim);
        print_board(board);

        cout << "Enter reset if you are not satisfied with the board configuration, or enter anything else to continue: ";
        cin >> input;

        if (input == "reset") {
            continue;
        } else {
            break;
        }
    }

    valid_exist(board, dim, B_valid, W_valid);

    while (check_endgame(B_valid, W_valid)) {

        int row;
        int col;
        char color; 

        if (B_valid.size() != 0) {

            string input;
            cout << "It's O's turn, please enter a coordinate: ";
            color = 'B';
            cin >> input;

            while (!(convert_input(input, row, col))) {
                cout << "Please enter a correctly formatted coordinate: ";
                cin >> input;
            }

            // at this step the input is definitely inbound

            while (!(check_valid(board, row, col, color, dim, num_flips))) {
                cout << "The move you have requested is not possible" << endl;
                cout << "Please enter a valid coordinate: ";
                cin >> input; 
                convert_input(input, row, col);
            }

            // at this step the move is definitely valid

            place_piece(board, row, col, color);
            flip_pieces(board, row, col, color, num_flips);

            // finished changing the board, display newboard
            cout << endl;
            print_board(board);

            // print new available moves
            valid_exist(board, dim, B_valid, W_valid);
        }

        if (W_valid.size() != 0) {

            if (opponent == 'H') {
    
                string input;
                cout << "It's X's turn, please enter a coordinate: ";
                color = 'W';
                cin >> input;

                while (!(convert_input(input, row, col))) {
                    cout << "Please enter a correctly formatted coordinate: ";
                    cin >> input;
                }

                // at this step the input is definitely inbound

                while (!(check_valid(board, row, col, color, dim, num_flips))) {
                    cout << "The move you have requested is not possible" << endl;
                    cout << "Please enter a valid coordinate: ";
                    cin >> input; 
                    convert_input(input, row, col);
                }

                // at this step the move is definitely valid

                place_piece(board, row, col, color);
                flip_pieces(board, row, col, color, num_flips);

            } else if (opponent == 'C') {
                color = 'W';

                // find optimal move, then make the move
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
    }

    // exit the while loop when neithe player has a valid move

    declare_score(board, true);

    return 1;
}
