#include <paintwidget.h>


const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent)
{
    myx = 200;
    myy = 200;
    curnap = 0;
    numberPatrons = -1;
    myNumberPatrons = 50;

    for (int i = 0; i < maxn; i++) {
        patrons[i][0] = patrons[i][1] = patrons[i][2] =
        arsenals[i][0] = arsenals[i][1] = bots[i][0] =
        bots[i][1] = bots[i][2] = -1;
    }

    arsenalPatrons = 200;
    myNumberSuperPatrons = 1;
    score = 0;
    scorebots = 0;
    superPatron = 0;
    finish = false;
    cheatgame = false;
//    reloadSkins("default");
}
void PaintWidget::paintEvent(QPaintEvent *event)
{
//    qDebug() << "paintevent called" << rand()%100;
    l4->setText(QString::number(scorebots) + " bots killed");

    l3->setText(QString::number(score / 50.0));
    QPainter p(this);

    if (finish) {
        p.drawText(this->width() / 2 - 100, this->height() / 2 - 10, QString("Finish, you score is: ") + QString::number(score));
        p.drawText(this->width() / 2 - 100, this->height() / 2 + 10, QString("       Total bots killed: ") + QString::number(scorebots));
        p.end();
        return;
    }

    p.drawPixmap(0, 0, width(), height(), *wallpaper);

    p.drawPixmap(myx - 8, myy - 8, *pix);

    p.setPen(QColor("red"));
    for (int i = 0; i < maxn; i++)
        if (patrons[i][0] > 0) {
            if (patrons[i][2] < 2)
                patron = vpatron;
            else
                patron = hpatron;

            p.drawPixmap(patrons[i][0] - 4, patrons[i][1] - 4, *patron);
        }

    p.setPen(QColor("magenta"));
    for (int i = 0; i < maxn; i++) {
        if ((arsenals[i][0] < 0) || (arsenals[i][0] > this->width()))
            continue;

        if ((arsenals[i][1] < 0) || (arsenals[i][1] > this->height()))
            continue;

//        p.drawRect(arsenals[i][0] - 5, arsenals[i][1] - 5, 10, 10);
        p.drawPixmap(arsenals[i][0] - 8, arsenals[i][1] - 8, *arsenal);
    }

    p.setPen(QColor("blue"));
    for (int i = 0; i < maxn; i++)
        if (bots[i][2] != -1) {
//            p.drawEllipse(bots[i][0] - 2, bots[i][1] - 2, 5, 5);
            p.drawPixmap(bots[i][0] - 8, bots[i][1] - 8, *monster);
        }

    if (superPatron != 0) {
        superPatron--;
        for (int i = 0; i < maxn; i++)
//            if (sqrt(sqr(bots[i][0] - myx) + sqr(bots[i][1] - myy)) < 100)
            if (sqrt(sqr(bots[i][0] - myx) + sqr(bots[i][1] - myy)) < (64 * (100 - superPatron) / 100 + 200)/2) {
                bots[i][0] = bots[i][1] = bots[i][2] = -1;
                scorebots++;
            }

//        p.drawEllipse(myx - 100, myy - 100, 200, 200);
        p.drawPixmap(myx - (64 * (100 - superPatron) / 100 + 200)/2,myy - (64 * (100 - superPatron) / 100 + 200) / 2, 64 * (100 - superPatron) / 100 + 200, 64 * (100 - superPatron) / 100 + 200, *superpatron);
    }

    p.end();
}

void PaintWidget::repaintSlot()
{
    repaint();
    l1->setText("MyPatrons: " + QString::number(myNumberPatrons));
    l2->setText("MySuperPatrons " + QString::number(myNumberSuperPatrons));
}

