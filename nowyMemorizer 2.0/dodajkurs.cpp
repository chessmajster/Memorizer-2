#include "dodajkurs.h"
#include "ui_dodajkurs.h"





Dodajkurs::Dodajkurs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dodajkurs)
{

    ui->setupUi(this);
    //this->setStyleSheet("background-image:url(:tla/img/nowy/library.jpg)");
     dzis=new QDateTime();
     czas=new QTime();
    ktoraPowtorka=2;
    user=QDir::home().dirName();

     flaga=false;

}

Dodajkurs::~Dodajkurs()
{
    delete ui;
}



void Dodajkurs::on_pushButton_2_clicked()
{
    //ktoraPowtorka=0;
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
////
/// Ustawnianie dnia

    QString dz=dane[2];
    dzien=dz.toInt();
///
///
///Ustawianie godziny
///
    QString hours=dane[3];
   QStringList godz=hours.split(":");
   godzina=godz[0].toInt();


///Ustawianie roku
///
    rok=dane[4].toInt();
///

   // qDebug()<<godzina<<"| "<<dzien<<". "<<miesiac<<". "<<rok;
    nazwaKursu=QInputDialog::getText(this,"Dodaj kurs","Nazwa kursu:",QLineEdit::Normal);
    rozdzial=QInputDialog::getText(this,"Rozdział:","Podaj rozdział: ");
    podrozdzial=QInputDialog::getText(this,"Podrozdział:","Podaj podrozdział: ");
    if((nazwaKursu.isEmpty()) || (rozdzial.isEmpty()) || (podrozdzial.isEmpty()))
    {
        QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
        return;
    }



    //qDebug()<<user;

    QString sciezka="c:/users/"+user+"/documents/Memorizer";
    QDir folder (sciezka);

    if(!folder.exists())
    {
        folder.mkpath(sciezka);
    }
    else
    {
        qDebug()<<"folder istnieje";
    }


    QFile plik("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");

    if(plik.exists())
    {
        QMessageBox::warning(this,"Dodawanie przedmiotu","Taki przedmiot już istnieje w bazie!");
        return;
    }
    QFile lista("c:/users/"+user+"/documents/Memorizer/list.txt");
    if(!lista.open(QFile::Text|QFile::WriteOnly|QFile::Append))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {
        QTextStream dolacz(&lista);
        dolacz<<nazwaKursu+"\n";
    }

    QFile mojKurs("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");
    if(!mojKurs.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {



            QTextStream tworzenie(&mojKurs);
            tworzenie<<nazwaKursu+"\n";
            tworzenie<<rozdzial+"\n";
            tworzenie<<podrozdzial+"\n";
            tworzenie<<QString::number(godzina)+"\n";
            tworzenie<<QString::number(dzien)+"\n";
            tworzenie<<QString::number(miesiac)+"\n";
            tworzenie<<QString::number(rok)+"\n";
            tworzenie<<QString::number(ktoraPowtorka)+"\n";






    }

    QFile ostatni("c:/users/"+user+"/documents/Memorizer/jaki.txt");
    if(!ostatni.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {
        QTextStream laste(&ostatni);
        laste<<nazwaKursu+" Rozdział: "+rozdzial+"podrozdział: "+podrozdzial;

    }
    ostatni.close();



    study=new Sesja(this,nazwaKursu,rozdzial,podrozdzial);

    connect(study,SIGNAL(dodajprzedm()),this,SLOT(dodajPrzedmiot()));
    connect(study,SIGNAL(dodajroz()),this,SLOT(dodajRoz()));
    connect(study,SIGNAL(dodajdoist(QString)),this,SLOT(dodajDoIstniejacego()));
    connect(study,SIGNAL(menu()),this,SLOT(powrotDoMenu()));
    //connect(lista,SIGNAL(
    //qDebug()<<nazwaKursu;
    study->show();
     mojKurs.close();


    this->hide();

}


void Dodajkurs::on_pushButton_clicked()
{
    this->hide();
    emit zakoncz();

}



void Dodajkurs::dodajPrzedmiotKopia()
{

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
////
/// Ustawnianie dnia

    QString dz=dane[2];
    dzien=dz.toInt();
///
///
///Ustawianie godziny
///
    QString hours=dane[3];
   QStringList godz=hours.split(":");
   godzina=godz[0].toInt();


///Ustawianie roku
///
    rok=dane[4].toInt();
    QString buf1,buf2,buf3;
    buf1=nazwaKursu;
    buf2=rozdzial;
    buf3=podrozdzial;
///
    nazwaKursu=QInputDialog::getText(this,"Dodaj kurs","Nazwa kursu:",QLineEdit::Normal);
    rozdzial=QInputDialog::getText(this,"Rozdział:","Podaj rozdział: ");
    podrozdzial=QInputDialog::getText(this,"Podrozdział:","Podaj podrozdział: ");
    if((nazwaKursu.isEmpty()) || (rozdzial.isEmpty()) || (podrozdzial.isEmpty()))
    {
        QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
        nazwaKursu=buf1;
        rozdzial=buf2;
        podrozdzial=buf3;
        return;
    }


    user=QDir::home().dirName();
    //qDebug()<<user;

    QString sciezka="c:/users/"+user+"/documents/Memorizer";
    QDir folder (sciezka);

    if(!folder.exists())
    {
        folder.mkpath(sciezka);
    }
    else
    {
        qDebug()<<"folder istnieje";
    }

    //robienie listy przedmiotów




    QFile plik("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");

    if(plik.exists())
    {
        QMessageBox::warning(this,"Dodawanie przedmiotu","Taki przedmiot już istnieje w bazie!");
        return;
    }

    QFile lista("c:/users/"+user+"/documents/Memorizer/list.txt");
    if(!lista.open(QFile::Text|QFile::WriteOnly|QFile::Append))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {
        QTextStream dolacz(&lista);
        dolacz<<nazwaKursu+"\n";
    }

    QFile mojKurs("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");
    if(!mojKurs.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {



        QTextStream tworzenie(&mojKurs);
        tworzenie<<nazwaKursu+"\n";
        tworzenie<<rozdzial+"\n";
        tworzenie<<podrozdzial+"\n";
        tworzenie<<QString::number(godzina)+"\n";
        tworzenie<<QString::number(dzien)+"\n";
        tworzenie<<QString::number(miesiac)+"\n";
        tworzenie<<QString::number(rok)+"\n";
        tworzenie<<QString::number(ktoraPowtorka)+"\n";


    }
    QFile ostatni("c:/users/"+user+"/documents/Memorizer/jaki.txt");
    if(!ostatni.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {
        QTextStream laste(&ostatni);
        laste<<nazwaKursu+" Rozdział: "+rozdzial+"podrozdział: "+podrozdzial;

    }
    ostatni.close();






     mojKurs.close();
   emit krzyk(nazwaKursu,rozdzial,podrozdzial);
     qDebug()<<nazwaKursu<<rozdzial<<podrozdzial;
    // wsk->pobierzKurs(nazwaKursu,rozdzial,podrozdzial);
  QMessageBox::information(this,"Informacja","Rozdział został dodany");
}






















void Dodajkurs::dodajPrzedmiot()
{
   // ktoraPowtorka=1;
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
////
/// Ustawnianie dnia

    QString dz=dane[2];
    dzien=dz.toInt();
///
///
///Ustawianie godziny
///
    QString hours=dane[3];
   QStringList godz=hours.split(":");
   godzina=godz[0].toInt();


///Ustawianie roku
///
    rok=dane[4].toInt();
    QString buf1,buf2,buf3;
    buf1=nazwaKursu;
    buf2=rozdzial;
    buf3=podrozdzial;
///
    nazwaKursu=QInputDialog::getText(this,"Dodaj kurs","Nazwa kursu:",QLineEdit::Normal);
    rozdzial=QInputDialog::getText(this,"Rozdział:","Podaj rozdział: ");
    podrozdzial=QInputDialog::getText(this,"Podrozdział:","Podaj podrozdział: ");
    if((nazwaKursu.isEmpty()) || (rozdzial.isEmpty()) || (podrozdzial.isEmpty()))
    {
        QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
        nazwaKursu=buf1;
        rozdzial=buf2;
        podrozdzial=buf3;
        return;
    }


    user=QDir::home().dirName();
    //qDebug()<<user;

    QString sciezka="c:/users/"+user+"/documents/Memorizer";
    QDir folder (sciezka);

    if(!folder.exists())
    {
        folder.mkpath(sciezka);
    }
    else
    {
        qDebug()<<"folder istnieje";
    }

    //robienie listy przedmiotów




    QFile plik("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");

    if(plik.exists())
    {
        QMessageBox::warning(this,"Dodawanie przedmiotu","Taki przedmiot już istnieje w bazie!");
        return;
    }

    QFile lista("c:/users/"+user+"/documents/Memorizer/list.txt");
    if(!lista.open(QFile::Text|QFile::WriteOnly|QFile::Append))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {
        QTextStream dolacz(&lista);
        dolacz<<nazwaKursu+"\n";
    }

    QFile mojKurs("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");
    if(!mojKurs.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
        return;
    }
    else
    {



        QTextStream tworzenie(&mojKurs);
        tworzenie<<nazwaKursu+"\n";
        tworzenie<<rozdzial+"\n";
        tworzenie<<podrozdzial+"\n";
        tworzenie<<QString::number(godzina)+"\n";
        tworzenie<<QString::number(dzien)+"\n";
        tworzenie<<QString::number(miesiac)+"\n";
        tworzenie<<QString::number(rok)+"\n";
        tworzenie<<QString::number(ktoraPowtorka)+"\n";


    }






     mojKurs.close();
     QFile ostatni("c:/users/"+user+"/documents/Memorizer/jaki.txt");
     if(!ostatni.open(QFile::WriteOnly|QFile::Text))
     {
         QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
         return;
     }
     else
     {
         QTextStream laste(&ostatni);
         laste<<nazwaKursu+" Rozdział: "+rozdzial+"podrozdział: "+podrozdzial;

     }
     ostatni.close();

     study->pobierzKurs(nazwaKursu,rozdzial,podrozdzial);
  QMessageBox::information(this,"Informacja","Rozdział został dodany");


}




void Dodajkurs::dodajRozDoNauki(QString nameK)
{



    //qDebug()<<"pracuje";
    QString data=dzis->currentDateTime().toString();
    QStringList dane=data.split(" ");
    QString mie=dane[1];
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
    ///
    ///
    ///Ustawianie godziny
    ///
        QString hours=dane[3];
       QStringList godz=hours.split(":");
       godzina=godz[0].toInt();


    ///Ustawianie roku
    ///
        rok=dane[4].toInt();
    ///
        if(nazwaKursu.isEmpty())
        {
            nazwaKursu=nameK;
        }

       qDebug()<<nazwaKursu;
         rozdzial=QInputDialog::getText(this,"Rozdział:","Podaj rozdział: ");
        podrozdzial=QInputDialog::getText(this,"Podrozdział:","Podaj podrozdział: ");
        //study->pobierzKurs(nazwaKursu,rozdzial,podrozdzial);

        if((rozdzial.isEmpty()) || (podrozdzial.isEmpty()))
        {
            QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
            return;
        }

         QFile mojKurs("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");
         if(!mojKurs.open(QFile::WriteOnly|QFile::Text|QFile::Append))
         {
             QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
             return;
         }

         QTextStream tworzenie(&mojKurs);
         tworzenie<<nazwaKursu+"\n";
         tworzenie<<rozdzial+"\n";
         tworzenie<<podrozdzial+"\n";
         tworzenie<<QString::number(godzina)+"\n";
         tworzenie<<QString::number(dzien)+"\n";
         tworzenie<<QString::number(miesiac)+"\n";
         tworzenie<<QString::number(rok)+"\n";
         tworzenie<<QString::number(ktoraPowtorka)+"\n";
            mojKurs.close();
            QFile ostatni("c:/users/"+user+"/documents/Memorizer/jaki.txt");
            if(!ostatni.open(QFile::WriteOnly|QFile::Text))
            {
                QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
                return;
            }
            else
            {
                QTextStream laste(&ostatni);
                laste<<nazwaKursu+" Rozdział: "+rozdzial+" podrozdział: "+podrozdzial;

            }
            ostatni.close();
     //emit krzyk(nazwaKursu,rozdzial,podrozdzial);
         QMessageBox::information(this,"Informacja","Rozdział został dodany");




}





void Dodajkurs::dodajRozKopia()
{
   // ktoraPowtorka=1;
    //qDebug()<<"pracuje";
    QString data=dzis->currentDateTime().toString();
    QStringList dane=data.split(" ");
    QString mie=dane[1];
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
    ///
    ///
    ///Ustawianie godziny
    ///
        QString hours=dane[3];
       QStringList godz=hours.split(":");
       godzina=godz[0].toInt();


    ///Ustawianie roku
    ///
        rok=dane[4].toInt();
    ///
    ///
         rozdzial=QInputDialog::getText(this,"Rozdział:","Podaj rozdział: ");
        podrozdzial=QInputDialog::getText(this,"Podrozdział:","Podaj podrozdział: ");
        //study->pobierzKurs(nazwaKursu,rozdzial,podrozdzial);

        if((rozdzial.isEmpty()) || (podrozdzial.isEmpty()))
        {
            QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
            return;
        }

         QFile mojKurs("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");
         if(!mojKurs.open(QFile::WriteOnly|QFile::Text|QFile::Append))
         {
             QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
             return;
         }

         QTextStream tworzenie(&mojKurs);
         tworzenie<<nazwaKursu+"\n";
         tworzenie<<rozdzial+"\n";
         tworzenie<<podrozdzial+"\n";
         tworzenie<<QString::number(godzina)+"\n";
         tworzenie<<QString::number(dzien)+"\n";
         tworzenie<<QString::number(miesiac)+"\n";
         tworzenie<<QString::number(rok)+"\n";
         tworzenie<<QString::number(ktoraPowtorka)+"\n";
            mojKurs.close();
            QFile ostatni("c:/users/"+user+"/documents/Memorizer/jaki.txt");
            if(!ostatni.open(QFile::WriteOnly|QFile::Text))
            {
                QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
                return;
            }
            else
            {
                QTextStream laste(&ostatni);
                laste<<nazwaKursu+" Rozdział: "+rozdzial+" podrozdział: "+podrozdzial;

            }
            ostatni.close();

         QMessageBox::information(this,"Informacja","Rozdział został dodany");
         emit krzyk2(nazwaKursu,rozdzial,podrozdzial);
}






void Dodajkurs::dodajRoz()
{
    //ktoraPowtorka=1;
    //qDebug()<<"pracuje";
    QString data=dzis->currentDateTime().toString();
    QStringList dane=data.split(" ");
    QString mie=dane[1];
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
    ///
    ///
    ///Ustawianie godziny
    ///
        QString hours=dane[3];
       QStringList godz=hours.split(":");
       godzina=godz[0].toInt();


    ///Ustawianie roku
    ///
        rok=dane[4].toInt();
    ///
    ///
         rozdzial=QInputDialog::getText(this,"Rozdział:","Podaj rozdział: ");
        podrozdzial=QInputDialog::getText(this,"Podrozdział:","Podaj podrozdział: ");
        study->pobierzKurs(nazwaKursu,rozdzial,podrozdzial);

        if((rozdzial.isEmpty()) || (podrozdzial.isEmpty()))
        {
            QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
            return;
        }

         QFile mojKurs("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");
         if(!mojKurs.open(QFile::WriteOnly|QFile::Text|QFile::Append))
         {
             QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
             return;
         }

         QTextStream tworzenie(&mojKurs);
         tworzenie<<nazwaKursu+"\n";
         tworzenie<<rozdzial+"\n";
         tworzenie<<podrozdzial+"\n";
         tworzenie<<QString::number(godzina)+"\n";
         tworzenie<<QString::number(dzien)+"\n";
         tworzenie<<QString::number(miesiac)+"\n";
         tworzenie<<QString::number(rok)+"\n";
         tworzenie<<QString::number(ktoraPowtorka)+"\n";
            mojKurs.close();
            QFile ostatni("c:/users/"+user+"/documents/Memorizer/jaki.txt");
            if(!ostatni.open(QFile::WriteOnly|QFile::Text))
            {
                QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
                return;
            }
            else
            {
                QTextStream laste(&ostatni);
                laste<<nazwaKursu+" Rozdział: "+rozdzial+" podrozdział: "+podrozdzial;

            }
            ostatni.close();

         QMessageBox::information(this,"Informacja","Rozdział został dodany");

}


 void Dodajkurs::dodajDoIstniejacego()
 {


     //ktoraPowtorka=1;
     //qDebug()<<"pracuje";
     QString data=dzis->currentDateTime().toString();
     QStringList dane=data.split(" ");
     QString mie=dane[1];
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
     ///
     ///
     ///Ustawianie godziny
     ///
         QString hours=dane[3];
        QStringList godz=hours.split(":");
        godzina=godz[0].toInt();


     ///Ustawianie roku
     ///
         rok=dane[4].toInt();
     ///
        nazwaKursu=study->staryPrzedm;
        qDebug()<<nazwaKursu;
          rozdzial=QInputDialog::getText(this,"Rozdział:","Podaj rozdział: ");
         podrozdzial=QInputDialog::getText(this,"Podrozdział:","Podaj podrozdział: ");
         study->pobierzKurs(nazwaKursu,rozdzial,podrozdzial);

         if((rozdzial.isEmpty()) || (podrozdzial.isEmpty()))
         {
             QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
             return;
         }

          QFile mojKurs("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");
          if(!mojKurs.open(QFile::WriteOnly|QFile::Text|QFile::Append))
          {
              QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
              return;
          }

          QTextStream tworzenie(&mojKurs);
          tworzenie<<nazwaKursu+"\n";
          tworzenie<<rozdzial+"\n";
          tworzenie<<podrozdzial+"\n";
          tworzenie<<QString::number(godzina)+"\n";
          tworzenie<<QString::number(dzien)+"\n";
          tworzenie<<QString::number(miesiac)+"\n";
          tworzenie<<QString::number(rok)+"\n";
          tworzenie<<QString::number(ktoraPowtorka)+"\n";
             mojKurs.close();
             QFile ostatni("c:/users/"+user+"/documents/Memorizer/jaki.txt");
             if(!ostatni.open(QFile::WriteOnly|QFile::Text))
             {
                 QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
                 return;
             }
             else
             {
                 QTextStream laste(&ostatni);
                 laste<<nazwaKursu+" Rozdział: "+rozdzial+" podrozdział: "+podrozdzial;

             }
             ostatni.close();

          QMessageBox::information(this,"Informacja","Rozdział został dodany");

 }

 void Dodajkurs::dodajDoIstniejacegoKopia(QString name)
 {
     //ktoraPowtorka=1;
     //qDebug()<<"pracuje";
     QString data=dzis->currentDateTime().toString();
     QStringList dane=data.split(" ");
     QString mie=dane[1];
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
     ///
     ///
     ///Ustawianie godziny
     ///
         QString hours=dane[3];
        QStringList godz=hours.split(":");
        godzina=godz[0].toInt();


     ///Ustawianie roku
     ///
         rok=dane[4].toInt();
     ///
        nazwaKursu=name;
        qDebug()<<nazwaKursu;
          rozdzial=QInputDialog::getText(this,"Rozdział:","Podaj rozdział: ");
         podrozdzial=QInputDialog::getText(this,"Podrozdział:","Podaj podrozdział: ");
         //study->pobierzKurs(nazwaKursu,rozdzial,podrozdzial);

         if((rozdzial.isEmpty()) || (podrozdzial.isEmpty()))
         {
             QMessageBox::warning(this,"Brak danych","Nie podano potrzebnych danych");
             return;
         }

          QFile mojKurs("c:/users/"+user+"/documents/Memorizer/"+nazwaKursu+".txt");
          if(!mojKurs.open(QFile::WriteOnly|QFile::Text|QFile::Append))
          {
              QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
              return;
          }

          QTextStream tworzenie(&mojKurs);
          tworzenie<<nazwaKursu+"\n";
          tworzenie<<rozdzial+"\n";
          tworzenie<<podrozdzial+"\n";
          tworzenie<<QString::number(godzina)+"\n";
          tworzenie<<QString::number(dzien)+"\n";
          tworzenie<<QString::number(miesiac)+"\n";
          tworzenie<<QString::number(rok)+"\n";
          tworzenie<<QString::number(ktoraPowtorka)+"\n";
             mojKurs.close();
             QFile ostatni("c:/users/"+user+"/documents/Memorizer/jaki.txt");
             if(!ostatni.open(QFile::WriteOnly|QFile::Text))
             {
                 QMessageBox::warning(this,"Ostrzeżenie","Nie odnaleziono właściwej ścieżki",QMessageBox::Ok);
                 return;
             }
             else
             {
                 QTextStream laste(&ostatni);
                 laste<<nazwaKursu+" Rozdział: "+rozdzial+" podrozdział: "+podrozdzial;

             }
             ostatni.close();

          QMessageBox::information(this,"Informacja","Rozdział został dodany");
          emit krzyk3(nazwaKursu,rozdzial,podrozdzial);
 }


 void Dodajkurs::powrotDoMenu()
 {
     this->hide();
     emit zakoncz();
 }




