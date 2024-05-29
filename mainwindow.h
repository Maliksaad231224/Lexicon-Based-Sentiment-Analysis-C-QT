#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./ui_mainwindow.h"
#include "QPixmap"
#include <QProgressBar>
#include<QtGui>
#include<QtWidgets>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
      Ui::MainWindow ui;

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();


    void on_home_2_clicked();

    void on_pushButton_clicked();
    void on_home_3_clicked();


    void on_pushButton_3_clicked();
};
class filereader:MainWindow{
public:
    void positivefile();
    void negativefile();
    void negatorfile();
    void allwordslist();
    void intensifierfile();
};
class textread:MainWindow{
public:
    QString reader(){
         return ui.textbox->toPlainText();
    }
};

class sentence:filereader{
    public:
    int total;
bool hasIntensifier;
   bool sentiment = false;
QStringList sentences;

    void tokenizor(QString s);
   bool analyzeSentence(QString m);
    int posit;
   int negat;


};
class compare:public sentence,public textread{
public:
    bool comparetext(QString q);
    int totalwords;
};
class sentimentanalysis:public compare{
public:
    void analysis();
};



#endif // MAINWINDOW_H
