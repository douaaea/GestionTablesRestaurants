#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include "connection.h"
using namespace std;
class Login {
private:
    string username;
    string password;

public:
    Login();
    Login(string username, string password);

    bool authentifier(string inputUsername, string inputPassword) const;

    string getUsername() const;
    string getPassword() const;
};

#endif // LOGIN_H
