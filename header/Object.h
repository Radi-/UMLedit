#ifndef OBJECT_H
#define OBJECT_H

#include "header/Connection.h"
#include "header/Element.h"

class Object : public Element
{

Q_OBJECT

private:

protected slots:

    virtual void updateDrawingParameters();
    virtual void pointPropertyUpdated(QtProperty* property, QPoint size);

protected:

    QScopedPointer<QtPointPropertyManager> pointPropertyManager;

    QtProperty* sizep;
    QtProperty* size;
    QtProperty* objectGroup;

    QVector<Connection> startPointConnections;
    QVector<Connection> endPointConnections;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

public:

    Object();
    virtual ~Object();

    virtual void setSize(QPoint size);
    virtual QtTreePropertyBrowser* getPropertyBrowser() = 0;

    void connectConnectorStartPoint(Connection connection);
    void disconnectConnectorStartPoint(Connection connection);
    void connectConnectorEndPoint(Connection connection);
    void disconnectConnectorEndPoint(Connection connection);

    QRectF boundingRect() const override;
};

#endif // OBJECT_H
