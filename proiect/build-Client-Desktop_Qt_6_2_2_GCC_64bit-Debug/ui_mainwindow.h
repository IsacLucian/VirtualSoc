/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *loginEmail;
    QLineEdit *loginParola;
    QPushButton *loginButton;
    QLabel *registerLabel;
    QLabel *postariLabel;
    QLineEdit *registerParola;
    QLineEdit *registerUsername;
    QLineEdit *registerEmail;
    QLineEdit *registerNume;
    QLineEdit *registerPrenume;
    QLineEdit *registerConfirm;
    QPushButton *registerButton;
    QLabel *errLabel;
    QLabel *usernameLabel;
    QPushButton *logoutButton;
    QPushButton *setariButton;
    QPushButton *prietentiButton;
    QPushButton *mesajButton;
    QPushButton *postButton;
    QPushButton *postari_allButton;
    QPushButton *postari_mineButton;
    QPushButton *postari_prieteniButton;
    QPushButton *postari_prieteni_apropiatiButton;
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QPushButton *cancelButton;
    QPushButton *addfriendButton;
    QLabel *searchLabel;
    QScrollArea *postBrowser;
    QWidget *scrollAreaWidgetContents;
    QPushButton *adminButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1000, 606);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(114, 159, 207, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(196, 225, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(155, 192, 231, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(57, 79, 103, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(76, 106, 138, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(184, 207, 231, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush9(QColor(239, 239, 239, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush6);
        QBrush brush10(QColor(202, 202, 202, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        QBrush brush11(QColor(159, 159, 159, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        QBrush brush12(QColor(184, 184, 184, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        QBrush brush13(QColor(118, 118, 118, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush13);
        QBrush brush14(QColor(247, 247, 247, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush14);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush15(QColor(177, 177, 177, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush15);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush14);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        MainWindow->setPalette(palette);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        loginEmail = new QLineEdit(centralwidget);
        loginEmail->setObjectName(QString::fromUtf8("loginEmail"));
        loginEmail->setGeometry(QRect(810, 10, 171, 22));
        loginParola = new QLineEdit(centralwidget);
        loginParola->setObjectName(QString::fromUtf8("loginParola"));
        loginParola->setGeometry(QRect(630, 10, 171, 22));
        loginParola->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(540, 10, 80, 23));
        registerLabel = new QLabel(centralwidget);
        registerLabel->setObjectName(QString::fromUtf8("registerLabel"));
        registerLabel->setGeometry(QRect(720, 110, 111, 31));
        QFont font;
        font.setPointSize(15);
        registerLabel->setFont(font);
        postariLabel = new QLabel(centralwidget);
        postariLabel->setObjectName(QString::fromUtf8("postariLabel"));
        postariLabel->setGeometry(QRect(30, 60, 71, 16));
        QFont font1;
        font1.setPointSize(14);
        postariLabel->setFont(font1);
        registerParola = new QLineEdit(centralwidget);
        registerParola->setObjectName(QString::fromUtf8("registerParola"));
        registerParola->setGeometry(QRect(690, 270, 171, 22));
        registerParola->setEchoMode(QLineEdit::Password);
        registerParola->setAlignment(Qt::AlignCenter);
        registerUsername = new QLineEdit(centralwidget);
        registerUsername->setObjectName(QString::fromUtf8("registerUsername"));
        registerUsername->setGeometry(QRect(690, 150, 171, 22));
        registerUsername->setLayoutDirection(Qt::LeftToRight);
        registerUsername->setAlignment(Qt::AlignCenter);
        registerEmail = new QLineEdit(centralwidget);
        registerEmail->setObjectName(QString::fromUtf8("registerEmail"));
        registerEmail->setGeometry(QRect(690, 240, 171, 22));
        registerEmail->setAlignment(Qt::AlignCenter);
        registerNume = new QLineEdit(centralwidget);
        registerNume->setObjectName(QString::fromUtf8("registerNume"));
        registerNume->setGeometry(QRect(690, 181, 171, 21));
        registerNume->setAlignment(Qt::AlignCenter);
        registerPrenume = new QLineEdit(centralwidget);
        registerPrenume->setObjectName(QString::fromUtf8("registerPrenume"));
        registerPrenume->setGeometry(QRect(690, 210, 171, 22));
        registerPrenume->setAlignment(Qt::AlignCenter);
        registerConfirm = new QLineEdit(centralwidget);
        registerConfirm->setObjectName(QString::fromUtf8("registerConfirm"));
        registerConfirm->setGeometry(QRect(690, 300, 171, 22));
        registerConfirm->setLayoutDirection(Qt::LeftToRight);
        registerConfirm->setMaxLength(32765);
        registerConfirm->setEchoMode(QLineEdit::Password);
        registerConfirm->setAlignment(Qt::AlignCenter);
        registerButton = new QPushButton(centralwidget);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        registerButton->setGeometry(QRect(730, 340, 80, 23));
        errLabel = new QLabel(centralwidget);
        errLabel->setObjectName(QString::fromUtf8("errLabel"));
        errLabel->setGeometry(QRect(570, 50, 411, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush14);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush14);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        errLabel->setPalette(palette1);
        errLabel->setAlignment(Qt::AlignCenter);
        usernameLabel = new QLabel(centralwidget);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        usernameLabel->setEnabled(true);
        usernameLabel->setGeometry(QRect(630, 10, 361, 21));
        QFont font2;
        font2.setPointSize(10);
        usernameLabel->setFont(font2);
        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));
        logoutButton->setGeometry(QRect(540, 10, 80, 23));
        setariButton = new QPushButton(centralwidget);
        setariButton->setObjectName(QString::fromUtf8("setariButton"));
        setariButton->setGeometry(QRect(580, 70, 80, 23));
        prietentiButton = new QPushButton(centralwidget);
        prietentiButton->setObjectName(QString::fromUtf8("prietentiButton"));
        prietentiButton->setGeometry(QRect(680, 70, 80, 23));
        mesajButton = new QPushButton(centralwidget);
        mesajButton->setObjectName(QString::fromUtf8("mesajButton"));
        mesajButton->setGeometry(QRect(780, 70, 91, 23));
        postButton = new QPushButton(centralwidget);
        postButton->setObjectName(QString::fromUtf8("postButton"));
        postButton->setGeometry(QRect(890, 70, 80, 23));
        postari_allButton = new QPushButton(centralwidget);
        postari_allButton->setObjectName(QString::fromUtf8("postari_allButton"));
        postari_allButton->setGeometry(QRect(110, 60, 51, 23));
        postari_mineButton = new QPushButton(centralwidget);
        postari_mineButton->setObjectName(QString::fromUtf8("postari_mineButton"));
        postari_mineButton->setGeometry(QRect(170, 60, 61, 23));
        postari_prieteniButton = new QPushButton(centralwidget);
        postari_prieteniButton->setObjectName(QString::fromUtf8("postari_prieteniButton"));
        postari_prieteniButton->setGeometry(QRect(240, 60, 61, 23));
        postari_prieteni_apropiatiButton = new QPushButton(centralwidget);
        postari_prieteni_apropiatiButton->setObjectName(QString::fromUtf8("postari_prieteni_apropiatiButton"));
        postari_prieteni_apropiatiButton->setGeometry(QRect(310, 60, 111, 23));
        searchEdit = new QLineEdit(centralwidget);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));
        searchEdit->setGeometry(QRect(20, 10, 221, 22));
        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(250, 10, 80, 23));
        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(250, 10, 80, 23));
        addfriendButton = new QPushButton(centralwidget);
        addfriendButton->setObjectName(QString::fromUtf8("addfriendButton"));
        addfriendButton->setGeometry(QRect(340, 10, 121, 23));
        searchLabel = new QLabel(centralwidget);
        searchLabel->setObjectName(QString::fromUtf8("searchLabel"));
        searchLabel->setGeometry(QRect(110, 60, 431, 20));
        postBrowser = new QScrollArea(centralwidget);
        postBrowser->setObjectName(QString::fromUtf8("postBrowser"));
        postBrowser->setGeometry(QRect(30, 90, 431, 461));
        postBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        postBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        postBrowser->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 429, 459));
        postBrowser->setWidget(scrollAreaWidgetContents);
        adminButton = new QPushButton(centralwidget);
        adminButton->setObjectName(QString::fromUtf8("adminButton"));
        adminButton->setGeometry(QRect(480, 70, 80, 23));
        MainWindow->setCentralWidget(centralwidget);
        registerEmail->raise();
        registerNume->raise();
        loginEmail->raise();
        loginParola->raise();
        loginButton->raise();
        registerLabel->raise();
        postariLabel->raise();
        registerParola->raise();
        registerPrenume->raise();
        registerButton->raise();
        errLabel->raise();
        registerConfirm->raise();
        registerUsername->raise();
        usernameLabel->raise();
        logoutButton->raise();
        setariButton->raise();
        prietentiButton->raise();
        mesajButton->raise();
        postButton->raise();
        postari_allButton->raise();
        postari_mineButton->raise();
        postari_prieteniButton->raise();
        postari_prieteni_apropiatiButton->raise();
        searchEdit->raise();
        searchButton->raise();
        cancelButton->raise();
        addfriendButton->raise();
        searchLabel->raise();
        postBrowser->raise();
        adminButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VirtualSoc", nullptr));
        loginEmail->setPlaceholderText(QCoreApplication::translate("MainWindow", "email", nullptr));
        loginParola->setPlaceholderText(QCoreApplication::translate("MainWindow", "parola", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "login", nullptr));
        registerLabel->setText(QCoreApplication::translate("MainWindow", "Inregistrare", nullptr));
        postariLabel->setText(QCoreApplication::translate("MainWindow", "Postari", nullptr));
        registerParola->setPlaceholderText(QCoreApplication::translate("MainWindow", "parola", nullptr));
        registerUsername->setPlaceholderText(QCoreApplication::translate("MainWindow", "username", nullptr));
        registerEmail->setPlaceholderText(QCoreApplication::translate("MainWindow", "email", nullptr));
        registerNume->setPlaceholderText(QCoreApplication::translate("MainWindow", "nume", nullptr));
        registerPrenume->setPlaceholderText(QCoreApplication::translate("MainWindow", "prenume", nullptr));
        registerConfirm->setPlaceholderText(QCoreApplication::translate("MainWindow", "confirma parola", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "submit", nullptr));
        errLabel->setText(QString());
        usernameLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "logout", nullptr));
        setariButton->setText(QCoreApplication::translate("MainWindow", "Setari", nullptr));
        prietentiButton->setText(QCoreApplication::translate("MainWindow", "Prieteni", nullptr));
        mesajButton->setText(QCoreApplication::translate("MainWindow", "Trimite mesaj", nullptr));
        postButton->setText(QCoreApplication::translate("MainWindow", "Posteaza", nullptr));
        postari_allButton->setText(QCoreApplication::translate("MainWindow", "Publice", nullptr));
        postari_mineButton->setText(QCoreApplication::translate("MainWindow", "Ale mele", nullptr));
        postari_prieteniButton->setText(QCoreApplication::translate("MainWindow", "Prieteni", nullptr));
        postari_prieteni_apropiatiButton->setText(QCoreApplication::translate("MainWindow", "Prieteni apropiati", nullptr));
        searchEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "cauta persoane", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Cautare", nullptr));
        cancelButton->setText(QCoreApplication::translate("MainWindow", "Anuleaza", nullptr));
        addfriendButton->setText(QCoreApplication::translate("MainWindow", "Cerere de prietenie", nullptr));
        searchLabel->setText(QString());
        adminButton->setText(QCoreApplication::translate("MainWindow", "Ban", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
