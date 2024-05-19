// Dans le fichier reservation.cpp

#include "Reservation.h"
#include <iostream>
#include "Client.h"

Reservation::Reservation(int id, string date, float heureArr, float heureDep, int nbrPersonne, int idClient, int idTable)
    : idReservation(id), date(date), heureArr(heureArr), heureDep(heureDep), nbrPersonne(nbrPersonne), idClient(idClient), idTable(idTable) {}

int Reservation::getIdReservation() const {
    return idReservation;
}

string Reservation::getDate() const {
    return date;
}

float Reservation::getHeureArr() const {
    return heureArr;
}

float Reservation::getHeureDep() const {
    return heureDep;
}

int Reservation::getNbrPersonne() const {
    return nbrPersonne;
}

int Reservation::getIdClient() const {
    return idClient;
}

int Reservation::getIdTable() const {
    return idTable;
}

void Reservation::AfficherReservation() {
    // Connexion à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requête SQL pour récupérer toutes les réservations de la base de données
    SQLWCHAR query[255];
    swprintf(query, L"SELECT * FROM Reservation");

    SQLExecDirect(stmt, query, SQL_NTS);

    // Boucle à travers le résultat et afficher les détails de chaque réservation
    SQLLEN id, dateLength, idClient, idTable;
    SQLFLOAT heureArr, heureDep;
    SQLINTEGER nbrPersonne;

    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, sizeof(id), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, &date, sizeof(date), &dateLength);
        SQLGetData(stmt, 3, SQL_C_FLOAT, &heureArr, sizeof(heureArr), NULL);
        SQLGetData(stmt, 4, SQL_C_FLOAT, &heureDep, sizeof(heureDep), NULL);
        SQLGetData(stmt, 5, SQL_C_LONG, &nbrPersonne, sizeof(nbrPersonne), NULL);
        SQLGetData(stmt, 6, SQL_C_LONG, &idClient, sizeof(idClient), NULL);
        SQLGetData(stmt, 7, SQL_C_LONG, &idTable, sizeof(idTable), NULL);

        cout << "ID de réservation : " << id << endl;
        cout << "Date : " << date << endl;
        cout << "Heure d'arrivée : " << heureArr << endl;
        cout << "Heure de départ : " << heureDep << endl;
        cout << "Nombre de personnes : " << nbrPersonne << endl;
        cout << "ID du client : " << idClient << endl;
        std::cout << "ID de la table : " << idTable << endl << endl;
    }

    // Déconnexion de la base de données
    connection.disconnect();
}
void Reservation::AfficherReservationParId(int idReservation) {
    // Connexion à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requête SQL pour récupérer les détails de la réservation par ID
    SQLWCHAR query[255];
    swprintf(query, L"SELECT * FROM Reservation WHERE idReservation = %d", idReservation);

    SQLExecDirect(stmt, query, SQL_NTS);

    // Variables pour stocker les détails de la réservation
    SQLLEN id, dateLength, idClient, idTable;
    SQLFLOAT heureArr, heureDep;
    SQLINTEGER nbrPersonne;

    // Récupérer les détails de la réservation
    if (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, sizeof(id), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, &date, sizeof(date), &dateLength);
        SQLGetData(stmt, 3, SQL_C_FLOAT, &heureArr, sizeof(heureArr), NULL);
        SQLGetData(stmt, 4, SQL_C_FLOAT, &heureDep, sizeof(heureDep), NULL);
        SQLGetData(stmt, 5, SQL_C_LONG, &nbrPersonne, sizeof(nbrPersonne), NULL);
        SQLGetData(stmt, 6, SQL_C_LONG, &idClient, sizeof(idClient), NULL);
        SQLGetData(stmt, 7, SQL_C_LONG, &idTable, sizeof(idTable), NULL);

        // Afficher les détails de la réservation
        cout << "ID de réservation : " << id << endl;
        cout << "Date : " << date << endl;
        cout << "Heure d'arrivée : " << heureArr << endl;
        cout << "Heure de départ : " << heureDep << endl;
        cout << "Nombre de personnes : " << nbrPersonne << endl;
        cout << "ID du client : " << idClient <<endl;
        cout << "ID de la table : " << idTable << endl;
    }
    else {
        cout << "Aucune réservation trouvée avec l'ID fourni." << endl;
    }

    // Déconnexion de la base de données
    connection.disconnect();
}
void Reservation::ajouterReservation() {
    // Inputs pour la réservation
    string emailClient, dateReservation;
    float heureArrivee, heureDepart;
    int nbrPersonnes;

    // Saisie des inputs de l'utilisateur
    cout << "Entrez l'email du client : ";
    cin >> emailClient;
    cout << "Entrez la date de la réservation (format YYYY-MM-DD) : ";
    cin >> dateReservation;
    cout << "Entrez l'heure d'arrivée (format HH.MM) : ";
    cin >> heureArrivee;
    cout << "Entrez l'heure de départ (format HH.MM) : ";
    cin >> heureDepart;
    cout << "Entrez le nombre de personnes : ";
    cin >> nbrPersonnes;

    // Obtenir l'ID du client à partir de l'email
    int idClient = Client::getIdClientByEmail(emailClient);

    if (idClient != -1) { // Vérifier si le client existe dans la base de données
        // Connection à la base de données
        Connection connection;
        connection.connect();

        SQLHSTMT stmt = connection.getStatement();

        // Requête SQL pour ajouter la réservation à la base de données
        SQLWCHAR query[1024];
        swprintf(query, L"INSERT INTO Reservation (date, heureArr, heureDep, nbrPersonne, idClient) VALUES ('%s', %f, %f, %d, %d)",
            dateReservation.c_str(), heureArrivee, heureDepart, nbrPersonnes, idClient);

        SQLExecDirect(stmt, query, SQL_NTS);

        cout << "Réservation ajoutée avec succès !" << endl;

        // Déconnexion de la base de données
        connection.disconnect();
    }
    else {
        cout << "Client non trouvé dans la base de données. Veuillez vérifier l'email." << endl;
    }
}
void Reservation::modifierReservation(int idReservation) {
    // Inputs pour la réservation
    string dateReservation;
    float heureArrivee, heureDepart;
    int nbrPersonnes;

    // Saisie des nouvelles informations de la réservation par l'utilisateur
    cout << "Entrez la nouvelle date de la réservation (format YYYY-MM-DD) : ";
    cin >> dateReservation;
    cout << "Entrez la nouvelle heure d'arrivée (format HH.MM) : ";
    cin >> heureArrivee;
    cout << "Entrez la nouvelle heure de départ (format HH.MM) : ";
    cin >> heureDepart;
    cout << "Entrez le nouveau nombre de personnes : ";
    cin >> nbrPersonnes;

    // Connection à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requête SQL pour mettre à jour la réservation dans la base de données
    SQLWCHAR query[1024];
    swprintf(query, L"UPDATE Reservation SET date = '%s', heureArr = %f, heureDep = %f, nbrPersonne = %d WHERE idReservation = %d",
        dateReservation.c_str(), heureArrivee, heureDepart, nbrPersonnes, idReservation);

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Réservation modifiée avec succès !" << endl;

    // Déconnexion de la base de données
    connection.disconnect();
}
void Reservation::annulerReservation(int idReservation) {
    // Connexion à la base de données
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requête SQL pour supprimer la réservation de la base de données
    SQLWCHAR query[255];
    swprintf(query, L"DELETE FROM Reservation WHERE idReservation = %d", idReservation);

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Réservation annulée avec succès !" << endl;

    // Déconnexion de la base de données
    connection.disconnect();
}
