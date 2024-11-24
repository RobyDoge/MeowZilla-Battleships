#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "PlayerBoard.h"

class SetupWindow : public QWidget {
    Q_OBJECT

public:
    explicit SetupWindow(QWidget* parent = nullptr);

private slots:
    void confirmSetup();

private:
    PlayerBoard* board;
    QPushButton* confirmButton;
};

#endif // SETUPWINDOW_H
