#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_registerButton_clicked();

    void on_loginButton_clicked();

    void on_logoutButton_clicked();

    void on_postButton_clicked();

    void post();

    void on_prietentiButton_clicked();

    void on_postari_allButton_clicked();

    void on_postari_mineButton_clicked();

    void on_searchButton_clicked();

    void on_cancelButton_clicked();

    void on_addfriendButton_clicked();

    void aceptaCerere();

    void refuzaCerere();

    void on_postari_prieteniButton_clicked();

    void on_postari_prieteni_apropiatiButton_clicked();

    void on_setariButton_clicked();

    void updateSetari();

    void on_mesajButton_clicked();

    void creazaConv();

    void submitConv();

    void adaugaInGrup();

    void stergeDinGrup();

    void selectConv();

    void sendMess();

    void showMess();

    void adaugaInGrupCreate();

    void stergeDinGrupCreate();

    void leaveConv();

    void on_adminButton_clicked();

    void Ban();
private:
    Ui::MainWindow *ui;
    void AfiseazaPost(std::string header, std::string buffer);
    void loggedForm(int v);
};
#endif // MAINWINDOW_H
