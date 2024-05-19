#include "Table.h"
#include <iostream>

Table::Table(int id, int capacite, int idRestaurant) : idTable(id), capacite(capacite), idRestaurant(idRestaurant) {}

int Table::getIdTable() const {
    return idTable;
}

int Table::getCapacite() const {
    return capacite;
}

int Table::getIdRestaurant() const {
    return idRestaurant;
}

void Table::AjouterTable() {
    // Inputs pour la nouvelle table
    int capacite;
    int idRestaurant;

    // Saisie des informations de la table par l'utilisateur
    cout << "Entrez la capacite de la nouvelle table : ";
    cin >> capacite;
    cout << "Entrez l'identifiant du restaurant auquel la table appartient : ";
    cin >> idRestaurant;

    // Connection � la base de donn�es
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requ�te SQL pour ajouter la table � la base de donn�es
    SQLWCHAR query[255];
    swprintf(query, L"INSERT INTO Tbla (capacite, IdRestaurant) VALUES (%d, %d)", capacite, idRestaurant);

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Table ajout�e avec succ�s !" << endl;

    // D�connexion de la base de donn�es
    connection.disconnect();
}

void Table::SupprimerTable(string nomRestaurant) {
    // Connection � la base de donn�es
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();
    
    // Requ�te SQL pour supprimer la table de la base de donn�es
    SQLWCHAR query[255];
    swprintf(query, L"DELETE FROM Tbla WHERE idRestaurant IN (SELECT idRestaurant FROM Restaurant WHERE nom = '%s')", 
        nomRestaurant.c_str());

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Table supprim�e avec succ�s !" << endl;

    // D�connexion de la base de donn�es
    connection.disconnect();
}

void Table::ModifierTable(int idTable) {
    // Inputs pour les nouvelles informations de la table
    int nouvelleCapacite;

    // Saisie des nouvelles informations de la table par l'utilisateur
    cout << "Entrez la nouvelle capacite de la table : ";
    cin >> nouvelleCapacite;

    // Connection � la base de donn�es
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requ�te SQL pour modifier la capacit� de la table dans la base de donn�es
    SQLWCHAR query[255];
    swprintf(query, L"UPDATE Tbla SET capacite = %d WHERE idTbla = %d", nouvelleCapacite, idTable);

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Table modifi�e avec succ�s !" << endl;

    // D�connexion de la base de donn�es
    connection.disconnect();
}

void Table::Disponibilite() {
    // Connection � la base de donn�es
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requ�te SQL pour r�cup�rer les tables disponibles
    SQLWCHAR query[255];
    swprintf(query, L"SELECT idTbla, capacite FROM Tbla WHERE idTbla NOT IN (SELECT idTbla FROM Reservation)");

    SQLExecDirect(stmt, query, SQL_NTS);

    // R�cup�ration des donn�es
    SQLLEN idTable, capacite;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &idTable, sizeof(idTable), NULL);
        SQLGetData(stmt, 2, SQL_C_LONG, &capacite, sizeof(capacite), NULL);

        cout << "Table ID: " << idTable << ", Capacite: " << capacite << endl;
    }

    // D�connexion de la base de donn�es
    connection.disconnect();
}
