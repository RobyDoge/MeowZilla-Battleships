#include "SetupWindow.h"
#include "Board.h"
#include "Ship.h"
#include <qgraphicsview.h>
SetupWindow::SetupWindow(QWidget* parent)
    : QWidget(parent) {

	ui.setupUi(this);
    setupUi();
}

SetupWindow::~SetupWindow() {}

void SetupWindow::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Creează un QGraphicsView și o scenă
    QGraphicsView* view = new QGraphicsView(this);
    QGraphicsScene* scene = new QGraphicsScene(this);

    view->setScene(scene);

    // Creează grid-ul pentru board
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            QRectF cell(j * 50, i * 50, 50, 50); // 10x10 celule de 50x50 pixeli
            scene->addRect(cell, QPen(Qt::black), QBrush(Qt::lightGray));
        }
    }

    // Adaugă grid-ul în layout
    mainLayout->addWidget(view);
    setLayout(mainLayout);

    Ship* ship5x1 = new Ship(5, Qt::black);
    scene->addItem(ship5x1);
    ship5x1->setPos(0, 0);

    Ship* ship5x1_2 = new Ship(5, Qt::black);
    scene->addItem(ship5x1_2);
    ship5x1_2->setPos(0, 50);

    Ship* ship3x1 = new Ship(3, Qt::blue);
    scene->addItem(ship3x1);
    ship3x1->setPos(0, 100);

    Ship* ship3x1_2 = new Ship(3, Qt::blue);
    scene->addItem(ship3x1_2);
    ship3x1_2->setPos(0, 150);

    Ship* ship2x1 = new Ship(2, Qt::green);
    scene->addItem(ship2x1);
    ship2x1->setPos(0, 200);

    mainLayout->addWidget(view);
    setLayout(mainLayout);
}


