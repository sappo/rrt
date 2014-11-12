#include "window.h"
#include <QStatusBar>
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    setWindowTitle(tr("Robotik Projekt - RRT"));

    glWidget = new GLWidget(this);
    glWidget->resize(1000, 1000);
    QGridLayout *gridLayout = new QGridLayout();

    gridLayout->addWidget(new QPushButton(this), 1, 1);
    gridLayout->addWidget(new QPushButton(this), 1, 2);
    gridLayout->addWidget(glWidget, 2, 1, 1, 2);
    ui->widget->setLayout(gridLayout);
    resize(glWidget->size());
}

Window::~Window()
{
    delete ui;
}

void Window::printStatus(QString status)
{
    statusBar()->showMessage(status);
}
