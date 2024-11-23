#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "board.h"

class SetupWindow : public QWidget {
    Q_OBJECT

public:
    explicit SetupWindow(QWidget* parent = nullptr);

private slots:
    void confirmSetup();

private:
    Board* board;
    QPushButton* confirmButton;
};

#endif // SETUPWINDOW_H
