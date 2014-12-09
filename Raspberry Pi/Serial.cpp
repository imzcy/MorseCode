#include "Serial.h"

using namespace NTUOSS::TgifHacks;

#include <QtCore/QTimer>
#include <QtSerialPort/QSerialPort>

Serial::Serial(void)
{
    _SerialPort = new QSerialPort;
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(checkData()));
}

bool Serial::Connect(const char *port)
{
    _SerialPort->close();
    _SerialPort->setPortName(port);
    _SerialPort->open(QIODevice::ReadWrite);
    if (!_SerialPort->isOpen())
    {
        return false;
    }
    _SerialPort->setBaudRate(9600);
    _SerialPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    _SerialPort->setParity(QSerialPort::Parity::NoParity);
    _SerialPort->setDataBits(QSerialPort::DataBits::Data8);
    _SerialPort->setStopBits(QSerialPort::StopBits::OneStop);
    timer->start(20);
    return true;
}

Serial *Serial::GetInstance(void)
{
    static class _helper
    {
    public:
        _helper(Serial *&s)
        {
            s = new Serial;
        }
    } helper(s);
    return s;
}

void Serial::GetChar(EntryGetCharCallback GetCharCallback)
{
    _GetCharCallback = GetCharCallback;
}

void Serial::PutChar(const char c)
{
    QByteArray arr;
    arr[0] = c;
    s->_SerialPort->write(arr);
}

void Serial::checkData(void)
{
    QByteArray data;
    data = _SerialPort->readAll();
    if (data.length() == 0)
    {
        return;
    }
    for (int i = 0; i < data.length(); i++)
    {
        _GetCharCallback(data[i]);
    }
}

EntryGetCharCallback Serial::_GetCharCallback;
Serial *Serial::s;