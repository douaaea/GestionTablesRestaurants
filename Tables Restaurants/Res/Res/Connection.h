#ifndef CONNECTION_H
#define CONNECTION_H
#include <cstddef>
#include <sql.h>
#include <sqlext.h>

class Connection {
public:
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SQLRETURN retcode;

public:
    Connection();
    ~Connection();
    void connect();
    void disconnect();
    SQLHSTMT getStatement() const;
};

#endif // CONNECTION_H
