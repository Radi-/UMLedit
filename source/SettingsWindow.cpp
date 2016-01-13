
#include "header/SettingsWindow.h"

void SettingsWindow::rowChangedSlot(int row){

    stackWidget->setCurrentIndex(row);
}

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent)
{
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
    listWidget->setSpacing(5);
    listWidget->setCurrentRow(0);

    stackWidget = new QStackedWidget(this);
    stackWidget->setCurrentIndex(0);

    generalSettings = new QWidget(stackWidget);
    keyboardSettings = new QWidget(stackWidget);
    alternateModeCheckBox = new QCheckBox(generalSettings);
    alternateModeCheckBox->setText(tr("Enable Drawing Tablet Mode"));
    alternateModeCheckBox->setToolTip(tr("Enables/Disables Drawing Tablet Mode which is a special mode "
                                         "optimised for users using the computer with a drawing tablet."));
    QVBoxLayout* general = new QVBoxLayout(generalSettings);
    general->addWidget(alternateModeCheckBox);
    generalSettings->setLayout(general);

    stackWidget->addWidget(generalSettings);
    stackWidget->addWidget(keyboardSettings);


    splitter->addWidget(listWidget);
    splitter->addWidget(stackWidget);

    layout->addWidget(splitter);
    layout->addWidget(dbuttonbox);
    setLayout(layout);

    connect(listWidget, &QListWidget::currentRowChanged, this, &SettingsWindow::rowChangedSlot);

}

SettingsWindow::~SettingsWindow(){

}
