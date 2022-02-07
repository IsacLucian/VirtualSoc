#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QDebug>
#include <iostream>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <vector>
#include <QTextEdit>
#include <QTimer>

const int Size = 1024;
int sd, port = 2000, isLogged = 0;
std::string null = "[null]\n";  // in query adaug campuri goale

bool setari = false;
bool prieteni = false;
bool mesaje = false;
bool posteaza = false;
bool admin = false;

QLineEdit *userid;
QLineEdit *postid;
QPushButton *ban;

QTimer timer;
QScrollArea *mess;
QScrollArea *conversatii;
QScrollArea *membri;
QTextEdit *inputmess;
QPushButton *sendmess;
QPushButton *createconv;
QLineEdit *inputnume;
std::vector <std::pair<long long, std::string> > id_membri;
long long currentconv;
int prevsize;

QPushButton *submitPost;
QTextEdit *editPost;
QRadioButton *allPost;
QRadioButton *prieteniPost;
QRadioButton *apropiatiPost;

QScrollArea *cereri;
QScrollArea *prieten;

QLabel *err;
QLineEdit *changeNume;
QLineEdit *changePrenume;
QLineEdit *changeParola;
QLineEdit *changeParolaConfirm;
QCheckBox *changeProfil;
QPushButton *change;

struct
{
    long long id;
    int admin;
    int profil;
    std::string nume;
    std::string prenume;
    std::string email;
    std::string username;
}user;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    timer.setInterval(1000);

    ui->setupUi(this);
    this->setFixedSize(QSize(1000, 600));

    loggedForm(1);
    ui->adminButton->setVisible(false);
    ui->cancelButton->setVisible(false);
    ui->addfriendButton->setVisible(false);
    ui->searchLabel->setVisible(false);
    struct sockaddr_in server;

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        qDebug() << "Eroare la socket().\n";
        return;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    if(::connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1)
    {
         qDebug() << "Eroare la connect().\n";
         return;
    }

    std::string header = "postari@select";
    std::string buffer = null + null + null + "0" + "\n" + null;

    AfiseazaPost(header, buffer);
}

void MainWindow::loggedForm(int v)
{
    ui->errLabel->setText("");
    ui->registerLabel->setVisible(v);
    ui->registerButton->setVisible(v);
    ui->registerConfirm->setVisible(v);
    ui->registerEmail->setVisible(v);
    ui->registerNume->setVisible(v);
    ui->registerParola->setVisible(v);
    ui->registerPrenume->setVisible(v);
    ui->registerUsername->setVisible(v);

    ui->loginButton->setVisible(v);
    ui->loginParola->setVisible(v);
    ui->loginEmail->setVisible(v);

    ui->postari_allButton->setVisible(1 - v);
    ui->postari_mineButton->setVisible(1 - v);
    ui->postari_prieteniButton->setVisible(1 - v);
    ui->postari_prieteni_apropiatiButton->setVisible(1 - v);
    ui->mesajButton->setVisible(1 - v);
    ui->prietentiButton->setVisible(1 - v);
    ui->setariButton->setVisible(1 - v);
    ui->postButton->setVisible(1 - v);
    ui->logoutButton->setVisible(1 - v);
    ui->usernameLabel->setVisible(1 - v);
    ui->searchEdit->setVisible(1 - v);
    ui->searchButton->setVisible(1 - v);
}

MainWindow::~MainWindow()
{
    write(sd, "exit\n", sizeof("exit\n"));
    delete ui;
}

void MainWindow::on_registerButton_clicked()
{
    std::string username = (ui->registerUsername->text()).toStdString();
    std::string nume = (ui->registerNume->text()).toStdString();
    std::string prenume = (ui->registerPrenume->text()).toStdString();
    std::string email = (ui->registerEmail->text()).toStdString();
    std::string parola = (ui->registerParola->text()).toStdString();
    std::string confirm = (ui->registerConfirm->text()).toStdString();

    if(username.length() == 0 || nume.length() == 0 || prenume.length() == 0 || email.length() == 0 || parola.length() == 0 || confirm.length() == 0)
    {
        ui->errLabel->setText("Toate campurile sunt obligatorii!");
        return;
    }

    if(parola != confirm)
    {
        ui->errLabel->setText("Confirmarea parolii a fost introdusa gresit!");
        return;
    }

    auto at = std::find(email.begin(), email.end(), '@');
    auto dot = std::find(at, email.end(), '.');
    if(at == email.end() || dot == email.end())
    {
        ui->errLabel->setText("Email invalid!");
        return;
    }

    char ans[Size];
    std::string header = "user@select";
    std::string buffer = null + null + null + null + email + "\n" + null + null;    // verific daca email exista in db

    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if((std::string(ans) + "\n") != null) // exista email
    {
        ui->errLabel->setText("Email-ul este deja folosit!");
        return;
    }

    header = "user@select";
    buffer = null + null + null + null + null + null + username + "\n";    // verific daca email exista in db

    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if((std::string(ans) + "\n") != null) // exista username
    {
        loggedForm(0);
        ui->errLabel->setText("Username-ul este deja folosit!");
        return;
    }


    header = "user@insert";
    buffer = "0\n0\n" + nume + "\n" + prenume + "\n" + email + "\n" + parola + "\n" + username;

    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if(strncmp(ans, "Success", strlen("Success")) == 0)
    {
        isLogged = 1;
        user.id = std::stol(std::string(ans).substr(strlen("Success")));
        user.email = email;
        user.admin = 0;
        user.profil = 0;
        user.nume = nume;
        user.prenume = prenume;
        user.username = username;

        if(user.admin == 1)
            ui->adminButton->setVisible(true);

        //I hate my life
        loggedForm(0);
        ui->usernameLabel->setText(QString::fromStdString(std::string("Wlecome, " + user.username + " (" + user.nume + " " + user.prenume +")")));
    }
    else
    {
        ui->errLabel->setText("Eroare la inregistrare");
        return;
    }
}

void MainWindow::on_loginButton_clicked()
{
    std::string email = (ui->loginEmail->text()).toStdString();
    std::string parola = (ui->loginParola->text()).toStdString();

    if(email.length() == 0 || parola.length() == 0)
    {
        ui->errLabel->setText("Email sau parola gresita");
        return;
    }

    std::string header = "user@select";
    std::string buffer = null + null + null + null + email + "\n" + parola + "\n" + null;

    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if((std::string(ans) + "\n") == null)
    {
        ui->errLabel->setText("Email sau parola gresita");
        return;
    }
    else if(std::string(ans) == "Found")
    {
        ui->errLabel->setText("Contul este deja autentificat");
        return;
    }

    isLogged = 1;
    char* p = strtok(ans, "\n");

    user.email = email;
    while(p)
    {
        std::string x(p);
        if(strncmp(p, "username", strlen("username")) == 0)
            user.username = x.substr(x.find(':') + 1);

        if(strncmp(p, "admin", strlen("admin")) == 0)
            user.admin = std::stoi(x.substr(x.find(':') + 1));

        if(strncmp(p, "profil", strlen("profil")) == 0)
            user.profil = std::stoi(x.substr(x.find(':') + 1));

        if(strncmp(p, "nume", strlen("nume")) == 0)
            user.nume = x.substr(x.find(':') + 1);

        if(strncmp(p, "prenume", strlen("prenume")) == 0)
            user.prenume = x.substr(x.find(':') + 1);

        if(strncmp(p, "id", strlen("id")) == 0)
            user.id = std::stol(x.substr(x.find(':') + 1));

        p = strtok(NULL, "\n");
    }

    if(user.admin == 1)
        ui->adminButton->setVisible(true);

    //I hate my life
    loggedForm(0);
    ui->usernameLabel->setText(QString::fromStdString(std::string("Wlecome, " + user.username + " (" + user.nume + " " + user.prenume +")")));
}

