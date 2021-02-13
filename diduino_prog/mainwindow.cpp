#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDesktopWidget>

//----функция прорисовки буфера на экране------
void MainWindow::showBuf()
{
    QString temp = "", temp2 = "";
    for(unsigned int i = first_line; i<=bufSize/16; i++){
        temp += QString("%1").arg(i*10, 7, 10, QChar('0')) + "\n";
    }
    ui->offset_row->setText(temp);
    temp = "";
    for(unsigned int i = first_line*16; i<bufSize; i++){
        temp += QString("%1").arg((int(bufWork[i])&0xff), 2, 16, QChar('0')) + " ";


        if((int(bufWork[i])&0xff)>=0x20){    temp2 += QString::fromLocal8Bit(QByteArray::fromHex(QString::number((int(bufWork[i])&0xff),16).toLocal8Bit()));}
        else{                 temp2 += ".";}

        if (i%16 == 15){ temp += "\n"; temp2 += "\n";}
    }
    ui->text_out->setText(temp);
    ui->decoded->setText(temp2);
}
//--------------------------------------------
void MainWindow::log(QString str)
{
    ui->status_text_out->append(str);
    ui->status_text_out->moveCursor(QTextCursor::End);
}
//--------------------------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    serialPort(new QSerialPort)
{
    ui->setupUi(this);

    int h_mon = (QApplication::desktop()->screenGeometry().height());
    ui->text_out->setMaximumHeight(h_mon-350);
    ui->offset_row->setMaximumHeight(h_mon-350);
    ui->decoded->setMaximumHeight(h_mon-350);

    ui->offset_row->setStyleSheet("QLabel { color : blue; }");
    ui->offset_line->setStyleSheet("QLabel { color : blue; }");
    //ui->decode_head->setStyleSheet("QLabel { color : blue; }");

    updatePortsConnection = QObject::connect(&updatePortsTimer, SIGNAL(timeout()), this, SLOT(reload_ports()));
    updatePortsTimer.setInterval(2000);
    updatePortsTimer.start();
    reload_ports();

    ui->checkBox->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->checkBox->hide();
    ui->pushButton->hide();
    ui->horizontalSlider->hide();

    QObject::connect(this, SIGNAL(bufferUpdated()), this, SLOT(showBuf()));
    bufSize = 32;
    for(uint32_t i = 0; i<bufSize; i++){
        bufWork.append((char)0);
    }
    emit bufferUpdated();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//------код отвечающий за com порты-----
void MainWindow::reload_ports()
{
    QString temp = ui->port_comboBox->currentText();
    ui->port_comboBox->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        //необходимо условия доработать
        if (info.isBusy() /*|| (serialPort->portName()==info.portName() && !serialPort->isOpen())*/){
            ui->port_comboBox->addItem(info.portName() + " (Busy)");
        }
        else{
            ui->port_comboBox->addItem(info.portName());
        }
    }
    ui->port_comboBox->setCurrentText(temp);
}

void MainWindow::on_port_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1.indexOf("(Busy)") != -1){
        log("Port :" + arg1.left(arg1.indexOf("(Busy)")) + " is buzy");
        ui->openPort->setDisabled(true);
    }
    else{
        ui->openPort->setDisabled(false);
    }

}

void MainWindow::openSerialPort(QString path)
{
    log("Open " + path);
    serialPort->setPortName(path);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    ui->openPort->setText("Close");
    updatePortsTimer.stop();
    if (serialPort->open(QIODevice::ReadWrite)) {
        serialPort->waitForReadyRead(4000);
        QByteArray readData = serialPort->readAll();
        while (serialPort->waitForReadyRead(100)){
            readData.append(serialPort->readAll());
        }

        if (readData.indexOf("ARDUINO PROGRAMMER") != -1){
            log(QString("Connect successful"));
            mArduino = new arduino(serialPort);
            //mArduino->selectChip(arduino::NONE);
            ic_version_select(readData/*.right(readData.indexOf("ARDUINO PROGRAMMER", 0)-18)*/);
            //set_text((unsigned char*)(readData.data()), readData.length());

        }
        else{
            log(QString("Arduino programmer not found."));
            closeSerialPort();
        }
    } else {
        QMessageBox::critical(this, tr("Error"), serialPort->errorString());
    }
}

void MainWindow::closeSerialPort()
{
    //updatePortsTimer.start();

    if (serialPort->isOpen()){
        serialPort->close();
        log(QString("Disconnect..."));
        ui->openPort->setText("Open");
        updatePortsTimer.start();
        ui->online_but->setEnabled(false);
        QObject::disconnect(serialDataConnection);

    }
}

