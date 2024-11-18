#pragma once

#include <QWidget>
#include "ui_SetupWindow.h"

#include <QGridLayout>
#include <QPushButton>

class SetupWindow : public QWidget {
    Q_OBJECT

public:
    explicit SetupWindow(QWidget* parent = nullptr);
    ~SetupWindow();

signals:
    void setupConfirmed();

private:
    QGridLayout* gridLayout;
    void setupUi();
	Ui::SetupWindowClass ui;
};
