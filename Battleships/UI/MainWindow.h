#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void openSetupWindow();
    void openGameWindow();
private:
    QStackedWidget* stackedWidget;

    void setupUi(); // Funcție pentru inițializarea UI-ului
};