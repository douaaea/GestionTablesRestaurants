#include "Personne.h"

Personne::Personne() {
    idPersonne = 0;
    nom = "";
}

Personne::Personne(int id, string nom) : idPersonne(id), nom(nom) {}

int Personne::getIdPersonne() {
    return idPersonne;
}

string Personne::getNom() {
    return nom;
}

