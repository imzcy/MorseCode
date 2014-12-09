#ifndef _MORSECODEAPP_H_
#define _MORSECODEAPP_H_

#include <QtWidgets/QApplication>

namespace NTUOSS { namespace TgifHacks {

class MainWindow;

class MorseCodeApp : public QApplication
{
    Q_OBJECT

public:
    MorseCodeApp(int &argc, char *argv[]);
    ~MorseCodeApp(void);

private:
    MainWindow *mainWindow;

private slots:
    void Start(void);
};

} }

#endif // _MORSECODEAPP_H_