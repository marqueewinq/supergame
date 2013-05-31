#ifndef GETNAME_H
#define GETNAME_H

#include <QWidget>

namespace Ui {
class GetName;
}

class GetName : public QWidget
{
    Q_OBJECT
    
public:
    explicit GetName(QWidget *parent = 0);
    QString *returnValue;
    ~GetName();
    
private:
    Ui::GetName *ui;
};

#endif // GETNAME_H
