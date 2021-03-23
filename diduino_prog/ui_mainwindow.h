/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *buttons_layout;
    QPushButton *open_file_but;
    QPushButton *save_file_but;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *read_ic_but;
    QPushButton *check_ic_but;
    QPushButton *scan_ic_but;
    QPushButton *flash_ic_but;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *options_but;
    QPushButton *help_but;
    QPushButton *online_but;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *tab_body;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *port_comboBox;
    QPushButton *openPort;
    QComboBox *ic_comboBox;
    QSpacerItem *horizontalSpacer_11;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QSlider *horizontalSlider;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *tab_1_but;
    QPushButton *tab_2_but;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_8;
    QLabel *offset;
    QSpacerItem *verticalSpacer_3;
    QLabel *offset_row;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *offset_line;
    QSpacerItem *horizontalSpacer_7;
    QTextEdit *text_out;
    QVBoxLayout *verticalLayout_6;
    QLabel *decode_head;
    QTextEdit *decoded;
    QSpacerItem *horizontalSpacer_9;
    QScrollBar *verticalScrollBar;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *status_floor;
    QProgressBar *progressBar;
    QTextBrowser *status_text_out;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(993, 701);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        buttons_layout = new QHBoxLayout();
        buttons_layout->setObjectName(QString::fromUtf8("buttons_layout"));
        open_file_but = new QPushButton(centralwidget);
        open_file_but->setObjectName(QString::fromUtf8("open_file_but"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ico/open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        open_file_but->setIcon(icon);
        open_file_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(open_file_but);

        save_file_but = new QPushButton(centralwidget);
        save_file_but->setObjectName(QString::fromUtf8("save_file_but"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("ico/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        save_file_but->setIcon(icon1);
        save_file_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(save_file_but);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        buttons_layout->addItem(horizontalSpacer_3);

        read_ic_but = new QPushButton(centralwidget);
        read_ic_but->setObjectName(QString::fromUtf8("read_ic_but"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("ico/ico.ico"), QSize(), QIcon::Normal, QIcon::Off);
        read_ic_but->setIcon(icon2);
        read_ic_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(read_ic_but);

        check_ic_but = new QPushButton(centralwidget);
        check_ic_but->setObjectName(QString::fromUtf8("check_ic_but"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("ico/check.ico"), QSize(), QIcon::Normal, QIcon::Off);
        check_ic_but->setIcon(icon3);
        check_ic_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(check_ic_but);

        scan_ic_but = new QPushButton(centralwidget);
        scan_ic_but->setObjectName(QString::fromUtf8("scan_ic_but"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("ico/scan.ico"), QSize(), QIcon::Normal, QIcon::Off);
        scan_ic_but->setIcon(icon4);
        scan_ic_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(scan_ic_but);

        flash_ic_but = new QPushButton(centralwidget);
        flash_ic_but->setObjectName(QString::fromUtf8("flash_ic_but"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("ico/burn.ico"), QSize(), QIcon::Normal, QIcon::Off);
        flash_ic_but->setIcon(icon5);
        flash_ic_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(flash_ic_but);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        buttons_layout->addItem(horizontalSpacer_4);

        options_but = new QPushButton(centralwidget);
        options_but->setObjectName(QString::fromUtf8("options_but"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("ico/options.ico"), QSize(), QIcon::Normal, QIcon::Off);
        options_but->setIcon(icon6);
        options_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(options_but);

        help_but = new QPushButton(centralwidget);
        help_but->setObjectName(QString::fromUtf8("help_but"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("ico/help.ico"), QSize(), QIcon::Normal, QIcon::Off);
        help_but->setIcon(icon7);
        help_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(help_but);

        online_but = new QPushButton(centralwidget);
        online_but->setObjectName(QString::fromUtf8("online_but"));
        online_but->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("ico/online.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon8.addFile(QString::fromUtf8("E:/PROJECTS/online.ico"), QSize(), QIcon::Normal, QIcon::On);
        icon8.addFile(QString::fromUtf8("ico/offline.ico"), QSize(), QIcon::Disabled, QIcon::Off);
        icon8.addFile(QString::fromUtf8("ico/offline.ico"), QSize(), QIcon::Disabled, QIcon::On);
        online_but->setIcon(icon8);
        online_but->setIconSize(QSize(48, 48));

        buttons_layout->addWidget(online_but);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        buttons_layout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttons_layout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(buttons_layout);


        verticalLayout->addLayout(verticalLayout_2);

        tab_body = new QVBoxLayout();
        tab_body->setObjectName(QString::fromUtf8("tab_body"));
        tab_body->setSizeConstraint(QLayout::SetDefaultConstraint);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        tab_body->addWidget(line_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        port_comboBox = new QComboBox(centralwidget);
        port_comboBox->setObjectName(QString::fromUtf8("port_comboBox"));
        port_comboBox->setEditable(false);

        horizontalLayout_4->addWidget(port_comboBox);

        openPort = new QPushButton(centralwidget);
        openPort->setObjectName(QString::fromUtf8("openPort"));

        horizontalLayout_4->addWidget(openPort);

        ic_comboBox = new QComboBox(centralwidget);
        ic_comboBox->setObjectName(QString::fromUtf8("ic_comboBox"));

        horizontalLayout_4->addWidget(ic_comboBox);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);


        tab_body->addLayout(horizontalLayout_4);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        tab_body->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setMinimumSize(QSize(50, 0));
        lineEdit_2->setReadOnly(false);

        horizontalLayout_5->addWidget(lineEdit_2);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMinimumSize(QSize(50, 0));
        lineEdit->setReadOnly(false);

        horizontalLayout_5->addWidget(lineEdit);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);
        lineEdit_3->setMinimumSize(QSize(50, 0));
        lineEdit_3->setReadOnly(false);

        horizontalLayout_5->addWidget(lineEdit_3);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setEnabled(false);
        lineEdit_4->setMinimumSize(QSize(50, 0));
        lineEdit_4->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEdit_4);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimumSize(QSize(100, 0));
        horizontalSlider->setMaximum(7);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBothSides);

        horizontalLayout_5->addWidget(horizontalSlider);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setChecked(true);

        horizontalLayout_5->addWidget(checkBox);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        horizontalSpacer_10 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);


        tab_body->addLayout(horizontalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        tab_1_but = new QPushButton(centralwidget);
        tab_1_but->setObjectName(QString::fromUtf8("tab_1_but"));
        tab_1_but->setEnabled(false);

        horizontalLayout->addWidget(tab_1_but);

        tab_2_but = new QPushButton(centralwidget);
        tab_2_but->setObjectName(QString::fromUtf8("tab_2_but"));
        tab_2_but->setEnabled(false);
        tab_2_but->setFlat(false);

        horizontalLayout->addWidget(tab_2_but);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout);


        tab_body->addLayout(verticalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setSizeConstraint(QLayout::SetMinimumSize);
        offset = new QLabel(centralwidget);
        offset->setObjectName(QString::fromUtf8("offset"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(offset->sizePolicy().hasHeightForWidth());
        offset->setSizePolicy(sizePolicy2);
        offset->setMinimumSize(QSize(70, 20));
        offset->setMaximumSize(QSize(70, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(12);
        font.setStyleStrategy(QFont::PreferAntialias);
        offset->setFont(font);
        offset->setAutoFillBackground(false);
        offset->setAlignment(Qt::AlignCenter);
        offset->setWordWrap(false);

        verticalLayout_8->addWidget(offset);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_3);

        offset_row = new QLabel(centralwidget);
        offset_row->setObjectName(QString::fromUtf8("offset_row"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(offset_row->sizePolicy().hasHeightForWidth());
        offset_row->setSizePolicy(sizePolicy3);
        offset_row->setMinimumSize(QSize(70, 0));
        offset_row->setMaximumSize(QSize(70, 16777215));
        offset_row->setFont(font);
        offset_row->setAutoFillBackground(false);
        offset_row->setScaledContents(false);
        offset_row->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        offset_row->setWordWrap(true);

        verticalLayout_8->addWidget(offset_row);

        horizontalSpacer_8 = new QSpacerItem(75, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_8->addItem(horizontalSpacer_8);


        horizontalLayout_3->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        offset_line = new QLabel(centralwidget);
        offset_line->setObjectName(QString::fromUtf8("offset_line"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(offset_line->sizePolicy().hasHeightForWidth());
        offset_line->setSizePolicy(sizePolicy4);
        offset_line->setMinimumSize(QSize(240, 20));
        offset_line->setFont(font);
        offset_line->setAutoFillBackground(false);

        horizontalLayout_2->addWidget(offset_line);

        horizontalSpacer_7 = new QSpacerItem(5, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);


        verticalLayout_7->addLayout(horizontalLayout_2);

        text_out = new QTextEdit(centralwidget);
        text_out->setObjectName(QString::fromUtf8("text_out"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(text_out->sizePolicy().hasHeightForWidth());
        text_out->setSizePolicy(sizePolicy5);
        text_out->setMinimumSize(QSize(245, 0));
        text_out->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier New"));
        font1.setPointSize(12);
        text_out->setFont(font1);
        text_out->setFrameShape(QFrame::NoFrame);
        text_out->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text_out->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text_out->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        text_out->setUndoRedoEnabled(false);
        text_out->setLineWrapMode(QTextEdit::NoWrap);
        text_out->setReadOnly(true);

        verticalLayout_7->addWidget(text_out);


        horizontalLayout_3->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetDefaultConstraint);
        decode_head = new QLabel(centralwidget);
        decode_head->setObjectName(QString::fromUtf8("decode_head"));
        sizePolicy1.setHeightForWidth(decode_head->sizePolicy().hasHeightForWidth());
        decode_head->setSizePolicy(sizePolicy1);
        decode_head->setMinimumSize(QSize(100, 20));
        decode_head->setFont(font);
        decode_head->setAutoFillBackground(false);
        decode_head->setFrameShadow(QFrame::Plain);

        verticalLayout_6->addWidget(decode_head);

        decoded = new QTextEdit(centralwidget);
        decoded->setObjectName(QString::fromUtf8("decoded"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(decoded->sizePolicy().hasHeightForWidth());
        decoded->setSizePolicy(sizePolicy6);
        decoded->setMinimumSize(QSize(100, 0));
        decoded->setFont(font1);
        decoded->setFrameShape(QFrame::NoFrame);
        decoded->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        decoded->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_6->addWidget(decoded);


        horizontalLayout_3->addLayout(verticalLayout_6);

        horizontalSpacer_9 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        verticalScrollBar = new QScrollBar(centralwidget);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(verticalScrollBar->sizePolicy().hasHeightForWidth());
        verticalScrollBar->setSizePolicy(sizePolicy7);
        verticalScrollBar->setMinimumSize(QSize(25, 0));
        verticalScrollBar->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette;
        QBrush brush(QColor(51, 51, 51, 0));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(68, 68, 68, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        verticalScrollBar->setPalette(palette);
        verticalScrollBar->setAutoFillBackground(true);
        verticalScrollBar->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(verticalScrollBar);


        tab_body->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(tab_body);

        verticalSpacer_2 = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);

        status_floor = new QVBoxLayout();
        status_floor->setObjectName(QString::fromUtf8("status_floor"));
        status_floor->setSizeConstraint(QLayout::SetDefaultConstraint);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setValue(100);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(true);

        status_floor->addWidget(progressBar);

        status_text_out = new QTextBrowser(centralwidget);
        status_text_out->setObjectName(QString::fromUtf8("status_text_out"));
        QSizePolicy sizePolicy8(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(status_text_out->sizePolicy().hasHeightForWidth());
        status_text_out->setSizePolicy(sizePolicy8);
        status_text_out->setMinimumSize(QSize(0, 50));
        status_text_out->setMaximumSize(QSize(16777215, 50));

        status_floor->addWidget(status_text_out);


        verticalLayout->addLayout(status_floor);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 993, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        open_file_but->setText(QString());
        save_file_but->setText(QString());
        read_ic_but->setText(QString());
        check_ic_but->setText(QString());
        scan_ic_but->setText(QString());
        flash_ic_but->setText(QString());
        options_but->setText(QString());
        help_but->setText(QString());
        online_but->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\201\320\270\321\217 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217 0.1", nullptr));
        openPort->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\270\320\274\320\277\321\203\320\273\321\214\321\201\320\276\320\262", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "1000", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\270\320\274\320\277\321\203\320\273\321\214\321\201\320\260 \320\267\320\260\320\277\320\270\321\201\320\270, \320\274\320\272\321\201", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "40", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\270\320\265 %", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\320\265, \320\222", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\260\320\262\321\202\320\276", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        tab_1_but->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\320\274\321\217\321\202\321\214 \320\274\320\270\320\272\321\200\320\276\321\201\321\205\320\265\320\274\321\213", nullptr));
        tab_2_but->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\320\260\321\217 \320\277\321\200\320\276\321\210\320\270\320\262\320\272\320\260", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "FileName.bin", nullptr));
        offset->setText(QCoreApplication::translate("MainWindow", "Offset", nullptr));
        offset_row->setText(QString());
        offset_line->setText(QCoreApplication::translate("MainWindow", "00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15", nullptr));
        decode_head->setText(QCoreApplication::translate("MainWindow", "Decode text", nullptr));
        status_text_out->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
