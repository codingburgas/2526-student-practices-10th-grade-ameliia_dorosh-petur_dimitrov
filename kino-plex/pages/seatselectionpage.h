#pragma once

#include <QWidget>
#include <QVector>
#include <QString>

class QGridLayout;
class QPushButton;

class SeatSelectionPage : public QWidget
{
    Q_OBJECT
public:
    explicit SeatSelectionPage(QWidget *parent = nullptr);
    ~SeatSelectionPage();

    void setMovie(const QString &movieId);

signals:
    void proceedToCheckout(const QString &movieId, const QStringList &seats);

private:
    QString currentId;
    QGridLayout *grid;
    QVector<QPushButton*> seatButtons;
};
