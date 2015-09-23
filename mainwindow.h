#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void currentRowChanged(int row);
    void loadSurah();
    void translationOptionTrigger();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    unsigned int currentSura;
    QString queryStr;
};

#endif // MAINWINDOW_H
