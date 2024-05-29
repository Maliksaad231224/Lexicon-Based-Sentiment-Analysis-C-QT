#include "mainwindow.h"
#include <QtWidgets>
#include <QtCharts/QChart>
#include<QStackedWidget>
#include "QPixmap"
#include<QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include "QMessageBox"
#include<QtWidgets>
#include <QDebug>

   QStringList negative;
QStringList intensifier;
    QStringList negator;
     QStringList positive;
    QStringList allwords;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);

      ui.progress->setTextVisible(false);
    QObject::connect(ui.home_2,&QPushButton::clicked, this, &MainWindow::on_home_2_clicked);
     QObject::connect(ui.pushButton,&QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
QObject::connect(ui.pushButton_5,&QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);
QObject::connect(ui.pushButton_2,&QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
QObject::connect(ui.pushButton_3,&QPushButton::clicked, this, &MainWindow::on_pushButton_3_clicked);


    ui.stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {}



void MainWindow::on_pushButton_2_clicked()
{

    ui.stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_pushButton_4_clicked()
{
     ui.stackedWidget->setCurrentIndex(0);
}

void filereader::positivefile(){

    QFile positivefile(":/ico/Icon/positive-words.txt");
    if (!positivefile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr,"Error Opening File","We were Unable to Open the Potive.txt file");
        return;
    }

    QTextStream posIn(&positivefile);
    while (!posIn.atEnd()) {
        QString word = posIn.readLine().trimmed();
        positive.append(word);
    }
    positivefile.close();
}
void filereader::negativefile(){

    QFile negativefile(":/ico/Icon/Negative (1).txt");
    if (!negativefile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr,"Error Opening File","We were Unable to Open the Potive.txt file");
        return;
    }

    QTextStream negIn(&negativefile);
    while (!negIn.atEnd()) {
        QString word = negIn.readLine().trimmed();
       negative.append(word);
    }
    negativefile.close();


}void filereader::allwordslist(){
    QFile allfile(":/ico/Icon/allwords.txt");
    if (!allfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr,"Error Opening File","We were Unable to Open the Potive.txt file");
        return;
    }

    QTextStream allIn(&allfile);
    while (!allIn.atEnd()) {
        QString word = allIn.readLine().trimmed();
        allwords.append(word);
    }
    allfile.close();

}


void filereader::intensifierfile()
{
    QFile intensifierfile(":/ico/Icon/intensifiers.txt");
    if(!intensifierfile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::information(nullptr,"Error Opening File","We were Unable to Open the Intensifer Words file");
        return;
    }
    QTextStream intenIn(&intensifierfile);
    while(!intenIn.atEnd()){
        QString word =intenIn.readLine().trimmed();
        intensifier.append(word);
    }
    intensifierfile.close();
}

void filereader::negatorfile(){

    QFile negatorfile(":/ico/Icon/negator.txt");
    if (!negatorfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr,"Error Opening File","We were Unable to Open the Potive.txt file");
        return;
    }

    QTextStream negaIn(&negatorfile);
    while (!negaIn.atEnd()) {
        QString word = negaIn.readLine().trimmed();
        negator.append(word);
    }
    negatorfile.close();


}


void sentence::tokenizor(QString paragraph){
     sentences = paragraph.split(".");
    foreach(QString sentence, sentences) {
        total=0;
         hasIntensifier= analyzeSentence(sentence.trimmed());
    }
}



bool compare::comparetext(QString p){
    bool flag;


    QStringList inputWords = p.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);
     totalwords=0;
    foreach(QString word, inputWords) {
        flag=true;
        if (!allwords.contains(word, Qt::CaseInsensitive)) {
             flag=false;
            break;

        }
        if (allwords.contains(word, Qt::CaseInsensitive)) {
            totalwords++;


        }

    }

    return flag;
}

    bool sentence::analyzeSentence(QString sentence) {
        QStringList inputWords;
        total=0;

        QStringList punctuationMarks = { " ", ",", ".", ";", ":", "!", "?", "-", "'", "\"", "(", ")", "[", "]", "{", "}", "/", "<", ">", "&", "#", "@", "*", "%", "+", "=", "|", "\\" };
        foreach(QString mark, punctuationMarks) {
            sentence.replace(mark, " " + mark + " ");
        }
        inputWords = sentence.split(QRegularExpression("\\s+"));

        // Remove empty strings
        inputWords.removeAll("");
        bool intense=false;
        bool next=false;
        posit=0;
        negat=0;
        foreach(QString word, inputWords) {
            if (positive.contains(word, Qt::CaseInsensitive)) {
                total++;
                if (next==true) {
                     total *= -1;
                    next = false;
                }
                posit++;
            }
            if (negative.contains(word, Qt::CaseInsensitive)) {

                total--;

                if (next==true) {
                      total *= -1;
                    next = false;
                }
                negat++;
            }
            if (negator.contains(word, Qt::CaseInsensitive)) {
                  next=true;
            }
            if(intensifier.contains(word,Qt::CaseInsensitive)){
                intense=true;
            }
        }
        return intense;
    }


void MainWindow::on_pushButton_5_clicked()
{

    filereader f;
    bool v;
    f.positivefile();
    f.negativefile();
    f.negatorfile();
    f.allwordslist();
    f.intensifierfile();
    textread t;
    sentence s;
    compare c;

    s.total=0;


    QString paragraph=ui.textbox->toPlainText();
    s.tokenizor(paragraph);
   v= c.comparetext(paragraph);
    if(v==true){
       int finalSentiment = 0;
       bool hasIntensifier = false;
       int totalPosit = 0;
       int totalNegat = 0;

           foreach(QString sentence, s.sentences) {
           s.analyzeSentence(sentence.trimmed());
               finalSentiment += s.total ;
           hasIntensifier = s.hasIntensifier || hasIntensifier;
               totalPosit+=s.posit;
           totalNegat+=s.negat;
       }
    if(finalSentiment > 0) {
           if(hasIntensifier==true){
            ui.progress->setValue(90);
            ui.progress->setStyleSheet("QProgressBar { background-color: rgb(4, 143, 32); }");
            ui.result->setText("Very Positive");
        }
           else{
        ui.progress->setValue(70);
         ui.progress->setStyleSheet("QProgressBar { background-color: rgb(32, 102, 155);}");
          ui.result->setText("Positive");
        }
    }
    else if(finalSentiment < 0) {
        if(hasIntensifier==true){
            ui.progress->setValue(10);
            ui.progress->setStyleSheet("QProgressBar {  background-color: rgb(198, 55, 172);  }");
            ui.result->setText("Very Negative");
        }

        else{
         ui.progress->setValue(30);
         ui.progress->setStyleSheet("QProgressBar { background-color: rgb(255, 28, 43); }");
           ui.result->setText("Negative");
        }
    }
    else {

         ui.progress->setValue(50);
         ui.progress->setStyleSheet("QProgressBar { background-color:#A9A9A9 border:}");
         ui.result->setText("Neutral");
    }

    ui.totalwords->setText(QString::number(c.totalwords));
    ui.positive->setText(QString::number( totalPosit));
    ui.negative->setText(QString::number( totalNegat));

    }
    else{

        QMessageBox::critical(nullptr,"Error In Reading Text","Your Text cantains Words That Donot Belong To the English Language");

    }


}


void MainWindow::on_home_2_clicked()
{
    ui.stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButton_clicked()
{
   ui.stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_home_3_clicked()
{



}


void MainWindow::on_pushButton_3_clicked()
{
  ui.stackedWidget->setCurrentIndex(2);
}

