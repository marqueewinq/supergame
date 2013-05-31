#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <math.h>

#define maxn 1000

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);

    bool finish;
    QLabel *l1, *l2, *l3, *l4;
    QString skinprefix;
    int myx;
    int myy;
    int score;
    void enableCheats(bool);

private:
    int myNumberPatrons;
    int myNumberSuperPatrons;
    int arsenalPatrons;
    int superPatron;

    QPixmap *pix, *monster, *hpatron, *vpatron, *patron, *arsenal, *superpatron, *wallpaper;

    int curnap;
    int scorebots;
    int patrons[maxn][3];
    int monsters[maxn][3];
    int arsenals[maxn][3];
    int bots[maxn][3];
    int numberPatrons;
    int sqr(int a);
    bool cheatgame;
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void fail();
public slots:
    void repaintSlot();
    void doAbstractEvent();
    void addArsenal();
    void botAdd();
    void reloadSkins(QString);
};

#endif // PAINTWIDGET_H
