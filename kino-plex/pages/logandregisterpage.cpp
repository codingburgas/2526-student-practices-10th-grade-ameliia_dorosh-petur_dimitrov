#include "logandregisterpage.h"

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

LogAndRegisterPage::LogAndRegisterPage(QWidget *parent)
	: QWidget(parent),
      signInBtn(nullptr), registerBtn(nullptr), stack(nullptr),
      loginUser(nullptr), loginPass(nullptr), loginSubmit(nullptr), loginError(nullptr),
      regUser(nullptr), regPass(nullptr), regPassRepeat(nullptr), regSubmit(nullptr), regError(nullptr)
{
	createTopBar();
	createLoginPage();
	createRegisterPage();

	QVBoxLayout *root = new QVBoxLayout(this);
	QHBoxLayout *topBar = new QHBoxLayout;
    topBar->addWidget(signInBtn);
    topBar->addWidget(registerBtn);
	topBar->addStretch();

	root->addLayout(topBar);

    stack = new QStackedWidget(this);
    root->addWidget(stack, 1);

	setLayout(root);

	// default to sign in
    stack->setCurrentIndex(0);
}

LogAndRegisterPage::~LogAndRegisterPage()
{
}

void LogAndRegisterPage::createTopBar()
{
    signInBtn = new QPushButton(tr("Sign In"), this);
    registerBtn = new QPushButton(tr("Register"), this);

    signInBtn->setObjectName("navButton");
    registerBtn->setObjectName("navButton");

    connect(signInBtn, &QPushButton::clicked, this, [this]() {
        if (stack) stack->setCurrentIndex(0);
	});

    connect(registerBtn, &QPushButton::clicked, this, [this]() {
        if (stack) stack->setCurrentIndex(1);
	});
}

void LogAndRegisterPage::createLoginPage()
{
	QWidget *page = new QWidget(this);
	QVBoxLayout *v = new QVBoxLayout(page);

    loginError = new QLabel(page);
    loginError->setStyleSheet("color: #e11b22");
    loginError->setWordWrap(true);
    v->addWidget(loginError);

	QFormLayout *form = new QFormLayout;
    loginUser = new QLineEdit(page);
    loginUser->setPlaceholderText(tr("Username"));
    loginPass = new QLineEdit(page);
    loginPass->setPlaceholderText(tr("Password"));
    loginPass->setEchoMode(QLineEdit::Password);
    form->addRow(tr("Username"), loginUser);
    form->addRow(tr("Password"), loginPass);
	v->addLayout(form);

    loginSubmit = new QPushButton(tr("Sign In"), page);
    v->addWidget(loginSubmit);

    connect(loginSubmit, &QPushButton::clicked, this, [this]() {
        loginError->clear();
        const QString user = loginUser->text().trimmed();
        const QString pass = loginPass->text();
		if (user.isEmpty() || pass.isEmpty()) {
            loginError->setText(tr("Please enter username and password."));
			return;
		}
		emit loginRequested(user, pass);
	});

    stack->addWidget(page);
}

void LogAndRegisterPage::createRegisterPage()
{
	QWidget *page = new QWidget(this);
	QVBoxLayout *v = new QVBoxLayout(page);

    regError = new QLabel(page);
    regError->setStyleSheet("color: #e11b22");
    regError->setWordWrap(true);
    v->addWidget(regError);

	QFormLayout *form = new QFormLayout;
    regUser = new QLineEdit(page);
    regUser->setPlaceholderText(tr("Username"));
    regPass = new QLineEdit(page);
    regPass->setPlaceholderText(tr("Password"));
    regPass->setEchoMode(QLineEdit::Password);
    regPassRepeat = new QLineEdit(page);
    regPassRepeat->setPlaceholderText(tr("Repeat Password"));
    regPassRepeat->setEchoMode(QLineEdit::Password);

    form->addRow(tr("Username"), regUser);
    form->addRow(tr("Password"), regPass);
    form->addRow(tr("Repeat"), regPassRepeat);
	v->addLayout(form);

    regSubmit = new QPushButton(tr("Create Account"), page);
    v->addWidget(regSubmit);

    connect(regSubmit, &QPushButton::clicked, this, [this]() {
        regError->clear();
        const QString user = regUser->text().trimmed();
        const QString pass = regPass->text();
        const QString pass2 = regPassRepeat->text();
		if (user.isEmpty() || pass.isEmpty() || pass2.isEmpty()) {
            regError->setText(tr("All fields are required."));
			return;
		}
		if (pass != pass2) {
            regError->setText(tr("Passwords do not match."));
			return;
		}
		if (pass.length() < 8) {
            regError->setText(tr("Password must be at least 8 characters."));
			return;
		}
		emit registerRequested(user, pass);
	});

    stack->addWidget(page);
}
