#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <string>
#include <vector>

using namespace std;

string Encrypt(string &inMessage,string &key);
void Blockify( string& msg, vector<string> blocs);