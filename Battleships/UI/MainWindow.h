#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include "ui_mainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void openSetupWindow();
    void openGameWindow();
private:
     Ui::MainWindowClass ui;
     QStackedWidget* stackedWidget;

};