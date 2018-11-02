#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

#include <string>

class Rsa
{
    public:
        Rsa();
        ~Rsa();
        void genererCles(unsigned int tailleCle);
        std::string clePrivee();
        void clePrivee(std::string cle);
        std::string clePublique();
        void clePublique(std::string cle);
        std::string chiffrerAvecClePrivee(std::string message);
        std::string dechiffrerAvecClePrivee(std::string message);
        std::string chiffrerAvecClePublique(std::string message);
        std::string dechiffrerAvecClePublique(std::string message);
        unsigned int tailleMaxChiffrable();
};

#endif // RSA_H_INCLUDED
