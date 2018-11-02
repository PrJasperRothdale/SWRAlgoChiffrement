//C++ program for encryption and decryption
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctime>
#include<base64.h>

using namespace std;

long p, q, n, t, i, flag, e, d;
string msg;

int prime(long int); //function to check for prime number
void encrypt();
void decrypt();
long test(long min, long max);
int lcm(long a, long b);
int gcd(long a, long b);

int main()
{
   	p =test(pow(10,32),pow(10,33));

	q =test(2,1000);

   cout << "\nENTER MESSAGE OR STRING TO ENCRYPT\n";
   cin >> msg;

   totient = lcm((p-1),(q-1));

   n = q*p;

   e = totient -1 ;

   do
   {
   		e--;
   }while(gcd(e, totient) != 1)
   

   d = (1%totient)/e;


   return 0;
} //end of the main program

int prime(long int pr)
{
   int i;
   j = sqrt(pr);
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
	string msg64 = base64_encode(msg, msg.size());
	long msgInt = stol(msg64);
	msgInt = pow(msgInt,e)%n;
	msg = base64_decode(msg);
	return msg;
}

//function to decrypt the message
string decrypt(long d, string msg, long n)
{
   string msg64 = base64_encode(msg, msg.size);
   long msgInt = stol(msg64);
   msgInt = pow(c,d)%n;
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