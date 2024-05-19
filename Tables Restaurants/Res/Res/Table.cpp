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

    // Connection à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requête SQL pour ajouter la table à la base de données
    SQLWCHAR query[255];
    swprintf(query, L"INSERT INTO Tbla (capacite, IdRestaurant) VALUES (%d, %d)", capacite, idRestaurant);

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Table ajoutée avec succès !" << endl;

    // Déconnexion de la base de données
    connection.disconnect();
}

void Table::SupprimerTable(string nomRestaurant) {
    // Connection à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();
    
    // Requête SQL pour supprimer la table de la base de données
    SQLWCHAR query[255];
    swprintf(query, L"DELETE FROM Tbla WHERE idRestaurant IN (SELECT idRestaurant FROM Restaurant WHERE nom = '%s')", 
        nomRestaurant.c_str());

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Table supprimée avec succès !" << endl;

    // Déconnexion de la base de données
    connection.disconnect();
}

void Table::ModifierTable(int idTable) {
    // Inputs pour les nouvelles informations de la table
    int nouvelleCapacite;

    // Saisie des nouvelles informations de la table par l'utilisateur
    cout << "Entrez la nouvelle capacite de la table : ";
    cin >> nouvelleCapacite;

    // Connection à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requête SQL pour modifier la capacité de la table dans la base de données
    SQLWCHAR query[255];
    swprintf(query, L"UPDATE Tbla SET capacite = %d WHERE idTbla = %d", nouvelleCapacite, idTable);

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Table modifiée avec succès !" << endl;

    // Déconnexion de la base de données
    connection.disconnect();
}

void Table::Disponibilite() {
    // Connection à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requête SQL pour récupérer les tables disponibles
    SQLWCHAR query[255];
    swprintf(query, L"SELECT idTbla, capacite FROM Tbla WHERE idTbla NOT IN (SELECT idTbla FROM Reservation)");

    SQLExecDirect(stmt, query, SQL_NTS);

    // Récupération des données
    SQLLEN idTable, capacite;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &idTable, sizeof(idTable), NULL);
        SQLGetData(stmt, 2, SQL_C_LONG, &capacite, sizeof(capacite), NULL);

        cout << "Table ID: " << idTable << ", Capacite: " << capacite << endl;
    }

    // Déconnexion de la base de données
    connection.disconnect();
}