void PaintWidget::doAbstractEvent()
{
    score++;
    myx += dx[curnap];
    myy += dy[curnap];

    for (int i = 0; i < maxn; i++) {
        if ((patrons[i][0] < 0) || (patrons[i][0] > this->width()))
            continue;

        if ((patrons[i][1] < 0) || (patrons[i][1] > this->height()))
            continue;
        patrons[i][0] += dx[patrons[i][2]] * 5;
        patrons[i][1] += dy[patrons[i][2]] * 5;
    }

    for (int i = 0; i < maxn; i++)
        if ((abs(arsenals[i][0] - myx) < 16) && (abs(arsenals[i][1] - myy) < 16)) {
            myNumberPatrons += arsenalPatrons;
            if (rand()%1 == 0)
                myNumberSuperPatrons++;

            arsenals[i][0] = -10;
        }


    if (myx == this->width()) myx--;
    if (myx == 0) myx++;
    if (myy == this->height()) myy--;
    if (myy == 0) myy++;

    for (int i = 0; i < maxn; i++)
        if (bots[i][2] != -1) {
            if (bots[i][0] <= myx) bots[i][0]++;
            if (bots[i][0] > myx) bots[i][0]--;
            if (bots[i][1] <= myy) bots[i][1]++;
            if (bots[i][1] > myy) bots[i][1] --;

//            bots[i][0] += rand()%4 - 2;
//            bots[i][1] -= rand()%4 - 2;

            for (int j = 0; j < maxn; j++)
                if ((abs(patrons[j][0] - bots[i][0]) < 5) &&
                        (abs(patrons[j][1] - bots[i][1]) < 5)) {
                            if (bots[i][2] == -1)
                                    continue;
                            bots[i][2] = -1;
                            patrons[j][0] = -1;
                            patrons[j][1] = -1;
                            scorebots++;
                        }


            if ((abs(bots[i][0] - myx) < 3) && (abs(bots[i][1] - myy) < 3) && (!cheatgame))
                emit fail();
        }

}
void PaintWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "detectKey " << event->key();
    if (finish)
        return;

    if (event->key() == Qt::Key_Up) curnap = 1;
    if (event->key() == Qt::Key_Down) curnap = 0;
    if (event->key() == Qt::Key_Right) curnap = 2;
    if (event->key() == Qt::Key_Left) curnap = 3;
    if (event->key() == Qt::Key_Space)
        if ((myNumberPatrons > 0) || (cheatgame)) {
            myNumberPatrons--;
            for (int i = 0; i < maxn; i++)
                if ((patrons[i][0] < 0) || (patrons[i][0] > this->width()) ||
                    (patrons[i][1] < 0) || (patrons[i][1] > this->height())) {

                    patrons[i][0] = myx;
                    patrons[i][1] = myy;
                    patrons[i][2] = curnap;
                    break;
                }
        }
    if (event->key() == Qt::Key_Alt)
        if (((myNumberSuperPatrons > 0) || (cheatgame)) && (superPatron == 0)) {
            myNumberSuperPatrons--;
            superPatron = 100;
        }

}

void PaintWidget::addArsenal()
{
    for (int i = 0; i < maxn; i++) {
        if ((arsenals[i][0] > 0) && (arsenals[i][0] < this->width()))
            continue;

        if ((arsenals[i][1] > 0) && (arsenals[i][1] < this->height()))
            continue;

        arsenals[i][0] = rand()%this->width();
        arsenals[i][1] = rand()%this->height();
        break;
    }
}

void PaintWidget::botAdd() {
    for (int i = 0; i < maxn; i++)
        if (bots[i][2] == -1) {
            bots[i][0] = rand() % 3000 - 1500 + this->width() / 2;
            if (abs(bots[i][0] - myx) < 100)
                continue;

            bots[i][1] = rand() % 3000 - 1500 + this->height() / 2;
            if (abs(bots[i][1] - myy) < 100)
                continue;

            bots[i][2] = 1;
            break;
        }
}

int PaintWidget::sqr(int a)
{
    return a * a;
}

void PaintWidget::enableCheats(bool a) {
    cheatgame = a;
}

void PaintWidget::reloadSkins(QString s) {
    skinprefix = "../skins/";
    pix = new QPixmap(skinprefix + s + "/hero.png");
    monster = new QPixmap(skinprefix + s + "/monster.png");
    vpatron = new QPixmap(skinprefix + s + "/vertpatron.png");
    hpatron = new QPixmap(skinprefix + s + "/horizpatron.png");
    arsenal = new QPixmap(skinprefix + s + "/arsenal.png");
    superpatron = new QPixmap(skinprefix + s + "/superpatron.png");
    wallpaper = new QPixmap(skinprefix + s +"/wallpaper.png");

    repaint();
}
