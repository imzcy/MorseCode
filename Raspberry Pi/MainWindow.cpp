#include "MainWindow.h"

#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>

#include "Serial.h"
#include "Protocol.h"

using namespace NTUOSS::TgifHacks;

MainWindow::MainWindow(void)
    : iptContent(new QTextEdit(this))
    , iptPort(new QLineEdit(this))
    , btnSubmit(new QPushButton(this))
    , btnConnDiscon(new QPushButton(this))
    , serial(Serial::GetInstance())
    , protocol(new Protocol)
{
    resize(400 * QPaintDevice::logicalDpiX() / 96., 200 * QPaintDevice::logicalDpiX() / 96.);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *vlayout = new QVBoxLayout;
    QWidget *btnGroup = new QWidget(this);
    QHBoxLayout *hlayout = new QHBoxLayout(btnGroup);
    btnGroup->setLayout(hlayout);
    centralWidget->setLayout(vlayout);
    iptContent->setStyleSheet(/*NOXLATE*/"selection-background-color: black; selection-color: white;");
    vlayout->addWidget(iptContent, 1);
    vlayout->addWidget(iptPort);
    vlayout->addWidget(btnGroup);
    btnSubmit->setText(tr("Send"));
    btnConnDiscon->setText(tr("Connect/Disconnect"));
    hlayout->addStretch(1);
    hlayout->addWidget(btnConnDiscon);
    hlayout->addWidget(btnSubmit);

    connect(btnConnDiscon, SIGNAL(clicked()), this, SLOT(Connect()));
    connect(btnSubmit, SIGNAL(clicked()), this, SLOT(Send()));

    protocol->Init(Serial::GetChar, Serial::PutChar, MainWindow::MessageReceived);
}

MainWindow::~MainWindow(void)
{

}

MainWindow *MainWindow::GetInstance(void)
{
    static class _helper
    {
    public:
        _helper(MainWindow *&mw)
        {
            mw = new MainWindow;
        }
    } helper(mw);
    return mw;
}

void MainWindow::Connect(void)
{
    if (!serial->Connect(iptPort->text().toUtf8().constData()))
    {
        QMessageBox::critical(this, "Error", "Cannot connect to Arduino.");
        return;
    }
    QMessageBox::information(this, "", "Connected.");
}

void MainWindow::Send(void)
{
    Protocol::Send(iptContent->toPlainText().toUtf8().constData(), iptContent->toPlainText().length());
}

void MainWindow::MessageReceived(const uint16_t pos)
{
    QTextCursor c = mw->iptContent->textCursor();
    c.setPosition(0);
    c.setPosition(pos + 1, QTextCursor::KeepAnchor);
    mw->iptContent->setTextCursor(c);
}

MainWindow *MainWindow::mw = nullptr;