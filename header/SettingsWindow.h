#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class SettingsWindow : public QDialog
{
Q_OBJECT

signals:

    void alternateModeCheckBoxToggled(bool checked);

private:

    QSplitter* splitter;
    QListWidget* listWidget;
    QStackedWidget* stackWidget;
    QVBoxLayout* layout;
    QDialogButtonBox* dbuttonbox;

    QWidget* generalSettings;
    QVBoxLayout* generalLayout;
    QCheckBox* alternateModeCheckBox;
    QCheckBox* checkUpdatesCheckBox;

    QWidget* keyboardSettings;
    QVBoxLayout* keyboardLayout;
    QTreeWidget* shortcutsWidget;
    QTreeWidgetItem* DTMShortcutsCategory;
    QTreeWidgetItem* generalShortcutsCategory;

    void createGeneralPage();
    void createKeyboardPage();
    //Slot methods
    void rowChangedSlot(int row);
    void dialogButtonClicked(QAbstractButton* button);

public:
    explicit SettingsWindow(QWidget* parent = 0);
    ~SettingsWindow();
};

#endif // SETTINGS_H
