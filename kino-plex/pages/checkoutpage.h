#pragma once

#include <QWidget>
#include <QString>
#include <QStringList>

class QLabel;
class QPushButton;

class CheckoutPage : public QWidget
{
    Q_OBJECT
public:
    explicit CheckoutPage(QWidget *parent = nullptr);
    ~CheckoutPage();

    void setSummary(const QString &movieTitle, const QStringList &seats, double total);

signals:
    void purchaseConfirmed();

private:
    QLabel *summaryLabel;
    QPushButton *buyBtn;
};
