#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QPushButton>

#include "header/MenuBar.h"

class MainWindow : public QMainWindow
{

Q_OBJECT

private slots:

    void newActionSlot();

private:

    MenuBar* menuBar;
    QMenu* fileMenu;
    QMenu* editMenu;
    QAction* newAction;
    QAction* openAction;
    QAction* exitAction;

    QTabWidget* tabWidget;
    QPushButton* menuButton;




public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
