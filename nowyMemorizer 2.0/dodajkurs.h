#ifndef DODAJKURS_H
#define DODAJKURS_H

#include <QDialog>
#include"QInputDialog"
#include<QFile>
#include<QDir>
#include<QMessageBox>
#include<QTextStream>
#include<QDateTime>
#include<QTime>
#include"sesja.h"
#include"listaprzedmiotow.h"


namespace Ui {
class Dodajkurs;
}

class Dodajkurs : public QDialog
{
    Q_OBJECT
    friend class listaPrzedmiotow;
signals:
    void zakoncz();
    void wlaczsesje();
public:



    explicit Dodajkurs(QWidget *parent = nullptr);
    ~Dodajkurs();
    QDateTime *dzis;
    QTime *czas;
    Sesja *study;

    QString nazwaKursu;
    QString user;
    QString rozdzial;
    QString podrozdzial;
    int godzina;
    int dzien;
    int miesiac;
    int rok;
    bool flaga;
    int ktoraPowtorka;


    //void pobierz(MainWindow *rodzic);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


signals:
    void krzyk(QString nazwa,QString roz,QString pod);
    void krzyk2(QString nazwa,QString roz,QString pod);
    void krzyk3(QString nazwa,QString roz,QString pod);
public slots:
    void dodajRoz();
    void dodajRozKopia();
    void dodajPrzedmiot();
    void dodajPrzedmiotKopia();
    void dodajDoIstniejacego();
    void dodajDoIstniejacegoKopia(QString name);
    void dodajRozDoNauki(QString nameK);

    void powrotDoMenu();




private:




    Ui::Dodajkurs *ui;
};

#endif // DODAJKURS_H
