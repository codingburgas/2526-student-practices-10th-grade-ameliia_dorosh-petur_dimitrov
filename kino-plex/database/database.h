#pragma once

#include <QObject>

class Database
{
public:
    static Database& createInstance();
    bool initialize();
    bool createUsersTable();
    bool registerUser(const QString& username, const QString& plainPass);
    bool validateLogin(const QString& username, const QString& plainPass);
    void close();

private:
    explicit Database();
    ~Database();
    QString hashPassword(const QString& plainPass) const;

protected:
    QString connectionName = "kino-plex-connection";

signals:
};


