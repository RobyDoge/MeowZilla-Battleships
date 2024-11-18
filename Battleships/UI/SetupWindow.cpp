#include "SetupWindow.h"

SetupWindow::SetupWindow(QWidget* parent)
    : QWidget(parent), gridLayout(new QGridLayout(this)) {
    setupUi();
}

SetupWindow::~SetupWindow() {}

void SetupWindow::setupUi() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            QPushButton* cell = new QPushButton(this);
            cell->setFixedSize(30, 30);
            gridLayout->addWidget(cell, i, j);
        }
    }

    QPushButton* btnConfirm = new QPushButton("Confirm Setup", this);
    gridLayout->addWidget(btnConfirm, 11, 0, 1, 10);

    connect(btnConfirm, &QPushButton::clicked, this, &SetupWindow::setupConfirmed);
}
