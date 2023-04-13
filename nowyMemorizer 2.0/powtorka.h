#ifndef POWTORKA_H
#define POWTORKA_H

#include <QDialog>
#include<QStringListModel>
#include<QDir>
#include"sesja.h"
#include<QTextStream>

namespace Ui {
class Powtorka;
}

class Powtorka : public QDialog
{
    Q_OBJECT

public slots:
    void przekazListe();

public:
    explicit Powtorka(QWidget *parent = nullptr);
    ~Powtorka();
    QStringListModel *lista;
    QString user;

    void pokazListe();

    void nastepnaPowtorka();
    void sprawdzanie_czasu();

    void wczytajPowtorki(QStringList zawartoscPow);
    QStringList zawartoscPowTutaj;


    QString pobierzPlikPrzedmiotu;
    QString idzDoKursu;
    QStringList nazwykursow;
    QStringList rozdzialy;
    QStringList podrozdzialy;
    QStringList godziny;
    QStringList dni;
    QStringList miesiace;
    QStringList lata;
    QStringList ktorePowtorki;



    QString pobierzPlikPrzedmiotu1;
    QString idzDoKursu1;
    QStringList nazwykursow1;
    QStringList rozdzialy1;
    QStringList podrozdzialy1;
    QStringList godziny1;
    QStringList dni1;
    QStringList miesiace1;
    QStringList lata1;
    QStringList ktorePowtorki1;



    int godzina;
    int dzien;
    int miesiac;
    int rok;
    int powtorka;

    QString obecnaNazwa;
    QString obecnyRozdzial;
    QString obecnyPodrozdzial;
    QString obecnaGodzina;
    QString obecnydzien;
    QString obecnyMiesiac;
    QString obecnyRok;
    QString obecnaPowtorka;




    QStringList ilePowtorek;

    Sesja *powtorkaSesja;

    void przekazListy(QStringList kurs,QStringList roz,QStringList pod,QStringList godz,QStringList day,QStringList month,QStringList year,QStringList repeat);
private slots:
    void on_pushButton_clicked();



private:
    Ui::Powtorka *ui;
};

#endif // POWTORKA_H
