#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QVariant>
#include <QCoreApplication>

Database::Database(QWidget *parent)
    : QWidget{parent}
{}

Database::~Database(){}

Database& Database::createInstance(){
    static Database databaseInstance;
    return databaseInstance;
}

bool Database::initialize(){
    // open DB file and set filepath
    return true;
}

bool Database::createUsersTable(){
    // CREATE TABLE IF NOT EXISTS users (...)
    return true;
}

QString Database::hashPassword(const QString& plainPass) const{
    // return sha256 hex string
    return QString();
}

bool Database::registerUser(const QString& username, const QString& plainPass){
    // prepare INSERT query and bind values
    return true;
}

bool Database::validateLogin(const QString& username, const QString& plainPass){
    // select stored hash and compare
    return false;
}

void Database::close(){
    // close connection if open
}
