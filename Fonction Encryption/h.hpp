#include <stdlib.h>
#include <stdio.h>

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <vector>

using namespace std;

string Encrypt(string &msg,string &key);

void Cipher(vector<string> &blocs, vector<string> &key);
vector<vector<bitset<8>>> vstr_to_bitgrid( vector<string> &msg);
void shift_rows(vector<vector<bitset<8>>> &grid);
string grid_to_str( vector<vector<bitset<8>>> &grid);
int Blockify( string& msg, vector<string>& blocs);

void printBytes(vector<string> v_s);