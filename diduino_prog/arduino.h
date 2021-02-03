#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>

class arduino : public QObject
{
    Q_OBJECT

private:
    uint32_t bufSize;
    uint32_t g_i;
    QByteArray buffer;
    QByteArray buffer_w;
    QSerialPort *serialPort = NULL;
    QMetaObject::Connection serialDataConnection;


    void send(const QByteArray &data);

private slots:
    void recieve();
    void write_recieve();

public:
    enum chip {
        NONE,
        C16,
        C32,
        C64,
        C128,
        C256,
        C512,
        RE3,
        RT4,
        RT14,
        RT5
    };

    uint16_t n_impulses = 1000;
    uint16_t length_of_impulse_mks = 40;
    uint8_t duty = 10;
    uint8_t voltage_prog = 12;

    chip get_chip_selected = NONE;
    explicit arduino(QSerialPort *port);
    uint32_t getChipSize();
    void selectChip(chip type);
    void readChip();
    void writeChip(QByteArray data);
    void voltageMesurment(bool enable);


signals:
    void chipUpdated(uint32_t size);
    void blockComplete(uint32_t address);
    void readComplete(QByteArray data);
    void readError(uint16_t address, uint8_t value);
    void writeComplete();
    void writeError(uint16_t address, uint8_t value);
    void voltage(float v);

};


#endif // ARDUINO_H

