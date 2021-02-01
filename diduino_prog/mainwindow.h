#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "arduino.h"
#include <QMainWindow>
#include <QSerialPort>
#include <QListWidgetItem>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_text(unsigned char * Data, unsigned int len);

private slots:
    void resizeBuffers(uint32_t size);
    void verifyData();
    void checkClear(QByteArray buff);
    void showBuf();
    void reload_ports();
    void showVoltage();
    void chipOperationProgressBar(uint32_t value);

    void on_openPort_clicked();


    void on_port_comboBox_currentIndexChanged(const QString &arg1);

    void on_ic_comboBox_currentIndexChanged(const QString &arg1);

    void on_verticalScrollBar_sliderMoved(int position);

    void on_read_ic_but_clicked();

    void on_save_file_but_clicked();

    void on_flash_ic_but_clicked();

    void on_open_file_but_clicked();

    void on_check_ic_but_clicked();

    void on_options_but_clicked();

signals:

  void chipReaded();
  void bufferUpdated();  
  //void chipUpdated(uint32_t size);

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort = NULL;
    arduino *mArduino = NULL;

    QTimer updatePortsTimer;
    QTimer updateVoltageTimer;
    QMetaObject::Connection updatePortsConnection;

    QMetaObject::Connection progressBarConnection;
    QMetaObject::Connection serialDataConnection;
    QMetaObject::Connection verifyDataConnection;
    QMetaObject::Connection checkClearConnection;
    QMetaObject::Connection updateBufConnection;
    QMetaObject::Connection updateVoltageConnection;

    bool verify_data = false;
    bool bufferClear = true;
    bool setting_view = false;
    uint32_t bufSize = 0;
    uint16_t first_line = 0;

    QByteArray bufWork;
    QByteArray bufCheck;

    void log(QString str);
    void openSerialPort(QString path);
    void closeSerialPort();
    void ic_version_select(QString boot_name);

};
#endif // MAINWINDOW_H
