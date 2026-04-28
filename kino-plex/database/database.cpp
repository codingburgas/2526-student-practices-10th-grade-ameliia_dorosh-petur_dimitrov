#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QVariant>
#include <QCoreApplication>
#include <QDir>


#include <iostream>


Database::Database(){
    initialize();
    createUsersTable();
}

Database::~Database(){}

Database& Database::createInstance(){
    static Database databaseInstance;
    return databaseInstance;
}

bool Database::initialize(){
    QDir(QCoreApplication::applicationDirPath()).mkdir("data");

    QString dbPath = QCoreApplication::applicationDirPath() + "/data/kino-plex.db";
    qInfo() << dbPath;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(dbPath);

    if (db.open()){
        return true;
    }
    qDebug() << "APP DIR:" << QCoreApplication::applicationDirPath();
    qDebug() << "DB PATH:" << dbPath;
    qDebug() << "FOLDER EXISTS?" << QDir(QCoreApplication::applicationDirPath() + "/data").exists();

    return false;
    // #TODO - 1
}

bool Database::createUsersTable(){
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    QSqlQuery sqlQuery(db);

    const QString table = "CREATE TABLE IF NOT EXISTS users("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "username TEXT NOT NULL UNIQUE,"
                          "password TEXT NOT NULL,"
                          "createdOn TEXT DEFAULT CURRENT_TIMESTAMP"
                          ");";

    if (sqlQuery.exec(table)){
        return true;
    }

    return false;
    //I should actually implement a way of showing the error tbh #TODO - 1
}

QString Database::hashPassword(const QString& plainPass) const{
    // return sha256 hex string
    return QString();
}

bool Database::registerUser(const QString& username, const QString& plainPass){
    // prepare INSERT query and bind values
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    QSqlQuery sqlQuery(db);

    return true;
}

bool Database::validateLogin(const QString& username, const QString& plainPass){
    // select stored hash and compare
    QSqlDatabase db = QSqlDatabase::database(connectionName);

    return false;
}

void Database::close(){
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    QSqlQuery sqlQuery(db);

    if (db.isOpen()){
        db.close();
        std::cout << "Closed DB (WAS ACTIVE)" << std::endl;
    }else{
        std::cout << "Closed DB (WAS NOT ACTIVE)" << std::endl;
    }

}
