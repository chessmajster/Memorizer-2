#include "powtorka.h"
#include "ui_powtorka.h"


Powtorka::Powtorka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Powtorka)
{
    ui->setupUi(this);
    user=QDir::home().dirName();


}

Powtorka::~Powtorka()
{
    delete ui;
}

void Powtorka::pokazListe()
{
    lista=new QStringListModel(this);
    lista->setStringList(zawartoscPowTutaj);
    ui->listView->setModel(lista);

}

void Powtorka::wczytajPowtorki(QStringList zawartoscPow)
{
    zawartoscPowTutaj=zawartoscPow;

}

void Powtorka::on_pushButton_clicked()
{

     int ktory=ui->listView->currentIndex().row();

   QStringList wierszPowtorki=zawartoscPowTutaj[ktory].split(" ");


   int ileWyrazow=wierszPowtorki.length();
   qDebug()<<ileWyrazow;



   for(int i=0;i<=ileWyrazow-5;i++)
   {
       obecnaNazwa+=wierszPowtorki[i];
       if(i<ileWyrazow-5){obecnaNazwa+=" ";}
   }
   int komorka=2+(ileWyrazow-5)*1;
   obecnyRozdzial=wierszPowtorki[komorka];
   obecnyPodrozdzial=wierszPowtorki[komorka+2];














   zawartoscPowTutaj.remove(ktory,1);




    /*obecnaGodzina=wierszPowtorki[0];
    obecnydzien=wierszPowtorki[0];
    obecnyMiesiac=miesiace[ktory];
    obecnyRok=lata[ktory];
    obecnaPowtorka=ilePowtorek[ktory];*/







    QFile otworz("c:/users/"+user+"/documents/Memorizer/"+obecnaNazwa+".txt");
    if(!otworz.open( QFile::ReadOnly|QFile::Text))
    {
        qDebug()<<obecnaNazwa;
        qDebug("Blad pliku xD");
        return;
    }
    QString pobierzWszystko;
    pobierzWszystko=otworz.readAll();
    QStringList wszystko=pobierzWszystko.split("\n");
    int sprawdzenieIlepodrozdzialow;
    sprawdzenieIlepodrozdzialow=wszystko.length()-1;
   sprawdzenieIlepodrozdzialow=sprawdzenieIlepodrozdzialow/8;



  /* godzina=obecnaGodzina.toInt();
   dzien=obecnydzien.toInt();
   miesiac=obecnyMiesiac.toInt();
   rok=obecnyRok.toInt();
   powtorka=obecnaPowtorka.toInt();*/



 otworz.close();

 otworz.remove();
   //sprawdzanie ktory podrozdzial podmienic
   // qDebug()<<sprawdzenieIlepodrozdzialow;

    for(int m=1;m<=wszystko.length()-1;m++)
    {


        for(int l=0;l<=sprawdzenieIlepodrozdzialow;l++)
        {
            switch(m-(l*8))
            {
                case 1:{nazwykursow1<<wszystko[m-1];}break;
                case 2:{rozdzialy1<<wszystko[m-1];} break;
                case 3:{podrozdzialy1<<wszystko[m-1];} break;
                case 4:{godziny1<<wszystko[m-1];} break;
                case 5:{dni1<<wszystko[m-1];} break;
                case 6:{miesiace1<<wszystko[m-1];} break;
                case 7:{lata1<<wszystko[m-1];} break;
                case 8:{ktorePowtorki1<<wszystko[m-1];} break;


            }

        }



    }
    //int ktoryPodrozdzial=0;





   for(int i=0;i<=sprawdzenieIlepodrozdzialow-1;i++)
   {
       if((obecnaNazwa==nazwykursow1[i]) && (obecnyRozdzial==rozdzialy1[i]) && (obecnyPodrozdzial==podrozdzialy1[i]))
       {

            godzina=godziny1[i].toInt();
            dzien=dni1[i].toInt();
            miesiac=miesiace1[i].toInt();
            rok=lata1[i].toInt();
            powtorka=ktorePowtorki1[i].toInt();
              nastepnaPowtorka();
              sprawdzanie_czasu();
              godziny1[i]=QString::number(godzina);
              dni1[i]=QString::number(dzien);
              miesiace1[i]=QString::number(miesiac);
              lata1[i]=QString::number(rok);
              ktorePowtorki1[i]=QString::number(powtorka);
              qDebug()<<"Znalezione";


          /* wszystko[i]=QString::number(godzina);
           wszystko[i]=QString::number(dzien);
           wszystko[i]=QString::number(miesiac);
           wszystko[i]=QString::number(rok);
           wszystko[i]=QString::number(powtorka);
           nastepnaPowtorka(wszystko[i].toInt());*/

       }
       else{
           qDebug()<<"nie moge znalezc";
       }
   }
    qDebug()<<obecnaNazwa;

    QFile zapisz("c:/users/"+user+"/documents/Memorizer/"+obecnaNazwa+".txt");
    if(!zapisz.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug("Blad pliku xD");
        return;
    }

    QTextStream zapiszNoweDane(&zapisz);

    for(int it=0;it<=sprawdzenieIlepodrozdzialow-1;it++)
    {    qDebug()<<"nazwy kursów "<<nazwykursow1;
        zapiszNoweDane<<nazwykursow1[it]+"\n";
        zapiszNoweDane<<rozdzialy1[it]+"\n";
        zapiszNoweDane<<podrozdzialy1[it]+"\n";
        zapiszNoweDane<<godziny1[it]+"\n";
        zapiszNoweDane<<dni1[it]+"\n";
        zapiszNoweDane<<miesiace1[it]+"\n";
        zapiszNoweDane<<lata1[it]+"\n";
        zapiszNoweDane<<ktorePowtorki1[it]+"\n";

    }
    nazwykursow1.clear();
    rozdzialy1.clear();
    podrozdzialy1.clear();
    godziny1.clear();
    dni1.clear();
    miesiace1.clear();
    lata1.clear();
    ktorePowtorki1.clear();

    zapisz.close();

     qDebug()<<"Dziala";



    powtorkaSesja= new Sesja(this,obecnaNazwa,obecnyRozdzial,obecnyPodrozdzial,true);


    connect(powtorkaSesja,SIGNAL(pokazListe()),this,SLOT(przekazListe()));
    powtorkaSesja->show();
   this->hide();

    obecnaNazwa.clear();
    obecnyRozdzial.clear();
    obecnyPodrozdzial.clear();


}

