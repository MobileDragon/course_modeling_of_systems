#include "mylineedit.h"

MyLineEdit::MyLineEdit(QString id):QLineEdit()
{
    build(id);
}

QString MyLineEdit::getID()
{
    return myid;
}

void MyLineEdit::build(QString id)
{
    myid=id;
    connect(this, SIGNAL(textChanged(QString)) ,this,SLOT(myChanged(QString) ));

}
void MyLineEdit::myChanged(QString s)
{
    emit MySignal(this);
}
