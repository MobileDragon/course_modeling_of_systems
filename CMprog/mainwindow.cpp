#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    build();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build()
{
    subLayout1=0;
    subLayout1 = new QCPLayoutGrid;
    ui->graph_1->plotLayout()->addElement(1, 0, subLayout1);
    subLayout1->setMargins(QMargins(5, 0, 5, 5));
    //subLayout1->clear();
    subLayout1->addElement(0, 0, ui->graph_1->legend);
    //ui->graph_1->legend->setVisible(false);
    ui->graph_1->legend->setVisible(true);
    ui->graph_1->legend->setFillOrder(QCPLegend::foColumnsFirst);
    QColor none; none.setRgb(255,255,255);
    QPen p; p.setColor(none);
    ui->graph_1->legend->setBorderPen(p );
    model=0;
    valueChanged=false;
    headerName<<"i"<<"τ"<<"Χ"<<"G"<<"Υ"<<"F"<<"Z";//<<"ΔΥ2"<<"δΥ1"<<"δΥ2";

    //

    lebelObjName<<"Δτ"<<"n"<<"A"<<"B"<<"k1"<<"k2"<<"Y0"<<"F0=Y\'0";
    lebelRegName<<"C"<<"k3"<<"k4"<<"k5"<<"Z0";
    lebelXName<<"a0"<<"a1"<<"a2"<<"a3"<<"a4";
    lebelGName<<"b0"<<"b1"<<"b2";

    colColumn=headerName.length()-1;

    //
    tableRate=new QTableView();
    tableRate->setFont(QFont("Arial",10,5000));
    tableRate->verticalHeader()->hide();
    tableRate->horizontalHeader()->hide();
    ui->verticalLayout_4->addWidget(tableRate);
    ui->verticalLayout_4->setAlignment(Qt::AlignLeft);


    ui->verticalLayout_2->setAlignment(Qt::AlignTop);
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
    for(int i=0; i<lebelObjName.length(); i++)//MyLineEdit начинается с 0
    {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *label = new QLabel(QString("%1=").arg(lebelObjName[i] ));

        MyLineEdit *line = new MyLineEdit(lebelObjName[i]);
        line->setFixedWidth(50);
        //
        linesObjValue.append(line);
        connect(line, SIGNAL(MySignal(MyLineEdit*)) ,this,SLOT(lineChanged(MyLineEdit*) ));
        //
        hLayout->addWidget(label);
        hLayout->addWidget(line);
        hLayout->setAlignment(label,Qt::AlignLeft);
        hLayout->setAlignment(line,Qt::AlignLeft);
        ui->verticalLayout_2->addLayout(hLayout);
    }
    for(int i=0; i<lebelRegName.length(); i++)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *label = new QLabel(QString("%1=").arg(lebelRegName[i] ));

        MyLineEdit *line = new MyLineEdit(lebelRegName[i]);
        line->setFixedWidth(50);
        //
        linesRegValue.append(line);
        //labelForKompetent.append(label);
        connect(line, SIGNAL(MySignal(MyLineEdit*)) ,this,SLOT(lineChanged(MyLineEdit*) ));
        //
        hLayout->addWidget(label);
        hLayout->addWidget(line);
        hLayout->setAlignment(label,Qt::AlignLeft);
        hLayout->setAlignment(line,Qt::AlignLeft);

        ui->verticalLayout_2->addLayout(hLayout);
    }
    for(int i=0; i<lebelXName.length(); i++)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *label = new QLabel(QString("%1=").arg(lebelXName[i] ));

        MyLineEdit *line = new MyLineEdit(lebelXName[i]);
        line->setFixedWidth(50);
        //
        linesXValue.append(line);
        //labelForKompetent.append(label);
        connect(line, SIGNAL(MySignal(MyLineEdit*)) ,this,SLOT(lineChanged(MyLineEdit*) ));
        //
        hLayout->addWidget(label);
        hLayout->addWidget(line);
        hLayout->setAlignment(label,Qt::AlignLeft);
        hLayout->setAlignment(line,Qt::AlignLeft);

        ui->verticalLayout_3->addLayout(hLayout);
    }
    for(int i=0; i<lebelGName.length(); i++)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *label = new QLabel(QString("%1=").arg(lebelGName[i] ));

        MyLineEdit *line = new MyLineEdit(lebelGName[i]);
        line->setFixedWidth(50);
        //
        linesGValue.append(line);
        //labelForKompetent.append(label);
        connect(line, SIGNAL(MySignal(MyLineEdit*)) ,this,SLOT(lineChanged(MyLineEdit*) ));
        //
        hLayout->addWidget(label);
        hLayout->addWidget(line);
        hLayout->setAlignment(label,Qt::AlignLeft);
        hLayout->setAlignment(line,Qt::AlignLeft);

        ui->verticalLayout_3->addLayout(hLayout);
    }


    linesObjValue[0]->setText("0.2");//"Δτ"
    linesObjValue[1]->setText("51");//"n"

    linesObjValue[2]->setText("2.186");//"A"
    linesObjValue[3]->setText("0.5");//"B"
    linesObjValue[4]->setText("1.5");//"k1"
    linesObjValue[5]->setText("-1");//"k2"
    linesObjValue[6]->setText("0.5");//"Y0"
    linesObjValue[7]->setText("0.5");//"F0=Y\'0"


    linesRegValue[0]->setText("0.5");//"C"
    linesRegValue[1]->setText("1.5");//"k3"
    linesRegValue[2]->setText("2");//"k4"
    linesRegValue[3]->setText("0");//"k5"
    linesRegValue[4]->setText("0");//"Z0"

    linesXValue[0]->setText("2");//"a0"
    linesXValue[1]->setText("-0.01");//"a1"
    linesXValue[2]->setText("0.001");//"a2"
    linesXValue[3]->setText("0");//"a3"
    linesXValue[4]->setText("0");//"a4"

    linesGValue[0]->setText("1");//"b0"
    linesGValue[1]->setText("-0.01");//"b1"
    linesGValue[2]->setText("0");//"b2"


    //
    rebuild();
}

