/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *posx;
    QLineEdit *posy;
    QPushButton *input;
    QPlainTextEdit *point_line_edit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *Number;
    QPushButton *delet;
    QPushButton *deletall;
    QLineEdit *car_width;
    QLineEdit *car_height;
    QPushButton *showcar;
    QPushButton *save_points_image;
    QPushButton *hide_car;
    QLineEdit *code_path_edit;
    QLabel *label_6;
    QPushButton *load;
    QLineEdit *length;
    QLabel *label_7;
    QLineEdit *number;
    QLabel *label_9;
    QPushButton *plot;
    QFrame *line;
    QFrame *line_3;
    QLabel *label_8;
    QFrame *line_4;
    QFrame *line_6;
    QFrame *line_7;
    QLabel *label_10;
    QFrame *line_8;
    QFrame *line_11;
    QFrame *line_12;
    QLabel *label_11;
    QFrame *line_13;
    QFrame *line_14;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *max_speed;
    QLabel *label_15;
    QLineEdit *kspeed;
    QFrame *line_16;
    QFrame *line_17;
    QFrame *line_18;
    QLabel *label_18;
    QFrame *line_19;
    QLineEdit *num_btw_two_points;
    QLabel *label_17;
    QLabel *label_16;
    QLineEdit *line_edit_true_height;
    QLabel *label_19;
    QLineEdit *line_edit_true_width;
    QPushButton *load_trace;
    QPushButton *input_next;
    QPushButton *load_trace_2;
    QLabel *label_20;
    QLineEdit *kspeed_2;
    QPushButton *sure;
    QPushButton *save_points;
    QPushButton *load_picture;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *comboBox_2;
    QPushButton *refresh;
    QPushButton *pushButton_open_2;
    QComboBox *comboBox_baudrate_2;
    QTextBrowser *textEdit_2;
    QLineEdit *lineEdit_send;
    QPushButton *pushButton_send;
    QCheckBox *checkBox_send_newline;
    QPushButton *pushButton_clear;
    QLineEdit *lineEdit_send_2;
    QPushButton *pushButton_send_2;
    QLineEdit *lineEdit_send_1;
    QPushButton *pushButton_send_1;
    QLineEdit *lineEdit_send_3;
    QPushButton *pushButton_send_3;
    QLineEdit *lineEdit_address;
    QLabel *label_21;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1364, 718);
        MainWindow->setMaximumSize(QSize(1388, 768));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        posx = new QLineEdit(centralWidget);
        posx->setObjectName(QString::fromUtf8("posx"));
        posx->setGeometry(QRect(810, 20, 61, 21));
        posy = new QLineEdit(centralWidget);
        posy->setObjectName(QString::fromUtf8("posy"));
        posy->setGeometry(QRect(900, 20, 61, 21));
        input = new QPushButton(centralWidget);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(790, 40, 151, 28));
        point_line_edit = new QPlainTextEdit(centralWidget);
        point_line_edit->setObjectName(QString::fromUtf8("point_line_edit"));
        point_line_edit->setGeometry(QRect(790, 100, 351, 321));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(790, 20, 16, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(880, 20, 21, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(970, 20, 61, 16));
        Number = new QLineEdit(centralWidget);
        Number->setObjectName(QString::fromUtf8("Number"));
        Number->setGeometry(QRect(1030, 20, 61, 21));
        delet = new QPushButton(centralWidget);
        delet->setObjectName(QString::fromUtf8("delet"));
        delet->setGeometry(QRect(960, 40, 151, 28));
        deletall = new QPushButton(centralWidget);
        deletall->setObjectName(QString::fromUtf8("deletall"));
        deletall->setGeometry(QRect(800, 520, 101, 31));
        car_width = new QLineEdit(centralWidget);
        car_width->setObjectName(QString::fromUtf8("car_width"));
        car_width->setGeometry(QRect(1250, 540, 81, 21));
        car_height = new QLineEdit(centralWidget);
        car_height->setObjectName(QString::fromUtf8("car_height"));
        car_height->setGeometry(QRect(1250, 560, 81, 21));
        showcar = new QPushButton(centralWidget);
        showcar->setObjectName(QString::fromUtf8("showcar"));
        showcar->setGeometry(QRect(920, 550, 101, 31));
        save_points_image = new QPushButton(centralWidget);
        save_points_image->setObjectName(QString::fromUtf8("save_points_image"));
        save_points_image->setGeometry(QRect(920, 520, 101, 31));
        hide_car = new QPushButton(centralWidget);
        hide_car->setObjectName(QString::fromUtf8("hide_car"));
        hide_car->setGeometry(QRect(1040, 550, 91, 31));
        code_path_edit = new QLineEdit(centralWidget);
        code_path_edit->setObjectName(QString::fromUtf8("code_path_edit"));
        code_path_edit->setGeometry(QRect(800, 600, 331, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(800, 580, 72, 20));
        load = new QPushButton(centralWidget);
        load->setObjectName(QString::fromUtf8("load"));
        load->setGeometry(QRect(1040, 520, 91, 31));
        length = new QLineEdit(centralWidget);
        length->setObjectName(QString::fromUtf8("length"));
        length->setGeometry(QRect(1250, 500, 81, 21));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1150, 520, 71, 21));
        number = new QLineEdit(centralWidget);
        number->setObjectName(QString::fromUtf8("number"));
        number->setGeometry(QRect(1250, 520, 81, 21));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(1150, 500, 81, 21));
        plot = new QPushButton(centralWidget);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(800, 550, 101, 31));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(1130, 10, 20, 761));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(1140, 490, 81, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(1210, 490, 51, 16));
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(1260, 490, 81, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(780, -10, 131, 20));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setGeometry(QRect(980, -10, 151, 20));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(930, 0, 72, 15));
        line_8 = new QFrame(centralWidget);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setGeometry(QRect(780, -180, 20, 671));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);
        line_11 = new QFrame(centralWidget);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setGeometry(QRect(990, 420, 151, 20));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);
        line_12 = new QFrame(centralWidget);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setGeometry(QRect(790, 420, 151, 20));
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(940, 420, 51, 16));
        line_13 = new QFrame(centralWidget);
        line_13->setObjectName(QString::fromUtf8("line_13"));
        line_13->setGeometry(QRect(780, 470, 20, 241));
        line_13->setFrameShape(QFrame::VLine);
        line_13->setFrameShadow(QFrame::Sunken);
        line_14 = new QFrame(centralWidget);
        line_14->setObjectName(QString::fromUtf8("line_14"));
        line_14->setGeometry(QRect(1130, 0, 20, 141));
        line_14->setFrameShape(QFrame::VLine);
        line_14->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(1150, 540, 71, 21));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(1150, 600, 71, 21));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(1150, 620, 71, 31));
        max_speed = new QLineEdit(centralWidget);
        max_speed->setObjectName(QString::fromUtf8("max_speed"));
        max_speed->setGeometry(QRect(1250, 580, 81, 21));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(1150, 560, 61, 21));
        kspeed = new QLineEdit(centralWidget);
        kspeed->setObjectName(QString::fromUtf8("kspeed"));
        kspeed->setGeometry(QRect(1250, 600, 81, 21));
        line_16 = new QFrame(centralWidget);
        line_16->setObjectName(QString::fromUtf8("line_16"));
        line_16->setGeometry(QRect(1130, 130, 211, 20));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);
        line_17 = new QFrame(centralWidget);
        line_17->setObjectName(QString::fromUtf8("line_17"));
        line_17->setGeometry(QRect(1330, 0, 20, 141));
        line_17->setFrameShape(QFrame::VLine);
        line_17->setFrameShadow(QFrame::Sunken);
        line_18 = new QFrame(centralWidget);
        line_18->setObjectName(QString::fromUtf8("line_18"));
        line_18->setGeometry(QRect(1130, -10, 71, 20));
        line_18->setFrameShape(QFrame::HLine);
        line_18->setFrameShadow(QFrame::Sunken);
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(1200, 0, 72, 15));
        line_19 = new QFrame(centralWidget);
        line_19->setObjectName(QString::fromUtf8("line_19"));
        line_19->setGeometry(QRect(1270, -10, 71, 20));
        line_19->setFrameShape(QFrame::HLine);
        line_19->setFrameShadow(QFrame::Sunken);
        num_btw_two_points = new QLineEdit(centralWidget);
        num_btw_two_points->setObjectName(QString::fromUtf8("num_btw_two_points"));
        num_btw_two_points->setGeometry(QRect(1240, 20, 81, 31));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(1150, 60, 91, 31));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(1150, 20, 91, 31));
        line_edit_true_height = new QLineEdit(centralWidget);
        line_edit_true_height->setObjectName(QString::fromUtf8("line_edit_true_height"));
        line_edit_true_height->setGeometry(QRect(1240, 60, 81, 31));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(1150, 100, 91, 31));
        line_edit_true_width = new QLineEdit(centralWidget);
        line_edit_true_width->setObjectName(QString::fromUtf8("line_edit_true_width"));
        line_edit_true_width->setGeometry(QRect(1240, 100, 81, 31));
        load_trace = new QPushButton(centralWidget);
        load_trace->setObjectName(QString::fromUtf8("load_trace"));
        load_trace->setGeometry(QRect(960, 70, 151, 28));
        input_next = new QPushButton(centralWidget);
        input_next->setObjectName(QString::fromUtf8("input_next"));
        input_next->setGeometry(QRect(790, 70, 151, 28));
        load_trace_2 = new QPushButton(centralWidget);
        load_trace_2->setObjectName(QString::fromUtf8("load_trace_2"));
        load_trace_2->setGeometry(QRect(1040, 490, 93, 28));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(1150, 580, 91, 21));
        kspeed_2 = new QLineEdit(centralWidget);
        kspeed_2->setObjectName(QString::fromUtf8("kspeed_2"));
        kspeed_2->setGeometry(QRect(1250, 620, 81, 21));
        sure = new QPushButton(centralWidget);
        sure->setObjectName(QString::fromUtf8("sure"));
        sure->setGeometry(QRect(1330, 620, 31, 21));
        save_points = new QPushButton(centralWidget);
        save_points->setObjectName(QString::fromUtf8("save_points"));
        save_points->setGeometry(QRect(800, 490, 101, 28));
        load_picture = new QPushButton(centralWidget);
        load_picture->setObjectName(QString::fromUtf8("load_picture"));
        load_picture->setGeometry(QRect(1060, 580, 71, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1190, 140, 31, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1180, 210, 51, 16));
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(1250, 140, 93, 21));
        refresh = new QPushButton(centralWidget);
        refresh->setObjectName(QString::fromUtf8("refresh"));
        refresh->setGeometry(QRect(1250, 170, 93, 28));
        pushButton_open_2 = new QPushButton(centralWidget);
        pushButton_open_2->setObjectName(QString::fromUtf8("pushButton_open_2"));
        pushButton_open_2->setGeometry(QRect(1140, 170, 93, 28));
        comboBox_baudrate_2 = new QComboBox(centralWidget);
        comboBox_baudrate_2->addItem(QString());
        comboBox_baudrate_2->addItem(QString());
        comboBox_baudrate_2->setObjectName(QString::fromUtf8("comboBox_baudrate_2"));
        comboBox_baudrate_2->setGeometry(QRect(1250, 210, 93, 21));
        textEdit_2 = new QTextBrowser(centralWidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(1140, 340, 201, 151));
        lineEdit_send = new QLineEdit(centralWidget);
        lineEdit_send->setObjectName(QString::fromUtf8("lineEdit_send"));
        lineEdit_send->setGeometry(QRect(1140, 230, 151, 21));
        pushButton_send = new QPushButton(centralWidget);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(1290, 230, 51, 21));
        checkBox_send_newline = new QCheckBox(centralWidget);
        checkBox_send_newline->setObjectName(QString::fromUtf8("checkBox_send_newline"));
        checkBox_send_newline->setGeometry(QRect(1140, 310, 91, 19));
        pushButton_clear = new QPushButton(centralWidget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(1250, 310, 93, 28));
        lineEdit_send_2 = new QLineEdit(centralWidget);
        lineEdit_send_2->setObjectName(QString::fromUtf8("lineEdit_send_2"));
        lineEdit_send_2->setGeometry(QRect(1140, 270, 151, 21));
        pushButton_send_2 = new QPushButton(centralWidget);
        pushButton_send_2->setObjectName(QString::fromUtf8("pushButton_send_2"));
        pushButton_send_2->setGeometry(QRect(1290, 270, 51, 21));
        lineEdit_send_1 = new QLineEdit(centralWidget);
        lineEdit_send_1->setObjectName(QString::fromUtf8("lineEdit_send_1"));
        lineEdit_send_1->setGeometry(QRect(1140, 250, 151, 21));
        pushButton_send_1 = new QPushButton(centralWidget);
        pushButton_send_1->setObjectName(QString::fromUtf8("pushButton_send_1"));
        pushButton_send_1->setGeometry(QRect(1290, 250, 51, 21));
        lineEdit_send_3 = new QLineEdit(centralWidget);
        lineEdit_send_3->setObjectName(QString::fromUtf8("lineEdit_send_3"));
        lineEdit_send_3->setGeometry(QRect(1140, 290, 151, 21));
        pushButton_send_3 = new QPushButton(centralWidget);
        pushButton_send_3->setObjectName(QString::fromUtf8("pushButton_send_3"));
        pushButton_send_3->setGeometry(QRect(1290, 290, 51, 21));
        lineEdit_address = new QLineEdit(centralWidget);
        lineEdit_address->setObjectName(QString::fromUtf8("lineEdit_address"));
        lineEdit_address->setGeometry(QRect(800, 460, 331, 21));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(920, 440, 81, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1364, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        input->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244", nullptr));
        label->setText(QApplication::translate("MainWindow", "X\357\274\232", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Y\357\274\232", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Number\357\274\232", nullptr));
        delet->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", nullptr));
        deletall->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        showcar->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\350\275\246", nullptr));
        save_points_image->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        hide_car->setText(QApplication::translate("MainWindow", "\351\232\220\350\227\217\350\275\246", nullptr));
        code_path_edit->setText(QApplication::translate("MainWindow", "D:\\\\qt\\\\path1.0\\\\path\\\\picture3.png", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207\350\267\257\345\276\204", nullptr));
        load->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\350\276\223\345\205\245\347\202\271", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\350\275\250\350\277\271\346\200\273\351\225\277\357\274\232", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\350\275\250\350\277\271\346\200\273\347\202\271\346\225\260\357\274\232", nullptr));
        plot->setText(QApplication::translate("MainWindow", "\351\200\237\345\272\246\346\233\262\347\272\277", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\345\214\272", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\345\214\272", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "\345\212\237\350\203\275\345\214\272", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "\350\275\246\345\255\220\345\256\275\345\272\246\357\274\232", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "\350\275\246\345\255\220\351\225\277\345\272\246\357\274\232", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\351\200\237\345\272\246\357\274\232", nullptr));
        max_speed->setText(QApplication::translate("MainWindow", "1000", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "\345\207\217\351\200\237\346\257\224\357\274\232", nullptr));
        kspeed->setText(QApplication::translate("MainWindow", "100", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226", nullptr));
        num_btw_two_points->setText(QApplication::translate("MainWindow", "40", nullptr));
#ifndef QT_NO_WHATSTHIS
        label_17->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p>\345\234\272\345\234\260\345\233\276\347\211\207\347\232\204\346\260\264\345\271\263\346\226\271\345\220\221\345\256\236\351\231\205\351\225\277\345\272\246\357\274\214\345\215\225\344\275\215m</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        label_17->setText(QApplication::translate("MainWindow", "\347\253\226\347\233\264\351\225\277\345\272\246  \357\274\232", nullptr));
#ifndef QT_NO_WHATSTHIS
        label_16->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p>\350\276\223\345\205\245\347\232\204\344\270\244\344\270\252\346\216\247\345\210\266\347\202\271\344\271\213\351\227\264\345\272\224\350\257\245\346\217\222\345\205\245\345\244\232\345\260\221\344\270\252\350\264\235\345\241\236\345\260\224\347\202\271</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        label_16->setText(QApplication::translate("MainWindow", "\346\257\217\346\256\265\347\202\271\346\225\260  \357\274\232", nullptr));
        line_edit_true_height->setText(QApplication::translate("MainWindow", "10.0", nullptr));
#ifndef QT_NO_WHATSTHIS
        label_19->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p>\345\234\272\345\234\260\345\233\276\347\211\207\347\232\204\347\253\226\347\233\264\346\226\271\345\220\221\345\256\236\351\231\205\351\225\277\345\272\246\357\274\214\345\215\225\344\275\215m</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        label_19->setText(QApplication::translate("MainWindow", "\346\260\264\345\271\263\351\225\277\345\272\246  \357\274\232", nullptr));
        line_edit_true_width->setText(QApplication::translate("MainWindow", "13.3", nullptr));
        load_trace->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\346\233\262\347\272\277", nullptr));
        input_next->setText(QApplication::translate("MainWindow", "\346\233\262\347\272\277\346\225\260+1", nullptr));
        load_trace_2->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\350\267\257\345\276\204\347\202\271", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\345\212\240\351\200\237\345\272\246\357\274\232", nullptr));
        kspeed_2->setText(QApplication::translate("MainWindow", "25000", nullptr));
        sure->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", nullptr));
        save_points->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\347\202\271\346\226\207\344\273\266", nullptr));
        load_picture->setText(QApplication::translate("MainWindow", "\350\275\275\345\205\245\345\233\276\347\211\207", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("MainWindow", "COM1", nullptr));

        refresh->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        pushButton_open_2->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        comboBox_baudrate_2->setItemText(0, QApplication::translate("MainWindow", "115200", nullptr));
        comboBox_baudrate_2->setItemText(1, QApplication::translate("MainWindow", "9600", nullptr));

        pushButton_send->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        checkBox_send_newline->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\226\260\350\241\214", nullptr));
        pushButton_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        pushButton_send_2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        pushButton_send_1->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        pushButton_send_3->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        lineEdit_address->setText(QApplication::translate("MainWindow", "D:\\\\robocon\\\\trace.txt", nullptr));
        label_21->setText(QApplication::translate("MainWindow", "\347\202\271\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
