#pragma once

#include <QWidget>
#include <QString>

class QLabel;
class QPushButton;

class MovieDetailsPage : public QWidget
{
    Q_OBJECT
public:
    explicit MovieDetailsPage(QWidget *parent = nullptr);
    ~MovieDetailsPage();

    void showMovie(const QString &movieId);

signals:
    void selectSeats(const QString &movieId);

private:
    QLabel *titleLabel;
    QLabel *descLabel;
    QString currentId;
};
