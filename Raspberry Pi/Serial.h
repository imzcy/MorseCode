#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "Protocol.h"

#include <QtCore/QObject>

class QSerialPort;
class QTimer;

namespace NTUOSS { namespace TgifHacks {

class Serial : public QObject
{
    Q_OBJECT

private:
    Serial(void);

public:
    bool Connect(const char *port);
    static Serial *GetInstance(void);
    static void GetChar(EntryGetCharCallback GetCharCallback);
    static void PutChar(const char c);

private slots:
    void checkData(void);

private:
    QSerialPort *_SerialPort;
    QTimer *timer;
    static EntryGetCharCallback _GetCharCallback;

    static Serial *s;
};

} }
#endif // _SERIAL_H_