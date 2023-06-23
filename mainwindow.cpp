#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    campoTexto();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::Text)) {
                textEdit->setPlainText(file.readAll());
                currentFile = fileName;
                isModified = false;
            }
        }
    }
}*/

void MainWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "", tr("Archivos de Texto (*.txt);;Todos los Archivos (*)"));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("No se pudo abrir el archivo"));
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll();
        file.close();

        ui->textEdit->setText(text);
        currentFilePath = fileName;  // Almacena la ruta del archivo.
    }
}


void MainWindow::on_actionSalir_triggered()
{
    this->close();
}


void MainWindow::on_actionGuardar_triggered()
{
    if (!currentFilePath.isEmpty())
    {
        QFile file(currentFilePath);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("No se pudo abrir el archivo"));
            return;
        }
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        file.close();
    }
    else
    {
        // Aquí puedes manejar el caso en que no se haya abierto ningún archivo.
        // Tal vez mostrar una ventana de diálogo de guardar como...
    }
}

void MainWindow::updateStatusBar()
{
    statusBar()->setFixedHeight(30);
    statusBar()->setStyleSheet("font-size: 20px");
    int characterCount = ui->textEdit->toPlainText().length();
    statusBar()->showMessage(tr("Contador: %1").arg(characterCount));

}

void MainWindow::campoTexto()
{
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::updateStatusBar);
}
