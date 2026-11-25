#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <algorithm>
#include <QDebug>


void MainWindow::fancyFrame(Image& image, int colorChoice)
{
    int width = image.width;
    int height = image.height;
    int outer = 20;
    int inner = 12;
    int r = 255, g = 0, b = 0;
    if (colorChoice == 2) { r =255; g = 165; b= 0; }
    else if (colorChoice== 3) { r=255; g = 215; b = 0; }
    else if (colorChoice== 4) { r=0; g = 128; b = 0; }
    else if (colorChoice== 5) { r=0; g= 0; b= 255; }
    else if (colorChoice== 6) { r=75; g = 0; b = 130; }
    else if (colorChoice== 7) { r=238; g= 130; b = 238; }
    else if (colorChoice== 8) { r=0; g = 0; b = 0; }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x<outer||x>= width-outer ||
                y<outer||y>= height- outer)
            {
                image.setPixel(x, y, 0, 255);
                image.setPixel(x, y, 1, 255);
                image.setPixel(x, y, 2, 255);
            }
            else if (x<outer+inner||
                     x>=width-outer-inner||
                     y<outer+inner||
                     y >= height-outer-inner)
            {
                image.setPixel(x, y, 0, r);
                image.setPixel(x, y, 1, g);
                image.setPixel(x, y, 2, b);
            }
        }
    }
}

