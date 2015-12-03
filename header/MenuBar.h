#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>

class MenuBar : public QMenuBar
{

Q_OBJECT

private:


public:
    explicit MenuBar(QWidget* parent = 0);
    ~MenuBar();

};

#endif // MENUBAR_H
