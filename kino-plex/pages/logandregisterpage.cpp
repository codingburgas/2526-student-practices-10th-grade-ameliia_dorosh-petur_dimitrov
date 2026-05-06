#include "logandregisterpage.h"

#include <QWidget>

#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "../database/database.h"

LogAndRegisterPage::LogAndRegisterPage(QWidget *parent) : QWidget(parent)
{
    setObjectName("logRegisterRoot");

    tabs = new QTabWidget(this);

    // Login
    QWidget *loginTab = new QWidget(this);
    QFormLayout *loginForm = new QFormLayout(loginTab);

    loginUsername = new QLineEdit(loginTab);
    loginUsername->setPlaceholderText("Username");
    loginUsername->setObjectName("input");

    loginPassword = new QLineEdit(loginTab);
    loginPassword->setPlaceholderText("Password");
    loginPassword->setEchoMode(QLineEdit::Password);
    loginPassword->setObjectName("input");

    loginButton = new QPushButton("Log In", loginTab);
    loginButton->setObjectName("primaryButton");

    loginForm->addRow("Username:", loginUsername);
    loginForm->addRow("Password:", loginPassword);
    loginForm->addRow(loginButton);

    // Register
    QWidget *registerTab = new QWidget(this);
    QFormLayout *regForm = new QFormLayout(registerTab);

    regUsername = new QLineEdit(registerTab);
    regUsername->setPlaceholderText("Choose a username");
    regUsername->setObjectName("input");

    regPassword = new QLineEdit(registerTab);
    regPassword->setPlaceholderText("Password (min 9 chars)");
    regPassword->setEchoMode(QLineEdit::Password);
    regPassword->setObjectName("input");

    regPasswordConfirm = new QLineEdit(registerTab);
    regPasswordConfirm->setPlaceholderText("Confirm password");
    regPasswordConfirm->setEchoMode(QLineEdit::Password);
    regPasswordConfirm->setObjectName("input");

    registerButton = new QPushButton("Register", registerTab);
    registerButton->setObjectName("primaryButton");

    regForm->addRow("Username:", regUsername);
    regForm->addRow("Password:", regPassword);
    regForm->addRow("Confirm:", regPasswordConfirm);
    regForm->addRow(registerButton);

    tabs->addTab(loginTab, "Login");
    tabs->addTab(registerTab, "Register");

    QVBoxLayout *root = new QVBoxLayout(this);
    QLabel *title = new QLabel("Welcome to Kino-Plex", this);
    title->setObjectName("pageTitle");
    title->setAlignment(Qt::AlignCenter);
    root->addWidget(title);
    root->addWidget(tabs, 1);

    // connections
    connect(loginButton, &QPushButton::clicked, this, &LogAndRegisterPage::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &LogAndRegisterPage::onRegisterClicked);
}

LogAndRegisterPage::~LogAndRegisterPage()
{
}

void LogAndRegisterPage::onLoginClicked()
{
    const QString user = loginUsername->text().trimmed();
    const QString pass = loginPassword->text();

    if (user.isEmpty() || pass.isEmpty())
    {
        QMessageBox::warning(this, "Login", "Please provide username and password.");
        return;
    }

    Database &db = Database::createInstance();
    bool ok = db.validateLogin(user, pass);

    if (ok)
    {
        QMessageBox::information(this, "Login", "Login successful!");
    }
    else
    {
        QMessageBox::critical(this, "Login", "Login failed: check credentials.");
    }
}

void LogAndRegisterPage::onRegisterClicked()
{
    const QString user = regUsername->text().trimmed();
    const QString pass = regPassword->text();
    const QString pass2 = regPasswordConfirm->text();

    if (user.isEmpty() || pass.isEmpty() || pass2.isEmpty())
    {
        QMessageBox::warning(this, "Register", "Please fill all fields.");
        return;
    }

    if (pass != pass2)
    {
        QMessageBox::warning(this, "Register", "Passwords do not match.");
        return;
    }

    Database &db = Database::createInstance();
    bool created = db.registerUser(user, pass);

    if (created)
    {
        QMessageBox::information(this, "Register", "Account created successfully. You can now log in.");
        tabs->setCurrentIndex(0);
    }
    else
    {
        QMessageBox::critical(this, "Register", "Failed to create account. Username may be taken or input invalid.");
    }
}
