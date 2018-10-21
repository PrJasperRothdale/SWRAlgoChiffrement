#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <string>
#include <vector>

using namespace std;

string Encrypt(string &msg,string &key);

//void Cipher(vector<string> &blocs, vector<string> &key);
int Blockify( string& msg, vector<string>& blocs);