void MainWindow::on_logoutButton_clicked()
{
    isLogged = 0;
    if(prieteni)
    {
        delete cereri;
        delete prieten;
        prieteni = false;
    }
    if(posteaza)
    {
        delete allPost;
        delete prieteniPost;
        delete apropiatiPost;
        delete submitPost;
        delete editPost;
        posteaza = false;
    }
    if(mesaje)
    {
        disconnect(&timer, &QTimer::timeout, this, &MainWindow::showMess);

        //delete timer;
        delete mess;
        delete conversatii;
        delete membri;
        delete inputmess;
        delete sendmess;
        delete createconv;
        delete inputnume;
        mesaje = false;
    }
    if(setari)
    {
        delete err;
        delete change;
        delete changeNume;
        delete changePrenume;
        delete changeParola;
        delete changeParolaConfirm;
        delete changeProfil;
        setari = false;
    }
    if(admin)
    {
        delete userid;
        delete postid;
        delete ban;
        admin = false;
    }

    loggedForm(1);
    ui->searchEdit->setEnabled(true);
    ui->addfriendButton->setVisible(false);
    ui->cancelButton->setVisible(false);
    ui->searchLabel->setVisible(false);
    ui->adminButton->setVisible(false);

    std::string msg("logout\n");
    write(sd, msg.c_str(), strlen(msg.c_str()));
    std::string header = "postari@select";
    std::string buffer = null + null + null + "0" + "\n" + null;

    AfiseazaPost(header, buffer);
}

void MainWindow::on_postButton_clicked()
{
    if(posteaza)
        return;

    posteaza = true;
    if(prieteni)
    {
        delete cereri;
        delete prieten;
        prieteni = false;
    }
    if(mesaje)
    {
        disconnect(&timer, &QTimer::timeout, this, &MainWindow::showMess);

        //delete timer;
        delete mess;
        delete conversatii;
        delete membri;
        delete inputmess;
        delete sendmess;
        delete createconv;
        delete inputnume;
        mesaje = false;
    }
    if(setari)
    {
        delete err;
        delete change;
        delete changeNume;
        delete changePrenume;
        delete changeParola;
        delete changeParolaConfirm;
        delete changeProfil;
        setari = false;
    }
    if(admin)
    {
        delete userid;
        delete postid;
        delete ban;
        admin = false;
    }

    allPost = new QRadioButton("Public", this);
    prieteniPost = new QRadioButton("Prieteni", this);
    apropiatiPost = new QRadioButton("Apropiati",this);
    allPost->move(830, 500);
    prieteniPost->move(830, 520);
    apropiatiPost->move(830, 540);
    allPost->setChecked(true);
    allPost->setVisible(true);
    prieteniPost->setVisible(true);
    apropiatiPost->setVisible(true);

    editPost = new QTextEdit(this);
    editPost->resize(390,400);
    editPost->move(580,100);
    editPost->setVisible(true);

    submitPost = new QPushButton(this);
    submitPost->setText("Submit");
    submitPost->setVisible(true);
    submitPost->resize(80, 23);
    submitPost->move(735, 520);
    QObject::connect(submitPost, &QPushButton::clicked, this, &MainWindow::post);
}

void MainWindow::post()
{
    std::string text(editPost->toPlainText().toStdString());

    std::string mod;
    if(allPost->isChecked()) mod = "0";
    else if(prieteniPost->isChecked()) mod = "1";
    else if(apropiatiPost->isChecked()) mod = "2";

    editPost->clear();
    size_t pos = 0;
    while((pos = text.find("\n", pos)) != std::string::npos)
    {
        text.replace(pos, std::string("\n").length(), std::string("[enter]"));
        pos += std::string("[enter]").length();
    }

    // YYYY-MM-DD.HH:mm:ss
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%H:%M:%S", &tstruct);

    std::string header = "postari@insert";
    std::string buffer = text + "\n" + std::to_string(user.id) + "\n" + user.username + "\n" + mod + "\n" + buf + "\n";
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

//    if(strncmp(ans, "Success", strlen("Success")) == 0)
//        qDebug() << "E bine";
}

