//Legacy Libraries
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>

//C++11 Libraries
//#include <algorithm>
#include <thread>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>


/////////////////////////////////////////// Constantes
#define DEFAULT_BUFLEN 1024


#define BERNARD_PORT "27015"
#define BERNARD_ADRESS "127.0.0.1"

#define CLEMENT_PORT "27016"
#define CLEMENT_ADRESS "127.0.0.1"

#define AGNES_PORT "27017"
#define AGNES_ADRESS "127.0.0.1"
/////////////////////////////////////////////////////

#ifndef HEAD_H
#define HEAD_H


using namespace std;


///////////////////////////////////Autres

int Clement(const int nbConnection);
int Agnes();
int Bernard();

///////////////////////////////////


///////////////////////////////////Fonctions réseaux
bool InitialiseWinsock();
void CleanupWinsock();

bool ListenTo(SOCKET& socket, const std::string& port);
bool connectTo(SOCKET& socket, const std::string& address, const std::string& port);
bool closeSocket(SOCKET& socket);

bool sendTo(SOCKET& socket, const std::string& inMessage);
int receiveFrom(SOCKET& socket, std::string& outMessage);
///////////////////////////////////


///////////////////////////////////Fonctions chiffrement
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
void printBytes(vector<string> v_s);
///////////////////////////////////

#endif // HEAD_H