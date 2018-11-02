//C++ program for encryption and decryption
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctime>

#include"base64.h"

using namespace std;

int prime(long pr); // on regarde si est premier
string encrypt(long e, string msg, long n);
string decrypt(long d, string msg, long n);
long rpng(long min, long max);//random prime number generation
int lcm(long a, long b);
long gcd(long a, long b);
void genKey(long &e, long &d, long &n);

int main()
{
	long  e, d, n;
	string message;

	genKey(e,d,n);

	message = "test";

	string encMes = encrypt(e, message, n);

	cout << encMes << endl;

	string decMes = decrypt(d, encMes, n);

	cout << decMes << endl;

	cin >> message;
}

void genKey(long &e, long &d, long &n)
{
	long p =rpng(pow(10,32),pow(10,33));

	long q =rpng(2,1000);


	n = p*q;
	long totient = lcm((p-1),(q-1));

	e = totient-1;

	do{
		e--;
	}while(gcd(e, totient) != 1);

	d = (1%totient)/e;
}
int prime(long pr)
{
   int i;
   long j = sqrt(pr);
   for(i = 2; i <= j; i++)
   {
      if(pr % i == 0)
         return 0;
   }
   return 1;
}

long gcd(long a, long b)
{
	if (a == 0 || b == 0)  
        return 0;  
   
    // Base case     
    if (a == b)  
        return a;  
   
    // a is greater  
    if (a > b)  
        return gcd(a-b, b);  
    return gcd(a, b-a);
}

int lcm(long a, long b)  
 {  
    return (a*b)/gcd(a, b);  
 }  

//function to encrypt the message
string encrypt(long e, string msg, long n)
{
	unsigned char* msgChar = (unsigned char*)msg.c_str();

	string msg64 = base64_encode(msgChar, msg.size());
	long msgInt = stol(msg64);
	msgInt =(long) pow(msgInt,e)%n;
	msg = base64_decode(msg);
	return msg;
}

//function to decrypt the message
string decrypt(long d, string msg, long n)
{
	unsigned char* msgChar = (unsigned char*)msg.c_str();

	string msg64 = base64_encode(msgChar, msg.size());

   long msgInt = stol(msg64);
   msgInt = (long) pow(msgInt,d)%n;
   msg = base64_decode(msg);
   return msg;
}

long rpng(long min, long max)
{
	srand(time(NULL));
	long rdnum = 0;


	do
	{
		rdnum = min + (rand()%(int)(max - min + 1));
	}while(prime(rdnum) == 0);

	return rdnum;
}