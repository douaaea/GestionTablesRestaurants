#include <iostream>
#include <cstdlib> 
#include "Admin.h"
#include "Client.h"
#include "Login.h"
#include "Restaurant.h"
#include "Reservation.h"
using namespace std;
int main() {
    int choix;

    cout << "Bienvenue !" << endl;

    // Demander à l'utilisateur de choisir entre Client et Administrateur
    cout << "Choisissez l'option : " << endl;
    cout << "1. Client" << endl;
    cout << "2. Administrateur" << endl;
    cout << "Votre choix : ";
    cin >> choix;

    // Si l'utilisateur est administrateur
    if (choix == 2) {
        // Authentification de l'administrateur
        Admin admin;
        Login login;
        Restaurant restaurant;
        Reservation reservation;
        if (login.authentifier()) {
            // Effacer la console
            system("cls");

            // Affichage du menu de l'administrateur
            cout << "Menu Administrateur :" << endl;
            cout << "1. Ajouter un restaurant" << endl;
            cout << "2. Supprimer un restaurant" << endl;
            cout << "3. Modifier un restaurant" << endl;
            cout << "4. Liste des restaurants" << endl;
            cout << "5. Modifier une réservation" << endl;
            cout << "6. Supprimer une réservation" << endl;
            cout << "7. Consulter les réservations" << endl;
            cout << "8. Consulter une réservation par ID" << endl;
            cout << "9. Consulter les statistiques" << endl;
            cout << "Votre choix : ";
            cin >> choix;

            // Traiter le choix de l'administrateur
           switch (choix) {
                // Ajouter un restaurant
            case 1:
                restaurant.AjouterRestaurant();
                break;
                // Supprimer un restaurant
            case 2:
                string nomRestaurant;
                cout << "entrer le nom du restaurant:" << endl;
                cin >> nomRestaurant;
                restaurant.SupprimerRestaurant(nomRestaurant);
                break;
                // Modifier un restaurant
            case 3:
                int idRestaurant;
                cout << "entrer l id du restaurant:" << endl;
                cin >> idRestaurant;
                restaurant.modifierRestaurant(idRestaurant);
                break;
                // Liste des restaurants
            case 4:
                restaurant.listRestaurants();
                break;
                // Modifier une réservation
            case 5:
                int idReservation;
                cout << "entrer l id du reservation:" << endl;
                cin >> idReservation;
                reservation.modifierReservation(idReservation);
                break;
                // Supprimer une réservation
            case 6:
                int idReservation;
                cout << "entrer l id du reservation:" << endl;
                cin >> idReservation;
                reservation.annulerReservation( idReservation);
                break;
                // Consulter les réservations
            case 7:
                reservation.AfficherReservation();
                break;
                // Consulter une réservation par ID
            case 8:
                int idReservation;
                cout << "entrer l id du reservation:" << endl;
                cin >> idReservation;
                reservation.AfficherReservationParId(idReservation);
                break;
            default:
                std::cout << "Choix invalide !" << std::endl;
                break;
            }
        }
        else {
            std::cout << "Echec de l'authentification." << std::endl;
        }
    }
    else if (choix == 1) { // Si l'utilisateur est client
        // Effacer la console
        system("cls");
        Reservation res;
        Restaurant rest;

        // Affichage du menu du client
        cout << "Menu Client :" << endl;
        cout << "1. Effectuer une réservation" << endl;
        cout << "2. Modifier une réservation" <<endl;
        cout << "3. Annuler une réservation" << endl;
        cout << "4. Chercher un restaurant par cuisine" << endl;
        cout << "5. Chercher un restaurant par lieu" << endl;
        cout << "6. Consulter la disponibilité" << endl;
        cout << "7. Liste des restaurants" << endl;
        cout << "Votre choix : ";
        cin >> choix;

        // Traiter le choix du client
        switch (choix) {
            
        case 1:
            res.ajouterReservation();
            break;
            // Modifier une réservation
        case 2:
            int idReservation;
            cout << "entrer l id du reservation:" << endl;
            cin >> idReservation;
            res.modifierReservation(idReservation);
            break;
            // Annuler une réservation
        case 3:
            int idReservation;
            cout << "entrer l id du reservation:" << endl;
            cin >> idReservation;
             res.annulerReservation(idReservation);
            break;
            // Chercher un restaurant par cuisine
        case 4:
            string cuisine;
            cout << "entrer la cuisine:" << endl;
            cin >> cuisine;
            rest.chercherRestaurantCuisine(cuisine);
            break;
            // Chercher un restaurant par lieu
        case 5:
            string lieu;
            cout << "entrer le lieu:" << endl;
            cin >> lieu;
            rest.chercherRestaurantLieu(lieu);
            break;
            // Consulter la disponibilité
        case 6:
           rest.disponibilite();
            break;
            // Liste des restaurants
        case 7:
            rest.listRestaurants();
            break;
        default:
            cout << "Choix invalide !" << endl;
            break;
        }
    }
    else {
        cout << "Choix invalide !" << endl;
    }

    return 0;
}
