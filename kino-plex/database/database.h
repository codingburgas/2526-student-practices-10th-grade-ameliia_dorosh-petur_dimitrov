#pragma once

#include <QWidget>

class Database : public QWidget
{
    Q_OBJECT
public:
    static Database& createInstance();
    bool initialize();
    bool createUsersTable();
    QString hashPassword(const QString& plainPass) const;
    bool registerUser(const QString& username, const QString& plainPass);
    bool validateLogin(const QString& username, const QString& plainPass);
    void close();

private:
    explicit Database(QWidget *parent = nullptr);
    ~Database();

signals:
};


