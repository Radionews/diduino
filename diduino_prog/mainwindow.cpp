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

//----функция прорисовки открытой прошивки на экране------
void MainWindow::showFile()
{
    QString temp = "", temp2 = "";
    for(unsigned int i = first_line; i<=bufSize/16; i++){
        temp += QString("%1").arg(i*10, 7, 10, QChar('0')) + "\n";
    }
    ui->offset_row->setText(temp);
    temp = "";
    for(unsigned int i = first_line*16; i<bufSize; i++){
        temp += QString("%1").arg((int(bufFile[i])&0xff), 2, 16, QChar('0')) + " ";


        if((int(bufFile[i])&0xff)>=0x20){    temp2 += QString::fromLocal8Bit(QByteArray::fromHex(QString::number((int(bufFile[i])&0xff),16).toLocal8Bit()));}
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

    ui->label->hide();

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
    log("Подключение " + path);
    serialPort->setPortName(path);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    ui->openPort->setText("Disconnect");
    updatePortsTimer.stop();
    if (serialPort->open(QIODevice::ReadWrite)) {
        serialPort->waitForReadyRead(4000);
        QByteArray readData = serialPort->readAll();
        while (serialPort->waitForReadyRead(100)){
            readData.append(serialPort->readAll());
        }

        if (readData.indexOf("ARDUINO PROGRAMMER") != -1){
            log(QString("Программатор обнаружен"));
            mArduino = new arduino(serialPort);
            //mArduino->selectChip(arduino::NONE);
            ic_version_select(readData/*.right(readData.indexOf("ARDUINO PROGRAMMER", 0)-18)*/);
            //set_text((unsigned char*)(readData.data()), readData.length());

        }
        else{
            log(QString("Программатор не найден"));
            closeSerialPort();
        }
    } else {
        QMessageBox::critical(this, tr("Ошибка"), serialPort->errorString());
    }
}

void MainWindow::closeSerialPort()
{
    //updatePortsTimer.start();

    if (serialPort->isOpen()){
        serialPort->close();
        log(QString("Отключение..."));
        ui->openPort->setText("Connect");
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
        log("DIDUINO найдена. версия " + version);
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
    if (arg1 == "K155RE3")  {mArduino->selectChip(arduino::RE3); log("Выбрана К155РЕ3");  ui->verticalScrollBar->setMaximum(1);}
    if (arg1 == "KR556RT4") {mArduino->selectChip(arduino::RT4); log("Выбрана КR556РТ4"); ui->verticalScrollBar->setMaximum(15);}
    if (arg1 == "KR556RT14"){mArduino->selectChip(arduino::RT14);log("Выбрана КР556РТ14");ui->verticalScrollBar->setMaximum(124);}
    if (arg1 == "KR556RT5") {mArduino->selectChip(arduino::RT5); log("Выбрана КР556РТ5"); ui->verticalScrollBar->setMaximum(31);}
}

void MainWindow::resizeBuffers(uint32_t size)
{
    bufSize = size;
    bufWork.resize(bufSize);
    bufCheck.resize(bufSize);
    bufCheck.fill(0);
    for(uint32_t i = 0; i<bufSize; i++){
        if(mArduino->get_chip_selected == mArduino->RT5){ bufWork[i] = 0xff;   }
        else{                                             bufWork[i] = 0x00;   }
    }

    emit bufferUpdated();
}

void MainWindow::checkClear(QByteArray buff)
{
    uint32_t count = 0;
    QObject::disconnect(progressBarConnection);
    ui->progressBar->setValue(ui->progressBar->maximum());
    QObject::disconnect(checkClearConnection);
    for (count = 0; count < buff.length(); count++){
        if((buff[count] != (char)0x00)&&(mArduino->get_chip_selected != mArduino->RT5)){
            log(QString("Чип не пустой. Проверьте возможность программирования перед прожигом!"));
            break;
        }
        if((buff[count] != (char)0xff)&&(mArduino->get_chip_selected == mArduino->RT5)){
            log(QString("Чип не пустой. Проверьте возможность программирования перед прожигом!"));
            break;
        }
    }
    if (count >= bufSize)
        log(QString("Чип чист"));
    bufWork = buff;
    if(verify_data) verifyData();
    emit bufferUpdated();
}

void MainWindow::checkClear_2(QByteArray buff)
{
    uint32_t count = 0;
    uint32_t error_bit = 0;
    QObject::disconnect(progressBarConnection);
    ui->progressBar->setValue(ui->progressBar->maximum());
    ui->progressBar->setMaximum(buff.length());
    QObject::disconnect(checkClearConnection);
    for (count = 0; count < buff.length(); count++){
        for(uint8_t bit = 0; bit<8; bit++){
            if((((buff[count]>>bit)&0x01) == 1)&&(((bufCheck[count]>>bit)&0x01) == 0)&&(mArduino->get_chip_selected != mArduino->RT5)){
                error_bit++;
            }

            if((((buff[count]>>bit)&0x01) == 0)&&(((bufCheck[count]>>bit)&0x01) == 1)&&(mArduino->get_chip_selected == mArduino->RT5)){
                error_bit++;
            }
        }
        ui->progressBar->setValue(count);
    }
    ui->progressBar->setValue(ui->progressBar->maximum());
    if (error_bit!=0)
        log(QString("Чип не подойдет для записи! Вставьте другой чип!"));
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
    ui->progressBar->setValue(bufSize);

    if(errors_count == 0) { log(QString("Данные совпадают!"));}
    else {
        log(QString("Данные не сопадают!"));
        log(QString("Ошибка: %1.").arg(errors_count));
    }
}

void MainWindow::showVoltage()
{

}

void MainWindow::on_read_ic_but_clicked()
{
    if(serialPort->isOpen()){

        for(uint32_t i = 0; i<bufSize; i++){
            if(mArduino->get_chip_selected == mArduino->RT5){ bufWork[i] = 0xff;   }
            else{                                             bufWork[i] = 0x00;   }
        }

        ui->progressBar->setMaximum(mArduino->getChipSize());
        log(QString("Чтение %1 байт из чипа...").arg(mArduino->getChipSize()));
        mArduino->readChip();
        ui->tab_1_but->setEnabled(true);

        progressBarConnection = QObject::connect(mArduino, SIGNAL(blockComplete(uint32_t)), this, SLOT(chipOperationProgressBar(uint32_t)));
        checkClearConnection = QObject::connect(mArduino, SIGNAL(readComplete(QByteArray)), this, SLOT(checkClear(QByteArray)));

        ui->tab_1_but->setFlat(true);
        if(ui->tab_2_but->isEnabled()){
            ui->tab_2_but->setFlat(false);
        }
    }
    else{
        log(QString("Программатор не подключен!"));
    }
}

void MainWindow::on_flash_ic_but_clicked()
{
    if((serialPort->isOpen())&&(bufFile.length() != -1)){
        ui->progressBar->setMaximum(mArduino->getChipSize());
        log(QString("Прожиг %1 байт в чип...").arg(mArduino->getChipSize()));

        mArduino->writeChip(bufFile);
        progressBarConnection = QObject::connect(mArduino, SIGNAL(blockComplete(uint32_t)), this, SLOT(chipOperationProgressBar(uint32_t)));
        checkClearConnection = QObject::connect(mArduino, SIGNAL(readComplete(QByteArray)), this, SLOT(checkClear(QByteArray)));

        ui->tab_1_but->setFlat(true);
        if(ui->tab_2_but->isEnabled()){
            ui->tab_2_but->setFlat(false);
        }
    }
    else{
        log(QString("Программатор не подключен!"));
    }
}

void MainWindow::on_check_ic_but_clicked()
{//запуск сравнения данных на чипе и загруженных в основной буфер

    if((serialPort->isOpen())&&(!bufWork.isEmpty())){

        bufCheck.clear();
        bufCheck = bufWork;

        for(uint32_t i = 0; i<bufSize; i++){
            if(mArduino->get_chip_selected == mArduino->RT5){ bufWork[i] = 0xff;   }
            else{                                             bufWork[i] = 0x00;   }
        }
        verify_data = true;

        log(QString("Сравнение буфера памяти микросхемы с подключенной микросхемой"));
        ui->progressBar->setMaximum(mArduino->getChipSize());
        log(QString("Чтение %1 байт из чипа...").arg(mArduino->getChipSize()));
        mArduino->readChip();
        progressBarConnection = QObject::connect(mArduino, SIGNAL(blockComplete(uint32_t)), this, SLOT(chipOperationProgressBar(uint32_t)));
        checkClearConnection = QObject::connect(mArduino, SIGNAL(readComplete(QByteArray)), this, SLOT(checkClear(QByteArray)));

        ui->tab_1_but->setFlat(true);
        if(ui->tab_2_but->isEnabled()){
            ui->tab_2_but->setFlat(false);
        }
    }
    else{
        log(QString("Программатор не подключен!"));
    }

}

void MainWindow::on_scan_ic_but_clicked()
{//проверка возможности прошивки в микросхему
    if((serialPort->isOpen())&&(!bufFile.isEmpty())){
        resizeBuffers(bufSize);
        bufCheck.clear();
        bufCheck = bufFile;
        verify_data = true;

        log(QString("Сравнение открытой прошивки с подключенной микросхемой"));
        ui->progressBar->setMaximum(mArduino->getChipSize());
        log(QString("Чтение %1 байт из чипа...").arg(mArduino->getChipSize()));
        mArduino->readChip();
        progressBarConnection = QObject::connect(mArduino, SIGNAL(blockComplete(uint32_t)), this, SLOT(chipOperationProgressBar(uint32_t)));
        checkClearConnection = QObject::connect(mArduino, SIGNAL(readComplete(QByteArray)), this, SLOT(checkClear(QByteArray)));

        ui->tab_1_but->setFlat(true);
        if(ui->tab_2_but->isEnabled()){
            ui->tab_2_but->setFlat(false);
        }
    }
    else{
        log(QString("Программатор не подключен или файл прошивки не открыт!"));
    }

}

//-----------------------------------------
//*****************************************
//-----------------------------------------
void MainWindow::on_save_file_but_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить буфер"), "",
                                                    tr("Binary (*.bin);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        if (fileName.right(4).indexOf(".bin", 0) == -1){
            fileName.append(QString(".bin"));
        }
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Невозможно открыть файл!"),
                                     file.errorString());
            return;
        }
        file.write(bufWork);
        file.close();
        log(QString("Буфер сохранен в файл %1").arg(fileName));
    }
}

