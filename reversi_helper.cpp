
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int dim;
vector <int> num_flips;
int row;
int col;

int sum_vector(vector<int> nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += nums.at(i);
    }
    return sum;
}

void declare_score(const vector< vector<char> > board, bool endgame = false) {
    int black_count = 0;
    int white_count = 0;

    // iterate through the board and tabulates the amount of B and W
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[0].size(); col++) {
            if (board[row][col] == 'B') {
                black_count++;
            } else if (board[row][col] == 'W') {
                white_count++;
            }
        }
    }

    // report the result to terminal
    cout << "Circles: " << black_count << endl;
    cout << "Crosses: " << white_count << endl;

    if (endgame) {
        if (black_count > white_count) {
            cout << "Circle won!" << endl;
        } else if (white_count > black_count) {
            cout << "Cross won!" << endl;
        } else if (white_count == black_count) {
            cout << "It's a draw!" << endl;
        }
    }
}

bool convert_input(const string input, int &row, int &col) {

    if (alphabet.find(input[0]) != string::npos && alphabet.find(input[1]) != string::npos) {
        row = alphabet.find(input[0]);
        col = alphabet.find(input[1]);
        return true;
    }

    return false;
}

void print_board(const vector< vector<char> > board) {
    declare_score(board);
    cout << endl;

    cout << "   ";
    for (int i = 0; i < board.size(); i++) {
        cout << alphabet[i] << " ";
    }
    cout << endl;

    // print a line of dashes
    cout << "  -";
    for (int col = 0; col < board[0].size(); col++) {
        cout << "--";
    }
    cout << endl;

    for (int row = 0; row < board.size(); row++) {
        cout << alphabet[row] << " |";

        // print pieces on the board
        // Black is O, White is X, blank is space
        for (int col = 0; col < board[0].size(); col++) {
            if (board[row][col] == 'U') {
                cout << " ";
            } else if (board[row][col] == 'B') {
                cout << "O";
            } else if (board[row][col] == 'W') {
                cout << 'X';
            }
            // print a vertical separating line
            cout << '|';
        }
        cout << endl;
        cout << "  -";

        // for each row of content, print a row of dashes
        for (int col = 0; col < board[0].size(); col++) {
            cout << "--";
        }
        cout << endl;
    }
    cout << endl;
}

vector< vector<char> > initialize_board(int &dim) {

    while (true) {
        cout << "Board Dimension (even only between 2 and 26): ";
        cin >> dim;
        if (dim % 2 != 0) {
            cout << "Board dimension can only be even." << endl;
        } else if (dim <= 26 && dim >= 2) {
            // check board dimension is valid
            break;
        }
    }

    vector<char> row(dim, 'U');
    vector< vector<char> > board(dim, row);

    int mid_up = dim/2;
    int mid_low = mid_up - 1;

    // initialize default centerpieces 

    board[mid_up][mid_up] = 'W';
    board[mid_low][mid_low] = 'W';
    board[mid_low][mid_up] = 'B';
    board[mid_up][mid_low] = 'B';

    print_board(board);

    string mods;
    cout << "Additional Board Modifications " << endl;
    cout << "Format: {Row}{Column}{W|B}" << endl;
    cout << "Enter !!! when finished:" << endl;

    while (true) {
        cin >> mods;
        if (mods == "!!!") {
            break;
        }
        // check input is of correct format
        if (mods[2] != 'W' && mods[2] != 'B') {
            cout << "You can only change a grid to black (O) or white (X)." << endl;
            continue;
        } else {
            // check the coordinate we want to change is inbound
            if (alphabet.find(mods[0]) != string::npos && alphabet.find(mods[1]) != string::npos) {
                int row = alphabet.find(mods[0]);
                col = alphabet.find(mods[1]);

                // now we implement the change
                if (row < dim && col < dim) {
                    board[row][col] = mods[2];
                    cout << "Change implemented" << endl;
                    print_board(board);
                    cout << "Continue entering modifications, or !!! when done:" << endl;
                } else {
                    cout << "Please enter a inbound coordinate" << endl;
                }   
            } else {
                cout << "Please enter a valid coordinate" << endl;
                continue;
            }
        }
    }

    return board; 
}

bool check_inbound(int row, int col, int dim) {
    // can assume dim exists
    // check inbound
    if (row < 0 || row >= dim) {
        return false;
    } else if (col < 0 || col >= dim) {
        return false;
    }
    return true;
}

bool check_direction(const vector< vector<char> > board, int row, int col, int del_row, int del_col, char color, int dim, int &counter) {
    // keeping the counter to be used in num_flips in check_valid
    // move one step in the direction we want to check 

    int row_now = row + del_row;
    int col_now = col + del_col;

    // check if neighbor is of the same color

    if (check_inbound(row_now, col_now, dim)) {
        if (board[row_now][col_now] == color) {
            return false;
        }
    } else {
        return false;
    }

    // check if neighbor is opposite color
    // if so, continue to check if there is a same color down the line

    bool continue_check = false;
    if (color == 'W') {
        if (board[row_now][col_now] == 'B') {
            continue_check = true;
        }
    }

    if (color == 'B') {
        if (board[row_now][col_now] == 'W') {
            continue_check = true;
        }
    }

    if (continue_check) {
        // move to the coordinate after the neighbor
        row_now += del_row;
        col_now += del_col;

        // at least one move possible here
        counter = 1;

        while (check_inbound(row_now, col_now, dim)) {
            if (board[row_now][col_now] == 'U') {
                // if there is a blank in the direction, direction is invalid
                return false;
            } else if (board[row_now][col_now] == color) {
                // if there is piece of the same color, direction is valid
                return true;
            }

            counter++;
            row_now += del_row;
            col_now += del_col;
        }
    }

    return false;
}