void MainWindow::on_prietentiButton_clicked()
{
    if(prieteni)
    {
        delete cereri;
        delete prieten;
    }

    prieteni = true;
    if(posteaza)
    {
        delete allPost;
        delete prieteniPost;
        delete apropiatiPost;
        delete editPost;
        delete submitPost;
        posteaza = false;
    }
    if(mesaje)
    {
        disconnect(&timer, &QTimer::timeout, this, &MainWindow::showMess);

        //delete timer;
        delete mess;
        delete conversatii;
        delete membri;
        delete inputmess;
        delete sendmess;
        delete createconv;
        delete inputnume;
        mesaje = false;
    }
    if(setari)
    {
        delete err;
        delete change;
        delete changeNume;
        delete changePrenume;
        delete changeParola;
        delete changeParolaConfirm;
        delete changeProfil;
        setari = false;
    }
    if(admin)
    {
        delete userid;
        delete postid;
        delete ban;
        admin = false;
    }

    std::string header = "prietenii@select";
    std::string buffer = std::to_string(user.id) + "\n" + null + null;

    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    header = "prietenii@select";
    buffer = null + std::to_string(user.id) + "\n" + null;

    char ans_[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans_, 0, sizeof(ans));
    read(sd, ans_, sizeof(ans));

    strcat(ans, ans_);
    std::vector <std::tuple<long long, long long, int ,int> > pr;
    std::vector <std::pair<long long, long long> > ids_cereri;
    char *p;
    p = strtok(ans, "\n");
    int mod;
    long long id_1 = -1, id_2 = -1, id;

    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id_1:", strlen("id_1:")) == 0)
            id_1 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "id_2:", strlen("id_2:")) == 0)
            id_2 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "id:", strlen("id:")) == 0)
            id = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "close:", strlen("close:")) == 0)
            mod = std::stoi(x.substr(x.find(":") + 1));

        if(strncmp(p, "}", strlen("}")) == 0)
        {
            //0, 1, 2, 3, 4
            long long id_pr = (id_1 == user.id ? id_2 : id_1);
            if(mod == 0)
            {
                if(id_1 == user.id) ids_cereri.push_back({id_pr, id});
            }
            else pr.push_back({id_pr, id, (id_1 == user.id ? 1 : 2), mod});
        }

        p = strtok(NULL, "\n");
    }

    cereri = new QScrollArea(this);
    cereri->setGeometry(480, 120, 240, 400);
    QWidget *wgtMain = new QWidget();
    QVBoxLayout *vlay = new QVBoxLayout(wgtMain);
    for(auto x : ids_cereri)
    {
        header = "user@select#" + std::to_string(x.first);
        buffer = "";
        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        memset(ans, 0, sizeof(ans));
        read(sd, ans, sizeof(ans));

         p = strtok(ans, "\n");
         std::string username;
         while(p)
         {
             std::string x(p);
             if(strncmp(p, "username:", strlen("username:")) == 0)
                 username = x.substr(x.find(":") + 1);

             p = strtok(NULL, "\n");
         }

         QWidget *wgtSub = new QWidget();
         QHBoxLayout *hlay = new QHBoxLayout(wgtSub);

         QLabel *n = new QLabel;
         n->setText(QString::fromStdString(username));

         QPushButton *acc = new QPushButton();
         acc->setText("Accept");
         acc->setFixedSize(QSize(50, 23));
         acc->setObjectName(QString::fromStdString("acc,1:" + std::to_string(x.second)));
         connect(acc, &QPushButton::clicked, this, &MainWindow::aceptaCerere);

         QPushButton *dec = new QPushButton();
         dec->setText("Refuza");
         dec->setFixedSize(QSize(50, 23));
         dec->setObjectName(QString::fromStdString("dec:" + std::to_string(x.second)));
         connect(dec, &QPushButton::clicked, this, &MainWindow::refuzaCerere);

         hlay->addWidget(n);
         hlay->addWidget(acc);
         hlay->addWidget(dec);

         vlay->addWidget(wgtSub);
    }
    cereri->setWidget(wgtMain);
    cereri->setVisible(true);

    prieten = new QScrollArea(this);
    prieten->setGeometry(740, 120, 250, 400);

    QWidget *wgtMain_ = new QWidget();
    QVBoxLayout *vlay_ = new QVBoxLayout(wgtMain_);
    for(auto x : pr)
    {
        header = "user@select#" + std::to_string(std::get<0>(x));
        buffer = "";
        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        memset(ans, 0, sizeof(ans));
        read(sd, ans, sizeof(ans));

         p = strtok(ans, "\n");
         std::string username;
         while(p)
         {
             std::string x(p);
             if(strncmp(p, "username:", strlen("username:")) == 0)
                 username = x.substr(x.find(":") + 1);

             p = strtok(NULL, "\n");
         }

         QWidget *wgtSub = new QWidget();
         QHBoxLayout *hlay = new QHBoxLayout(wgtSub);

         QLabel *n = new QLabel;
         n->setText(QString::fromStdString(username));

         QPushButton *acc = new QPushButton();
         int val = 1;
         if(std::get<3>(x) == 1 || (std::get<2>(x) == 1 && std::get<3>(x) == 3) || (std::get<2>(x) == 2 && std::get<3>(x) == 2))
         {
             acc->setText("Adauga apropiat");
             val = std::get<2>(x) + std::get<3>(x);
         }
         else
         {
             acc->setText("Sterge apropiat");
             val = std::get<3>(x) - std::get<2>(x);
         }
         acc->setFixedSize(QSize(110, 23));
         acc->setObjectName(QString::fromStdString("acc," + std::to_string(val) + ":" + std::to_string(std::get<1>(x))));
         connect(acc, &QPushButton::clicked, this, &MainWindow::aceptaCerere);

         QPushButton *dec = new QPushButton();
         dec->setText("Sterge");
         dec->setFixedSize(QSize(50, 23));
         dec->setObjectName(QString::fromStdString("dec:" + std::to_string(std::get<1>(x))));
         connect(dec, &QPushButton::clicked, this, &MainWindow::refuzaCerere);

         hlay->addWidget(n);
         hlay->addWidget(acc);
         hlay->addWidget(dec);

         vlay_->addWidget(wgtSub);
    }

    prieten->setWidget(wgtMain_);
    prieten->setVisible(true);
}

void MainWindow::AfiseazaPost(std::string header, std::string buffer)
{
    //ui->postBrowser->clear();
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if((std::string(ans) + "\n") == null)
    {
        QWidget *wgtMain = new QWidget();
        QLabel *msj = new QLabel(wgtMain);
        msj->setText("Nu exista postari");
        ui->postBrowser->setWidget(wgtMain);
        return;
    }

    char* p = strtok(ans, "\n");
    std::string mesaj, username, data, id_user, id_post;
    std::map<std::string, std::tuple <std::string, std::string, std::string, std::string>> postari;
    while(p)
    {
        if(strncmp(p, "mesaj", strlen("mesaj")) == 0)
            mesaj = std::string(p);

        if(strncmp(p, "username", strlen("username")) == 0)
            username = std::string(p);

        if(strncmp(p, "data", strlen("data")) == 0)
            data = std::string(p);

        if(strncmp(p, "id_user", strlen("id_user")) == 0)
            id_user = std::string(p);

        if(strncmp(p, "id:", strlen("id:")) == 0)
            id_post = std::string(p);

        if(strncmp(p, "}", strlen("}")) == 0)
        {
            size_t pos = 0;
            username.replace(username.find(":", 0), std::string(":").length(), std::string(": "));
            data.replace(data.find(":", 0), std::string(":").length(), std::string(": "));
            data.replace(data.find(".", 0), std::string(".").length(), std::string("  "));
            id_user = id_user.substr(id_user.find(":") + 1);
            id_post = id_post.substr(id_post.find(":") + 1);

            mesaj.replace(mesaj.find(":", 0), std::string(":").length(), std::string(":\n       "));
            while((pos = mesaj.find("[enter]", pos)) != std::string::npos)
            {
                mesaj.replace(pos, std::string("[enter]").length(), std::string("\n       "));
                pos += std::string("\n       ").length();
            }

            postari[data] = {username, mesaj, id_user, id_post};
        }
        p = strtok(NULL, "\n");
    }


    QWidget *wgtMain = new QWidget();
    QVBoxLayout *hlay = new QVBoxLayout(wgtMain);
    for(auto it = postari.rbegin(); it != postari.rend(); it++)
    {
        QWidget *wgtSub = new QWidget();
        QVBoxLayout *hlay_ = new QVBoxLayout(wgtSub);

        if(user.admin == 1)
        {
            QLabel *post_id = new QLabel();
            post_id->setText(QString::fromStdString(std::get<3>(it->second)));

            hlay_->addWidget(post_id);
        }

        QLabel *username = new QLabel();

        username->setText(QString::fromStdString(std::get<0>(it->second) +
                                                (user.admin == 1 ? "(" + std::get<2>(it->second) + ")" : "")));
        username->setStyleSheet("QLabel {"
        "border-style: solid;"
        "border-width: 1px;"
        "border-color: black; "
        "}");
        QLabel *data = new QLabel();
        data->setText(QString::fromStdString(it->first));
        data->setStyleSheet("QLabel {"
        "border-style: solid;"
        "border-width: 1px;"
        "border-color: black; "
        "}");
        QLabel *mesaj = new QLabel();
        mesaj->setText(QString::fromStdString(std::get<1>(it->second)));
        mesaj->setStyleSheet("QLabel {"
        "border-style: solid;"
        "border-width: 1px;"
        "border-color: black; "
        "}");
        hlay_->addWidget(username);
        hlay_->addWidget(data);
        hlay_->addWidget(mesaj);

        hlay->addWidget(wgtSub);
    }

    if(postari.size() < 4)
    {
        QLabel *empt = new QLabel();
        QLabel *empt1 = new QLabel();
        QLabel *empt2 = new QLabel();
        QLabel *empt3 = new QLabel();

        hlay->addWidget(empt);
        hlay->addWidget(empt1);
        hlay->addWidget(empt2);
        hlay->addWidget(empt3);
    }

    ui->postBrowser->setWidget(wgtMain);

    //ui->postBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::on_postari_allButton_clicked()
{
    std::string header = "postari@select";
    std::string buffer = null + null + null + "0" + "\n" + null;

    AfiseazaPost(header, buffer);
}

void MainWindow::on_postari_mineButton_clicked()
{
    std::string header = "postari@select";
    std::string buffer = null + std::to_string(user.id) + "\n" + null + "0,1,2" + "\n" + null;

    AfiseazaPost(header, buffer);
}

void MainWindow::on_searchButton_clicked()
{
    std::string username(ui->searchEdit->text().toStdString());

    if(username == user.username)
    {
        QWidget *wgtMain = new QWidget();
        QLabel *msj = new QLabel(wgtMain);
        msj->setText("Actiune interzisa!");
        ui->postBrowser->setWidget(wgtMain);
        return;
    }

    ui->searchEdit->setEnabled(false);
    ui->searchButton->setVisible(false);
    ui->postari_allButton->setVisible(false);
    ui->postari_mineButton->setVisible(false);
    ui->postari_prieteniButton->setVisible(false);
    ui->postari_prieteni_apropiatiButton->setVisible(false);
    ui->searchLabel->setVisible(true);
    ui->cancelButton->setVisible(true);

    std::string header = "user@select";
    std::string buffer = null + null + null + null + null + null + username;

    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if((std::string(ans) + "\n") == null)
    {
        QWidget *wgtMain = new QWidget();
        QLabel *msj = new QLabel(wgtMain);
        msj->setText("Utilizatorul nu exista");
        ui->postBrowser->setWidget(wgtMain);
        return;
    }

    char *p = strtok(ans, "\n");
    std::string nume, prenume;
    int ispriv = 0, id = 0;
    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id:", strlen("id:")) == 0)
            id = std::stoi(x.substr(x.find(":") + 1));

        if(strncmp(p, "profil:", strlen("profil:")) == 0)
            ispriv = std::stoi(x.substr(x.find(":") + 1));

        if(strncmp(p, "nume:", strlen("nume:")) == 0)
            nume = (x.substr(x.find(":") + 1));

        if(strncmp(p, "prenume:", strlen("prenume:")) == 0)
            prenume = (x.substr(x.find(":") + 1));

        p = strtok(NULL, "\n");
    }


    ui->addfriendButton->setVisible(true);

    if(ispriv)
    {
        header = "prietenii@select";
        buffer = std::to_string(id) + "," + std::to_string(user.id) + "\n" +
                 std::to_string(id) + "," + std::to_string(user.id) + "\n" + "1,2,3,4\n";

        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        memset(ans, 0, sizeof(ans));
        read(sd, ans, sizeof(ans));

        if((std::string(ans) + "\n") == null)
        {
            QWidget *wgtMain = new QWidget();
            QLabel *msj = new QLabel(wgtMain);
            msj->setText("Profilul este privat!");
            ui->postBrowser->setWidget(wgtMain);
            return;
        }
    }

    ui->searchLabel->setText(QString::fromStdString(nume + " " + prenume));
    header = "postari@select";
    buffer = null + null + username + "\n" + "0\n" + null;
    AfiseazaPost(header, buffer);
}

