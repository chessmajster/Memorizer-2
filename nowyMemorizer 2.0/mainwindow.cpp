#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{










   user=QDir::home().dirName();
    ui->setupUi(this);

    minGlobalne=0;
    sekGlobalne=0;
    pasekGlobalne=0;
    this->setStyleSheet("background-image: url(:tla/img/nowy/tlo.jpg)");
    sumaPodrozdzialow=0;
    nowy=new Dodajkurs(this);
    if(nowy->close())
    {
        this->show();
    }

    connect(nowy,SIGNAL(zakoncz()),this,SLOT(show()));

    repeat=new Powtorka(this);
    QFile przyciskPowtorki("c:/users/"+user+"/documents/Memorizer/list.txt");
        if(!przyciskPowtorki.exists())
        {
            ui->groupBox_3->hide();
        }
        przyciskPowtorki.close();




    QFile lista("c:/users/"+user+"/documents/Memorizer/list.txt");
    if(!lista.exists())
    {
       ui->groupBox5->hide();
    }
    else
    {
         nauka=new listaPrzedmiotow(this);

    }


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    //close




    QMessageBox::StandardButton guzik;


    guzik=QMessageBox::information(this,"Wyjście","Czy chcesz opuścić program ?",QMessageBox::Yes | QMessageBox::No);

    if(guzik==QMessageBox::Yes)
    {
        close();
    }
    else
    {
        return;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    //dodaj nowy kurs

    nowy->show();


    this->hide();
}


void MainWindow::wczytajDane()
{
    QFile przedmioty("c:/users/"+user+"/documents/Memorizer/list.txt");
    if(!przedmioty.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,"przedmioty","Plik lista nie istnieje");return;

    }
   QString przed=przedmioty.readAll();
   QStringList lista;
   lista=przed.split("\n");
   ilePrzed=lista.length()-1;




   //towrzenie buforow z wczytanych kursow



   for(int k=0;k<=ilePrzed-1;k++)
   {
       QFile powtorki("c:/users/"+user+"/documents/Memorizer/"+lista[k]+".txt");
       if(!powtorki.open(QFile::ReadOnly|QFile::Text))
       {
           QMessageBox::warning(this,"przedmioty","Plik lista nie istnieje");

       }
       QString bufor;
       bufor=powtorki.readAll();
       QStringList calyKurs;
       calyKurs=bufor.split("\n");


        sprawdzenieIlepodrozdzialow=calyKurs.length()-1;
       sprawdzenieIlepodrozdzialow=sprawdzenieIlepodrozdzialow/8;
       sumaPodrozdzialow+=sprawdzenieIlepodrozdzialow;



       for(int m=1;m<=calyKurs.length()-1;m++)
       {

           for(int l=0;l<=sprawdzenieIlepodrozdzialow;l++)
           {
               switch(m-(l*8))
               {
                   case 1:{nazwykursow<<calyKurs[m-1];}break;
                   case 2:{rozdzialy<<calyKurs[m-1];} break;
                   case 3:{podrozdzialy<<calyKurs[m-1];} break;
                   case 4:{godziny<<calyKurs[m-1];} break;
                   case 5:{dni<<calyKurs[m-1];} break;
                   case 6:{miesiace<<calyKurs[m-1];} break;
                   case 7:{lata<<calyKurs[m-1];} break;
                   case 8:{ktorePowtorki<<calyKurs[m-1];} break;


               }

           }



       }




        przedmioty.close();
        powtorki.close();
    }



}



