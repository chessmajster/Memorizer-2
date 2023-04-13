#include "listaprzedmiotow.h"
#include "ui_listaprzedmiotow.h"

listaPrzedmiotow::listaPrzedmiotow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listaPrzedmiotow)
{
    ui->setupUi(this);
    lista=new QStringListModel(this);



    user=QDir::home().dirName();
    wczytaj();
}

listaPrzedmiotow::~listaPrzedmiotow()
{
    delete ui;
}

void listaPrzedmiotow::wczytaj()
{
    QFile przedmioty("c:/users/"+user+"/documents/Memorizer/list.txt");
    if(!przedmioty.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,"przedmioty","Plik lista nie istnieje");return;
    }
   QString przed=przedmioty.readAll();
   list=przed.split("\n");
   list.removeLast();
   ilePrzedmiotow=list.length();
  // qDebug()<<ilePrzedmiotow;
   lista->setStringList(list);
   ui->listView->setModel(lista);



}

void listaPrzedmiotow::on_pushButton_clicked()
{
    int ktoryPrzedmiot;
    ktoryPrzedmiot=ui->listView->currentIndex().row();
    qDebug()<<ktoryPrzedmiot;
    przedmiot=list[ktoryPrzedmiot];




    emit powiedz();
    close();

}