void MainWindow::on_cancelButton_clicked()
{
    ui->searchEdit->setEnabled(true);
    ui->searchButton->setVisible(true);
    ui->postari_allButton->setVisible(true);
    ui->postari_mineButton->setVisible(true);
    ui->postari_prieteniButton->setVisible(true);
    ui->postari_prieteni_apropiatiButton->setVisible(true);
    ui->searchLabel->setVisible(false);
    ui->addfriendButton->setVisible(false);
    ui->cancelButton->setVisible(false);

    on_postari_allButton_clicked();
}

void MainWindow::on_addfriendButton_clicked()
{
    std::string username(ui->searchEdit->text().toStdString());

    std::string header = "user@select";
    std::string buffer = null + null + null + null + null + null + username;

    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    std::string id;
    char *p = strtok(ans, "\n");

    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id", strlen("id")) == 0)
            id = x.substr(x.find(":") + 1);

        p = strtok(NULL, "\n");
    }

    header = "prietenii@select";
    buffer = id + "," + std::to_string(user.id) + "\n" +
             id + "," + std::to_string(user.id) + "\n" + null;

    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if((std::string(ans) + "\n") != null)
    {
        ui->searchLabel->setText("Sunteti deja prieteni sau a mai fost trimisa o cerere de prietenie!");
        return;
    }

    header = "prietenii@insert";
    buffer = id + "\n" + std::to_string(user.id) + "\n" + "0\n";

    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if(strncmp(ans, "Success", strlen("Success")) == 0)
    {
        ui->searchLabel->setText("Cerere trimisa!");
        return;
    }
}

void MainWindow::aceptaCerere()
{
    QPushButton *self = qobject_cast<QPushButton *>(sender());

    std::string id(self->objectName().toStdString());
    id = id.substr(id.find(":") + 1);

    std::string mod = (self->objectName().toStdString())
                        .substr((self->objectName().toStdString()).find(",") + 1, 1);

    std::string header = "prietenii@update#" + id;
    std::string buffer =  null + null + mod +"\n";

    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    char ans[Size];
    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if(strncmp(ans, "Success", strlen("Success")) != 0)
    {
        qDebug() << ans;
        return;
    }

    // reload
    delete cereri;
    delete prieten;
    prieteni = false;
    on_prietentiButton_clicked();
}

void MainWindow::refuzaCerere()
{
    QPushButton *self = qobject_cast<QPushButton *>(sender());

    std::string id(self->objectName().toStdString());
    id = id.substr(id.find(":") + 1);

    std::string header = "prietenii@delete#" + id;
    std::string buffer = "";

    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    char ans[Size];
    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if(strncmp(ans, "Success", strlen("Success")) != 0)
    {
        qDebug() << ans;
        return;
    }

    // reload la cereri
    delete cereri;
    delete prieten;
    prieteni = false;
    on_prietentiButton_clicked();
}

void MainWindow::on_postari_prieteniButton_clicked()
{
    std::string header = "prietenii@select";
    std::string buffer = std::to_string(user.id) + "\n" + null + "1,2,3,4\n";

    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    header = "prietenii@select";
    buffer = null + std::to_string(user.id) + "\n" + "1,2,3,4\n";

    char ans_[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans_, 0, sizeof(ans));
    read(sd, ans_, sizeof(ans));

    strcat(ans, ans_);

    std::string ids("");

    char* p = strtok(ans, "\n");
    int s = 0;
    long long id_1 = -1, id_2 = -1;
    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id_1:", strlen("id_1:")) == 0)
            id_1 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "id_2:", strlen("id_2:")) == 0)
            id_2 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "}", strlen("}")) == 0)
        {
            s++;
            long long id_pr = (id_1 == user.id ? id_2 : id_1);
            ids = ids + std::to_string(id_pr) + ",";
        }

        p = strtok(NULL, "\n");
    }

    ids = ids + std::to_string(user.id);

    header = "postari@select";
    buffer = null + ids + "\n" + null + "1\n" + null;
    AfiseazaPost(header, buffer);
}

