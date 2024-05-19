#include "restaurant.h"
#include <iostream>

Restaurant::Restaurant(int id, string nom, string adresse, string cuisine)
    : idRestaurant(id), nom(nom), adresse(adresse), cuisine(cuisine) {}

int Restaurant::getIdRestaurant() const {
    return idRestaurant;
}

string Restaurant::getNom() const {
    return nom;
}

string Restaurant::getAdresse() const {
    return adresse;
}

string Restaurant::getCuisine() const {
    return cuisine;
}

void Restaurant::listRestaurants() {
    // Connection to the database
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // SQL query pour afficher les restaurants
    SQLWCHAR query[255];
    swprintf(query, L"SELECT * FROM Restaurant");

    SQLExecDirect(stmt, query, SQL_NTS);

    // Loop through the result set and display restaurant information
    SQLLEN id, nameLength, addressLength, cuisineLength;
    SQLWCHAR name[255], address[255], cuisine[255];

    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, sizeof(id), NULL);
        SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), &nameLength);
        SQLGetData(stmt, 3, SQL_C_WCHAR, address, sizeof(address), &addressLength);
        SQLGetData(stmt, 4, SQL_C_WCHAR, cuisine, sizeof(cuisine), &cuisineLength);

        cout << "Restaurant ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Cuisine: " << cuisine << endl << endl;
    }

    // Disconnect from the database
    connection.disconnect();
}

void Restaurant::AjouterRestaurant() {
    // Input restaurant details from console
    string nom, adresse, cuisine;
    cout << "Nom du restaurant: ";
    getline(cin, nom);
    cout << "Adresse du restaurant: ";
    getline(cin, adresse);
    cout << "Cuisine du restaurant: ";
    getline(cin, cuisine);

    // Connection to the database
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // SQL query to add restaurant to the database
    SQLWCHAR query[1024];
    swprintf(query, L"INSERT INTO Restaurant (nom, adresse, cuisine) VALUES ('%s', '%s', '%s')",
        nom.c_str(), adresse.c_str(), cuisine.c_str());

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Restaurant ajouté avec succès !" << endl;

    // Disconnect from the database
    connection.disconnect();
}

void Restaurant::SupprimerRestaurant(const string& nomRestaurant) {
    // Connection a la database
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // SQL query pour supprimer une restaurant
    SQLWCHAR query[1024];
    swprintf(query, L"DELETE FROM Restaurant WHERE nom = '%s'", nomRestaurant.c_str());

    SQLExecDirect(stmt, query, SQL_NTS);

    cout << "Restaurant supprimé avec succès !" << endl;

    // Disconnect from the database
    connection.disconnect();
}

void Restaurant::modifierRestaurant(int idRestaurant) {
    // Connection to the database
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // SQL querypour afficher les details d une restaurant
    SQLWCHAR query[255];
    swprintf(query, L"SELECT * FROM Restaurant WHERE idRestaurant = %d", idRestaurant);

    SQLExecDirect(stmt, query, SQL_NTS);

    // Fetch and display current restaurant details
    SQLLEN id, nameLength, addressLength, cuisineLength;
    SQLWCHAR name[255], address[255], cuisine[255];

    if (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, sizeof(id), NULL);
        SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), &nameLength);
        SQLGetData(stmt, 3, SQL_C_WCHAR, address, sizeof(address), &addressLength);
        SQLGetData(stmt, 4, SQL_C_WCHAR, cuisine, sizeof(cuisine), &cuisineLength);

        cout << "Nom actuel du restaurant: " << name << endl;
        cout << "Adresse actuelle du restaurant: " << address << endl;
        cout << "Cuisine actuelle du restaurant: " << cuisine << endl << endl;

        // Input new restaurant details from console
        string nouveauNom, nouvelleAdresse, nouvelleCuisine;
        cout << "Nouveau nom du restaurant: ";
        getline(cin, nouveauNom);
        cout << "Nouvelle adresse du restaurant: ";
        getline(cin, nouvelleAdresse);
        cout << "Nouvelle cuisine du restaurant: ";
        getline(cin, nouvelleCuisine);

        // SQL query to update restaurant details in the database
        SQLWCHAR updateQuery[1024];
        swprintf(updateQuery, L"UPDATE Restaurant SET nom = '%s', adresse = '%s', cuisine = '%s' WHERE idRestaurant = %d", 
            nouveauNom.c_str(), nouvelleAdresse.c_str(), nouvelleCuisine.c_str(), idRestaurant);

        SQLExecDirect(stmt, updateQuery, SQL_NTS);

        cout << "Restaurant modifié avec succès !" << endl;
    }
    else {
        cout << "Aucun restaurant trouvé avec l'ID fourni." << endl;
    }

    // Disconnect from the database
    connection.disconnect();
}

