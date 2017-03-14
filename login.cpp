#include "login.h"
#include "ui_login.h"
#include "newuser.h"
#include <QtWidgets>
#include <QRect>
/*#include <QPainter>
#include <QPaintEvent>*/
#include <cmath>
#include "processing.h"
#include "mainwindow.h"

Login::Login(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Login)
{
	setupUi(this);
	connect(ui->pushButton_nu, SIGNAL(clicked()),this,SLOT(newuser()));

    QPixmap pix("/home/iris/Vidéos/login/login/Kart_carree.png");
    ui->label_logo->setScaledContents(true);
    ui->label_logo->setPixmap(pix);

    db = QSqlDatabase::addDatabase("QMYSQL");

        db.setHostName("localhost");
        db.setDatabaseName("BDD");
        db.setUserName("root");
        db.setPassword("iris");

        if(!db.open())
            ui->label->setText("Erreur d'accès à la base de données");
        else
            ui->label->setText("Connecté");

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString pseudo,motdepasse;
    pseudo=ui->lineEdit_id->text();
    motdepasse=ui->lineEdit_mdp->text();

    if(!db.isOpen()){

        qDebug()<<"Erreur d'accès à la base de données";
        return;
    }
    QSqlQuery requete;

    if(requete.exec("SELECT * FROM User WHERE pseudo='"+pseudo+"' and motdepasse='"+motdepasse+"'"))
    {
        int count=0;
        while(requete.next())
        {
            count++;
        }
        if(count==1){
            ui->label->setText("identifiant et mot de passe correcte");

            this->hide();
            BDD bdd;
            bdd.setModal(true);
            bdd.exec();
        }
        if(count<1)
            ui->label->setText("identifiant et mot de passe incorrecte");
    }


}

void Login::newuser()
{
    NewUser *nu = new NewUser(this);
    nu->show();
}
