#include "MorseCodeApp.h"

#include "MainWindow.h"

#include <QtCore/QTimer>

using namespace NTUOSS::TgifHacks;

MorseCodeApp::MorseCodeApp(int &argc, char *argv[])
    : QApplication(argc, argv)
{
    QTimer::singleShot(0, this, SLOT(Start()));
}

MorseCodeApp::~MorseCodeApp(void)
{

}

void MorseCodeApp::Start(void)
{
    mainWindow = MainWindow::GetInstance();
    mainWindow->show();
}