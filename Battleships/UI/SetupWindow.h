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

private slots:
    void confirmSetup();

private:
    std::shared_ptr<UIObserver> m_observer;
    PlayerBoard* m_playerBoard;
    QPushButton* confirmButton;
    GameWindow* m_gameWindow;
    IGamePtr m_game;
};

#endif // SETUPWINDOW_H