void MainWindow::on_postari_prieteni_apropiatiButton_clicked()
{
    std::string header = "prietenii@select";
    std::string buffer = std::to_string(user.id) + "\n" + null + "3,4\n";

    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    header = "prietenii@select";
    buffer = null + std::to_string(user.id) + "\n" + "2,4\n";

    char ans_[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans_, 0, sizeof(ans));
    read(sd, ans_, sizeof(ans));

    strcat(ans, ans_);

    std::string ids("");

    char* p = strtok(ans, "\n");
    int s = 0;
    long long id_1 = -1, id_2 = -1;
    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id_1:", strlen("id_1:")) == 0)
            id_1 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "id_2:", strlen("id_2:")) == 0)
            id_2 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "}", strlen("}")) == 0)
        {
            s++;
            long long id_pr = (id_1 == user.id ? id_2 : id_1);
            ids = ids + std::to_string(id_pr) + ",";
        }

        p = strtok(NULL, "\n");
    }

    ids = ids + std::to_string(user.id);

    header = "postari@select";
    buffer = null + ids + "\n" + null + "2\n" + null;
    AfiseazaPost(header, buffer);
}

void MainWindow::on_setariButton_clicked()
{
    if(setari)
        return;

    setari = true;
    if(admin)
    {
        delete userid;
        delete postid;
        delete ban;
        admin = false;
    }
    if(prieteni)
    {
        delete cereri;
        delete prieten;
        prieteni = false;
    }
    if(mesaje)
    {
        disconnect(&timer, &QTimer::timeout, this, &MainWindow::showMess);

        delete mess;
        delete conversatii;
        delete membri;
        delete inputmess;
        delete sendmess;
        delete createconv;
        delete inputnume;
        mesaje = false;
    }
    if(posteaza)
    {
        delete allPost;
        delete prieteniPost;
        delete apropiatiPost;
        delete editPost;
        delete submitPost;
        posteaza = false;
    }


    changeNume = new QLineEdit(this);
    changeNume->setGeometry(690, 150, 170, 22);
    changeNume->setText(QString::fromStdString(user.nume));
    changeNume->setPlaceholderText("Nume");
    changeNume->setAlignment(Qt::AlignCenter);
    changeNume->setVisible(true);

    changePrenume = new QLineEdit(this);
    changePrenume->setGeometry(690, 180, 170, 22);
    changePrenume->setText(QString::fromStdString(user.prenume));
    changePrenume->setPlaceholderText("Prenume");
    changePrenume->setAlignment(Qt::AlignCenter);
    changePrenume->setVisible(true);

    changeParola = new QLineEdit(this);
    changeParola->setGeometry(690, 210, 170, 22);
    changeParola->setPlaceholderText("Parola");
    changeParola->setAlignment(Qt::AlignCenter);
    changeParola->setVisible(true);

    changeParolaConfirm = new QLineEdit(this);
    changeParolaConfirm->setGeometry(690, 240, 170, 22);
    changeParolaConfirm->setPlaceholderText("Confirma Parola");
    changeParolaConfirm->setAlignment(Qt::AlignCenter);
    changeParolaConfirm->setVisible(true);

    changeProfil = new QCheckBox(this);
    changeProfil->setText("Profil privat");
    changeProfil->setChecked(user.profil);
    changeProfil->move(690, 270);
    changeProfil->setVisible(true);

    err = new QLabel(this);
    err->setGeometry(670, 330, 190, 22);
    err->setAlignment(Qt::AlignCenter);
    err->setText("");
    err->setVisible(true);

    change = new QPushButton(this);
    change->setText("Submit");
    change->setGeometry(730, 300, 80, 23);
    change->setVisible(true);

    connect(change, &QPushButton::clicked, this, &MainWindow::updateSetari);
}

void MainWindow::updateSetari()
{
    std::string nume = changeNume->text().toStdString();
    std::string prenume = changePrenume->text().toStdString();
    std::string parola = changeParola->text().toStdString();
    std::string parolaconfirm = changeParolaConfirm->text().toStdString();
    int privat = changeProfil->isChecked();

    if(nume.length() == 0)
    {
        err->setText("Campul nume este obligatoriu!");
        return;
    }

    if(prenume.length() == 0)
    {
        err->setText("Campul prenume este obligatoriu!");
        return;
    }

    if(parola.length() > 0 || parolaconfirm.length() > 0)
    {
        if(parola != parolaconfirm)
        {
            err->setText("Parolele nu se potrivesc");
            return;
        }
    }
    std::string header = "user@update#" + std::to_string(user.id);
    std::string buffer = null + std::to_string(privat) + "\n" + nume + "\n" + prenume + "\n" + null + (parola.length() == 0 ? null : (parola + "\n")) + null;

    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    changeParola->setText("");
    changeParolaConfirm->setText("");
    user.nume = nume;
    user.prenume = prenume;
    user.profil = privat;

    if(strncmp(ans, "Success", strlen("Success")) != 0)
    {
        qDebug() << ans;
    }
}

void MainWindow::on_mesajButton_clicked()
{
    if(mesaje)
    {
        delete mess;
        delete conversatii;
        delete membri;
        delete inputmess;
        delete sendmess;
        delete createconv;
        delete inputnume;
    }

    mesaje = true;
    if(admin)
    {
        delete userid;
        delete postid;
        delete ban;
        admin = false;
    }
    if(posteaza)
    {
        delete allPost;
        delete prieteniPost;
        delete apropiatiPost;
        delete editPost;
        delete submitPost;
        posteaza = false;
    }
    if(prieteni)
    {
        delete cereri;
        delete prieten;
        prieteni = false;
    }
    if(setari)
    {
        delete err;
        delete change;
        delete changeNume;
        delete changePrenume;
        delete changeParola;
        delete changeParolaConfirm;
        delete changeProfil;
        setari = false;
    }

    mess = new QScrollArea(this);
    mess->setGeometry(480, 120, 300, 440);
    mess->setVisible(true);

    inputmess = new QTextEdit(this);
    inputmess->setGeometry(480, 560, 250, 30);
    inputmess->setVisible(true);
    inputmess->setEnabled(false);

    sendmess = new QPushButton(this);
    sendmess->setGeometry(730, 560, 50, 30);
    sendmess->setText("Submit");
    sendmess->setVisible(true);
    sendmess->setEnabled(false);

    conversatii = new QScrollArea(this);
    conversatii->setGeometry(790, 120, 180, 230);
    conversatii->setVisible(true);

    membri = new QScrollArea(this);
    membri->setGeometry(790, 360, 180, 200);
    membri->setVisible(true);

    createconv = new QPushButton(this);
    createconv->setGeometry(790, 560, 80, 23);
    createconv->setVisible(true);
    createconv->setText("Creaza");

    inputnume = new QLineEdit(this);
    inputnume->setGeometry(880, 560, 100, 23);
    connect(createconv, &QPushButton::clicked, this, &MainWindow::creazaConv);


    std::string header = "membri@select";
    std::string buffer = null + std::to_string(user.id) + "\n" + null;
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    char *p = strtok(ans, "\n");
    std::vector <long long> id_grups;

    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id_grup:", strlen("id_grup:")) == 0)
            id_grups.push_back(std::stol(x.substr(x.find(":") + 1)));
        p = strtok(NULL, "\n");
    }

    QWidget *wgtGrup = new QWidget();
    QVBoxLayout *vlay = new QVBoxLayout(wgtGrup);
    for(auto i : id_grups)
    {
        header = "grupuri@select#" + std::to_string(i);
        buffer = "";
        char ans[Size];
        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        memset(ans, 0, sizeof(ans));
        read(sd, ans, sizeof(ans));
        std::string nume;
        char *p = strtok(ans, "\n");
        while(p)
        {
            std::string x(p);
            if(strncmp(p, "nume:", strlen("nume:")) == 0)
                nume = x.substr(x.find(":") + 1);

            p = strtok(NULL, "\n");
        }

        QWidget *wgtSub = new QWidget();
        QHBoxLayout *hlay = new QHBoxLayout(wgtSub);
        QPushButton *selectconv = new QPushButton();
        selectconv->setText(QString::fromStdString(nume));
        selectconv->setObjectName(QString::fromStdString("Buton:" + std::to_string(i)));
        selectconv->setVisible(true);
        connect(selectconv, &QPushButton::clicked, this, &MainWindow::selectConv);

        QPushButton *leaveconv = new QPushButton();
        leaveconv->setText("Paraseste");
        leaveconv->setObjectName(QString::fromStdString("Buton," + std::to_string(user.id) + ":" + std::to_string(i)));
        leaveconv->setVisible(true);
        connect(leaveconv, &QPushButton::clicked, this, &MainWindow::leaveConv);
        hlay->addWidget(selectconv);
        hlay->addWidget(leaveconv);

        vlay->addWidget(wgtSub);
    }

    conversatii->setWidget(wgtGrup);
    connect(sendmess, &QPushButton::clicked, this, &MainWindow::sendMess);

}

