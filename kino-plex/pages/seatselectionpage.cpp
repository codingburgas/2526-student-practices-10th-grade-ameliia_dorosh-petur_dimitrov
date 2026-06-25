#include "seatselectionpage.h"

#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

SeatSelectionPage::SeatSelectionPage(QWidget *parent)
    : QWidget(parent), grid(new QGridLayout)
{
    QVBoxLayout *v = new QVBoxLayout(this);
    v->addWidget(new QLabel(tr("Select seats"), this));
    QWidget *gridWidget = new QWidget(this);
    gridWidget->setLayout(grid);
    v->addWidget(gridWidget, 1);

    // simple 5 rows x 8 cols
    const int rows = 5;
    const int cols = 8;
    for (int r=0; r<rows; ++r) {
        for (int c=0; c<cols; ++c) {
            QString seat = QString("%1%2").arg(QChar('A'+r)).arg(c+1);
            QPushButton *b = new QPushButton(seat, this);
            b->setCheckable(true);
            connect(b, &QPushButton::toggled, this, [b](bool on){
                if (on) b->setStyleSheet("background:#4caf50;color:white;"); else b->setStyleSheet("");
            });
            grid->addWidget(b, r, c);
            seatButtons.append(b);
        }
    }

    QHBoxLayout *h = new QHBoxLayout;
    QPushButton *checkout = new QPushButton(tr("Checkout"), this);
    h->addStretch();
    h->addWidget(checkout);
    v->addLayout(h);

    connect(checkout, &QPushButton::clicked, this, [this]() {
        QStringList sel;
        for (QPushButton *b : seatButtons) {
            if (b->isChecked()) sel << b->text();
        }
        emit proceedToCheckout(currentId, sel);
    });

    setLayout(v);
}

SeatSelectionPage::~SeatSelectionPage() {}

void SeatSelectionPage::setMovie(const QString &movieId)
{
    currentId = movieId;
    // reset selections
    for (QPushButton *b : seatButtons) b->setChecked(false);
}
