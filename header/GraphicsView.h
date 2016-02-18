#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QString>
#include <QUndoStack>
#include <QPointer>
#include <QMenu>
#include <QContextMenuEvent>
#include <QListWidget>

class GraphicsView : public QGraphicsView
{

Q_OBJECT

private:
   QString filePath;
   bool changed;
   QPointer<QMenu> contextMenu;

public:
   GraphicsView(QWidget* parent = 0);
   GraphicsView(QString& path, QWidget* parent = 0);
   ~GraphicsView();

   QString getFilePath();
   void setFilePath(QString& path);
   void setContextMenu(QMenu* contextMenu);

   bool hasChanged();

   bool saveFile();
   bool saveFileAs();

   void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // GRAPHICSVIEW_H
