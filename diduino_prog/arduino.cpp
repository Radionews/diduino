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
    /*
    static uint32_t count = 0;
    const QByteArray data = serialPort->readAll();
    if (data.count()){
        memcpy(&(bufWork.data())[count], data.data(), data.count());
        count += data.count();
    }
    ui->progressBar->setValue(count);
    if (count >= bufSize){
        ui->progressBar->setValue(bufSize);
        QObject::disconnect(serialDataConnection);
        updateButtons(true, true);

        log(QString("Readed %1 bytes.").arg(count));
        count = 0;

        emit readComplete(data);
        //emit bufferUpdated();
    }
*/
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
    /*for (uint32_t i = 0; i <= data.length(); i++){
        buf.append(data[i]);
        send(buf);
        serialPort->waitForBytesWritten(500);
        buf.clear();
    }*/
    /*
    QByteArray ack;
    QByteArray buf;
    buf.clear();

    // +1 нужен для записи последнего блока
    for (uint32_t i = 0; i <= bufSize; i++){
        buf.append(data[i]);
        if (i && ((i & 0xf) == 0)){
            // 16 bytes block
            send(buf);
            buf.clear();
            ack = serialPort->readAll();
            ack.clear();

            if (bufSize == 2048){
                // Correct time to 27C16
                while (serialPort->waitForReadyRead(320)){
                    ack.append(serialPort->readAll());
                }
            } else {
                while (serialPort->waitForReadyRead(20)){
                    ack.append(serialPort->readAll());
                }
            }
            if (ack.indexOf("Complete block ") == -1){
                uint16_t address = 0;
                uint8_t value = 0xff;
                emit writeError(address, value);
                return;
            }
        }
    }
    emit writeComplete();*/
}

void arduino::voltageMesurment(bool enable)
{
    if (enable) {
        send("v");
    }
}
