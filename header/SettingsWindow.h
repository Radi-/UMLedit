#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QCheckBox>

class SettingsWindow : public QDialog
{

private:

    QSplitter* splitter;
    QListWidget* listWidget;
    QStackedWidget* stackWidget;
    QVBoxLayout* layout;
    QDialogButtonBox* dbuttonbox;

    QWidget* generalSettings;
    QCheckBox* alternateModeCheckBox;

    QWidget* keyboardSettings;



    void rowChangedSlot(int row);

public:
    explicit SettingsWindow(QWidget* parent = 0);
    ~SettingsWindow();


};

#endif // SETTINGS_H
