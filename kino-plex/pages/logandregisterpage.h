#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>

class QLabel;

class LogAndRegisterPage : public QWidget
{
    Q_OBJECT

public:
    explicit LogAndRegisterPage(QWidget *parent = nullptr);
    ~LogAndRegisterPage();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    QTabWidget *tabs = nullptr;

    // Login widgets
    QLineEdit *loginUsername = nullptr;
    QLineEdit *loginPassword = nullptr;
    QPushButton *loginButton = nullptr;

    // Register widgets
    QLineEdit *regUsername = nullptr;
    QLineEdit *regPassword = nullptr;
    QLineEdit *regPasswordConfirm = nullptr;
    QPushButton *registerButton = nullptr;
};
