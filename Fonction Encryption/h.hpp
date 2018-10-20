#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <string>
#include <vector>

using namespace std;

string Encrypt(char *inMessage,char *key);
void Blockify( string& msg, vector<string> blocs);