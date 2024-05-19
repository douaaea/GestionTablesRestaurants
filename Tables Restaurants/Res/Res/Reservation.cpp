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
    // Connexion � la base de donn�es
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requ�te SQL pour r�cup�rer toutes les r�servations de la base de donn�es
    SQLWCHAR query[255];
    swprintf(query, L"SELECT * FROM Reservation");

    SQLExecDirect(stmt, query, SQL_NTS);

    // Boucle � travers le r�sultat et afficher les d�tails de chaque r�servation
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

        cout << "ID de r�servation : " << id << endl;
        cout << "Date : " << date << endl;
        cout << "Heure d'arriv�e : " << heureArr << endl;
        cout << "Heure de d�part : " << heureDep << endl;
        cout << "Nombre de personnes : " << nbrPersonne << endl;
        cout << "ID du client : " << idClient << endl;
        std::cout << "ID de la table : " << idTable << endl << endl;
    }

    // D�connexion de la base de donn�es
    connection.disconnect();
}
void Reservation::AfficherReservationParId(int idReservation) {
    // Connexion � la base de donn�es
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requ�te SQL pour r�cup�rer les d�tails de la r�servation par ID
    SQLWCHAR query[255];
    swprintf(query, L"SELECT * FROM Reservation WHERE idReservation = %d", idReservation);

    SQLExecDirect(stmt, query, SQL_NTS);

    // Variables pour stocker les d�tails de la r�servation
    SQLLEN id, dateLength, idClient, idTable;
    SQLFLOAT heureArr, heureDep;
    SQLINTEGER nbrPersonne;

    // R�cup�rer les d�tails de la r�servation
    if (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, sizeof(id), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, &date, sizeof(date), &dateLength);
        SQLGetData(stmt, 3, SQL_C_FLOAT, &heureArr, sizeof(heureArr), NULL);
        SQLGetData(stmt, 4, SQL_C_FLOAT, &heureDep, sizeof(heureDep), NULL);
        SQLGetData(stmt, 5, SQL_C_LONG, &nbrPersonne, sizeof(nbrPersonne), NULL);
        SQLGetData(stmt, 6, SQL_C_LONG, &idClient, sizeof(idClient), NULL);
        SQLGetData(stmt, 7, SQL_C_LONG, &idTable, sizeof(idTable), NULL);

        // Afficher les d�tails de la r�servation
        cout << "ID de r�servation : " << id << endl;
        cout << "Date : " << date << endl;
        cout << "Heure d'arriv�e : " << heureArr << endl;
        cout << "Heure de d�part : " << heureDep << endl;
        cout << "Nombre de personnes : " << nbrPersonne << endl;
        cout << "ID du client : " << idClient <<endl;
        cout << "ID de la table : " << idTable << endl;
    }
    else {
        cout << "Aucune r�servation trouv�e avec l'ID fourni." << endl;
    }

    // D�connexion de la base de donn�es
    connection.disconnect();
}
void Reservation::ajouterReservation() {
    // Inputs pour la r�servation
    string emailClient, dateReservation;
    float heureArrivee, heureDepart;
    int nbrPersonnes;

    // Saisie des inputs de l'utilisateur
    cout << "Entrez l'email du client : ";
    cin >> emailClient;
    cout << "Entrez la date de la r�servation (format YYYY-MM-DD) : ";
    cin >> dateReservation;
    cout << "Entrez l'heure d'arriv�e (format HH.MM) : ";
    cin >> heureArrivee;
    cout << "Entrez l'heure de d�part (format HH.MM) : ";
    cin >> heureDepart;
    cout << "Entrez le nombre de personnes : ";
    cin >> nbrPersonnes;

    // Obtenir l'ID du client � partir de l'email
    int idClient = Client::getIdClientByEmail(emailClient);

    if (idClient != -1) { // V�rifier si le client existe dans la base de donn�es
        // Connection � la base de donn�es
        Connection connection;
        connection.connect();

        SQLHSTMT stmt = connection.getStatement();

        // Requ�te SQL pour ajouter la r�servation � la base de donn�es
        SQLWCHAR query[1024];
        swprintf(query, L"INSERT INTO Reservation (date, heureArr, heureDep, nbrPersonne, idClient) VALUES ('%s', %f, %f, %d, %d)",
            dateReservation.c_str(), heureArrivee, heureDepart, nbrPersonnes, idClient);

        SQLExecDirect(stmt, query, SQL_NTS);

        cout << "R�servation ajout�e avec succ�s !" << endl;

        // D�connexion de la base de donn�es
        connection.disconnect();
    }
    else {
        cout << "Client non trouv� dans la base de donn�es. Veuillez v�rifier l'email." << endl;
    }
}
void Reservation::modifierReservation(int idReservation) {
    // Inputs pour la r�servation
    string dateReservation;
    float heureArrivee, heureDepart;
    int nbrPersonnes;

    // Saisie des nouvelles informations de la r�servation par l'utilisateur
    cout << "Entrez la nouvelle date de la r�servation (format YYYY-MM-DD) : ";
    cin >> dateReservation;
    cout << "Entrez la nouvelle heure d'arriv�e (format HH.MM) : ";
    cin >> heureArrivee;
    cout << "Entrez la nouvelle heure de d�part (format HH.MM) : ";
    cin >> heureDepart;
    cout << "Entrez le nouveau nombre de personnes : ";
    cin >> nbrPersonnes;

    // Connection � la base de donn�es
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requ�te SQL pour mettre � jour la r�servation dans la base de donn�es
    SQLWCHAR query[1024];
    swprintf(query, L"UPDATE Reservation SET date = '%s', heureArr = %f, heureDep = %f, nbrPersonne = %d WHERE idReservation = %d",
        dateReservation.c_str(), heureArrivee, heureDepart, nbrPersonnes, idReservation);

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "R�servation modifi�e avec succ�s !" << endl;

    // D�connexion de la base de donn�es
    connection.disconnect();
}
void Reservation::annulerReservation(int idReservation) {
    // Connexion � la base de donn�es
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // Requ�te SQL pour supprimer la r�servation de la base de donn�es
    SQLWCHAR query[255];
    swprintf(query, L"DELETE FROM Reservation WHERE idReservation = %d", idReservation);

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "R�servation annul�e avec succ�s !" << endl;

    // D�connexion de la base de donn�es
    connection.disconnect();
}
