#ifndef PERSONNE_H
#define PERSONNE_H
#include <cstddef>
#include <string>
#include"connection.h"
using namespace std;
class Personne {
protected:
    int idPersonne;
    string nom;
    Connection connection;


public:
    Personne();
    Personne(int id, string nom);
    int getIdPersonne();
    string getNom();
};

#endif // PERSONNE_H
