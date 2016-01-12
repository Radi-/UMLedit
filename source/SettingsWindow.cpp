
#include "header/SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent)
{
    layout = new QVBoxLayout(this);
    dbuttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                      this);
    setModal(true);
    setMinimumSize(600, 450);
    setWindowTitle(tr("Settings"));
    layout->setContentsMargins(0,0,0,0);
    splitter = new QSplitter(this);

    listWidget = new QListWidget(this);
    listWidget->setFixedWidth(200);
    listWidget->addItem(tr("General"));
    listWidget->setCurrentRow(0);
    stackWidget = new QStackedWidget(this);
    stackWidget->setCurrentIndex(0);

    splitter->addWidget(listWidget);
    splitter->addWidget(stackWidget);

    layout->addWidget(splitter);
    layout->addWidget(dbuttonbox);
    setLayout(layout);

}

SettingsWindow::~SettingsWindow(){

}