void MainWindow::creazaConv()
{
    disconnect(&timer, &QTimer::timeout, this, &MainWindow::showMess);

    QWidget *wgt = new QWidget();
    mess->setWidget(wgt);

    inputmess->setEnabled(false);
    sendmess->setEnabled(false);
    std::string header = "prietenii@select";
    std::string buffer = std::to_string(user.id) + "\n" + null + "1,2,3,4";
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    header = "prietenii@select";
    buffer = null + std::to_string(user.id) + "\n" + "1,2,3,4";

    char ans_[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans_, 0, sizeof(ans));
    read(sd, ans_, sizeof(ans));

    strcat(ans, ans_);
    char *p;
    p = strtok(ans, "\n");
    long long id_1 = -1, id_2 = -1;

    std::vector <long long> ids_pr;
    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id_1:", strlen("id_1:")) == 0)
            id_1 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "id_2:", strlen("id_2:")) == 0)
            id_2 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "}", strlen("}")) == 0)
        {
            long long id_pr = (id_1 == user.id ? id_2 : id_1);
            ids_pr.push_back(id_pr);

        }

        p = strtok(NULL, "\n");
    }
    id_membri.clear();
    QWidget *wgtPrieteni = new QWidget();
    QVBoxLayout *vlay = new QVBoxLayout(wgtPrieteni);
    for(auto i : ids_pr)
    {
        header = "user@select#" + std::to_string(i);
        buffer = "";
        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        char rec[Size];
        memset(rec, 0, sizeof(rec));
        read(sd, rec, sizeof(rec));

         char *q = strtok(rec, "\n");
         std::string username;
         while(q)
         {
             std::string x(q);
             if(strncmp(q, "username:", strlen("username:")) == 0)
                 username = x.substr(x.find(":") + 1);

             q = strtok(NULL, "\n");
         }
         QWidget *wgtSub = new QWidget();
         QHBoxLayout *hlay = new QHBoxLayout(wgtSub);

         QLabel *l = new QLabel();
         l->setText(QString::fromStdString(username));
         l->setVisible(true);

         QPushButton *insert = new QPushButton();
         insert->setText("Adauga");
         insert->setObjectName(QString::fromStdString("Buton," + username + ":" + std::to_string(i)));
         insert->setVisible(true);
         connect(insert, &QPushButton::clicked, this, &MainWindow::adaugaInGrupCreate);

         hlay->addWidget(l);
         hlay->addWidget(insert);

         vlay->addWidget(wgtSub);
    }
    membri->setWidget(wgtPrieteni);

    disconnect(createconv, &QPushButton::clicked, this, &MainWindow::creazaConv);
    connect(createconv, &QPushButton::clicked, this, &MainWindow::submitConv);
    createconv->setText("Submit");
    inputnume->setVisible(true);
}

void MainWindow::submitConv()
{
    std::string nume(inputnume->text().toStdString());
    if(nume.size() == 0 || id_membri.size() == 0)
    {
        QWidget *wgt = new QWidget();
        membri->setWidget(wgt);
        disconnect(createconv, &QPushButton::clicked, this, &MainWindow::submitConv);
        connect(createconv, &QPushButton::clicked, this, &MainWindow::creazaConv);
        createconv->setText("Creaza");
        inputnume->setVisible(false);
        mesaje = false;
        delete mess;
        delete conversatii;
        delete membri;
        delete inputmess;
        delete sendmess;
        delete createconv;
        delete inputnume;
        on_mesajButton_clicked();
        return;
    }

    std::string header = "grupuri@insert";
    std::string buffer = nume + "\n";
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    if(strncmp(ans, "Success", strlen("Success")) != 0)
        return;

    header = "grupuri@select";
    buffer = nume + "\n";
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    char *p = strtok(ans, "\n");
    long long id = -1;
    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id:", strlen("id:")) == 0)
            id = std::stol(x.substr(x.find(":") + 1));

        p = strtok(NULL, "\n");
    }

    id_membri.push_back({user.id, user.username});
    for(const auto &i : id_membri)
    {
        header = "membri@insert";
        buffer = std::to_string(id) + "\n" + std::to_string(i.first) + "\n" + i.second + "\n";
        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        memset(ans, 0, sizeof(ans));
        read(sd, ans, sizeof(ans));
    }

    QWidget *wgt = new QWidget();
    membri->setWidget(wgt);
    disconnect(createconv, &QPushButton::clicked, this, &MainWindow::submitConv);
    connect(createconv, &QPushButton::clicked, this, &MainWindow::creazaConv);
    createconv->setText("Creaza");
    inputnume->setVisible(false);
    mesaje = false;
    delete mess;
    delete conversatii;
    delete membri;
    delete inputmess;
    delete sendmess;
    delete createconv;
    delete inputnume;
    on_mesajButton_clicked();
}

void MainWindow::adaugaInGrup()
{
    QPushButton *self = qobject_cast<QPushButton *>(sender());
    std::string id(self->objectName().toStdString());
    id = id.substr(id.find(":") + 1);

    std::string id_membru = (self->objectName().toStdString())
                        .substr((self->objectName().toStdString()).find(",") + 1,
                                (self->objectName().toStdString()).find(":") - (self->objectName().toStdString()).find(",") - 1);


    std::string header = "user@select#" + id_membru;
    std::string buffer = "";
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    char *p = strtok(ans, "\n");
    std::string username;

    while(p)
    {
        std::string x(p);
        if(strncmp(p, "username:", strlen("username:")) == 0)
            username = x.substr(x.find(":") + 1);

        p = strtok(NULL, "\n");
    }
    header = "membri@insert";
    buffer = id + "\n" + id_membru + "\n" + username;
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));
    selectConv();
}

