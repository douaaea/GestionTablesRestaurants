#include "Admin.h"

Admin::Admin(int id, string nom,string username, string password) : Personne(id, nom), Login(username, password) {}

string Admin::getUsername() const {
    return login.getUsername();
}

string Admin::getPassword() const {
    return login.getPassword();
}
