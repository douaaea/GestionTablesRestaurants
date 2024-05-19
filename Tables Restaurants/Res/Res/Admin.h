
#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "Personne.h"
#include "Login.h"
using namespace std;

class Admin : public Personne {
private:
    Login login;

public:
    Admin(int id, string nom, string username, string password);

    string getUsername() const;
    string getPassword() const;
};

#endif // ADMIN_H
