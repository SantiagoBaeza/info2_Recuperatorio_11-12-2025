#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "muParser.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->boton1, &QPushButton::clicked, this, [this](){
        if(ui->lineEdit1->text().isEmpty()){
            //el ususario no ingreso la cantidad de puntos
            QMessageBox::information(nullptr, "atencion", "no ingreso la cantidad de puntos");
        }else if(ui->lineEdit2->text().isEmpty()){
            //el usuario no ingreso los Xmin
            QMessageBox::information(nullptr, "atencion", "no ingreso el origen de la grafica");
        }else if(ui->lineEdit3->text().isEmpty()){
            //el ususario no ingreso los Xmax
            QMessageBox::information(nullptr, "atencion", "no ingreso el final de la grafica");
        }else{
            graficar1(); //no tienen que ocurrir los casos anteriores para que se pueda graficar
        }
    });
    connect(ui->boton2, &QPushButton::clicked, this, [this](){
        if(ui->lineEdit1->text().isEmpty()){
            //el ususario no ingreso la cantidad de puntos
            QMessageBox::information(nullptr, "atencion", "no ingreso la cantidad de puntos");
        }else if(ui->lineEdit2->text().isEmpty()){
            //el usuario no ingreso los Xmin
            QMessageBox::information(nullptr, "atencion", "no ingreso el origen de la grafica");
        }else if(ui->lineEdit3->text().isEmpty()){
            //el ususario no ingreso los Xmax
            QMessageBox::information(nullptr, "atencion", "no ingreso el final de la grafica");
        }else{
            graficar2(); //no tienen que ocurrir los casos anteriores para que se pueda graficar
        }
    });

    connect(ui->botonCompute, &QPushButton::clicked, this, [this](){
        compute();
    });
    connect(ui->botonSuma, &QPushButton::clicked, this, [this](){
        suma();
    });
    connect(ui->botonResta, &QPushButton::clicked, this, [this](){
        resta();
    });
    connect(ui->botonMul, &QPushButton::clicked, this, [this](){
        mul();
    });
    connect(ui->botonDiv, &QPushButton::clicked, this, [this](){
        div();
    });
}

void MainWindow::graficar1(){
    mu::Parser parser;
    double valX;
    parser.DefineVar(L"x", &valX);
    parser.SetExpr(ui->lineEdit4->text().toStdWString());
    double N= ui->lineEdit1->text().toDouble();
    double Xmin= ui->lineEdit2->text().toDouble();
    double Xmax= ui->lineEdit3->text().toDouble();
    double dx= (Xmax-Xmin)/N;

    QVector<double> x(N), y(N);
    for(int i=0; i<N; i++){
        valX= Xmin + i * dx;
        x[i]= valX;
        y[i]= parser.Eval();
    }
    // Configura el gráfico en QCustomPlot
    ui->plot->clearGraphs();             // Limpia gráficos anteriores
    ui->plot->addGraph();                // Agrega un nuevo gráfico
    ui->plot->graph(0)->setPen(QPen(Qt::blue)); // Color azul para la curva
    ui->plot->graph(0)->setData(x, y);   // Asigna los datos calculados
    ui->plot->rescaleAxes();             // Ajusta los ejes al rango de datos
    ui->plot->replot();
}
void MainWindow::graficar2(){
    mu::Parser parser;
    double valX;
    parser.DefineVar(L"x", &valX);
    parser.SetExpr(ui->lineEdit5->text().toStdWString());
    double N= ui->lineEdit1->text().toDouble();
    double Xmin= ui->lineEdit2->text().toDouble();
    double Xmax= ui->lineEdit3->text().toDouble();
    double dx= (Xmax-Xmin)/N;

    QVector<double> x(N), y(N);
    for(int i=0; i<N; i++){
        valX= Xmin + i * dx;
        x[i]= valX;
        y[i]= parser.Eval();
    }
    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(Qt::red)); // Color rojo para la curva
    ui->plot->graph(1)->setData(x, y);   // Asigna los datos calculados
    ui->plot->replot();
}

