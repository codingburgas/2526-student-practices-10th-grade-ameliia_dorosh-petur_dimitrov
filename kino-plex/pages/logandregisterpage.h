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
};
