#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QWidget>

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT

signals:
    void cursorPositionChanged(qreal x, qreal y);
    void mouseClicked(Qt::MouseButton mouseButton);

private:

public:
    explicit GraphicsScene(QWidget* parent = 0);
    ~GraphicsScene();

    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // GRAPHICSSCENE_H
