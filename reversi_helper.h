
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int sum_vector(vector<int> nums);

vector< vector<char> > initialize_board(int &dim);

void print_board(const vector< vector<char> > board); 

bool convert_input(const string input, int &row, int &col);

bool check_inbound(int row, int col, int dim);

bool check_direction(const vector< vector<char> > board, int row, int col, int del_row, int del_col, char color, int dim);

bool check_valid(const vector< vector<char> > board, int row, int col, char color, int dim, vector<int> &num_flips);

void valid_exist(const vector< vector<char> > board, int dim, vector<int> &B_valid, vector<int> &W_valid);

void place_piece(vector< vector<char> > &board, int row, int col, char color);

void flip_pieces(vector< vector<char> > &board, int row, int col, char color, vector<int> num_flips);

bool check_endgame(const vector<int> B_valid, const vector<int> W_valid);

void declare_score(const vector< vector<char> > board, bool endgame = false);

void select_optimal(vector< vector<char> > board, int &row, int &col, int dim, vector<int> num_flips, char color = 'W');
