#ifndef COMMENTOBJECT_H
#define COMMENTOBJECT_H

#include <QString>

#include "header/Object.h"

class CommentObject : public Object
{

Q_OBJECT

private:

    QString string;
    QFont font;

public:

    CommentObject();
    CommentObject(QPoint size, QColor colour);
    ~CommentObject();
    QtTreePropertyBrowser* getPropertyBrowser() override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

#endif // COMMENTOBJECT_H
