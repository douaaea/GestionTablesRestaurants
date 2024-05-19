#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include "connection.h"
using namespace std;
class Restaurant {
private:
    int idRestaurant;
    string nom;
    string adresse;
    string cuisine;
    Connection connection;

public:
    Restaurant(int id, string nom, string adresse, string cuisine);

    int getIdRestaurant() const;
    string getNom() const;
    string getAdresse() const;
    string getCuisine() const;

    static void listRestaurants();
    static void AjouterRestaurant();
    static void SupprimerRestaurant(const string& nomRestaurant);
    static void modifierRestaurant(int idRestaurant);
    static void chercherRestaurantCuisine(const string& cuisine);
    static void chercherRestaurantLieu(const string& adresse);
    static void disponibilite();
};

#endif // RESTAURANT_H

