#ifndef LISTAPRZEDMIOTOW_H
#define LISTAPRZEDMIOTOW_H

#include <QDialog>
#include<QStringListModel>
#include<QFile>
#include<QMessageBox>
#include<QDir>
#include<QStringList>

namespace Ui {
class listaPrzedmiotow;
}

class listaPrzedmiotow : public QDialog
{
    Q_OBJECT

public:
    explicit listaPrzedmiotow(QWidget *parent = nullptr);
    ~listaPrzedmiotow();
    QStringListModel *lista;
    void wczytaj();
    QString user;
    int ilePrzedmiotow;
    QString przedmiot;
    QStringList list;


signals:
    void powiedz();


private slots:
    void on_pushButton_clicked();

private:
    Ui::listaPrzedmiotow *ui;
};

#endif // LISTAPRZEDMIOTOW_H
