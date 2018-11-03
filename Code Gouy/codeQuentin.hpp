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

string Hashage(string& msg);
void fctXOR_Hash(vector<vector<bitset<8>>> &grid, vector<bitset<8>> &hashCode);
void Xor2HashCode(vector<bitset<8>> &hashCode,vector<bitset<8>> &hashCodeSeconde, vector<bitset<8>> &hashCodeFinal);
string hashCode_to_str( vector<bitset<8>> &hashCode);
bool CompareHashcode(vector<bitset<8>> &hashCodeRecu,vector<bitset<8>> &monHashCode);
void FormatSendHashCode(vector<bitset<8>> &hashCodeFinal);