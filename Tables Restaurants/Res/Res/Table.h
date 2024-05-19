#ifndef TABLE_H
#define TABLE_H

#include <string>
#include "connection.h"
using namespace std;
class Table {
private:
    int idTable;
    int capacite;
    int idRestaurant; // Référence vers le restaurant auquel cette table appartient
    Connection connection;

public:
    Table(int id, int capacite, int idRestaurant);

    int getIdTable() const;
    int getCapacite() const;
    int getIdRestaurant() const;

    static void AjouterTable();
    static void SupprimerTable(string nomRestaurant);
    static void ModifierTable(int idTable);
    static void Disponibilite();
};

#endif // TABLE_H
