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
void cipher(vector<vector<bitset<8>>> &grid, vector<vector<bitset<8>>> &key);
void vstr_to_bitgrid(vector<string> &msg, vector<vector<bitset<8>>> &grid);
vector<vector<int>> generate_landing_points(vector<vector<bitset<8>>> &grid);
void extend_key_set(vector<vector<bitset<8>>> &grid, vector<vector<bitset<8>>> &key);
void row_sign(vector<bitset<8>> &set);
void out_2dint(vector<vector<int>> &vec);
void out_grid(vector<vector<bitset<8>>> &grid);
void mix_columns(vector<vector<bitset<8>>> &grid);
void shift_rows(vector<vector<bitset<8>>> &grid, int sfactor = 1);
string grid_to_str( vector<vector<bitset<8>>> &grid);
int Blockify( string& msg, vector<string>& blocs);
string hashage(string& msg);
void function_xor_hash(vector<vector<bitset<8>>> &grid, vector<bitset<8>> &hashCode);
void xor_between_2_hashcode(vector<bitset<8>> &hashCode,vector<bitset<8>> &hashCodeSeconde, vector<bitset<8>> &hashCodeFinal);
string hashcode_to_str( vector<bitset<8>> &hashCode);
bool compare_hashcode(string hashCodeRecu,string monHashCode);
void printBytes(vector<string> v_s);