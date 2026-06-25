#pragma once

#include <QWidget>
#include <QVector>

class QListWidget;
class QListWidgetItem;

class MovieListPage : public QWidget
{
    Q_OBJECT
public:
    explicit MovieListPage(QWidget *parent = nullptr);
    ~MovieListPage();

signals:
    void movieSelected(const QString &movieId);

private slots:
    void handleItemActivated(QListWidgetItem *item);

private:
    void loadMovies();
    QListWidget *listWidget;
};
