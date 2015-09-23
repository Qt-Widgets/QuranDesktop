#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    currentSura = 1;

    ui->setupUi(this);
    ui->listSura->setFont(QFont("SolaimanLipi"));
    ui->listAyah->setFont(QFont("SolaimanLipi"));

    connect(ui->listSura, SIGNAL(currentRowChanged(int)), this, SLOT(currentRowChanged(int)));

    connect(ui->bangla1, SIGNAL(clicked()), this, SLOT(translationOptionTrigger()));
    connect(ui->bangla2, SIGNAL(clicked()), this, SLOT(translationOptionTrigger()));
    connect(ui->bangla3, SIGNAL(clicked()), this, SLOT(translationOptionTrigger()));
    connect(ui->bangla4, SIGNAL(clicked()), this, SLOT(translationOptionTrigger()));


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/media/data/dev/qt/Quran/db/quran.db");
    db.open();

    QSqlQuery query("SELECT ID, NameAr, NameBn from surah");
    QSqlRecord record = query.record();
    while (query.next())
    {
        QString ID = query.value(record.indexOf("ID")).toString();
        QString NameAr = query.value(record.indexOf("NameAr")).toString();
        QString NameBn = query.value(record.indexOf("NameBn")).toString();
        ui->listSura->addItem(ID + " - " + NameAr + " - " + NameBn);
    }

    currentRowChanged(0);

    setWindowTitle("Quran");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::currentRowChanged(int row)
{
    currentSura = row + 1;
    translationOptionTrigger();
}

void MainWindow::loadSurah()
{
    ui->listAyah->clear();

    QSqlQuery query(queryStr);
    QSqlRecord record = query.record();

    int ayah = 0;

    while (query.next())
    {
        ayah++;

        QListWidgetItem *infoText = new QListWidgetItem(QString("%1.%2")
                                                        .arg(query.value(record.indexOf("SuraID")).toString())
                                                        .arg(query.value(record.indexOf("VerseID")).toString()));
        infoText->setTextAlignment(Qt::AlignCenter);
        ui->listAyah->addItem(infoText);
        //arabicText->setBackgroundColor(QColor("#EEEEEE"));

        QListWidgetItem *arabicText = new QListWidgetItem(query.value(record.indexOf("AyahText")).toString());
        arabicText->setTextAlignment(Qt::AlignRight);
        ui->listAyah->addItem(arabicText);
        arabicText->setBackgroundColor(QColor("#EEEEEE"));

        if(ui->bangla1->isChecked())
        {
            QListWidgetItem *banglaText = new QListWidgetItem(query.value(record.indexOf("AyahTextBn0")).toString());
            //banglaText->setTextAlignment(Qt::AlignRight);
            ui->listAyah->addItem(banglaText);
            banglaText->setBackgroundColor(QColor("#FFCDD2"));
        }
        if(ui->bangla2->isChecked())
        {
            QListWidgetItem *banglaText = new QListWidgetItem(query.value(record.indexOf("AyahTextBn1")).toString());
            //banglaText->setTextAlignment(Qt::AlignRight);
            ui->listAyah->addItem(banglaText);
            banglaText->setBackgroundColor(QColor("#BBDEFB"));
        }
        if(ui->bangla3->isChecked())
        {
            QListWidgetItem *banglaText = new QListWidgetItem(query.value(record.indexOf("AyahTextBn2")).toString());
            //banglaText->setTextAlignment(Qt::AlignRight);
            ui->listAyah->addItem(banglaText);
            banglaText->setBackgroundColor(QColor("#DCEDC8"));
        }
        if(ui->bangla4->isChecked())
        {
            QListWidgetItem *banglaText = new QListWidgetItem(query.value(record.indexOf("AyahTextBn3")).toString());
            //banglaText->setTextAlignment(Qt::AlignRight);
            ui->listAyah->addItem(banglaText);
            banglaText->setBackgroundColor(QColor("#FFF9C4"));
        }

    }
}

void MainWindow::translationOptionTrigger()
{
    queryStr = "SELECT SuraID, VerseID, AyahText";

    if(ui->bangla1->isChecked())
        queryStr += ", AyahTextBn0";
    if(ui->bangla2->isChecked())
        queryStr += ", AyahTextBn1";
    if(ui->bangla3->isChecked())
        queryStr += ", AyahTextBn2";
    if(ui->bangla4->isChecked())
        queryStr += ", AyahTextBn3";

    queryStr += QString(" from ayah WHERE SuraID = %1").arg(currentSura);

    loadSurah();
}