void MainWindow::on_open_file_but_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Открыть двоичный файл"), "",
                        tr("Binary (*.bin);;All Files (*)"));

        if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Невозможно открыть файл!"),
                                         file.errorString());
                return;
            }
            bufFile.clear();
            bufFile.fill(0);
            bufFile.append(file.readAll());
            log(QString("Чтение из файла %1").arg(fileName));
            log(QString("Прочитано %1 байт").arg(bufFile.count()));
            if ((uint32_t)bufFile.count() < bufSize) {
                bufFile.append((bufSize - bufFile.count()), 0xff);
            }
            if ((uint32_t)bufFile.count() < bufSize) {
                log(QString("Удалено %1 байт").arg(bufFile.count() - bufSize));
                bufFile.resize(bufSize);
            }
            //bufferClear = false;

            //updateButtons(true, true);

            ui->tab_2_but->setEnabled(true);
            ui->label->setText(fileName);
            ui->label->show();

            showFile();
            ui->tab_2_but->setFlat(true);
            if(ui->tab_1_but->isEnabled()){
                ui->tab_1_but->setFlat(false);
            }
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


void MainWindow::on_tab_2_but_clicked()
{
    showFile();
    if(ui->tab_1_but->isEnabled()){
        ui->tab_2_but->setFlat(true);
        ui->tab_1_but->setFlat(false);
    }
}

