#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <vector>

using namespace std;

string Encrypt(string &msg,string &key);

void Cipher(vector<string> &blocs, vector<string> &key);
vector<vector<int>> lb_colshift(vector<vector<bitset<8>>> &grid, int sfactor);
bitset<8> gamul(bitset<8> a, bitset<8> b);
vector<vector<bitset<8>>> vstr_to_bitgrid( vector<string> &msg);
vector<vector<int>> generate_landing_points(vector<vector<bitset<8>>> &grid);
void row_sign(vector<bitset<8>> &set);
void out_2dint(vector<vector<int>> &vec);
void out_grid(vector<vector<bitset<8>>> &grid);
void mix_columns(vector<vector<bitset<8>>> &grid);
void shift_rows(vector<vector<bitset<8>>> &grid, int sfactor = 1);
string grid_to_str( vector<vector<bitset<8>>> &grid);
int Blockify( string& msg, vector<string>& blocs);

void printBytes(vector<string> v_s);