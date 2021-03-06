#ifndef COMMENTOBJECT_H
#define COMMENTOBJECT_H

#include <QString>

#include "header/Object.h"

class CommentObject : public Object
{

Q_OBJECT

private:

    QScopedPointer<QtStringPropertyManager> stringPropertyManager;
    QScopedPointer<QtFontPropertyManager> fontPropertyManager;

    QtProperty* string;
    QtProperty* font;

public:

    CommentObject();
    ~CommentObject();

    QtTreePropertyBrowser* getPropertyBrowser() override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

#endif // COMMENTOBJECT_H
