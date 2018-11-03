//Legacy Libraries
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
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

//Fonction main réseau, de connexion et d'écoute sur un réseau
bool ListenTo(SOCKET& socket, const std::string& port);
bool connectTo(SOCKET& socket, const std::string& address, const std::string& port);
bool closeSocket(SOCKET& socket);

//Fonction d'envoi et de réception d'un message vers un socket précis
bool sendTo(SOCKET& socket, const std::string& inMessage);
int receiveFrom(SOCKET& socket, std::string& outMessage);

void handshake(string message, string portDest, string addrDest, string portSend);
string rhas(string port);
///////////////////////////////////

vector<int> dhk_kg(string mes);

///////////////////////////////////Fonctions chiffrement
//Fonction main chiffrement et déchiffrement du message
string encrypt(string msg,string key);
string decrypt( string msg, string key);

vector<vector<int>> lb_colshift(vector<vector<bitset<8>>> &grid, int sfactor);
bitset<8> gamul(bitset<8> a, bitset<8> b);
void cipher(vector<vector<bitset<8>>> &grid, vector<vector<bitset<8>>> &key);
void vstr_to_bitgrid(vector<string> &msg, vector<vector<bitset<8>>> &grid);
vector<vector<int>> generate_landing_points(vector<vector<bitset<8>>> &grid);
void extend_key_set(vector<vector<bitset<8>>> &grid, vector<vector<bitset<8>>> &key);
void col_sign(vector<bitset<8>> &set);

//Fonction d'affichage
void out_2dint(vector<vector<int>> &vec);
void out_grid(vector<vector<bitset<8>>> &grid);

void mix_columns(vector<vector<bitset<8>>> &grid);
void shift_rows(vector<vector<bitset<8>>> &grid, int sfactor = 1);
string grid_to_str( vector<vector<bitset<8>>> &grid);
void Blockify( string& msg, vector<string>& blocs);
void printBytes(vector<string> v_s);
///////////////////////////////////

////////////////////////////////Fonctions de hashage
//Fonction main hashcode
string hashage(string& msg);

//Xor function sur des matrices
void function_xor_hash(vector<vector<bitset<8>>> &grid, vector<bitset<8>> &hashCode);
void xor_between_2_hashcode(vector<bitset<8>> &hashCode,vector<bitset<8>> &hashCodeSeconde, vector<bitset<8>> &hashCodeFinal);

//Compare hashcode
bool compare_hashcode(string hashCodeRecu,string monHashCode);

//Affichage String hashcode
string hashcode_to_str( vector<bitset<8>> &hashCode);

//////////////////////////////////////

#endif // HEAD_H