void MainWindow::drawFirstG()
{//headerName<<"i"<<"τ"<<"Χ"<<"G"<<"Υ"<<"F"<<"Z";
    ui->graph_1->clearGraphs();//очищаем все графики
    ui->graph_1->addGraph();
    ui->graph_1->addGraph();
    ui->graph_1->addGraph();
    ui->graph_1->addGraph();
    ui->graph_1->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->graph_1->graph(0)->setData(valuesForTable[0], valuesForTable[1]);
    ui->graph_1->graph(1)->setData(valuesForTable[0], valuesForTable[2]);
    ui->graph_1->graph(2)->setData(valuesForTable[0], valuesForTable[3]);
    ui->graph_1->graph(3)->setData(valuesForTable[0], valuesForTable[4]);
    ui->graph_1->graph(4)->setData(valuesForTable[0], valuesForTable[5]);
    //
    ui->graph_1->graph(0)->setPen(QColor(0, 0, 0, 255));//задаем цвет точки
    ui->graph_1->graph(1)->setPen(QColor(0, 0, 0, 255));
    ui->graph_1->graph(2)->setPen(QColor(0, 0, 0, 255));
    ui->graph_1->graph(3)->setPen(QColor(0, 0, 0, 255));
    ui->graph_1->graph(4)->setPen(QColor(0, 0, 0, 255));
    //формируем вид точек
    ui->graph_1->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond, 8));
    ui->graph_1->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, 5));
    ui->graph_1->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, 5));
    ui->graph_1->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->graph_1->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 5));
    //
    ui->graph_1->graph(0)->setName(headerName[2]);
    ui->graph_1->graph(1)->setName(headerName[3]);
    ui->graph_1->graph(2)->setName(headerName[4]);
    ui->graph_1->graph(3)->setName(headerName[5]);
    ui->graph_1->graph(4)->setName(headerName[6]);
    //Подписываем оси Ox и Oy
    ui->graph_1->xAxis->setLabel("τ");
    ui->graph_1->yAxis->setLabel("X, G, Y, F, Z");
    int N=valuesForTable[0].size();
    //Установим область, которая будет показываться на графике
    ui->graph_1->xAxis->setRange(valuesForTable[0][0], valuesForTable[0][N-1] );//Для оси Ox
    double minY = valuesForTable[1][0], maxY = valuesForTable[1][0];
    for (int i=1; i<N; i++)
    {
        if (valuesForTable[1][i]<minY) minY = valuesForTable[1][i];
        if (valuesForTable[1][i]>maxY) maxY = valuesForTable[1][i];

        if (valuesForTable[2][i]<minY) minY = valuesForTable[2][i];
        if (valuesForTable[2][i]>maxY) maxY = valuesForTable[2][i];
        //
        if (valuesForTable[3][i]<minY) minY = valuesForTable[3][i];
        if (valuesForTable[3][i]>maxY) maxY = valuesForTable[3][i];

        if (valuesForTable[4][i]<minY) minY = valuesForTable[4][i];
        if (valuesForTable[4][i]>maxY) maxY = valuesForTable[4][i];

        if (valuesForTable[5][i]<minY) minY = valuesForTable[5][i];
        if (valuesForTable[5][i]>maxY) maxY = valuesForTable[5][i];


    }
    ui->graph_1->yAxis->setRange(minY -0.2, maxY +0.2);//Для оси Oy
    ui->graph_1->plotLayout()->setRowStretchFactor(1, 0.001);
    ui->graph_1->replot();
    ui->graph_1->setFixedHeight(350);

}

