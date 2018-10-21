#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>

#include <string>
#include <vector>

using namespace std;

string Encrypt(string &msg,string &key);

void Cipher(vector<string> &blocs, vector<string> &key);
void Bytify( vector<string> &msg);
int Blockify( string& msg, vector<string>& blocs);

void printBytes(vector<string> v_s);