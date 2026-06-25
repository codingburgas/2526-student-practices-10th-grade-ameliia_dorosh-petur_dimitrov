#include "moviedetailspage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

MovieDetailsPage::MovieDetailsPage(QWidget *parent)
    : QWidget(parent), titleLabel(new QLabel(this)), descLabel(new QLabel(this))
{
    QVBoxLayout *v = new QVBoxLayout(this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 20px;");
    descLabel->setWordWrap(true);
    v->addWidget(titleLabel);
    v->addWidget(descLabel);
    QPushButton *seats = new QPushButton(tr("Select Seats"), this);
    v->addWidget(seats);
    connect(seats, &QPushButton::clicked, this, [this]() {
        if (!currentId.isEmpty()) emit selectSeats(currentId);
    });
    setLayout(v);
}

MovieDetailsPage::~MovieDetailsPage() {}

void MovieDetailsPage::showMovie(const QString &movieId)
{
    currentId = movieId;
    QFile f(":/data/movies.json");
    if (!f.open(QIODevice::ReadOnly)) return;
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if (!doc.isArray()) return;
    for (const QJsonValue &v : doc.array()) {
        if (!v.isObject()) continue;
        QJsonObject o = v.toObject();
        if (o.value("id").toString() == movieId) {
            titleLabel->setText(o.value("title").toString());
            descLabel->setText(o.value("description").toString());
            return;
        }
    }
}
