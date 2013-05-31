#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <getname.h>

const int level[5] = {60, 45, 30, 20, 6};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    frequence = 1000;
    ui->setupUi(this);

    t1 = new QTimer;
    t2 = new QTimer;
    t3 = new QTimer;
    t4 = new QTimer;
    t5 = new QTimer;
    t6 = new QTimer;

    t1->connect(t1, SIGNAL(timeout()), ui->widget, SLOT(repaintSlot()));
    t2->connect(t2, SIGNAL(timeout()), ui->widget, SLOT(doAbstractEvent()));
    t3->connect(t3, SIGNAL(timeout()), ui->widget, SLOT(addArsenal()));
    t4->connect(t4, SIGNAL(timeout()), ui->widget, SLOT(botAdd()));
    t5->connect(t5, SIGNAL(timeout()), this, SLOT(accelerate()));
    t6->connect(t6, SIGNAL(timeout()), ui->widget, SLOT(setFocus()));
    t1->setInterval(30);
    t2->setInterval(20);
    t3->setInterval(10000);
    t4->setInterval(frequence);
    t5->setInterval(level[0] * 1000);
    t6->setInterval(200);



    QObject::connect(ui->BotAdd, SIGNAL(clicked()), this, SLOT(botAddClicked()));
    QObject::connect(ui->widget, SIGNAL(fail()), this, SLOT(fail()));

    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), this->t1, SLOT(start()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), this->t2, SLOT(start()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), this->t3, SLOT(start()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), this->t4, SLOT(start()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), this->t5, SLOT(start()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), this->t6, SLOT(start()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), ui->lineEdit, SLOT(raise()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked(bool)), ui->commandLinkButton_2, SLOT(setHidden(bool)));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked(bool)), ui->commandLinkButton, SLOT(setVisible(bool)));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked(bool)), ui->comboBox, SLOT(setEnabled(bool)));

    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked()), this->t1, SLOT(stop()));
    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked()), this->t2, SLOT(stop()));
    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked()), this->t3, SLOT(stop()));
    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked()), this->t4, SLOT(stop()));
    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked()), this->t5, SLOT(stop()));
    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked()), this->t6, SLOT(stop()));
    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked(bool)), ui->commandLinkButton, SLOT(setHidden(bool)));
    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked(bool)), ui->commandLinkButton_2, SLOT(setVisible(bool)));

    QObject::connect(ui->commandLinkButton_3, SIGNAL(clicked()), this, SLOT(restart()));
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(levelup(int)));
    QObject::connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), ui->widget, SLOT(reloadSkins(QString)));
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reloadRecordString(int)));

    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutSlot()));
    QObject::connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(starttriggered()));
    QObject::connect(ui->actionPause, SIGNAL(triggered()), this, SLOT(pausetriggered()));
    QObject::connect(ui->actionStart, SIGNAL(triggered()), ui->commandLinkButton, SLOT(click()));
    QObject::connect(ui->actionPause, SIGNAL(triggered()), ui->commandLinkButton_2, SLOT(click()));
    QObject::connect(ui->commandLinkButton, SIGNAL(clicked()), this, SLOT(starttriggered()));
    QObject::connect(ui->commandLinkButton_2, SIGNAL(clicked()), this, SLOT(pausetriggered()));
    QObject::connect(ui->actionNew_game, SIGNAL(triggered()), this, SLOT(restart()));



    restoreSettings();
    win = NULL;
    ui->pushButton->setVisible(false);
    ui->BotAdd->setVisible(false);
    ui->widget->setFocus();
    reloadRecordString();
    ui->widget->l1 = ui->label;
    ui->widget->l2 = ui->label_2;
    ui->widget->l3 = ui->label_3;
    ui->widget->l4 = ui->botsKilled;
    ui->commandLinkButton_2->setVisible(false);
    ui->lineEdit->setText(name);
    this->showMaximized();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (win == NULL)
        saveSettings();
}

MainWindow::~MainWindow() {
    if (win != NULL)
        delete win;
    delete ui;
}

void MainWindow::botAddClicked() {
    ui->widget->setFocus();
    ui->widget->botAdd();
}

