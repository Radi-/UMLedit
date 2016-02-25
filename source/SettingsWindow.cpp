
#include <QStringList>
#include <QTreeWidgetItem>
#include <QDebug>

#include "header/SettingsWindow.h"
#include "header/MainWindow.h"

void SettingsWindow::createGeneralPage(){

    generalSettings = new QWidget(stackWidget);

    alternateModeCheckBox = new QCheckBox(tr("Enable Drawing Tablet Mode"), generalSettings);
    alternateModeCheckBox->setToolTip(tr("Enables/Disables Drawing Tablet Mode which is a special mode "
                                         "optimised for users using the computer with a drawing tablet."));
    checkUpdatesCheckBox = new QCheckBox(tr("Check updates at startup"), generalSettings);
    checkUpdatesCheckBox->setToolTip(tr("Enables/Disables update checking at startup. This may decrease "
                                        "the time it takes to start up the program."));

    generalLayout = new QVBoxLayout(generalSettings);
    generalLayout->setContentsMargins(0,0,0,0);
    generalLayout->addWidget(alternateModeCheckBox);
    generalLayout->addWidget(checkUpdatesCheckBox);

    generalSettings->setLayout(generalLayout);
    stackWidget->addWidget(generalSettings);
}

void SettingsWindow::createKeyboardPage(){

    //Create a widget and a layout
    keyboardSettings = new QWidget(stackWidget);
    QStringList headerLabels;
    headerLabels << tr("Action") << tr("Shortcut key");
    shortcutsWidget = new QTreeWidget(keyboardSettings);
    shortcutsWidget->setHeaderLabels(headerLabels);
    shortcutsWidget->setColumnWidth(0, 180);
    keyboardLayout = new QVBoxLayout(keyboardSettings);
    keyboardLayout->setContentsMargins(0,0,0,0);
    keyboardLayout->addWidget(shortcutsWidget);
    stackWidget->addWidget(keyboardSettings);

    //Create sample content to the widget
    QStringList DTMOpenObjects;
    DTMOpenObjects << tr("Open Objects menu") << "Q";
    QStringList generalNew;
    generalNew << tr("New project") << "Ctrl+N";
    DTMShortcutsCategory = new QTreeWidgetItem(QStringList(tr("Drawing Tablet Mode shortcuts")));
    DTMShortcutsCategory->addChild(new QTreeWidgetItem(DTMOpenObjects));
    generalShortcutsCategory = new QTreeWidgetItem(QStringList(tr("General shortcuts")));
    generalShortcutsCategory->addChild(new QTreeWidgetItem(generalNew));
    shortcutsWidget->addTopLevelItem(generalShortcutsCategory);
    shortcutsWidget->addTopLevelItem(DTMShortcutsCategory);
}

void SettingsWindow::rowChangedSlot(int row){

    stackWidget->setCurrentIndex(row);
}

void SettingsWindow::dialogButtonClicked(QAbstractButton* button){

    if (dbuttonbox->buttonRole(button) == QDialogButtonBox::AcceptRole){
        this->close();
    }
}

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent){

    layout = new QVBoxLayout(this);
    dbuttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Reset,
                                      this);
    setModal(true);
    setMinimumSize(600, 450);
    setWindowTitle(tr("Settings"));
    layout->setContentsMargins(0,0,0,0);
    splitter = new QSplitter(this);

    listWidget = new QListWidget(this);
    listWidget->setFixedWidth(200);
    listWidget->addItem(tr("General"));
    listWidget->item(0)->setIcon(QIcon::fromTheme("preferences-system"));
    listWidget->addItem(tr("Keyboard"));
    listWidget->item(1)->setIcon(QIcon::fromTheme("preferences-desktop-keyboard"));
    listWidget->setMovement(QListView::Static);
    listWidget->setIconSize(QSize(25, 25));
    listWidget->setCurrentRow(0);

    stackWidget = new QStackedWidget(this);
    stackWidget->setCurrentIndex(0);

    createGeneralPage();
    createKeyboardPage();

    splitter->addWidget(listWidget);
    splitter->addWidget(stackWidget);

    layout->addWidget(splitter);
    layout->addWidget(dbuttonbox);
    setLayout(layout);

    connect(listWidget, &QListWidget::currentRowChanged, this, &SettingsWindow::rowChangedSlot);
    connect(dbuttonbox, &QDialogButtonBox::clicked, this, &SettingsWindow::dialogButtonClicked);
    connect(alternateModeCheckBox, &QCheckBox::toggled, this, &SettingsWindow::alternateModeCheckBoxToggled);
}

SettingsWindow::~SettingsWindow(){
}
