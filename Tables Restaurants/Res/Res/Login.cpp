#include "login.h"
Login::Login() : username(""), password("") {}
Login::Login(string username, string password) : username(username), password(password) {}

bool Login::authentifier(string inputUsername, string inputPassword) const {
    // Connect to the database
    Connection connection;
    connection.connect();

    // Execute SQL query to fetch password for the provided username
    SQLHSTMT stmt = connection.getStatement();
    SQLWCHAR query[255];
    swprintf(query, L"SELECT password FROM Login WHERE username = '%s'", inputUsername.c_str());
    SQLExecDirect(stmt, query, SQL_NTS);

    // Fetch password from the database
    string dbPassword;
    SQLCHAR password[255];
    SQLLEN passwordLength;
    if (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_CHAR, password, sizeof(password), &passwordLength);
        dbPassword = string(reinterpret_cast<char*>(password), passwordLength);
    }
    else {
        // Username does not exist in the database
        return false;
    }

    // Compare database password with provided password
    bool authenticated = (dbPassword == inputPassword);

    // Disconnect from the database
    connection.disconnect();

    return authenticated;
}

string Login::getUsername() const {
    return username;
}

string Login::getPassword() const {
    return password;
}
