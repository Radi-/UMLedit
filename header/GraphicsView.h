#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QString>
#include <QUndoStack>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

private:
   QString filePath;
   bool changed;

public:
   GraphicsView(QWidget* parent = 0);
   GraphicsView(QString& path, QWidget* parent = 0);
   ~GraphicsView();

   QString getFilePath();
   void setFilePath(QString& path);

   bool hasChanged();

   bool saveFile();
   bool saveFileAs();

};

#endif // GRAPHICSVIEW_H
