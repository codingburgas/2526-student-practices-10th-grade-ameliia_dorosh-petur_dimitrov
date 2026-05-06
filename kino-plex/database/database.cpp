#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QVariant>
#include <QCoreApplication>
#include <QDir>

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

    qDebug() << "initialize failed initialization of DB file";
    return false;
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

    qDebug() << "createUserTable failed to create table";
    return false;
    //I should actually implement a way of showing the error tbh #TODO - 1
}

QString Database::hashPassword(const QString& plainPass) const{
    //Australopithecus afarensis (I hashed the salt :))
    QByteArray saltHash = QCryptographicHash::hash("Australopithecus afarensis", QCryptographicHash::Sha256);
    QByteArray pass = saltHash + plainPass.toUtf8();
    QByteArray hashPass = QCryptographicHash::hash(pass, QCryptographicHash::Sha256);
    return QString(hashPass);
}

bool Database::registerUser(const QString& username, const QString& plainPass){
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    QSqlQuery sqlQuery(db);
    
    if (username.trimmed().isEmpty() || plainPass.size() <= 8){
        qDebug() << "Bad credentials";
        return false;
    }

    QString hashPass = hashPassword(plainPass);

    sqlQuery.prepare("INSERT INTO users (username, password) VALUES (:username, :pass)");
    sqlQuery.bindValue(":username", username.trimmed());
    sqlQuery.bindValue(":pass", hashPass);

    if (!sqlQuery.exec()){
        qDebug() << "registerUser: failed to insert user:" << sqlQuery.lastError().text();
        return false;
    }

    return true;
}

bool Database::validateLogin(const QString& username, const QString& plainPass){
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    QSqlQuery sqlQuery(db);

    QString hashPass = hashPassword(plainPass);

    QString user = username.trimmed();

    if (user.isEmpty() || plainPass.isEmpty() || plainPass.size() <= 8){
        qDebug() << "Invalid credentials";
        return false;
    }

    sqlQuery.prepare("SELECT password FROM users WHERE username = :placeholder LIMIT 1");
    sqlQuery.bindValue(":placeholder", user);

    if (!sqlQuery.exec()){
        qDebug() << "validateLogin: query hasnt executed properly";
        return false;
    }

    if (!sqlQuery.next()){
        qDebug() << "validateLogin: no such username registered";
        return false;
    }

    const QString storedHash = sqlQuery.value(0).toString();

    if (storedHash == hashPass){
        return true;
    }else{
        qDebug() << "Wrond password broski";
        return false;
    }

}

void Database::close(){
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    QSqlQuery sqlQuery(db);

    if (db.isOpen()){
        db.close();
        qDebug() << "Closed DB (WAS ACTIVE)";
    }else{
        qDebug() << "Closed DB (WAS NOT ACTIVE)";
    }

}
