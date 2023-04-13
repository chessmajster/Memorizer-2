#ifndef SESJA_H
#define SESJA_H

#include <QDialog>
#include<QTimer>
#include"listaprzedmiotow.h"
#include<QInputDialog>
namespace Ui {
class Sesja;
}

class Sesja : public QDialog
{
    Q_OBJECT
signals:
    void menu();
    void dodajprzedm();
    void dodajroz();
    void dodajdoist(QString name);



public:
    explicit Sesja(QWidget *parent = nullptr,QString nazw="",QString roz="",QString pod="",bool przyciski=false);
    ~Sesja();
    QTimer *odmierz;


    listaPrzedmiotow *lista;
    int min;
    int sek;
    double pasek;
    QString nazwaKur;
    QString rozdzia;
    QString podrozdzia;

    QString staryPrzedm;
    QString ileSesji;
    double calosc;
    int ktoraSesja;
    bool flaga;
    int mnoznik;

public slots:
    void tick();
    void przeslij();
    void pobierzKurs(QString nazw,QString roz,QString pod);



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();


    void on_pushButton_6_clicked();

signals:
    void pokazListe();

private:
    Ui::Sesja *ui;


};

#endif // SESJA_H