void MainWindow::sprawdzDane()
{
    dzis=new QDateTime();
    czas=new QTime();


    QString data=dzis->currentDateTime().toString();
    QStringList dane=data.split(" ");
    QString mie=dane[1];
    //mie=mie.toStdString().c_str();
    //Ustawianie miesiąca
    if(mie=="Jan"){miesiac=1;}
    else if (mie=="Feb"){miesiac=2;}
    else if (mie=="Mar"){miesiac=3;}
    else if (mie=="Apr"){miesiac=4;}
    else if (mie=="May"){miesiac=5;}
    else if (mie=="Jun"){miesiac=6;}
    else if (mie=="Jul"){miesiac=7;}
    else if (mie=="Aug"){miesiac=8;}
    else if (mie=="Sep"){miesiac=9;}
    else if (mie=="Oct"){miesiac=10;}
    else if (mie=="Nov"){miesiac=11;}
    else if (mie=="Dec"){miesiac=12;}
    else
    {
        qDebug()<<"Źle pobrana data!!!";
        return;
    }
/// Ustawnianie dnia

    QString dz=dane[2];
    dzien=dz.toInt();
///Ustawianie godziny
    QString hours=dane[3];
    QStringList godz=hours.split(":");
    godzina=godz[0].toInt();
///Ustawianie roku
    rok=dane[4].toInt();
/// -------------------------------------




}













void MainWindow::on_pushButton_clicked()
{
    //nauka
    nauka->show();
    connect(nauka,SIGNAL(powiedz()),this,SLOT(wlaczenieSesji()));


}
void MainWindow::wlaczenieSesji()
{

    Dodajkurs *dodaj=new Dodajkurs(this);
    nowy->nazwaKursu=nauka->przedmiot;
    //qDebug()<<nowy->nazwaKursu;
    dodaj->dodajRozDoNauki(nowy->nazwaKursu);
   // qDebug()<<nowy->nazwaKursu;

    nowaSesja=new Sesja(this,nauka->przedmiot,dodaj->rozdzial,dodaj->podrozdzial);

    connect(nowaSesja,SIGNAL(dodajprzedm()),dodaj,SLOT(dodajPrzedmiotKopia()));
    connect(dodaj,SIGNAL(krzyk(QString, QString,QString)),nowaSesja,SLOT(pobierzKurs(QString,QString,QString)));



    connect(nowaSesja,SIGNAL(dodajroz()),dodaj,SLOT(dodajRozKopia()));
    connect(dodaj,SIGNAL(krzyk2(QString, QString,QString)),nowaSesja,SLOT(pobierzKurs(QString,QString,QString)));

     connect(nowaSesja,SIGNAL(dodajdoist(QString)),dodaj,SLOT(dodajDoIstniejacegoKopia(QString)));
     connect(dodaj,SIGNAL(krzyk3(QString, QString,QString)),nowaSesja,SLOT(pobierzKurs(QString,QString,QString)));



    nowaSesja->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    wczytajDane();

       sprawdzDane();

       bool flaga=false;

       for(int i=0;i<=sumaPodrozdzialow-1;i++)
       {



           if((dzien>=dni[i].toInt()) && (miesiac>=miesiace[i].toInt()) && (rok>=lata[i].toInt()))
           {
               listaPowtorek<<nazwykursow[i]+" Rozdział: "+rozdzialy[i]+" podrozdział: "+podrozdzialy[i];
               qDebug()<<nazwykursow[i]<<rozdzialy[i]<<podrozdzialy[i];
               if(!nazwykursow[i].isEmpty()){flaga=true;}

           }


      }
       if(flaga==false)
       {
           QMessageBox::information(this,"Powtórki","W tej chwili nie masz żadnych powtórek");
           return;
       }
       //powtorki



       repeat->wczytajPowtorki(listaPowtorek);
       repeat->pokazListe();
       repeat->przekazListy(nazwykursow,rozdzialy,podrozdzialy,godziny,dni,miesiace,lata,ktorePowtorki);

       repeat->show();

}


void MainWindow::on_pushButton_5_clicked()
{
    //Co ostatni się uczyłeś

    QFile zobacz("c:/users/"+user+"/documents/Memorizer/jaki.txt");
    if(!zobacz.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {
        QString tresc=zobacz.readAll();
        QMessageBox msg(this);
        msg.setText("Ostatnio uczyles sie: "+tresc);
        msg.setWindowTitle("Ostatnia nauka:");
        msg.setStyleSheet("QLabel{ color: white}");
        msg.exec();


     // QMessageBox::information(this,"Ostatnia nauka: ","Ostatnio uczyles sie: "+tresc);
    }
}