void MainWindow::on_openPort_clicked()
{
    if (serialPort->isOpen()){
        closeSerialPort();
    }
    else{
        openSerialPort(ui->port_comboBox->currentText());
    }
}

//------------------------------------------

void MainWindow::ic_version_select(QString boot_name){
    if(boot_name.indexOf("DIDUINO")!=-1){
        QString version = boot_name.right(boot_name.indexOf("VER", 0)-3);
        log("DIDUINO found version " + version);
        //при добавлении новой версии железа тут необходимо реализовать настройку по версиям
        ui->ic_comboBox->clear();
        ui->ic_comboBox->addItem("K155RE3");
        ui->ic_comboBox->addItem("KR556RT4");
        ui->ic_comboBox->addItem("KR556RT14");
        ui->ic_comboBox->addItem("KR556RT5");
        ui->ic_comboBox->setCurrentText("K155RE3");

        ui->online_but->setEnabled(true);
    }

}

void MainWindow::on_ic_comboBox_currentIndexChanged(const QString &arg1)
{
    QObject::connect(mArduino, SIGNAL(chipUpdated(uint32_t)), this, SLOT(resizeBuffers(uint32_t)));
    if (arg1 == "K155RE3")  {mArduino->selectChip(arduino::RE3); log("K155RE3 is selected");  ui->verticalScrollBar->setMaximum(1);}
    if (arg1 == "KR556RT4") {mArduino->selectChip(arduino::RT4); log("KR556RT4 is selected"); ui->verticalScrollBar->setMaximum(15);}
    if (arg1 == "KR556RT14"){mArduino->selectChip(arduino::RT14);log("KR556RT14 is selected");ui->verticalScrollBar->setMaximum(124);}
    if (arg1 == "KR556RT5") {mArduino->selectChip(arduino::RT5); log("KR556RT5 is selected"); ui->verticalScrollBar->setMaximum(31);}
}

void MainWindow::resizeBuffers(uint32_t size)
{
    bufSize = size;
    bufWork.resize(bufSize);
    bufCheck.resize(bufSize);
    bufCheck.fill(0);
    for(uint32_t i = 0; i<bufSize; i++){
        if(mArduino->get_chip_selected == mArduino->RT5){ bufWork[i] = 1;   }
        else{                                             bufWork[i] = 0;   }
    }
    emit bufferUpdated();
}

void MainWindow::checkClear(QByteArray buff)
{
    uint32_t count;
    QObject::disconnect(progressBarConnection);
    ui->progressBar->setValue(ui->progressBar->maximum());
    QObject::disconnect(checkClearConnection);
    for (count = 0; count < buff.length(); count++){
        if(bufWork[count] != (char)0xff){
        //if (((bufWork[count] != (char)0xff)&&(mArduino->get_chip_selected == mArduino->RT5))||((bufWork[count] != (char)0xff)&&(mArduino->get_chip_selected == mArduino->RT5))){
            log(QString("Chip not clear. Check before write."));
            break;
        }
    }
    if (count >= bufSize)
        log(QString("Chip clear."));
    bufWork = buff;
    if(verify_data) verifyData();
    emit bufferUpdated();
}

void MainWindow::verifyData()
{
    ui->progressBar->setMaximum(bufSize);
    ui->progressBar->setValue(0);
    verify_data = false;
    uint32_t errors_count = 0;
    for (uint32_t i = 0; i < bufSize; i++){
        if(bufWork[i] != bufCheck[i]) errors_count++;
        ui->progressBar->setValue(i);
    }
    if(errors_count == 0) { log(QString("Verification successful."));}
    else {
        log(QString("Verification failed."));
        log(QString("Errors: %1.").arg(errors_count));
    }
}

void MainWindow::showVoltage()
{

}

void MainWindow::on_read_ic_but_clicked()
{
    if(serialPort->isOpen()){
        ui->progressBar->setMaximum(mArduino->getChipSize());
        log(QString("Reading %1 bytes from chip...").arg(mArduino->getChipSize()));
        mArduino->readChip();
        progressBarConnection = QObject::connect(mArduino, SIGNAL(blockComplete(uint32_t)), this, SLOT(chipOperationProgressBar(uint32_t)));
        checkClearConnection = QObject::connect(mArduino, SIGNAL(readComplete(QByteArray)), this, SLOT(checkClear(QByteArray)));
    }
    else{
        log(QString("Программатор не подключен!"));
    }
}

