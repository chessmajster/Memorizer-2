#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"dodajkurs.h"
#include<QFile>
#include"listaprzedmiotow.h"
#include"powtorka.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int minGlobalne;
    int sekGlobalne;
    double pasekGlobalne;
    int ileSesjiGlobalne;
    int ktoraSesjaGlobalne;

    Dodajkurs *nowy;
    Sesja *nowaSesja;



    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void wczytajDane();
    listaPrzedmiotow *nauka;

    void sprawdzDane();

    int ilePrzed;

    QDateTime *dzis;
        QTime *czas;
        Powtorka *repeat;

        QStringList nazwykursow;
        QStringList rozdzialy;
        QStringList podrozdzialy;
        QStringList godziny;
        QStringList dni;
        QStringList miesiace;
        QStringList lata;
        QStringList ktorePowtorki;

        QStringList ilePowtorek;




        int godzina;
        int dzien;
        int miesiac;
        int rok;
        int sprawdzenieIlepodrozdzialow;

        QStringList listaPowtorek;
        QString user;
        int sumaPodrozdzialow;




public slots:
    void wlaczenieSesji();




private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();




    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
