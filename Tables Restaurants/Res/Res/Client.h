
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "Personne.h"
using namespace std;
class Client : public Personne {
private:
    string email;

public:
    Client(int id, string nom, string email);

    string getEmail() const;
    void setEmail(string email);

    static int getIdClientByEmail(string email); // M�thode statique pour obtenir l'ID du client � partir de l'email
};

#endif // CLIENT_H