void MainWindow::stergeDinGrup()
{
    QPushButton *self = qobject_cast<QPushButton *>(sender());
    std::string id(self->objectName().toStdString());
    id = id.substr(id.find(":") + 1);

    std::string id_membru = (self->objectName().toStdString())
                        .substr((self->objectName().toStdString()).find(",") + 1,
                                (self->objectName().toStdString()).find(":") - (self->objectName().toStdString()).find(",") - 1);


    std::string header = "membri@select";
    std::string buffer = id + "\n" + id_membru + "\n" + null;
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    char *p = strtok(ans, "\n");
    std::string id_lin;

    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id:", strlen("id:")) == 0)
            id_lin = x.substr(x.find(":") + 1);
        p = strtok(NULL, "\n");
    }
    header = "membri@delete#" + id_lin;
    buffer = "";
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));
    selectConv();
}

void MainWindow::selectConv()
{
    inputmess->setEnabled(true);
    sendmess->setEnabled(true);
    inputnume->setVisible(false);
    QPushButton *self = qobject_cast<QPushButton *>(sender());
    std::string id(self->objectName().toStdString());
    id = id.substr(id.find(":") + 1);
    if(id == "") id = std::to_string(currentconv);
    else currentconv = std::stol(id);

    prevsize = -1;
    connect(&timer, &QTimer::timeout, this, &MainWindow::showMess);
    timer.start(1000);
}

void MainWindow::showMess()
{
    if(mesaje == false)
        disconnect(&timer, &QTimer::timeout, this, &MainWindow::showMess);

    std::string id(std::to_string(currentconv));
    std::vector<std::pair<long long, std::string> > g_membri;
    std::string header = "membri@select";
    std::string buffer = id + "\n" + null + null;
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    char *p = strtok(ans, "\n");
    std::string id_membru, username_membru;
    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id_membru:", strlen("id_membru:")) == 0)
            id_membru = x.substr(x.find(":") + 1);
        if(strncmp(p, "username_membru:", strlen("username_membru:")) == 0)
            username_membru = x.substr(x.find(":") + 1);

        if(strncmp(p, "}", strlen("}")) == 0)
            g_membri.push_back({std::stol(id_membru), username_membru});

        p = strtok(NULL, "\n");
    }

    std::vector<std::pair<long long, std::string> > user_prieteni;
    header = "prietenii@select";
    buffer = null + std::to_string(user.id) + "\n" + "1,2,3,4";
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    char ans_[Size];
    header = "prietenii@select";
    buffer = std::to_string(user.id) + "\n" + null + "1,2,3,4";
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans_, 0, sizeof(ans_));
    read(sd, ans_, sizeof(ans_));
    strcat(ans, ans_);

    p = strtok(ans, "\n");
    long long id_1 = -1, id_2 = -1;
    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id_1:", strlen("id_1:")) == 0)
            id_1 = std::stol(x.substr(x.find(":") + 1));
        if(strncmp(p, "id_2:", strlen("id_2:")) == 0)
            id_2 = std::stol(x.substr(x.find(":") + 1));

        if(strncmp(p, "}", strlen("}")) == 0)
        {
            long long id_pr = (id_1 == user.id ? id_2 : id_1);
            user_prieteni.push_back({id_pr, ""});
        }

        p = strtok(NULL, "\n");
    }

    for(auto &i : user_prieteni)
    {
        header = "user@select#" + std::to_string(i.first);
        buffer = "";
        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        memset(ans, 0, sizeof(ans));
        read(sd, ans, sizeof(ans));

        p = strtok(ans, "\n");
        std::string username;
        while(p)
        {
            std::string x(p);
            if(strncmp(p, "username:", strlen("username:")) == 0)
                username = x.substr(x.find(":") + 1);

            if(strncmp(p, "}", strlen("}")) == 0)
                i.second = username;

            p = strtok(NULL, "\n");
        }
    }

    QWidget *wgtMain = new QWidget();
    QVBoxLayout *vlay = new QVBoxLayout(wgtMain);
    for(const auto &x : g_membri)
    {
        if(x.first == user.id)
            continue;

         QWidget *wgtSub = new QWidget();
         QHBoxLayout *hlay = new QHBoxLayout(wgtSub);

         QLabel *n = new QLabel;
         n->setText(QString::fromStdString(x.second));

         QPushButton *acc = new QPushButton();
         acc->setText("Sterge");
         acc->setFixedSize(QSize(50, 23));
         acc->setObjectName(QString::fromStdString("Buton," + std::to_string(x.first) + ":" +id));
         connect(acc, &QPushButton::clicked, this, &MainWindow::stergeDinGrup);

         hlay->addWidget(n);
         hlay->addWidget(acc);

         vlay->addWidget(wgtSub);
    }

    for(const auto &x : user_prieteni)
    {
        if(x.first == user.id || std::find(g_membri.begin(), g_membri.end(), x) != g_membri.end())
            continue;

         QWidget *wgtSub = new QWidget();
         QHBoxLayout *hlay = new QHBoxLayout(wgtSub);

         QLabel *n = new QLabel;
         n->setText(QString::fromStdString(x.second));

         QPushButton *acc = new QPushButton();
         acc->setText("Adauga");
         acc->setFixedSize(QSize(50, 23));
         acc->setObjectName(QString::fromStdString("Buton," + std::to_string(x.first) + ":" +id));
         connect(acc, &QPushButton::clicked, this, &MainWindow::adaugaInGrup);

         hlay->addWidget(n);
         hlay->addWidget(acc);

         vlay->addWidget(wgtSub);
    }

    membri->setWidget(wgtMain);

    //////////////////////// afisez mesaje

    header = "mesaje@select";
    buffer = null + std::to_string(currentconv) + "\n" + null + null;
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    p = strtok(ans, "\n");
    std::string mesaj, writer, data;
    std::map<std::string, std::pair <std::string, std::string>> postari;
    while(p)
    {
        if(strncmp(p, "mesaj", strlen("mesaj")) == 0)
            mesaj = std::string(p);

        if(strncmp(p, "writer", strlen("writer")) == 0)
            writer = std::string(p);

        if(strncmp(p, "data", strlen("data")) == 0)
            data = std::string(p);

        if(strncmp(p, "}", strlen("}")) == 0)
        {
            size_t pos = 0;
            writer = writer.substr(writer.find(":") + 1);
            data.replace(data.find(":", 0), std::string(":").length(), std::string(": "));
            data.replace(data.find(".", 0), std::string(".").length(), std::string("  "));

            mesaj.replace(mesaj.find(":", 0), std::string(":").length(), std::string(":\n       "));
            while((pos = mesaj.find("[enter]", pos)) != std::string::npos)
            {
                mesaj.replace(pos, std::string("[enter]").length(), std::string("\n       "));
                pos += std::string("\n       ").length();
            }
            postari[data] = {writer, mesaj};
        }
        p = strtok(NULL, "\n");
    }

    if(prevsize != postari.size())
    {
        prevsize = postari.size();
        QWidget *wgtMain_ = new QWidget();
        QVBoxLayout *hlay = new QVBoxLayout(wgtMain_);

        for(auto it = postari.rbegin(); it != postari.rend(); it++)
        {
            header = "user@select#" + it->second.first;
            buffer = "";
            write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

            memset(ans, 0, sizeof(ans));
            read(sd, ans, sizeof(ans));

            p = strtok(ans, "\n");
            std::string username;
            while(p)
            {
                std::string x(p);
                if(strncmp(p, "username", strlen("username")) == 0)
                    username = x.substr(x.find(":") + 1);

                p = strtok(NULL, "\n");
            }

            QWidget *wgtSub = new QWidget();
            QVBoxLayout *hlay_ = new QVBoxLayout(wgtSub);
            QLabel *name = new QLabel();
            name->setText(QString::fromStdString(username));
            name->setStyleSheet("QLabel {"
            "border-style: solid;"
            "border-width: 1px;"
            "border-color: black; "
            "}");
            QLabel *data = new QLabel();
            data->setText(QString::fromStdString(it->first));
            data->setStyleSheet("QLabel {"
            "border-style: solid;"
            "border-width: 1px;"
            "border-color: black; "
            "}");
            QLabel *mesaj = new QLabel();
            mesaj->setText(QString::fromStdString(it->second.second));
            mesaj->setStyleSheet("QLabel {"
            "border-style: solid;"
            "border-width: 1px;"
            "border-color: black; "
            "}");
            hlay_->addWidget(name);
            hlay_->addWidget(data);
            hlay_->addWidget(mesaj);

            hlay->addWidget(wgtSub);
        }

        if(postari.size() < 4)
        {
            QLabel *empt = new QLabel();
            QLabel *empt1 = new QLabel();
            QLabel *empt2 = new QLabel();
            QLabel *empt3 = new QLabel();

            hlay->addWidget(empt);
            hlay->addWidget(empt1);
            hlay->addWidget(empt2);
            hlay->addWidget(empt3);
        }

        mess->setAlignment(Qt::AlignHCenter);
        mess->setWidget(wgtMain_);
    }
}