void MainWindow::on_flash_ic_but_clicked()
{
    ui->progressBar->setMaximum(mArduino->getChipSize());
    log(QString("Burn %1 bytes to chip...").arg(mArduino->getChipSize()));
    mArduino->writeChip(bufWork);
    progressBarConnection = QObject::connect(mArduino, SIGNAL(blockComplete(uint32_t)), this, SLOT(chipOperationProgressBar(uint32_t)));
    checkClearConnection = QObject::connect(mArduino, SIGNAL(readComplete(QByteArray)), this, SLOT(checkClear(QByteArray)));
}

void MainWindow::on_check_ic_but_clicked()
{//запуск сравнения данных на чипе и загруженных в основной буфер

    if(serialPort->isOpen()){
        bufCheck.clear();
        bufCheck = bufWork;
        verify_data = true;

        ui->progressBar->setMaximum(mArduino->getChipSize());
        log(QString("Reading %1 bytes from chip...").arg(mArduino->getChipSize()));
        mArduino->readChip();
        progressBarConnection = QObject::connect(mArduino, SIGNAL(blockComplete(uint32_t)), this, SLOT(chipOperationProgressBar(uint32_t)));
        checkClearConnection = QObject::connect(mArduino, SIGNAL(readComplete(QByteArray)), this, SLOT(checkClear(QByteArray)));
    }
    else{
        log(QString("Программатор не подключен!"));
    }

}

//-----------------------------------------
//*****************************************
//-----------------------------------------
void MainWindow::on_save_file_but_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save buffer"), "",
                                                    tr("Binary (*.bin);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        if (fileName.right(4).indexOf(".bin", 0) == -1){
            fileName.append(QString(".bin"));
        }
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        file.write(bufWork);
        file.close();
        log(QString("Buffer saved to %1 file").arg(fileName));
    }
}

void MainWindow::on_open_file_but_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Open binary to buffer"), "",
                        tr("Binary (*.bin);;All Files (*)"));

        if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                                         file.errorString());
                return;
            }
            bufWork.clear();
            bufCheck.fill(0);
            bufWork.append(file.readAll());
            log(QString("Load from %1 file").arg(fileName));
            log(QString("Readed %1 bytes").arg(bufWork.count()));
            if ((uint32_t)bufWork.count() < bufSize) {
                bufWork.append((bufSize - bufWork.count()), 0xff);
            }
            if ((uint32_t)bufWork.count() < bufSize) {
                log(QString("Deleated %1 bytes").arg(bufWork.count() - bufSize));
                bufWork.resize(bufSize);
            }
            //bufferClear = false;

            //updateButtons(true, true);

            emit bufferUpdated();
        }
}
//-----------------------------------------
//*****************************************
//-----------------------------------------

void MainWindow::on_options_but_clicked()
{
    if(setting_view){
        ui->checkBox->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();
        ui->label_6->hide();
        ui->lineEdit->hide();
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->checkBox->hide();
        ui->pushButton->hide();
        ui->horizontalSlider->hide();
    }
    else{
        ui->checkBox->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->show();
        ui->label_6->show();
        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        ui->checkBox->show();
        ui->pushButton->show();
        ui->horizontalSlider->show();
    }
    setting_view = !setting_view;
}

void MainWindow::on_verticalScrollBar_sliderMoved(int position)
{
    first_line = position;
    emit bufferUpdated();
}

void MainWindow::chipOperationProgressBar(uint32_t value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{//снятие и установка галочки авто
    if(arg1 == 0){
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
    }
    else{
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);

        if(serialPort->isOpen()){
            mArduino->n_impulses = 1000;
            mArduino->length_of_impulse_mks = 40;
            mArduino->duty = 10;
            mArduino->voltage_prog = 12;
        }
    }

}

void MainWindow::on_help_but_clicked()
{
    QMessageBox::about(0, "Дидuino Программатор", "Программатор для советских ППЗУ: К155РЕ3, КР556РТ4, КР556РТ14, КР556РТ5.\n\nВерсия программы: 0.1\n\nСписок людей поддержавших проект:\n"
                       "U-M, walhi, Kavka_TSR, Voron_Kor, Dmitry Saychenko, Михаил Царёв, Кошкин Хвост,\n"
                       "Сергей Тюрюханов, Александр Драга, Андрей С., кот Обормот, Эскобар");
}