void MainWindow::on_tab_1_but_clicked()
{
    showBuf();
    if(ui->tab_2_but->isEnabled()){
        ui->tab_1_but->setFlat(true);
        ui->tab_2_but->setFlat(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(serialPort->isOpen()){
        QByteArray send_temp;
        if(ui->checkBox->isChecked()){
            send_temp.append('o');
            send_temp.append(0xE8);
            send_temp.append(0x03);
            send_temp.append(0x28);
            send_temp.append((char)NULL);
            send_temp.append(0x05);
            send_temp.append((char)NULL);
            serialPort->write(send_temp);
            send_temp.clear();
        }

        send_temp.append('o');
        send_temp.append((uint8_t)(ui->lineEdit_2->text().toInt()&0xFF));
        send_temp.append((uint8_t)((ui->lineEdit_2->text().toInt()>>8)&0xFF));

        send_temp.append((uint8_t)(ui->lineEdit->text().toInt()&0xFF));
        send_temp.append((uint8_t)((ui->lineEdit->text().toInt()>>8)&0xFF));

        send_temp.append((uint8_t)(ui->lineEdit_3->text().toInt()&0xFF));

        send_temp.append((uint8_t)ui->horizontalSlider->value());

        serialPort->write(send_temp);
        send_temp.clear();

        get_U = true;
        read_temp.clear();
        QObject::disconnect(serialDataConnection);
        serialDataConnection = QObject::connect(serialPort, SIGNAL(readyRead()), this, SLOT(recieve_U()));

    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lineEdit_4->setText(QString::number(power_U[value]));
}

void MainWindow::recieve_U()
{
    if(get_U == true){
        QByteArray send_temp;
        send_temp.append('v');
        serialPort->write(send_temp);
        get_U = false;
        return;
    }
    while (!serialPort->atEnd()) {
        read_temp.append(serialPort->read(1));
    }
    if(read_temp.indexOf("VOLTAGE: ")!=-1){
        ui->lineEdit_4->setText(read_temp.mid(read_temp.indexOf("VOLTAGE: ")+9,4));
        QObject::disconnect(serialDataConnection);
    }
}
