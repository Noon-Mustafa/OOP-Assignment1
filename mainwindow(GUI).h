#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QImage>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "Image_Class.h"
#include <iostream>
using namespace std;



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fancyFrame(Image& image, int colorChoice);
    void resizeFilter(Image& img, int newWidth, int newHeight);

private slots:
    void on_loadButton_clicked();
    void on_undoButton_clicked();
    void on_redoButton_clicked();
    void on_saveButton_clicked();
    void on_applyButton_clicked();

private:
    Ui::MainWindow *ui;
    QImage currentImage;
    QString currentFilePath;

  
    QVector<QImage> undoStack;
    QVector<QImage> redoStack;
};

#endif 
