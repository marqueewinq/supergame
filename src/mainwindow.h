#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QSettings>
#include <QVariant>
#include <QRegExp>
#include <QThread>
#include <QMessageBox>
#include <QDir>
#include <unistd.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QApplication *app;
    void enableCheats();
protected:
    void closeEvent(QCloseEvent *);
    
private:
    Ui::MainWindow *ui;
    QTimer *t1, *t2, *t3, *t4, *t5, *t6;
    QSettings *s;
    QStringList *skins;
    QString recordNames[5];
    MainWindow *win;
    double recordTime[5];
    int frequence;
    int currentSkin;
    int tmp;

    void saveSettings();
    void restoreSettings();
    QString getName();
    QString name;

private slots:
    void botAddClicked();
    void starttriggered();
    void pausetriggered();
    void aboutSlot();
    void fail();
    void restart();
    void accelerate();
    void levelup(int);
    void reloadRecordString(int a = 0);
};

#endif // MAINWINDOW_H
