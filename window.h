#ifndef WINDOW_H
#define WINDOW_H

#include "glwidget.h"

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>

#include <iostream>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private:
    Ui::Window *ui;
    GLWidget *glWidget;

public slots:
    void printStatus(QString status);
};

#endif // WINDOW_H
