#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit MyLineEdit(QString id);
    QString myid;
    QString getID();
signals:
  void MySignal(MyLineEdit *);

private:
    void build(QString id);

private slots:
     void myChanged(QString s);

};

#endif // MYLINEEDIT_H