void MainWindow::rebuild()
{
    model = new QStandardItemModel;
    QStandardItem *item;

    for(int i=0; i<colRow; i++)//нумерация первого стобца//пересестить в calculate()//не является названием столбца
    {
        rowName.append(QString().setNum(i) );
    }
    for (int i=0; i<colRow; i++)//номера строк
    {
        QString s = rowName[i];
        item = new QStandardItem(s);
        item->setFont(QFont("Arial",10,6500));
        item->setEditable(false);
        item->setSelectable(false);
        item->setBackground(QBrush(QColor(250,230,170)) );
        //
        model->setItem(i+1, 0, item);
    }
    for(int i=0; i<colColumn+1; i++)//названия столбцов
    {
        QString s = headerName[i];
        item = new QStandardItem(s);
        item->setFont(QFont("Arial",10,6500));
        item->setEditable(false);
        item->setSelectable(false);
        item->setBackground(QBrush(QColor(250,230,170)) );
        //
        model->setItem(0, i, item);
    }
    if(!valuesForTable.isEmpty())
    {
        for (int i=0; i<colRow; i++)
        {
            for(int j=0;j<colColumn; j++)
            {
                item=0;
                for(int col = 4; col >= 1; col--)
                {
                    int num = pow(10 ,col-1);
                    float number = valuesForTable[j][i] * num;

                    if( abs( number - int(number) ) > 0.1 )
                    {
                        item = new QStandardItem(QString().setNum(valuesForTable[j][i],'f',col));
                        break;
                    }
                }
                if(item == 0)
                    item = new QStandardItem(QString().setNum(valuesForTable[j][i],'f',0));
                item->setEditable(false);
                item->setFont(QFont("Arial",10,6500));
                model->setItem(i+1, j+1, item);
            }
        }

        drawFirstG();
    }

    tableRate->setModel(model);
    for(int i=0; i < colColumn+1; i++)//
    {
        tableRate->horizontalHeader()->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    }
    QSize size = getSize();//размер всей таблицы
    tableRate->setFixedWidth(size.width()+15);//15 для скролбара
    tableRate->setMaximumHeight(size.height());
    //tableRate->setFixedSize(getSize());
}

QSize MainWindow::getSize()
{
    QSize tableSize;
    int i=0;
    int height=0;
    int currentHeight=tableRate->rowHeight(i);
    while(currentHeight > 0)
    {
        height+=currentHeight;
        ++i;
        currentHeight=tableRate->rowHeight(i);
    }
    height+=i/2+1;
    i=0;
    int width=0;
    int currentWidth=tableRate->columnWidth(i);
    while(currentWidth > 0)
    {
        width+=currentWidth;
        ++i;
        currentWidth=tableRate->columnWidth(i);
    }
    width+=i/2+1;
    //width = tableCreterion->columnWidth(0)+20;
    tableSize.setHeight(height);
    tableSize.setWidth(width);
    return tableSize;
}

