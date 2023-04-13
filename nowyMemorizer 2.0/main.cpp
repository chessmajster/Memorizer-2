#include "mainwindow.h"

#include <QApplication>
#include"dodajkurs.h"
#include"sesja.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   MainWindow *w;
   //Sesja test;
   //test.show();
   w=new MainWindow;
    w->show();





    //Dodajkurs d;
    //d.show();
    return a.exec();
}