void Restaurant::chercherRestaurantCuisine(const string& cuisine) {
    // Connection to the database
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // SQL query pour afficher les restaurants du meme cuisine
    SQLWCHAR query[255];
    swprintf(query, L"SELECT * FROM Restaurant WHERE cuisine = '%s'", cuisine.c_str());

    SQLExecDirect(stmt, query, SQL_NTS);

    // Loop through the result set and display restaurant information
    SQLLEN id, nameLength, addressLength, cuisineLength;
    SQLWCHAR name[255], address[255], cuisineResult[255];

    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, sizeof(id), NULL);
        SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), &nameLength);
        SQLGetData(stmt, 3, SQL_C_WCHAR, address, sizeof(address), &addressLength);
        SQLGetData(stmt, 4, SQL_C_WCHAR, cuisineResult, sizeof(cuisineResult), &cuisineLength);

        wcout << L"Restaurant ID: " << id << endl;
        wcout << L"Name: " << name << endl;
        wcout << L"Address: " << address << endl;
        wcout << L"Cuisine: " << cuisineResult << endl << endl;
    }

    // Disconnect from the database
    connection.disconnect();
}

void Restaurant::chercherRestaurantLieu(const string& adresse) {
    // Connection to the database
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // SQL query pour afficher les restaurants du meme lieu
    SQLWCHAR query[255];
    swprintf(query, L"SELECT * FROM Restaurant WHERE adresse = '%s'", adresse.c_str());

    SQLExecDirect(stmt, query, SQL_NTS);

    // Loop through the result set and display restaurant information
    SQLLEN id, nameLength, addressLength, cuisineLength;
    SQLWCHAR name[255], addressResult[255], cuisine[255];

    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, sizeof(id), NULL);
        SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), &nameLength);
        SQLGetData(stmt, 3, SQL_C_WCHAR, addressResult, sizeof(addressResult), &addressLength);
        SQLGetData(stmt, 4, SQL_C_WCHAR, cuisine, sizeof(cuisine), &cuisineLength);

       wcout << L"Restaurant ID: " << id << endl;
        wcout << L"Name: " << name << endl;
        wcout << L"Address: " << addressResult << endl;
        wcout << L"Cuisine: " << cuisine << endl << endl;
    }

    // Disconnect from the database
    connection.disconnect();
}

void Restaurant::disponibilite() {
    // Connection to the database
    Connection connection;
    connection.connect();

    SQLHSTMT stmt = connection.getStatement();

    // SQL query pour afficher les restaurants qui ont des tables qui ne sont pas rservee
       SQLWCHAR query[1024];
    swprintf(query, L"SELECT DISTINCT R.* FROM Restaurant R JOIN Tbla T ON R.ID = T.idRestaurantLEFT JOIN Reservation RV ON T.idRestaurant = RV.idTbla WHERE RV.idTbla IS NULL OR (RV.heureArr IS NOT NULL AND RV.heureDep IS NOT NULL)");

    SQLExecDirect(stmt, query, SQL_NTS);

    // Loop through the result set and display restaurant information
    SQLLEN id, nameLength, addressLength, cuisineLength;
    SQLWCHAR name[255], address[255], cuisine[255];

    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, sizeof(id), NULL);
        SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), &nameLength);
        SQLGetData(stmt, 3, SQL_C_WCHAR, address, sizeof(address), &addressLength);
        SQLGetData(stmt, 4, SQL_C_WCHAR, cuisine, sizeof(cuisine), &cuisineLength);

        wcout << L"Restaurant ID: " << id << endl;
        wcout << L"Name: " << name << endl;
        wcout << L"Address: " << address << endl;
        wcout << L"Cuisine: " << cuisine << endl << endl;
    }

    // Disconnect from the database
    connection.disconnect();
}

