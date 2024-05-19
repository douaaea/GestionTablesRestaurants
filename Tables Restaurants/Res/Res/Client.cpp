#include "Client.h"


Client::Client(int id, string nom, string email) : Personne(id, nom), email(email) {}

string Client::getEmail() const {
    return email;
}

void Client::setEmail(string email) {
    this->email = email;
}

int Client::getIdClientByEmail(string email) {
    // Connexion à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requête SQL pour obtenir l'ID du client à partir de l'email
    SQLWCHAR query[255];
    swprintf(query, L"SELECT idClient FROM Client WHERE email = '%s'", email.c_str());

    SQLExecDirect(stmt, query, SQL_NTS);

    // Variable pour stocker l'ID du client
    SQLLEN idClient;

    // Récupérer l'ID du client s'il existe
    if (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &idClient, sizeof(idClient), NULL);
    }
    else {
        idClient = -1; // Retourner -1 si le client n'est pas trouvé
    }

    // Déconnexion de la base de données
    connection.disconnect();

    return idClient;
}

