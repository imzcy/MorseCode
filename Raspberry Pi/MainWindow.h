#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <inttypes.h>

#include <QtWidgets/QMainWindow>

class QTextEdit;
class QPushButton;
class QLineEdit;

namespace NTUOSS { namespace TgifHacks {

class Serial;
class Protocol;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    MainWindow(void);
    ~MainWindow(void);

public:
    static MainWindow *GetInstance(void);

private slots:
    void Connect(void);
    void Send(void);

private:
    static void MessageReceived(const uint16_t pos);

    QTextEdit *iptContent;
    QLineEdit *iptPort;
    QPushButton *btnSubmit;
    QPushButton *btnConnDiscon;

    Serial *serial;
    static MainWindow *mw;
    Protocol *protocol;
};

} }

#endif // _MAINWINDOW_H_