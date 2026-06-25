#include "movielistpage.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QListWidgetItem>

MovieListPage::MovieListPage(QWidget *parent)
    : QWidget(parent), listWidget(new QListWidget(this))
{
    QVBoxLayout *v = new QVBoxLayout(this);
    v->addWidget(listWidget, 1);
    setLayout(v);

    connect(listWidget, &QListWidget::itemActivated, this, &MovieListPage::handleItemActivated);

    loadMovies();
}

MovieListPage::~MovieListPage(){}

void MovieListPage::handleItemActivated(QListWidgetItem *item)
{
    if (!item) return;
    const QString id = item->data(Qt::UserRole).toString();
    emit movieSelected(id);
}

void MovieListPage::loadMovies()
{
    // Load a simple JSON resource with movies
    QFile f(":/data/movies.json");
    if (!f.open(QIODevice::ReadOnly)) return;
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if (!doc.isArray()) return;
    const QJsonArray arr = doc.array();
    for (const QJsonValue &v : arr) {
        if (!v.isObject()) continue;
        const QJsonObject o = v.toObject();
        QString id = o.value("id").toString();
        QString title = o.value("title").toString();
        QListWidgetItem *it = new QListWidgetItem(title, listWidget);
        it->setData(Qt::UserRole, id);
        listWidget->addItem(it);
    }
}