void Powtorka::przekazListy(QStringList kurs,QStringList roz,QStringList pod,QStringList godz,QStringList day,QStringList month,QStringList year,QStringList repeat)
{
    nazwykursow=kurs;
    rozdzialy=roz;
    podrozdzialy=pod;
    godziny=godz;
    dni=day;
    miesiace=month;
    lata=year;
    ilePowtorek=repeat;
}


void Powtorka::nastepnaPowtorka()
  {

      switch (powtorka)
      {
        case 1: {powtorka=powtorka+1; }break;
        case 2: {godzina++; powtorka=powtorka+1;QMessageBox::information(this,"Powtórka","Powtorz za godzinę !");}break;
        case 3: {dzien++;powtorka=powtorka+1; }break;
        case 4: {dzien += 7; powtorka=powtorka+1;}break;
        case 5: {miesiac++; powtorka=powtorka+1;}break;
        case 6: {miesiac += 6;powtorka=powtorka+1; }break;
        case 7:{rok++;powtorka=powtorka+1;}break;


      }



  }




void Powtorka::sprawdzanie_czasu()
 {
     int ile=0;
     switch (miesiac)
     {
     case 1: case 3: case 5: case 7:case 8: case 10: case 12:
         {
             if (dzien > 31)
             {
                 ile = dzien - 31;
                 dzien = ile;
                 miesiac++;
                 if (dzien == 0)
                 {
                     dzien++;
                 }
             }
         }
         break;


         case 2:
         {
             if (((rok % 4) && (rok % 100) && (rok % 400)) == false)
             {
                 if (dzien > 29)
                 {
                     ile = dzien - 29;
                     dzien = ile;
                     miesiac++;
                     if (dzien == 0)
                     {
                         dzien++;
                     }
                 }
             }
             else
             {
                 if (dzien > 28)
                 {
                     ile = dzien - 28;
                     dzien = ile;
                     miesiac++;
                     if (dzien == 0)
                     {
                         dzien++;
                     }
                 }
             }
         }
         break;
         default:
         {


             if (dzien > 30)
             {
                 ile = dzien - 30;
                 dzien = ile;
                 miesiac++;
                 int roznica = miesiac - 12;
                 miesiac = roznica;
                 rok++;
                 if (dzien == 0)
                 {
                     dzien++;
                 }
             }
         }
         break;

     }
     qDebug()<<"Sprawdzanie formatu czas...";
     //cout << "Sprawdzenie formatu czasu..." << endl;
 }


void Powtorka::przekazListe()
{
    wczytajPowtorki(zawartoscPowTutaj);
    pokazListe();
    show();
}