void MainWindow::adaugaInGrupCreate()
{
    QPushButton *self = qobject_cast<QPushButton *>(sender());
    std::string id(self->objectName().toStdString());
    id = id.substr(id.find(":") + 1);

    std::string username = (self->objectName().toStdString())
                            .substr((self->objectName().toStdString()).find(",") + 1,
                                (self->objectName().toStdString()).find(":") - (self->objectName().toStdString()).find(",") - 1);

    id_membri.push_back({std::stol(id), username});

    self->setText("Sterge");
    disconnect(self, &QPushButton::clicked, this, &MainWindow::adaugaInGrupCreate);
    connect(self, &QPushButton::clicked, this, &MainWindow::stergeDinGrupCreate);

}

void MainWindow::stergeDinGrupCreate()
{
    QPushButton *self = qobject_cast<QPushButton *>(sender());
    std::string id(self->objectName().toStdString());
    id = id.substr(id.find(":") + 1);

    std::string username = (self->objectName().toStdString())
                            .substr((self->objectName().toStdString()).find(",") + 1,
                                (self->objectName().toStdString()).find(":") - (self->objectName().toStdString()).find(",") - 1);

    for(unsigned int ind = 0; ind < id_membri.size(); ind++)
        if(id_membri[ind].first == std::stol(id) && id_membri[ind].second == username)
        {
            id_membri.erase(id_membri.begin() + ind);
            break;
        }

    self->setText("Adauga");
    disconnect(self, &QPushButton::clicked, this, &MainWindow::stergeDinGrupCreate);
    connect(self, &QPushButton::clicked, this, &MainWindow::adaugaInGrupCreate);
}

void MainWindow::leaveConv()
{
    QPushButton *self = qobject_cast<QPushButton *>(sender());
    std::string id(self->objectName().toStdString());
    id = id.substr(id.find(":") + 1);

    std::string id_membru = (self->objectName().toStdString())
                        .substr((self->objectName().toStdString()).find(",") + 1,
                                (self->objectName().toStdString()).find(":") - (self->objectName().toStdString()).find(",") - 1);

    std::string header = "membri@select";
    std::string buffer = id + "\n" + id_membru + "\n" + null;
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));

    char *p = strtok(ans, "\n");
    std::string id_lin;

    while(p)
    {
        std::string x(p);
        if(strncmp(p, "id:", strlen("id:")) == 0)
            id_lin = x.substr(x.find(":") + 1);
        p = strtok(NULL, "\n");
    }
    header = "membri@delete#" + id_lin;
    buffer = "";
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));
    disconnect(&timer, &QTimer::timeout, this, &MainWindow::showMess);
    mesaje = false;
    delete mess;
    delete conversatii;
    delete membri;
    delete inputmess;
    delete sendmess;
    delete createconv;
    delete inputnume;
    on_mesajButton_clicked();
}

void MainWindow::sendMess()
{
    std::string mesaj(inputmess->toPlainText().toStdString());
    inputmess->setText("");
    size_t pos = 0;
    while((pos = mesaj.find("\n", pos)) != std::string::npos)
    {
        mesaj.replace(pos, std::string("\n").length(), std::string("[enter]"));
        pos += std::string("[enter]").length();
    }

    // YYYY-MM-DD.HH:mm:ss
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%H:%M:%S", &tstruct);

    std::string header = "mesaje@insert";
    std::string buffer = std::to_string(user.id) + "\n" + std::to_string(currentconv) + "\n" + std::string(buf) + "\n" + mesaj + "\n";
    char ans[Size];
    write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

    memset(ans, 0, sizeof(ans));
    read(sd, ans, sizeof(ans));
}

void MainWindow::on_adminButton_clicked()
{
    if(admin)
        return;

    admin = true;

    if(prieteni)
    {
        delete cereri;
        delete prieten;
        prieteni = false;
    }
    if(mesaje)
    {
        disconnect(&timer, &QTimer::timeout, this, &MainWindow::showMess);

        delete mess;
        delete conversatii;
        delete membri;
        delete inputmess;
        delete sendmess;
        delete createconv;
        delete inputnume;
        mesaje = false;
    }
    if(posteaza)
    {
        delete allPost;
        delete prieteniPost;
        delete apropiatiPost;
        delete editPost;
        delete submitPost;
        posteaza = false;
    }
    if(setari)
    {
        delete err;
        delete change;
        delete changeNume;
        delete changePrenume;
        delete changeParola;
        delete changeParolaConfirm;
        delete changeProfil;
        setari = false;
    }

    userid = new QLineEdit(this);
    userid->setGeometry(690, 150, 170, 22);
    userid->setPlaceholderText("Id user");
    userid->setAlignment(Qt::AlignCenter);
    userid->setVisible(true);

    postid = new QLineEdit(this);
    postid->setGeometry(690, 180, 170, 22);
    postid->setPlaceholderText("Id postare");
    postid->setAlignment(Qt::AlignCenter);
    postid->setVisible(true);

    ban = new QPushButton(this);
    ban->setGeometry(730, 210, 80, 23);
    ban->setText("Ban");
    ban->setVisible(true);

    connect(ban, &QPushButton::clicked, this, &MainWindow::Ban);

}

void MainWindow::Ban()
{
    std::string id_p(postid->text().toStdString());
    std::string id_u(userid->text().toStdString());

    if(id_p != "")
    {
        std::string header = "postari@delete#" + id_p;
        std::string buffer = "";
        char ans[Size];
        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        memset(ans, 0, sizeof(ans));
        read(sd, ans, sizeof(ans));
    }

    if(id_u != "")
    {
        std::string header = "user@delete#" + id_u;
        std::string buffer = "";
        char ans[Size];
        write(sd, (header + "\n" + buffer).c_str(), strlen((header + "\n" + buffer).c_str()));

        memset(ans, 0, sizeof(ans));
        read(sd, ans, sizeof(ans));
    }
}

