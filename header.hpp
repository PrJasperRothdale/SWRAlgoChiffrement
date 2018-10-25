//Legacy Libraries
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

//C++11 Libraries
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


//Fonctions réseaux
bool InitialiseWinsock();
void CleanupWinsock();

bool ListenTo(SOCKET& socket, const string& port);
bool connectTo(SOCKET& socket, const string& address, const string& port);
bool closeSocket(SOCKET& socket);

bool sendTo(SOCKET& socket, const string& inMessage);
int receiveFrom(SOCKET& socket, string& outMessage);

void envoieA(string& adresse, string& port, string& message);
string recevoir(string port);

//Fonctions chiffrement
string Encrypt(string &msg,string &key);

void Cipher(vector<string> &blocs, vector<string> &key);
//bitset<8> gamul(bitset<8> a, bitset<8> b);
vector<vector<bitset<8>>> vstr_to_bitgrid( vector<string> &msg);
vector<vector<int>> generate_landing_points(vector<vector<bitset<8>>> &grid);
void out_2dint(vector<vector<int>> &vec);
void out_grid(vector<vector<bitset<8>>> &grid);
//void mix_columns(vector<vector<bitset<8>>> &grid);
void shift_rows(vector<vector<bitset<8>>> &grid, int sfactor = 1);
string grid_to_str( vector<vector<bitset<8>>> &grid);
int Blockify( string& msg, vector<string>& blocs);

void printBytes(vector<string> v_s);

#endif // HEAD_H