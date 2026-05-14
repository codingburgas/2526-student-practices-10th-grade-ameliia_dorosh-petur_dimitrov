#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>

class QLabel;

class QLineEdit;
class QPushButton;
class QLabel;
class QStackedWidget;

class LogAndRegisterPage : public QWidget
{
    Q_OBJECT

public:
    explicit LogAndRegisterPage(QWidget *parent = nullptr);
    ~LogAndRegisterPage();

<<<<<<< HEAD
signals:
    void loginRequested(const QString &username, const QString &password);
    void registerRequested(const QString &username, const QString &password);

private:
    void createTopBar();
    void createLoginPage();
    void createRegisterPage();

    // Top bar
    QPushButton *signInBtn;
    QPushButton *registerBtn;

    // Stacked pages
    QStackedWidget *stack;

    // Login widgets
    QLineEdit *loginUser;
    QLineEdit *loginPass;
    QPushButton *loginSubmit;
    QLabel *loginError;

    // Register widgets
    QLineEdit *regUser;
    QLineEdit *regPass;
    QLineEdit *regPassRepeat;
    QPushButton *regSubmit;
    QLabel *regError;
=======
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
>>>>>>> 5cb0458f0d06901e4cf4ee5770282626e17c14db
};
