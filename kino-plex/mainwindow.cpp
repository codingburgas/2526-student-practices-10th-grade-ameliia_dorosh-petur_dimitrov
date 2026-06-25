#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include "pages/logandregisterpage.h"
#include "pages/movielistpage.h"
#include "pages/moviedetailspage.h"
#include "pages/seatselectionpage.h"
#include "pages/checkoutpage.h"
#include <QStackedWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    setWindowTitle("Kino-Plex");
    setMinimumSize(1100,700);
    resize(1400, 860);

    // stacked navigation: auth -> movie list -> details -> seats -> checkout
    stack = new QStackedWidget(this);

    LogAndRegisterPage *authPage = new LogAndRegisterPage(this);
    MovieListPage *movieList = new MovieListPage(this);
    MovieDetailsPage *details = new MovieDetailsPage(this);
    SeatSelectionPage *seats = new SeatSelectionPage(this);
    CheckoutPage *checkout = new CheckoutPage(this);

    stack->addWidget(authPage); // index 0
    stack->addWidget(movieList); // index 1
    stack->addWidget(details); // index 2
    stack->addWidget(seats); // index 3
    stack->addWidget(checkout); // index 4

    setCentralWidget(stack);

    // navigation
    connect(authPage, &LogAndRegisterPage::loginRequested, this, [this, movieList](const QString &u, const QString &p){
        Q_UNUSED(u); Q_UNUSED(p);
        stack->setCurrentIndex(1);
    });

    connect(movieList, &MovieListPage::movieSelected, this, [this, details](const QString &mid){
        details->showMovie(mid);
        stack->setCurrentIndex(2);
    });

    connect(details, &MovieDetailsPage::selectSeats, this, [this, seats](const QString &mid){
        seats->setMovie(mid);
        stack->setCurrentIndex(3);
    });

    connect(seats, &SeatSelectionPage::proceedToCheckout, this, [this, checkout](const QString &mid, const QStringList &sel){
        // find movie title for summary
        QFile f(":/data/movies.json");
        QString title = mid;
        if (f.open(QIODevice::ReadOnly)){
            QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
            for (const QJsonValue &v : doc.array()){
                if (v.isObject() && v.toObject().value("id").toString()==mid) {
                    title = v.toObject().value("title").toString(); break;
                }
            }
        }
        double total = sel.size() * 8.0; // simple price
        checkout->setSummary(title, sel, total);
        stack->setCurrentIndex(4);
    });

    connect(checkout, &CheckoutPage::purchaseConfirmed, this, [this](){
        // after purchase go back to movie list
        stack->setCurrentIndex(1);
    });


}

MainWindow::~MainWindow()
{

}