bool check_valid(const vector< vector<char> > board, int row, int col, char color, int dim, vector<int> &num_flips) {

    if (!check_inbound(row, col, dim)) {
        return false;
    } 

    num_flips.clear();
    
    // order of running check: left, right
    // down, down+right, down+left
    // up, up+right, up+left

    // check whether the coordinate is already occupied

    if (board[row][col] != 'U') {
        return false;
    }
    
    vector<int> del_rows{0, 1, -1};
    vector<int> del_cols{0,1,-1};
    
    // initiate a variable that will record the amount of moves available on each direction 
    // to check all directions and not exit, need a value to store the validity 
    int counter;
    bool move_valid = false;

    for (int i = 0; i<del_rows.size(); i++) {
        for (int j = 0; j<del_cols.size(); j++) {
            // these two loops cover all the possible directions

            if (i == 0 && j == 0) {
                // this corresponds to the checker not moving, skip this
                continue;
            }
            int del_row = del_rows[i];
            int del_col = del_cols[j];

            if (check_direction(board, row, col, del_row, del_col, color, dim, counter)) {
                // check the direction
                num_flips.push_back(counter);
                move_valid = true;
            } else {
                num_flips.push_back(0);
            }
        } 
    }
    
    return move_valid; 
}

void valid_exist(const vector< vector<char> > board, int dim, vector<int> &B_valid, vector<int> &W_valid) {
    // print valid_moves for both W and B
    B_valid.clear();
    W_valid.clear();

    for (int row = 0; row < dim; row++) {
        for (int col = 0; col < dim; col++) {
            if (check_valid(board, row, col, 'B', dim, num_flips)) {
                B_valid.push_back(row);
                B_valid.push_back(col);
            }

            if (check_valid(board, row, col, 'W', dim, num_flips)) {
                W_valid.push_back(row);
                W_valid.push_back(col);
            }
        }
    }

    cout << "Available moves for O: " << endl;
    for (int i = 0; i < B_valid.size()/2; i++) {
        cout << alphabet[B_valid[2*i]] << alphabet[B_valid[2*i+1]] << endl;
    }

    cout << "Available moves for X: " << endl;
    for (int i = 0; i < W_valid.size()/2; i++) {
        cout << alphabet[W_valid[2*i]] << alphabet[W_valid[2*i+1]] << endl;
    }
}

bool check_endgame(const vector<int> B_valid, const vector<int> W_valid) {
    // assume B_valid and W_valid exist
    // that is, valid_exist was called prior to calling check_endgame
    // the game ends when both vectors are empty, aka no viable move for either player

    if (W_valid.size() == 0 && B_valid.size() == 0) {
        return true;
    }
    return false;
}

void place_piece(vector< vector<char> > &board, int row, int col, char color) {
    // can assume the move is valid
    board[row][col] = color; 
}

void flip_pieces(vector< vector<char> > &board, int row, int col, char color, vector<int> num_flips) {
    // assume that check valid is called and num_flips is ready for coordinate

    vector<int> del_rows{0,1,-1};
    vector<int> del_cols{0,1,-1};

    // iterate through the eight possible directions
    for (int i = 0; i < del_rows.size(); i++) {
        for (int j = 0; j < del_cols.size(); j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            
            // two new variables that are redeclared whenever the direction changes
            int row_now = row;
            int col_now = col; 

            // direction is a variable for converting the index of del_rows and del_cols
            // to one of the eight directions, which has its num_flip recorded in num_flips
            int direction = 3*i+j-1;

            // now move in desired direction, flipping a piece and move onto the next piece in direction
            // repeat num_flip times
            for (int num_flip = 0; num_flip < num_flips.at(direction); num_flip++) {
                row_now += del_rows.at(i);
                col_now += del_cols.at(j);
                board.at(row_now).at(col_now) = color;
            }
        } 
    }
}

void select_optimal(vector< vector<char> > board, int &row, int &col, int dim, vector<int> num_flips, char color = 'W') {

    // can assume there is at least one available move when this function is called

    int max_flip = 0;
    int max_row = 0;
    int max_col = 0;
    int current_flip = 0;

    for (int row_now = 0; row_now < dim; row_now++) {
        for (int col_now = 0; col_now < dim; col_now++) {
            if (check_valid(board, row_now, col_now, color, dim, num_flips)) {

                // for each valid coordinate, find the amount of flips it leads to 
                current_flip = sum_vector(num_flips);

                if (current_flip > max_flip) {
                    // record the best known position
                    max_flip = current_flip;
                    max_row = row_now;
                    max_col = col_now;
                }
            }
        }
    }

    row = max_row;
    col = max_col;
}