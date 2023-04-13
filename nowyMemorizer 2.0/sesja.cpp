#include "sesja.h"
#include "ui_sesja.h"
#include<QLCDNumber>
#include<QMessageBox>

Sesja::Sesja(QWidget *parent,QString nazw,QString roz,QString pod,bool przyciski) :
    QDialog(parent),
    ui(new Ui::Sesja)
{

     min=25;
     sek=0;
     pasek=0;
     ktoraSesja=1;
     ileSesji=QInputDialog::getText(this,"Liczba sesji","Ile sesji chcesz się uczyć");
     if(ileSesji.isEmpty())
     {
         QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
         exit(1);
     }


    ui->setupUi(this);
    //emit sesjaRuszyla();




    ui->pushButton_5->hide();
    ui->lcdNumber->display("25:00");
    if(przyciski==true)
    {
        ui->groupBox->hide();
        ui->pushButton_5->show();
    }
    nazwaKur=nazw;
    rozdzia=roz;
    podrozdzia=pod;

     mnoznik=1;





    int dodatkowe=ileSesji.toInt()/5;
    int minuty=0;
    for(int i=1;i<=dodatkowe;i++)
    {
        minuty=dodatkowe*20*i;
    }

    calosc=30*ileSesji.toInt()+minuty;

     flaga=false;

    ui->label_2->setText("Nauka: <b>"+nazwaKur+"</b><br/> Rozdział: "+rozdzia+" Podrozdział: "+podrozdzia+"</h1>");

    odmierz=new QTimer();
    odmierz->start(1000);
    connect(odmierz,SIGNAL(timeout()),this,SLOT(tick()));



}

Sesja::~Sesja()
{
    delete ui;
}
void Sesja::tick()
{

    if((min==0) && (sek==0))
    {
        if(ktoraSesja>=ileSesji.toInt())
        {
            odmierz->stop();
            QMessageBox::information(this,"Koniec","Dzisiejszy plan został wykonany, czas odpocząć !");
            exit(1);

        }
        else if(flaga==false)
        {
            if((ktoraSesja%4)==0)
            {
                int napis=mnoznik*20;
                QMessageBox::information(this,"Przerwa ",QString::number(napis)+" minutowa przerwa !");
                min=napis;
                mnoznik++;
                flaga=true;
            }
            else
            {
                QMessageBox::information(this,"Przerwa ","5 minutowa przerwa !");
                min=5;
                flaga=true;
            }


        }
        else if(flaga==true)
        {
            ktoraSesja++;
            QMessageBox::information(this,"Koniec przerwy ","Czas wracać do nauki !");
            min=25;
            flaga=false;
        }



    }


    ui->progressBar->setValue(pasek);
    if(sek==0)
    {
        min--;
        sek=59;
    }


    if((sek<=9) && (min<=9))
    {
         ui->lcdNumber->display("0"+QString::number(min)+":"+"0"+QString::number(sek));
    }
    else if(sek<=9)
    {
        ui->lcdNumber->display(QString::number(min)+":0"+QString::number(sek));
    }
    else if(min<=9)
    {
        ui->lcdNumber->display("0"+QString::number(min)+":"+QString::number(sek));
    }


    else
    {
        ui->lcdNumber->display(QString::number(min)+":"+QString::number(sek));
    }
    sek--;

    double ileDodac=100/(calosc*60);
    pasek+=ileDodac;
    qDebug()<<pasek;


}

void Sesja::on_pushButton_clicked()
{
    QMessageBox::information(this,"Powtórka","Powtorz ten rozdział odrazu!");
    QMessageBox::StandardButton guzik;

    guzik=QMessageBox::information(this,"Wyjście","Czy chcesz opuścić program ?",QMessageBox::Yes | QMessageBox::No);
    if(guzik==QMessageBox::Yes)
    {
        exit(0);
    }
    else
    {
        return;
    }

}



void Sesja::on_pushButton_2_clicked()
{
    //QMessageBox::information(this,"Powtórka","Powtorz ten rozdział odrazu!");
    emit dodajroz();
}
void Sesja::pobierzKurs(QString nazw, QString roz, QString pod)
{
   ui->label_2->setText("Nauka: <b>"+nazw+"</b><br/> Rozdział: "+roz+" Podrozdział: "+pod+"</h1>");
}


void Sesja::on_pushButton_3_clicked()
{
    //QMessageBox::information(this,"Powtórka","Powtorz ten rozdział odrazu!");
    emit dodajprzedm();
}


void Sesja::on_pushButton_4_clicked()
{
    QMessageBox::information(this,"Powtórka","Powtorz ten rozdział odrazu!");
    lista=new listaPrzedmiotow(this);
    connect(lista,SIGNAL(powiedz()),this,SLOT(przeslij()));

    lista->show();
}
void Sesja::przeslij()
{

    staryPrzedm=lista->przedmiot;
    emit dodajdoist(staryPrzedm);

}



void Sesja::on_pushButton_5_clicked()
{
    //pokaż listę
    //QMessageBox::information(this,"Powtórka","Powtorz ten rozdział odrazu!");
    emit pokazListe();
    this->hide();
}




void Sesja::on_pushButton_6_clicked()
{
    //powrót do menu
    odmierz->stop();
    this->hide();
    emit menu();

}