void MainWindow::resizeFilter(Image& image, int newWidth, int newHeight)
{
    if (newWidth<= 0||newHeight<= 0)
    {
        cout <<"Invalid image dimensions!"<<endl;
        return;
    }

    Image newImage(newWidth, newHeight);

    for (int y=0; y<newHeight;y++)
    {
        for (int x =0; x<newWidth;x++)
        {
            int oldX =x *image.width/newWidth;
            int oldY =y *image.height/newHeight;

            newImage.setPixel(x, y, 0, image.getPixel(oldX, oldY, 0));
            newImage.setPixel(x, y, 1, image.getPixel(oldX, oldY, 1));
            newImage.setPixel(x, y, 2, image.getPixel(oldX, oldY, 2));
        }
    }
    image=newImage;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ثيم الـ Deep Blue الأنيق
    this->setStyleSheet(
        "QMainWindow {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0F2027, stop:0.5 #203A43, stop:1 #2C5364);"
        "}"
        "QPushButton {"
        "   background-color: #1F4068;"
        "   color: #FFFFFF;"
        "   border: 1px solid #005691;"
        "   border-radius: 8px;"
        "   padding: 10px 20px;"
        "   min-height: 25px;"
        "   font-weight: bold;"
        "   font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #005691;"
        "   border-color: #00A8CC;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #003355;"
        "}"
        "QComboBox {"
        "   background-color: #162447;"
        "   color: #E4E4E4;"
        "   border: 1px solid #1F4068;"
        "   border-radius: 6px;"
        "   padding: 6px 12px;"
        "   font-size: 13px;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #1B1B2F;"
        "   color: #E4E4E4;"
        "   selection-background-color: #005691;"
        "}"
        "QLabel {"
        "   color: #E4E4E4;"
        "   font-size: 14px;"
        "}"
        );

    ui->imagelabel->setStyleSheet(
        "QLabel {"
        "   background-color: rgba(15, 32, 39, 0.6);"
        "   border: 2px dashed #005691;"
        "   border-radius: 12px;"
        "}"
        );

    connect(ui->exitButton, &QPushButton::clicked, this, &QMainWindow::close);

    ui->comboBox->addItem("1.Invert");
    ui->comboBox->addItem("2.DarkenLighten");
    ui->comboBox->addItem("3.Frame");
    ui->comboBox->addItem("4.Resize");
    ui->comboBox->addItem("5.Gray");
    ui->comboBox->addItem("6.Flip");
    ui->comboBox->addItem("7.BlackandWhite");
    ui->comboBox->addItem("8.Edge Detection");
    ui->comboBox->addItem("9.Blur");
    ui->comboBox->addItem("10.Infrared");
    ui->comboBox->addItem("11.crop");
    ui->comboBox->addItem("12.purple");
    ui->comboBox->addItem("13.OldTV");
    ui->comboBox->addItem("14.Rotate");
    ui->comboBox->addItem("15.Merge");
    ui->comboBox->addItem("16.sunlight");
    ui->comboBox->addItem("17.Skew");
    ui->comboBox->addItem("18.OilPaint");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_undoButton_clicked()
{
    qDebug()<<"Undo stack size before Undo:" <<undoStack.size();
    if (undoStack.isEmpty())
        return;
    redoStack.push_back(currentImage);
    currentImage = undoStack.last();
    undoStack.pop_back();
    qDebug()<< "Undo stack size after Undo:"<< undoStack.size();
    qDebug()<< "Restored image size:" <<currentImage.size();
    ui->imagelabel->setPixmap(
        QPixmap::fromImage(currentImage).scaled(
            ui->imagelabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
}



void MainWindow::on_redoButton_clicked()
{
    if (redoStack.isEmpty())
        return;
    undoStack.push_back(currentImage);
    currentImage = redoStack.last();
    redoStack.pop_back();
    ui->imagelabel->setPixmap(
        QPixmap::fromImage(currentImage).scaled(
            ui->imagelabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
}




void MainWindow::on_loadButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open Image",
        "",
        "Images (*.png *.jpg *.jpeg *.bmp)");

    if (filePath.isEmpty())
        return;

    QImage loadedImage(filePath);

    if (loadedImage.isNull()) {
        QMessageBox::warning(
            this, "Error", "Could not load image.");
        return;
    }

    currentFilePath = filePath;
    currentImage = loadedImage.convertToFormat(
        QImage::Format_RGB888);

    undoStack.clear();
    redoStack.clear();

    ui->imagelabel->setPixmap(
        QPixmap::fromImage(currentImage).scaled(
            ui->imagelabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
}

void MainWindow::on_applyButton_clicked()
{
    if (currentImage.isNull()) {
        QMessageBox::warning(this, "Warning", "Please load an image first!");
        return;
    }
    QImage previousImage=currentImage;
    if (!currentImage.save("current_temp.png")) {
        QMessageBox::warning(this, "Error", "Could not save temporary image.");
        return;
    }
    QString selectedFilter = ui->comboBox->currentText();
    qDebug()<<"Applying:"<<selectedFilter;
    qDebug()<<"Stack before filter:"<<undoStack.size();


    if (selectedFilter == "1.Invert") {
        Image image("current_temp.png");
        for (int i=0;i<image.width;i++)
        {
            for (int j=0;j<image.height;j++)
            {

                for (int k=0;k<image.channels;k++) {

                    image(i,j,k) = 255-image(i,j,k);
                }

            }
        }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");


    }
    else if (selectedFilter == "2.DarkenLighten") {

        bool ok;
        double userpercentage = QInputDialog::getDouble(this, "Darken / Lighten",
                                                        "Enter percentage (+ for lighten, - for darken):",
                                                        0, -100, 100, 1, &ok);
        if (!ok) return;
        Image image("current_temp.png");
        float newpercentage=(userpercentage/100);
        for (int i=0;i<image.width;i++){
            for(int j=0;j<image.height;j++){
                for(int k=0;k<image.channels;k++){
                    int oldpixel=image(i,j,k);
                    float newpixel=oldpixel+(oldpixel*newpercentage);
                    if (newpixel>255) newpixel=255;
                    if (newpixel<0) newpixel=0;
                    image(i,j,k)=newpixel;

                }
            }

        }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "3.Frame"){
        bool ok;
        int FilterType = QInputDialog::getInt(this, "Frame Filter",
                                              "Choose Filter Type:\n1. Simple\n2. Fancy",
                                              1, 1, 2, 1, &ok);
        if (!ok) return;
        Image image("current_temp.png");
        if(FilterType==1){
            int width = image.width;
            int height = image.height;
            int framesize= 20;
            for(int y=0; y< height;y++)
            {
                for(int x=0; x< width;x++)
                {
                    if(x<=framesize || x>=width-framesize || y<=framesize || y>=height-framesize)
                    {
                        image.setPixel(x,y,0,255);
                        image.setPixel(x,y,1,255);
                        image.setPixel(x,y,2,255);
                    }
                }
            }
        }else if(FilterType == 2){
            int colorChoice = QInputDialog::getInt(this, "Fancy Frame",
                                                   "Choose a color:\n1.Red, 2.Orange, 3.Yellow, 4.Green, 5.Blue, 6.Indigo, 7.Violet, 8.Black",
                                                   1, 1, 8, 1, &ok);
            if (!ok) return;
            fancyFrame(image, colorChoice);

        }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "4.Resize"){
        bool ok;
        int newWidth = QInputDialog::getInt(this, "Resize Image", "Enter new width:", 800, 10, 5000, 1, &ok);
        if (!ok) return;


        int newHeight = QInputDialog::getInt(this, "Resize Image", "Enter new height:", 600, 10, 5000, 1, &ok);
        if (!ok) return;


       Image image("current_temp.png");
        resizeFilter(image, newWidth, newHeight);


        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");
    }


    else if(selectedFilter == "5.Gray"){
        Image image("current_temp.png");
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                unsigned int avg = 0;

                for (int k = 0; k < image.channels; ++k) {
                    avg += image(i, j, k);
                }

                avg = avg / 3;

                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = avg;
                }
            }
        }

        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "6.Flip"){
        Image image("current_temp.png");
        int width = image.width;
        int height = image.height;

        for (int i = 0; i < width / 2; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    unsigned char temp = image(i, j, k);
                    image(i, j, k) = image(width - 1 - i, j, k);
                    image(width - 1 - i, j, k) = temp;
                }
            }
        }

        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "7.BlackandWhite"){
        Image image("current_temp.png");

        const int limit= 128;

        for (int row = 0; row < image.height; row++)
        {
            for (int col = 0; col < image.width; col++)
            {
                int r = image.getPixel(col, row, 0);
                int g = image.getPixel(col, row, 1);
                int b = image.getPixel(col, row, 2);

                int average = (r + g + b) /3;

                if (average>=limit)
                {
                    image.setPixel(col, row, 0, 255);
                    image.setPixel(col, row, 1, 255);
                    image.setPixel(col, row, 2, 255);
                }
                else
                {
                    image.setPixel(col, row, 0, 0);
                    image.setPixel(col, row, 1, 0);
                    image.setPixel(col, row, 2, 0);
                }
            }
        }
         image.saveImage("temp_output.png");
         currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "8.Edge Detection"){
       Image image("current_temp.png");
        for (int row = 0; row < image.height; row++)
        {
            for (int col = 0; col < image.width; col++)
            {
                int r = image.getPixel(col, row, 0);
                int g = image.getPixel(col, row, 1);
                int b = image.getPixel(col, row, 2);

                int brightness = (r + g + b) / 3;

                image.setPixel(col, row, 0, brightness);
                image.setPixel(col, row, 1, brightness);
                image.setPixel(col, row, 2, brightness);
            }
        }

        for (int row = 1; row < image.height - 1; row++)
        {
            for (int col = 1; col < image.width - 1; col++)
            {
                int currentPixel = image.getPixel(col, row, 0);

                int nextPixel = image.getPixel(col + 1, row, 0);
                int lowerPixel = image.getPixel(col, row + 1, 0);

                int horizontalChange = abs(currentPixel - nextPixel);
                int verticalChange = abs(currentPixel - lowerPixel);

                int edgeStrength = horizontalChange + verticalChange;

                if (edgeStrength > 40)
                {
                    image.setPixel(col, row, 0, 0);
                    image.setPixel(col, row, 1, 0);
                    image.setPixel(col, row, 2, 0);
                }
                else
                {
                    image.setPixel(col, row, 0, 255);
                    image.setPixel(col, row, 1, 255);
                    image.setPixel(col, row, 2, 255);
                }
            }


        }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");
    }


    else if(selectedFilter == "9.Blur"){
        bool ok;

        int level = QInputDialog::getInt(this, "Blur Filter", "Please enter the blur level (1-5):", 2, 1, 5, 1, &ok);
        if (!ok) return;

        Image image("current_temp.png");
        Image original=image;
        int radius= level;
        for (int y=radius; y<image.height-radius; y++)
        {
            for (int x=radius; x<image.width - radius; x++)
            {
                int sumR= 0, sumG= 0, sumB= 0;
                int count= 0;

                for (int ky=-radius; ky<=radius; ky++)
                {
                    for (int kx=-radius; kx<=radius; kx++)
                    {
                        int pixelX= x + kx;
                        int pixelY= y + ky;

                        sumR +=original.getPixel(pixelX, pixelY, 0);
                        sumG +=original.getPixel(pixelX, pixelY, 1);
                        sumB +=original.getPixel(pixelX, pixelY, 2);
                        count++;
                    }
                }

                image.setPixel(x, y, 0, sumR/count);
                image.setPixel(x, y, 1, sumG/count);
                image.setPixel(x, y, 2, sumB/count);
            }
        }

        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }

    else if(selectedFilter == "10.Infrared"){
        Image image("current_temp.png");
        for (int i=0;i<image.width;i++)
        {
            for (int j=0;j<image.height;j++)
            {
                int r=image.getPixel(i,j,0);
                int g=image.getPixel(i,j,1);
                int b=image.getPixel(i,j,2);

                image.setPixel(i,j,0,255);
                image.setPixel(i,j,1,255-g);
                image.setPixel(i,j,2,255-b);
            }
        }

        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");


    }
    else if(selectedFilter == "11.crop"){
           Image image("current_temp.png");

            bool ok;

            int height = QInputDialog::getInt(this, "Crop Image",
                                              QString("Image height is: %1. Enter crop height:").arg(image.height),
                                              image.height, 1, image.height, 1, &ok);
            if (!ok) return;

            int width = QInputDialog::getInt(this, "Crop Image",
                                             QString("Image width is: %1. Enter crop width:").arg(image.width),
                                             image.width, 1, image.width, 1, &ok);
            if (!ok) return;

            int start_row = QInputDialog::getInt(this, "Crop Image", "Enter start row (Y):", 0, 0, image.height, 1, &ok);
            if (!ok) return;

            int start_coloum = QInputDialog::getInt(this, "Crop Image", "Enter start column (X):", 0, 0, image.width, 1, &ok);
            if (!ok) return;

            Image croppedimage( width ,height);
            if(image.width>=start_coloum+width && start_coloum>=0 && image.height>=start_row+height && start_row>=0){
                for (int i=0;i<= croppedimage.height-1;i++){
                    for (int j=0;j<= croppedimage.width-1;j++){
                        for (int k=0; k<croppedimage.channels;k++){

                            croppedimage(j,i,k)=  image(start_coloum+j,start_row+i,k);
                        }


                    }
                }
                image=croppedimage;
            }else{
                QMessageBox::warning(this, "Error", "Invalid dimensions!");
            }

            image.saveImage("temp_output.png");
            currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "12.purple"){
          Image image("current_temp.png");
        for(int i=0;i<image.height;i++){

            for(int j=0;j<image.width;j++){

                int red=image(j,i,0);
                red=red*1.2;

                int green=image(j,i,1);
                green=green*0.2;

                int blue=image(j,i,2);
                blue=blue*1.5;

                if (blue>255) blue=255;
                if (red>255)  red=255;

                image(j,i,0)=red;
                image(j,i,1)=green;
                image(j,i,2)=blue;


            }
        }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "13.OldTV"){
         Image image("current_temp.png");
        for (int _y = 0; _y < image.height; _y++)
        {
            for (int _x = 0; _x < image.width; _x++)
            {
                int red = image.getPixel(_x, _y, 0);
                int green = image.getPixel(_x, _y, 1);
                int blue = image.getPixel(_x, _y, 2);

                int newRed = min(255, (red * 11 + green * 2 + blue) / 10);
                int newGreen = min(255, (red + green * 9 + blue) / 11);
                int newBlue = min(255, (red + green + blue * 7) / 12);

                if (_y % 2 == 0)
                {
                    newRed= newRed * 7/10;
                    newGreen= newGreen * 7/10;
                    newBlue= newBlue * 7/10;
                }

                image.setPixel(_x, _y, 0, newRed);
                image.setPixel(_x, _y, 1, newGreen);
                image.setPixel(_x, _y, 2, newBlue);
            }
        }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "14.Rotate"){
        bool ok;
        int angle = QInputDialog::getInt(this, "Rotate Image", "Enter rotation angle (90, 180, 270):", 90, 90, 270, 90, &ok);
        if (!ok) return;

        Image image("current_temp.png");
        if (angle == 90) {
            int oldWidth = image.width;
            int oldHeight = image.height;
            Image rotated(oldHeight, oldWidth);
            for (int i = 0; i < oldWidth; ++i) {
                for (int j = 0; j < oldHeight; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotated(oldHeight - 1 - j, i, k) = image(i, j, k);
                    }
                }
            }
            image = rotated;
        } else if (angle == 180) {
            int width = image.width;
            int height = image.height;
            Image rotated(width, height);
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotated(width - 1 - i, height - 1 - j, k) = image(i, j, k);
                    }
                }
            }
            image = rotated;
        } else if (angle == 270) {
            int oldWidth = image.width;
            int oldHeight = image.height;
            Image rotated(oldHeight, oldWidth);
            for (int i = 0; i < oldWidth; ++i) {
                for (int j = 0; j < oldHeight; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotated(j, oldWidth - 1 - i, k) = image(i, j, k);
                    }
                }
            }
            image = rotated;
        } else {
            QMessageBox::warning(this, "Warning", "Invalid angle or specialized transformation needed.");
    }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "15.Merge"){
        QString secondFileName = QFileDialog::getOpenFileName(this, "Select Second Image for Merge", "", "Images (*.png *.jpg *.jpeg *.bmp)");
        if (secondFileName.isEmpty()) return;

        Image image("current_temp.png");
        Image image2(secondFileName.toStdString());

        int newWidth = min(image.width, image2.width);
        int newHeight = min(image.height, image2.height);
        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "16.sunlight"){
          Image image("current_temp.png");
        for(int i=0;i<image.height;i++){
            for(int j=0;j<image.width;j++){

                int red=image(j,i,0);
                red=red*1.2;

                int green=image(j,i,1);
                green=green*1.0;

                int blue=image(j,i,2);
                blue=blue*0.8;

                if (green>255) green=255;
                if (red>255)  red=255;

                image(j,i,0)=red;
                image(j,i,1)=green;
                image(j,i,2)=blue;


            }
        }
        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "17.Skew"){
        bool ok;
        int angle = QInputDialog::getInt(this, "Skew Image", "Enter skew angle (-45 to 45):", 10, -45, 45, 1, &ok);
        if (!ok) return;

        Image image("current_temp.png");
        if (angle < -45 || angle > 45) {
            QMessageBox::warning(this, "Error", "Invalid angle!");
            return;
        }

        if (angle == 0) return;

        int width = image.width;
        int height = image.height;

        double rad = angle * 3.14159265 / 180.0;
        double skewFactor = tan(rad);

        int extraWidth = static_cast<int>(
            ceil(height * abs(skewFactor))
            );

        Image result(width + extraWidth, height);

        for (int y = 0; y < result.height; y++)
        {
            for (int x = 0; x < result.width; x++)
            {
                for (int c = 0; c < 3; c++)
                {
                    result(x, y, c) = 255;
                }
            }
        }

        for (int y = 0; y < height; y++)
        {
            int shift = static_cast<int>(
                round((height - 1 - y) * abs(skewFactor))
                );

            for (int x = 0; x < width; x++)
            {
                int newX;

                if (angle > 0)
                    newX = x + shift;
                else
                    newX = x + extraWidth - shift;

                if (newX >= 0 && newX < result.width)
                {
                    for (int c = 0; c < 3; c++)
                    {
                        result(newX, y, c) = image(x, y, c);
                    }
                }
            }
        }

        image = result;

        image.saveImage("temp_output.png");
        currentImage.load("temp_output.png");

    }
    else if(selectedFilter == "18.OilPaint"){
            bool ok;
            int radius = QInputDialog::getInt(this, "Oil Paint Effect", "Please enter the radius for the oil painting effect (1-10):", 2, 1, 10, 1, &ok);
            if (!ok) return;

            Image image("current_temp.png");

            int width = image.width;
            int height = image.height;
            Image original = image;

            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    int colorCount[256][3] = {0};
                    int count[256] = {0};
                    int maxCount = 0;
                    int dominantColor[3] = {0};

                    for (int dx = -radius; dx <= radius; dx++)
                    {
                        for (int dy = -radius; dy <= radius; dy++)
                        {
                            int nx = x + dx;
                            int ny = y + dy;

                            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                            {
                                int r = original(nx, ny, 0);
                                int g = original(nx, ny, 1);
                                int b = original(nx, ny, 2);

                                int intensity = (r + g + b) / 3;
                                count[intensity]++;
                                colorCount[intensity][0] += r;
                                colorCount[intensity][1] += g;
                                colorCount[intensity][2] += b;
                            }
                        }
                    }
                    int dominantIntensity = 0;
                    for (int i = 0; i < 256; i++)
                    {
                        if (count[i] > maxCount)
                        {
                            maxCount = count[i];
                            dominantIntensity = i;
                        }
                    }
                    if (maxCount > 0)
                    {
                        dominantColor[0] = colorCount[dominantIntensity][0] / maxCount;
                        dominantColor[1] = colorCount[dominantIntensity][1] / maxCount;
                        dominantColor[2] = colorCount[dominantIntensity][2] / maxCount;
                    }
                    image(x, y, 0) = dominantColor[0];
                    image(x, y, 1) = dominantColor[1];
                    image(x, y, 2) = dominantColor[2];
                }
            }

            image.saveImage("temp_output.png");
            currentImage.load("temp_output.png");

    }

    if (currentImage.isNull()) {
        QMessageBox::warning(this, "Error", "The filtered image could not be loaded.");
        return;
    }
    undoStack.push_back(previousImage);
    redoStack.clear();
    qDebug()<<"Applied:"<<selectedFilter;
    qDebug()<<"Stack after filter:"<<undoStack.size();
    ui->imagelabel->setPixmap(
        QPixmap::fromImage(currentImage).scaled(
            ui->imagelabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
}

void MainWindow::on_saveButton_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Image (*.png);;JPEG Image (*.jpg *.jpeg);;BMP Image (*.bmp)");
    if (!fileName.isEmpty()) {
        currentImage.save(fileName);
    }
}