void MainWindow::compute(){ //por ahora solo calcula el area de g(x)"grafica2"
    double N = ui->lineEdit1->text().toDouble();
    double xmin= ui->Xmin->text().toDouble(); //asigno los valores ingresados en los lineEdits
    double xmax= ui->Xmax->text().toDouble();
    double minGeneral= ui->lineEdit2->text().toDouble();
    double maxGeneral= ui->lineEdit3->text().toDouble();

    //traigo cosas de grafica2
    mu::Parser parser;
    double valX;
    parser.DefineVar(L"x", &valX);
    parser.SetExpr(ui->lineEdit5->text().toStdWString());
    double n= ui->lineEdit1->text().toDouble();
    double Xmin= ui->lineEdit2->text().toDouble();
    double Xmax= ui->lineEdit3->text().toDouble();
    double dx= (Xmax-Xmin)/n;
    QVector<double> x(N), y(N);

    //verifico que sean valores logicos
    if(xmin< minGeneral || xmax> maxGeneral){
        ui->lcdNumber->display(0); //si se sale afuera del rango pongo el display en cero
    }

    //integro por el metodo del trapecio
    double integral= 0.0;
    for(int i=xmin; i<xmax; i++){ //me muevo desde xmin hasta xmax (los valores que se ingresaron en el line edit)
        valX= Xmin + i * dx;
        x[i]= valX;
        y[i]= parser.Eval();
        double dt= x[i]-x[i-1];
        double b_avg= (y[i]+y[i-1])*0.5;
        integral= integral+ dt* b_avg;
    }
    ui->lcdNumber->display(integral); //
}

