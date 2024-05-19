
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include "connection.h"
using namespace std;
class Reservation {
private:
    int idReservation;
    string date;
    float heureArr;
    float heureDep;
    int nbrPersonne;
    int idClient;
    int idTable;
    Connection connection;

public:
    Reservation(int id, string date, float heureArr, float heureDep, int nbrPersonne, int idClient, int idTable);

    int getIdReservation() const;
    string getDate() const;
    float getHeureArr() const;
    float getHeureDep() const;
    int getNbrPersonne() const;
    int getIdClient() const;
    int getIdTable() const;

    static void ajouterReservation();
    static void modifierReservation(int idReservation);
    static void annulerReservation(int idReservation);
    static void AfficherReservation();
    static void AfficherReservationParId(int idReservation);
};

#endif // RESERVATION_H


