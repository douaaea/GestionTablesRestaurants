#include <cstddef>

#include "Connection.h"

Connection::Connection() {
    henv = SQL_NULL_HENV;
    hdbc = SQL_NULL_HDBC;
    hstmt = SQL_NULL_HSTMT;
    retcode = SQL_SUCCESS;
}

Connection::~Connection() {
    disconnect();
}

void Connection::connect() {
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    SQLWCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    SQLDriverConnect(hdbc, NULL, (SQLWCHAR*)"DRIVER={SQL Server};SERVER=DESKTOP-G5SLSAV\\SQLEXPRESS;DATABASE=ResDB;UID=DESKTOP-G5SLSAV\\Douaa;PWD=", 
        SQL_NTS, outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_NOPROMPT);
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
}

void Connection::disconnect() {
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

SQLHSTMT Connection::getStatement() const {
    return hstmt;
}
