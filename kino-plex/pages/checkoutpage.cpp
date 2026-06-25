#include "checkoutpage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

CheckoutPage::CheckoutPage(QWidget *parent)
    : QWidget(parent), summaryLabel(new QLabel(this)), buyBtn(new QPushButton(tr("Buy"), this))
{
    QVBoxLayout *v = new QVBoxLayout(this);
    summaryLabel->setWordWrap(true);
    v->addWidget(summaryLabel);
    v->addWidget(buyBtn, 0, Qt::AlignRight);
    connect(buyBtn, &QPushButton::clicked, this, [this]() { emit purchaseConfirmed(); });
    setLayout(v);
}

CheckoutPage::~CheckoutPage() {}

void CheckoutPage::setSummary(const QString &movieTitle, const QStringList &seats, double total)
{
    QString text = QString("Movie: %1\nSeats: %2\nTotal: $%3")
            .arg(movieTitle).arg(seats.join(", ")).arg(total, 0, 'f', 2);
    summaryLabel->setText(text);
}
