#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "", tr("Archivos de Texto (*.txt);;Todos los Archivos (*)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            //QMessageBox::critical(this, tr("Error"), tr("No se pudo abrir el archivo"));
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll();
        file.close();
        // Aquí puedes hacer lo que quieras con 'text', por ejemplo mostrarlo en un widget de texto
        ui->textEdit->setText(text); // Suponiendo que tienes un QTextEdit llamado textEdit
    }
}


void MainWindow::on_actionSalir_triggered()
{
    this->close();
}