void MainWindow::calculate()
{

    colRow = UserValue["n"];//число строк

    double _D1 = (UserValue["A"] - UserValue["B"] * UserValue["Δτ"]) / UserValue["A"];
    double _D2 = -UserValue["Δτ"] / UserValue["A"];
    double _D3 = UserValue["Δτ"] * UserValue["k1"] / UserValue["A"];
    double _D4 = UserValue["Δτ"] * UserValue["k2"] / UserValue["A"];
    double _D5 = ( UserValue["C"] - UserValue["Δτ"] ) / UserValue["C"];
    double _D6 = ( UserValue["k3"] + UserValue["k4"] ) * UserValue["Δτ"] / UserValue["C"];
    double _D7 = ( UserValue["k5"] * UserValue["Δτ"] - UserValue["k4"] ) * UserValue["Δτ"] / UserValue["C"];
    double _D8 = -( UserValue["k3"] + UserValue["k4"] ) * UserValue["Δτ"] / UserValue["C"];
    double _D9 = ( UserValue["k4"] - UserValue["k5"] * UserValue["Δτ"] ) * UserValue["Δτ"] / UserValue["C"];

    qDebug() <<QString("D1 = %1").arg(_D1);
    qDebug() <<QString("D2 = %1").arg(_D2);
    qDebug() <<QString("D3 = %1").arg(_D3);
    qDebug() <<QString("D4 = %1").arg(_D4);
    qDebug() <<QString("D5 = %1").arg(_D5);
    qDebug() <<QString("D6 = %1").arg(_D6);
    qDebug() <<QString("D7 = %1").arg(_D7);
    qDebug() <<QString("D8 = %1").arg(_D8);
    qDebug() <<QString("D9 = %1").arg(_D9);

    //headerName<<"i"<<"τ"<<"Χ"<<"G"<<"Υ"<<"F"<<"Z";

    double t=0;
    QVector<double> _FiColumn;//столбцы таблицы
    QVector<double> _YiColumn;
    QVector<double> _ZiColumn;
    QVector<double> _XColumn;
    QVector<double> _GColumn;
    QVector<double> _tiColumn;//время
    double _X=0;
    double _G=0;

    _FiColumn.append( UserValue["F0=Y\'0"] );//установка начальных значений
    _YiColumn.append( UserValue["Y0"] );
    _ZiColumn.append( UserValue["Z0"] );

    for(int i=0; i<lebelXName.length(); i++)
        _X += UserValue[QString("a%1").arg(i) ] * pow(t, i);
    _XColumn.append( _X );

    for(int i=0; i<lebelGName.length(); i++)
        _G += UserValue[QString("b%1").arg(i) ] * pow(t, i);
    _GColumn.append( _G );

    _tiColumn.append(t);
    t+=UserValue["Δτ"];

    int num=1;
    while( num<colRow )
    {

        _X = 0;
        for(int i=0; i<lebelXName.length(); i++)
        {
            //QString s = QString("a%1").arg(i);
            _X += UserValue[QString("a%1").arg(i)] * pow(t, i);
        }
        _XColumn.append( _X );

        _G = 0;
        for(int i=0; i<lebelGName.length(); i++)
            _G += UserValue[QString("b%1").arg(i) ] * pow(t, i);
        _GColumn.append( _G );

        _FiColumn.append( _FiColumn[num-1] * _D1 + _D2 * _YiColumn[num-1] + _D3 * _XColumn[num-1] + _D4 * _ZiColumn[num-1] );
        _YiColumn.append( _YiColumn[num-1] + UserValue["Δτ"] * _FiColumn[num-1] );
        _ZiColumn.append( _ZiColumn[num-1] * _D5 + _YiColumn[num] * _D6 + _YiColumn[num-1] * _D7 + _GColumn[num] * _D8 + _GColumn[num-1] * _D9  );

        _tiColumn.append(t);
        t+=UserValue["Δτ"];
        num++;
    }
    valuesForTable.append(_tiColumn);//"τ"
    valuesForTable.append(_XColumn);//"Χ"
    valuesForTable.append(_GColumn);//"G"
    valuesForTable.append(_YiColumn);//"Υ"
    valuesForTable.append(_FiColumn);//"F"
    valuesForTable.append(_ZiColumn);//"Z"

}

void MainWindow::start()
{
    foreach (QVector<double> collon, valuesForTable)
    {
        collon.clear();
    }
    valuesForTable.clear();
    //
    if(isFull())//проверку сделать//ок
    {
        calculate();//заполнение ответов для построения
    }
    rebuild();

}
void MainWindow::lineChanged(MyLineEdit * lE)
{
    if(valueChanged)
        return;
    QString id = lE->getID();
    bool ok;
    float f=lE->text().toFloat(&ok);
    if(lE->text().length() > 0 && ok)
    {
        UserValue[id]=f;
    }
    else
    {
        UserValue.remove(id);

        valueChanged=true;
        lE->setText("");
        valueChanged=false;
    }
    start();

}
bool MainWindow::isFull()//ok
{
    int size = linesObjValue.size() + linesRegValue.size() +
            linesXValue.size() + linesGValue.size();
    if(UserValue.size() != size)
        return false;
    return true;

}

