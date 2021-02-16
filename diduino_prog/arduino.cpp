#include "arduino.h"

#include <QDebug>

arduino::arduino(QSerialPort *port)
{
    serialPort = port;
}


void arduino::send(const QByteArray &data)
{
    serialPort->write(data);
}

void arduino::recieve()
{
    while (!serialPort->atEnd()) {
        buffer.append(serialPort->read(1));
        emit blockComplete(buffer.length());

        if (buffer.length() >= bufSize){
            QObject::disconnect(serialDataConnection);
            emit readComplete(buffer);
        }
    }
}

void arduino::write_recieve()
{
    while (!serialPort->atEnd()) {
        buffer.append(serialPort->read(1));
        emit blockComplete(buffer.length());

        if (buffer.length() >= bufSize){
            QObject::disconnect(serialDataConnection);
            emit readComplete(buffer);
        }
    }

    QByteArray temp;
    temp.append(buffer_w[g_i]);
    g_i++;
    send(temp);
}

void arduino::selectChip(chip type)
{
    get_chip_selected = type;
    switch(type){
    case NONE:
        bufSize = 0;
        break;
    case C16:
        bufSize = 0x07ff + 1;
        send("a");
        break;
    case C32:
        bufSize = 0x0fff + 1;
        send("b");
        break;
    case C64:
        bufSize = 0x1fff + 1;
        send("c");
        break;
    case C128:
        bufSize = 0x3fff + 1;
        send("d");
        break;
    case C256:
        bufSize = 0x7fff + 1;
        send("e");
        break;
    case C512:
        bufSize = 0xffff + 1;
        send("f");
        break;
    case RE3:
        bufSize = 0x1f + 1;
        send("g");
        break;
    case RT4:
        bufSize = 0xff + 1;
        send("h");
        break;
    case RT14:
        bufSize = 0x7cf + 1;
        send("i");
        break;
    case RT5:
        bufSize = 0x1ff + 1;
        send("j");
        break;
    }
    emit chipUpdated(bufSize);
}

uint32_t arduino::getChipSize()
{
    return bufSize;
}

void arduino::readChip()
{
    QObject::disconnect(serialDataConnection);
    buffer.clear();
    serialPort->clear();
    serialDataConnection = QObject::connect(serialPort, SIGNAL(readyRead()), this, SLOT(recieve()));
    send("r");
}

void arduino::writeChip(QByteArray data)
{
    QObject::disconnect(serialDataConnection);
    buffer.clear();
    serialPort->clear();
    buffer_w.clear();

    buffer_w = data;
    g_i = 1;
    serialDataConnection = QObject::connect(serialPort, SIGNAL(readyRead()), this, SLOT(write_recieve()));
    send("w");
    QByteArray temp;
    temp.append(buffer_w[0]);
    send(temp);
}

void arduino::voltageMesurment(bool enable)
{
    if (enable) {
        send("v");
    }
}
