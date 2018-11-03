#include "header.hpp"

using namespace std;


int Agnes()
{
	srand(time(NULL));

	int k;

	//Chiffres employés pour Diffie-Hellman
	int a = rand() % 100 + 1; 
	int g = rand() % 20 + 1;
	int p = 9999;
	int A;

	string message;
	string rep;
	//Signature utilisé par le centre de certificats
	string clemsignature = "#@$-";
	//Clé pour l'encryption asymetrique
	string keyAB;

	SOCKET clementSocket = INVALID_SOCKET;
	SOCKET bernardSocket = INVALID_SOCKET;
	SOCKET listenSocket = INVALID_SOCKET;
	
	//Signature utilisé pour retrouver la hashcode
	string hashCodeSignature = "@øªÈóÄ@ãA®ñ.▀¾ã";
	//Calcul de A pour Diffie-Hellman(DH)
	A = 1;
	for (int i=0; i < a; i++){
		A = fmod((A * g), p);
	}
	//Formation du message puis envoi au centre de certificats(CC)
	message = to_string(A)+"<=>"+to_string(g)+"<=>"+to_string(p);
	handshake(message, CLEMENT_PORT, CLEMENT_ADRESS, AGNES_PORT);
	rep = rhas(AGNES_PORT);

	//Transmission a Bernard
	handshake(rep, BERNARD_PORT, BERNARD_ADRESS, AGNES_PORT);
	rep = rhas(AGNES_PORT);

	//Arret si le message n'est pas Certifié
	if (rep.substr((rep.size()-clemsignature.size()), rep.size()) == clemsignature){
		rep = rep.substr(0, (rep.size()-clemsignature.size()));
	} else {
		cout << endl << "A:Not signed by C" << endl;
		exit(1);
	}

	//Recupération du B (pour DH)
	int B = stoi(rep);

	//Calcul de la clé
	k = 1;
	for (int i=0; i<a; i++){
		k = fmod((k * B), p);
	}
	keyAB = to_string(int(k));

	//Recupération du message utilisateur
	char input[50000];
	cout << "Entrez votre message ici (au moins 16 caractères) : " << endl;
	cin.getline(input,sizeof(input));
	string m(input);

	//Chiffrement et envoi du message par la clé partagée
	string messageCopie = m;
	string hashCode = hashage(messageCopie);
	message = encrypt(m, keyAB);
	string messageSend = message + hashCodeSignature +  hashCode;
	handshake(messageSend, BERNARD_PORT, BERNARD_ADRESS, AGNES_PORT);

	return 0;
}

int Bernard()
{
	//Element privé de Bernard pour DH
	int b = rand() % 100 + 1;

	string message;
	string clemsignature = "#@$-";
	string rep;
	string keyAB;
	vector<int> vk;
	
	SOCKET listenSocket = INVALID_SOCKET;
	SOCKET clementSocket = INVALID_SOCKET;
	SOCKET agnesSocket = INVALID_SOCKET;


	string hashCodeSignature = "@øªÈóÄ@ãA®ñ.▀¾ã";
	//Attente de la première communication
	rep = rhas(BERNARD_PORT);
	//Arret si le message n'est pas certifié
	if (rep.substr((rep.size()-clemsignature.size()), rep.size()) == clemsignature){
		rep = rep.substr(0, (rep.size()-clemsignature.size()));
	} else {
		cout << endl << "B:Not signed by C" << endl;
		exit(1);
	}

	//Procédure de génération de clé de DH
	rep += "<=>"+to_string(b)+"<=>";
	vk = dhk_kg(rep);
	message = to_string(vk[0]);
	keyAB = to_string(vk[1]);

	//Signature par CC de l'element public de Bernard
	handshake(message, CLEMENT_PORT, CLEMENT_ADRESS, BERNARD_PORT);
	rep = rhas(BERNARD_PORT);

	//Reception du message chiffré par la clé partagée
	handshake(rep, AGNES_PORT, AGNES_ADRESS, BERNARD_PORT);
	rep = rhas(BERNARD_PORT);
	//Récupération du message chiffré et du hashcode
	int posMessage = rep.find(hashCodeSignature);
	int posHashCode = rep.find_last_of(hashCodeSignature);
	string message_rep = rep.substr(0,posMessage);
	string hashCodeReceive = rep.substr(posHashCode + 1, rep.size());
	//Déchiffrement et Affichage en Sortie
	message = decrypt(message_rep,keyAB);
	string messageCopie = message;
	string hashCodeReCreate = hashage(messageCopie);
	if(compare_hashcode(hashCodeReceive,hashCodeReCreate))
		cout << "Message integre";
	else
		cout << "Message non integre";
	cout << endl << "Message en sortie : " << message << endl;

	return 0;
}

int Clement(const int nbConnection)
{
	string message;
	string rep;
	string clemsignature = "#@$-";


	SOCKET listenSocket = INVALID_SOCKET;
	SOCKET agnesSocket = INVALID_SOCKET;
	SOCKET bernardSocket = INVALID_SOCKET;

	//Signature des messages reçus
	rep = rhas(CLEMENT_PORT);
	message = rep + clemsignature;
	handshake(message, AGNES_PORT, AGNES_ADRESS, CLEMENT_PORT);

	rep = rhas(CLEMENT_PORT);
	message = rep + clemsignature;
	handshake(message, BERNARD_PORT, BERNARD_ADRESS, CLEMENT_PORT);

	return 0;
}

//Fonction d'envoi des messages
void handshake(string message, string portDest, string addrDest, string portSend){

	SOCKET destSocket = INVALID_SOCKET;
	SOCKET sendSocket = INVALID_SOCKET;
	string response;

	if (connectTo(destSocket, addrDest, portDest)){
		sendTo(destSocket, message);
		closeSocket(destSocket);

	}

}

//Fonction d'attente de réception des messages
string rhas(string port){

	SOCKET originSocket = INVALID_SOCKET;
	SOCKET listenSocket = INVALID_SOCKET;
	string mes;

	if (ListenTo(listenSocket, port)){
		receiveFrom(listenSocket, mes);
		closeSocket(listenSocket);
	}

	return mes;
}

//Fonction de génération de la clé
vector<int> dhk_kg(string mes){

	string delimiter = "<=>";
	double k;
	int B;
	vector<int> vk;
	vector<string> vs;

	//Parsing des informations importantes
	size_t pos = 0;
	string token;
	while ((pos = mes.find(delimiter)) != string::npos) {
    	token = mes.substr(0, pos);
    	vs.push_back(token);
    	mes.erase(0, pos + delimiter.length());
	}

	int A = stoi(vs[0]);
	int g = stoi(vs[1]);
	int p = stoi(vs[2]);
	int b = stoi(vs[3]);

	//Calcul de l'element public de Bernard
	B = 1;
	for(int i=0; i<b; i++){
		B = fmod((B * g), p);
	}

	//Calcul de la clé partagée
	k = 1;
	for (int n=0; n<b; n++){
		k = fmod((k * A), p);
	}

	//Retour sous forme de tableau de données
	vk.push_back(B);
	vk.push_back(k);

	return vk;


}


////////////////////////////////////////TEST VALUES FOR DH 
/*

	p = 997
	g = 2

	a= 11
	b = 13

	DONNE :

	A = 54
	B = 216

	K = 113

*/