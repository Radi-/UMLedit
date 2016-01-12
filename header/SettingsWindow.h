#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class SettingsWindow : public QDialog
{

private:
    QSplitter* splitter;
    QListWidget* listWidget;
    QStackedWidget* stackWidget;
    QVBoxLayout* layout;
    QDialogButtonBox* dbuttonbox;

public:
    explicit SettingsWindow(QWidget* parent = 0);
    ~SettingsWindow();


};

#endif // SETTINGS_H