void MainWindow::fail() {
    t6->stop();
    t5->stop();
    t4->stop();
    t3->stop();
    t2->stop();

    if (ui->widget->score / 50.0 > recordTime[ui->comboBox->currentIndex()]) {
        recordTime[ui->comboBox->currentIndex()] = ui->widget->score / 50.0;
        name = getName();
        recordNames[ui->comboBox->currentIndex()] = name;
    }

    reloadRecordString();

    ui->widget->finish = true;
    ui->commandLinkButton->setVisible(false);
    ui->commandLinkButton_2->setVisible(false);
    ui->actionPause->setVisible(false);
    ui->actionStart->setVisible(false);
    ui->comboBox->setEnabled(true);
}

void MainWindow::restart()
{
    t1->stop();
    t2->stop();
    t3->stop();
    t4->stop();
    t5->stop();
    t6->stop();
    saveSettings();
    this->close();
    win = new MainWindow();
    win->show();

    return;
}

void MainWindow::accelerate() {
    frequence /= 2;
    t4->setInterval(frequence);
}

void MainWindow::restoreSettings() {
    s = new QSettings("SuperGame.ini", QSettings::IniFormat);
    this->restoreGeometry(s->value("geometry").toByteArray());
    this->restoreState(s->value("state").toByteArray());
    ui->comboBox->setCurrentIndex(s->value("level").toInt());
    for (int i = 0; i < 5; i++)
        recordTime[i] = s->value("record" + QString::number(i)).toDouble();

    for (int i = 0; i < 5; i++)
        recordNames[i] = s->value("recordName" + QString::number(i)).toString();

    name = s->value("lastName").toString();
    skins = new QStringList;
    QFileInfoList tmp = QDir("../skins/").entryInfoList();
    for (int i = 1; i < tmp.size(); i++)
        *skins << tmp[i].baseName();
    skins->removeDuplicates();
    for (int i = 0; i < skins->size(); i++)
        ui->comboBox_2->addItem(skins->at(i));

    ui->comboBox_2->setCurrentIndex(s->value("defaultskin").toInt());
    ui->widget->reloadSkins(skins->at(s->value("defaultskin").toInt()));
    this->resize(s->value("size", QSize(640, 480)).toSize());
    this->move(s->value("pos", QPoint(1, 1)).toPoint());
}

void MainWindow::saveSettings() {
    s = new QSettings("SuperGame.ini", QSettings::IniFormat);
    s->setValue("geometry", QVariant(this->saveGeometry()));
    s->setValue("state", QVariant(this->saveState()));
    s->setValue("level", QVariant(ui->comboBox->currentIndex()));
    for (int i = 0; i < 5; i++)
        s->setValue("record" + QString::number(i), QVariant(recordTime[i]));

    for (int i = 0; i < 5; i++)
        s->setValue("recordName" + QString::number(i), QVariant(recordNames[i]));

    s->setValue("defaultskin", ui->comboBox_2->currentIndex());
    s->setValue("lastName", QVariant(ui->lineEdit->text()));
    s->setValue("size", size());
    s->setValue("pos", pos());
    s->sync();
    delete s;
}

void MainWindow::levelup(int a) {
    t5->setInterval(level[a] * 1000);
}

void MainWindow::reloadRecordString(int a) {
    ui->label_4->setText("Record: " + QString::number(recordTime[ui->comboBox->currentIndex()]));
    ui->label_5->setText(".. by " + recordNames[ui->comboBox->currentIndex()]);
}

void MainWindow::enableCheats() {
    ui->widget->enableCheats(true);
}

void MainWindow::starttriggered() {
    ui->actionStart->setVisible(false);
    ui->actionPause->setVisible(true);
}

void MainWindow::pausetriggered() {
    ui->actionStart->setVisible(true);
    ui->actionPause->setVisible(false);
}

void MainWindow::aboutSlot() {
    QMessageBox *a = new QMessageBox;
    a->setText("Program created by\n\tV.S.Tyulbashev\n<vladislav.tyulbashev@yandex.ru>");
    a->show();
}

QString MainWindow::getName() {
  /*  QString res = "adferb4";
    GetName *a = new GetName();
    a->returnValue = &res;
    while (res == "adferb4")
        usleep(200);

    return res;*/
    return ui->lineEdit->text();
}