void MainWindow::suma(){
    mu::Parser parser;
    double valX1;
    parser.DefineVar(L"x", &valX1);
    parser.SetExpr(ui->lineEdit4->text().toStdWString()); //grafica 1

    double N= ui->lineEdit1->text().toDouble(); //estos tres los uso para todos
    double Xmin= ui->lineEdit2->text().toDouble();
    double Xmax= ui->lineEdit3->text().toDouble();
    double dx= (Xmax-Xmin)/N;

    //primer QVector
    QVector<double> x(N), y(N);
    for(int i=0; i<N; i++){
        valX1= Xmin + i * dx;
        x[i]= valX1;
        y[i]= parser.Eval();
    }
    double valX2;
    parser.DefineVar(L"x", &valX2);
    parser.SetExpr(ui->lineEdit5->text().toStdWString()); //grafica 2

    //segundo QVector
    QVector<double> x2(N), y2(N);
    for(int i=0; i<N; i++){
        valX1= Xmin + i * dx;
        x2[i]= valX2;
        y2[i]= parser.Eval();
    }

    //tercer QVector de resultados
    QVector<double> x3(N), y3(N);
    for(int i=0; i<N; i++){
        x3[i]= x[i];
        y3[i]= y[i]+y2[i]; //hago las sumas
    }

    // Configura el gráfico en QCustomPlot
    ui->plot->clearGraphs();             // Limpia gráficos anteriores
    ui->plot->addGraph();                // Agrega un nuevo gráfico
    ui->plot->graph(0)->setPen(QPen(Qt::blue)); // Color azul para la curva
    ui->plot->graph(0)->setData(x3, y3);   // Asigna los datos calculados
    ui->plot->rescaleAxes();             // Ajusta los ejes al rango de datos
    ui->plot->replot();
}
void MainWindow::resta(){
    mu::Parser parser;
    double valX1;
    parser.DefineVar(L"x", &valX1);
    parser.SetExpr(ui->lineEdit4->text().toStdWString()); //grafica 1

    double N= ui->lineEdit1->text().toDouble(); //estos tres los uso para todos
    double Xmin= ui->lineEdit2->text().toDouble();
    double Xmax= ui->lineEdit3->text().toDouble();
    double dx= (Xmax-Xmin)/N;

    //primer QVector
    QVector<double> x(N), y(N);
    for(int i=0; i<N; i++){
        valX1= Xmin + i * dx;
        x[i]= valX1;
        y[i]= parser.Eval();
    }
    double valX2;
    parser.DefineVar(L"x", &valX2);
    parser.SetExpr(ui->lineEdit5->text().toStdWString()); //grafica 2

    //segundo QVector
    QVector<double> x2(N), y2(N);
    for(int i=0; i<N; i++){
        valX1= Xmin + i * dx;
        x2[i]= valX2;
        y2[i]= parser.Eval();
    }

    //tercer QVector de resultados
    QVector<double> x3(N), y3(N);
    for(int i=0; i<N; i++){
        x3[i]= x[i];
        y3[i]= y[i]-y2[i]; //hago las restas
    }

    // Configura el gráfico en QCustomPlot
    ui->plot->clearGraphs();             // Limpia gráficos anteriores
    ui->plot->addGraph();                // Agrega un nuevo gráfico
    ui->plot->graph(0)->setPen(QPen(Qt::blue)); // Color azul para la curva
    ui->plot->graph(0)->setData(x3, y3);   // Asigna los datos calculados
    ui->plot->rescaleAxes();             // Ajusta los ejes al rango de datos
    ui->plot->replot();
}
void MainWindow::mul(){
    mu::Parser parser;
    double valX1;
    parser.DefineVar(L"x", &valX1);
    parser.SetExpr(ui->lineEdit4->text().toStdWString()); //grafica 1

    double N= ui->lineEdit1->text().toDouble(); //estos tres los uso para todos
    double Xmin= ui->lineEdit2->text().toDouble();
    double Xmax= ui->lineEdit3->text().toDouble();
    double dx= (Xmax-Xmin)/N;

    //primer QVector
    QVector<double> x(N), y(N);
    for(int i=0; i<N; i++){
        valX1= Xmin + i * dx;
        x[i]= valX1;
        y[i]= parser.Eval();
    }
    double valX2;
    parser.DefineVar(L"x", &valX2);
    parser.SetExpr(ui->lineEdit5->text().toStdWString()); //grafica 2

    //segundo QVector
    QVector<double> x2(N), y2(N);
    for(int i=0; i<N; i++){
        valX1= Xmin + i * dx;
        x2[i]= valX2;
        y2[i]= parser.Eval();
    }

    //tercer QVector de resultados
    QVector<double> x3(N), y3(N);
    for(int i=0; i<N; i++){
        x3[i]= x[i];
        y3[i]= y[i]*y2[i]; //multiplico
    }

    // Configura el gráfico en QCustomPlot
    ui->plot->clearGraphs();             // Limpia gráficos anteriores
    ui->plot->addGraph();                // Agrega un nuevo gráfico
    ui->plot->graph(0)->setPen(QPen(Qt::blue)); // Color azul para la curva
    ui->plot->graph(0)->setData(x3, y3);   // Asigna los datos calculados
    ui->plot->rescaleAxes();             // Ajusta los ejes al rango de datos
    ui->plot->replot();
}
void MainWindow::div(){
    mu::Parser parser;
    double valX1;
    parser.DefineVar(L"x", &valX1);
    parser.SetExpr(ui->lineEdit4->text().toStdWString()); //grafica 1

    double N= ui->lineEdit1->text().toDouble(); //estos tres los uso para todos
    double Xmin= ui->lineEdit2->text().toDouble();
    double Xmax= ui->lineEdit3->text().toDouble();
    double dx= (Xmax-Xmin)/N;

    //primer QVector
    QVector<double> x(N), y(N);
    for(int i=0; i<N; i++){
        valX1= Xmin + i * dx;
        x[i]= valX1;
        y[i]= parser.Eval();
    }
    double valX2;
    parser.DefineVar(L"x", &valX2);
    parser.SetExpr(ui->lineEdit5->text().toStdWString()); //grafica 2

    //segundo QVector
    QVector<double> x2(N), y2(N);
    for(int i=0; i<N; i++){
        valX1= Xmin + i * dx;
        x2[i]= valX2;
        y2[i]= parser.Eval();
    }

    //tercer QVector de resultados
    QVector<double> x3(N), y3(N);
    for(int i=0; i<N; i++){
        x3[i]= x[i];
        if(y2[i]!=0){
          y3[i]= y[i]/y2[i];
        }else{
            y3[i]= y[i]; //si y2[i]= 0 no hago la division y solo dejo el valor de y[i]
        }

    }

    // Configura el gráfico en QCustomPlot
    ui->plot->clearGraphs();             // Limpia gráficos anteriores
    ui->plot->addGraph();                // Agrega un nuevo gráfico
    ui->plot->graph(0)->setPen(QPen(Qt::blue)); // Color azul para la curva
    ui->plot->graph(0)->setData(x3, y3);   // Asigna los datos calculados
    ui->plot->rescaleAxes();             // Ajusta los ejes al rango de datos
    ui->plot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
