#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "PlayerBoard.h"
#include "GameWindow.h"
#include "IGame.h"

class SetupWindow : public QWidget {
    Q_OBJECT

public:
    explicit SetupWindow(IGamePtr game,QWidget* parent = nullptr);
    void SetGame(IGamePtr game);

private slots:
    void confirmSetup();

private:
    PlayerBoard* board;
    QPushButton* confirmButton;
    GameWindow* m_gameWindow;
    IGamePtr m_game;
};

#endif // SETUPWINDOW_H
