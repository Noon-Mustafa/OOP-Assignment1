# include <iostream>
# include "Image_Class.h"
#include <stack>
using namespace std;

void Skew(Image& image)
{
    int angle;
    cout << "Enter skew angle: ";
    cin >> angle;
    int width = image.width;
    int height = image.height;

    Image result(width + height, height);

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
    //***/ /***//***//***//***//***//
   void applyMerge(Image& image) {
    string secondFileName;
    cout << "Enter the name of the second image to merge with: ";
    cin >> secondFileName;
    
    Image image2(secondFileName);
    
    int newWidth = min(image.width, image2.width);
    int newHeight = min(image.height, image2.height);
    
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }
}

//***/ /***//***//***//***//***//
void applyRotate45(Image& image) {
    int angle;
    cout << "Enter rotation angle (90, 180, 270): ";
    cin >> angle;
    
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
        cout << "For 45, 135, 225, 315 degrees, specialized matrix transformation is needed." << endl;
    }
}

int main() {
    Image image("luffy.jpg");
    
    applyRotate45(image);
    
    image.saveImage("luffy_rotated.jpg");
    
    return 0;
}
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int newX = x + (height - y) * angle / 100;

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

    cout << "Skew filter applied successfully!" << endl;
}

//***/ /***//***//***//***//***//

void OldTV(Image& image)
{
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
}

//***/ /***//***//***//***//***//

void purple(Image& image){
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
}

//***/ /***//***//***//***//***//

void crop(Image& image){

     cout<<"The image width is:"<<image.width<<"and height is:"<<image.height<<endl;

    int height , width;
    cout<<"please enter the hight and width"<<endl;
    cin>> height >> width;

    int start_row ,start_coloum;
    cout<<"please enter the start point in rows and in coloums"<<endl;
    cin>>start_row>>start_coloum;
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
        cout<<"invalid daimenions";
    }
}
//***/ /***//***//***//***//***//

void oilPaint(Image& image)
{
    int radius;
    cout<<"Please enter the radius for the oil painting effect (1-10): ";
    cin>>radius;
    while (radius<1||radius>10) {
        cout<<"Invalid radius. Please enter a value between 1 and 10: ";
        cin>>radius;
    }
    int width =image.width;
    int height =image.height;
    Image original =image;

    for (int x=0; x<width; x++)
    {
        for (int y=0; y<height; y++)
        {
            int colorCount[256][3]= {0};
            int count[256]= {0};
            int maxCount = 0;
            int dominantColor[3]= {0};

            for (int dx= -radius; dx<=radius; dx++)
            {
                for (int dy= -radius; dy<= radius; dy++)
                {
                    int nx= x + dx;
                    int ny= y + dy;

                    if (nx>=0 && nx<width &&
                        ny>=0 && ny<height)
                    {
                        int r=original(nx, ny, 0);
                        int g=original(nx, ny, 1);
                        int b=original(nx, ny, 2);

                        int intensity= (r + g + b)/3;
                        count[intensity]++;
                        colorCount[intensity][0]+= r;
                        colorCount[intensity][1]+= g;
                        colorCount[intensity][2]+= b;
                    }
                }
            }
            int dominantIntensity= 0;
            for (int i= 0; i< 256; i++)
            {
                if (count[i]> maxCount)
                {
                    maxCount=count[i];
                    dominantIntensity= i;
                }
            }
            if (maxCount>0)
            {
                dominantColor[0] =colorCount[dominantIntensity][0]/maxCount;
                dominantColor[1] =colorCount[dominantIntensity][1]/maxCount;
                dominantColor[2] =colorCount[dominantIntensity][2]/maxCount;
            }
            image(x, y, 0) =dominantColor[0];
            image(x, y, 1) =dominantColor[1];
            image(x, y, 2) =dominantColor[2];
        }
    }
}
//***/ /***//***//***//***//***//
void InfraredFilter(Image& image)
{
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
}
//***/ /***//***//***//***//***//
void BlurFilter(Image& image)
{
    int level;
    cout<< "Please enter the blur level (1-5): ";
    cin>> level;

    while (level<1 || level>5) {
        cout << "Invalid blur level. Please enter a value between 1 and 5: ";
        cin>>level;
    }
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
}
//***/ /***//***//***//***//***//
void makeBlackWhite(Image& img)
{
    const int limit= 128;

    for (int row = 0; row < img.height; row++)
    {
        for (int col = 0; col < img.width; col++)
        {
            int r = img.getPixel(col, row, 0);
            int g = img.getPixel(col, row, 1);
            int b = img.getPixel(col, row, 2);

            int average = (r + g + b) /3;

            if (average>=limit)
            {
                img.setPixel(col, row, 0, 255);
                img.setPixel(col, row, 1, 255);
                img.setPixel(col, row, 2, 255);
            }
            else
            {
                img.setPixel(col, row, 0, 0);
                img.setPixel(col, row, 1, 0);
                img.setPixel(col, row, 2, 0);
            }
        }
    }
}
//***/ /***//***//***//***//***//
void detectEdges(Image& img)
{

    for (int row = 0; row < img.height; row++)
    {
        for (int col = 0; col < img.width; col++)
        {
            int r = img.getPixel(col, row, 0);
            int g = img.getPixel(col, row, 1);
            int b = img.getPixel(col, row, 2);

            int brightness = (r + g + b) / 3;

            img.setPixel(col, row, 0, brightness);
            img.setPixel(col, row, 1, brightness);
            img.setPixel(col, row, 2, brightness);
        }
    }

    for (int row = 1; row < img.height - 1; row++)
    {
        for (int col = 1; col < img.width - 1; col++)
        {
            int currentPixel = img.getPixel(col, row, 0);

            int nextPixel = img.getPixel(col + 1, row, 0);
            int lowerPixel = img.getPixel(col, row + 1, 0);

            int horizontalChange = abs(currentPixel - nextPixel);
            int verticalChange = abs(currentPixel - lowerPixel);

            int edgeStrength = horizontalChange + verticalChange;

            if (edgeStrength > 40)
            {
                img.setPixel(col, row, 0, 0);
                img.setPixel(col, row, 1, 0);
                img.setPixel(col, row, 2, 0);
            }
            else
            {
                img.setPixel(col, row, 0, 255);
                img.setPixel(col, row, 1, 255);
                img.setPixel(col, row, 2, 255);
            }
        }
    }
}
//***/ /***//***//***//***//***//
void applyInvert(Image& image){
    for (int i=0;i<image.width;i++)
    {
        for (int j=0;j<image.height;j++)
        {

            for (int k=0;k<image.channels;k++) {

                image(i,j,k) = 255-image(i,j,k);
            }

        }
    }
}
//***/ /***//***//***//***//***//
void applyDarkenandLighten (Image& image){
    float userpercentage;
    cout<<"Please enter the lighten(+) or darken(-) percentage";
    cin>>userpercentage;

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
}
//***/ /***//***//***//***//***//
void applygray (Image& image){
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
}
//***/ /***//***//***//***//***//
void applyflip(Image& image) {
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
}
//***/ /***//***//***//***//***//
void fancyFrame(Image& image, int colorChoice)
{
    int width = image.width;
    int height = image.height;
    int outer=20;
    int inner=12;
    int r, g, b;
    if (colorChoice == 1) { r = 255; g = 0; b = 0; } 
    else if (colorChoice == 2) { r = 255; g = 165; b = 0; } 
    else if (colorChoice == 3) { r = 255; g = 215; b = 0; } 
    else if (colorChoice == 4) { r = 0; g = 128; b = 0; } 
    else if (colorChoice == 5) { r = 0; g = 0; b = 255; } 
    else if (colorChoice == 6) { r = 75; g = 0; b = 130; } 
    else if (colorChoice == 7) { r = 238; g = 130; b = 238; } 
    else if (colorChoice == 8) { r = 0; g = 0; b = 0; } 
    else {
        cout << "Invalid color choice. Using default color (Red)." << endl;
        r = 255;
        g = 0;
        b = 0;
    }
    
    for(int y=0; y< height;y++)
    {
        for(int x=0; x< width;x++)
        {
            if(x<=outer || x>=width-outer || y<=outer || y>=height-outer)
            {
                image.setPixel(x,y,0,255);
                image.setPixel(x,y,1,255);
                image.setPixel(x,y,2,255);
            }
            else if((x>=outer && x< outer+inner) || (x>=width-inner-outer && x<width-outer) || (y>=outer && y< outer+inner) || (y>=height-inner-outer && y<height-outer))
            {
                image.setPixel(x,y,0,r);
                image.setPixel(x,y,1,g);
                image.setPixel(x,y,2,b);
            }
        }
    }
}
//***/ /***//***//***//***//***//
void frameFilter(Image& image)
{
    int FilterType;
    cout <<"Please Choose Filter Type: 1.simple , 2.fancy\n";
    cin >> FilterType;
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
    }
    else if(FilterType==2){
        cout<<"Choose a color: 1.Red, 2.Orange, 3.Yellow,4.Green, 5.Blue, 6.Indigo, 7.Violet, 8.Black\n";
        int colorChoice;
        cin>>colorChoice;
        fancyFrame(image, colorChoice);
    }
}
//***/ /***//***//***//***//***//
void resizeFilter(Image& image, int newWidth, int newHeight)
{
    Image newImage;
    newImage.width = newWidth;
    newImage.height = newHeight;
    newImage.channels = 3;
    newImage.imageData = (unsigned char*)malloc(newWidth * newHeight * 3);
    for (int y = 0; y < newHeight; y++)
    {
        for (int x = 0; x < newWidth; x++)
        {
            int oldX = x * image.width / newWidth;
            int oldY = y * image.height / newHeight;

            newImage.setPixel(x, y, 0, image.getPixel(oldX, oldY, 0));
            newImage.setPixel(x, y, 1, image.getPixel(oldX, oldY, 1));
            newImage.setPixel(x, y, 2, image.getPixel(oldX, oldY, 2));
        }
    }
    image = newImage;
}
//***/ /***//***//***//***//***//

void loadimage(Image& image, string& filename){
    int iext;
    string ext;
    while(true){
        cout<<"Please enter the image file name: "<<endl;
        cin>>filename;
        ext="";
        iext=filename.find_last_of(".");
        if (iext!=string::npos){
            ext=filename.substr(iext);
        }
         if(ext==".jpg" || ext==".png" || ext==".bmp" || ext==".tga"|| ext==".jpeg"){
             try{image.loadNewImage(filename);
                cout<<"Image loaded successfully! "<<endl;  
               break;  }
               catch(...){ cout<<"File not found!"<<endl;}
            }
                         
        else{
      
         cout<<"This extention is invalid,please enter the a valid extention"<<endl;
            }
       
    }


}


int main(){
    string filename;
    Image image;
    loadimage(image,filename);
    Image OriginalImage=image;
    string Newimagename;

    

    stack<Image> undoStack;
    stack<Image> redoStack;
    int userchoice =-1;

    int choice=-1;
    int savechoice=-1;
    
    while(userchoice!=0){
        cout<<"Choose filter number: 1.Invert , 2.DarkenLighten , 3.Frame , 4.Resize ,5.Gray, 6.Flip , 7.BlackandWhite, 8.Edge Detection, 9.Blur, 10.Infrared, 11.crop, 12.purple, 13.OldTV, 17.Skew, 18.OilPaint, 19.Undo, 20.Redo, 21.load new image, 22.save current image, 0.Exit\n";
        cin>>userchoice;
        switch (userchoice)
        {    
            case 1:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                applyInvert(image);
                break;
    
            case 2:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                applyDarkenandLighten(image);
                break;

            case 3:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                frameFilter(image);
                 break;
            case 4:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                int newWidth, newHeight;
                cout<<"Please enter new width: ";
                cin >>newWidth;
                cout<<"Please enter new height: ";
                cin>>newHeight;
                resizeFilter(image, newWidth, newHeight);
                break;
            case 5:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                applygray(image);
                break;

            case 6:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                applyflip(image);
                break;

            case 7:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                makeBlackWhite(image);
                break;

            case 8:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                detectEdges(image);
                break;
    
            case 9:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                BlurFilter(image);
                break;

            case 10:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                InfraredFilter(image);
                break;
            case 11:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                crop(image);
                break;

            case 12:
            undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                purple(image);
                break;
    
            case 13:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                OldTV(image);
                break;

            case 17:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                Skew(image);
                break;
                   
            case 18:
                undoStack.push(image);
                while(!redoStack.empty()) {
                    redoStack.pop();
                }
                oilPaint(image);
                break;

            case 19:
                if(!undoStack.empty()) {
                    redoStack.push(image);
                    image = undoStack.top();
                    undoStack.pop();
                } 
                else {
                    cout << "No actions to undo." << endl;
                }
                break;

            case 20:
                if(!redoStack.empty()) {
                    undoStack.push(image);
                    image = redoStack.top();
                    redoStack.pop();
                } 
                else {
                    cout << "No actions to redo." << endl;
                }
                break;

            case 21:
                cout<<"Do you want to save current image before loading new one? (1.yes / 2.no)"<<endl;
                cin>>choice;
                if (choice==1){
                    cout<<"Do you want to save to the same file(1),or enter a new file name(2)"<<endl;
                    cin>>savechoice;
                    if(savechoice==1){
                        image.saveImage(filename);
                    } 
                    else if(savechoice==2){
                        cout<<"Please enter the new image name with extention to save: ";
                        cin>>Newimagename;
                        image.saveImage(Newimagename);
                    }
                }
                loadimage(image,filename);
                OriginalImage=image;
                while(!undoStack.empty()){
                    undoStack.pop();
                }
                while(!redoStack.empty()){
                    redoStack.pop();
                }
                break;
     
            case 22:
                cout<<"Do you want to save to the same file(1),or enter a new file name(2)"<<endl;
                cin>>savechoice;
                if(savechoice==1){
                    image.saveImage(filename);
                    cout<<"Image saved successfully!"<<endl;
                } 
                else if(savechoice==2){
                    cout<<"Please enter the new image name with extention to save: ";
                    cin>>Newimagename;
                    image.saveImage(Newimagename);
                    filename=Newimagename;
                    cout<<"Image saved successfully!"<<endl;
                }
                break;

            case 0:
                cout<<"Do you want to save the current image before exiting? 1.yes,2.no"<<endl;
                cin>>choice;
                if(choice==1){
                    cout<<"Do you want to save to the same file(1),or enter a new file name(2)"<<endl;
                    cin>>savechoice;
                    if(savechoice==1){
                        image.saveImage(filename);
                    } 
                    else if(savechoice==2){
                        cout<<"Please enter the new image name with extention to save: ";
                        cin>>Newimagename;
                        image.saveImage(Newimagename);
                    }
                }   
                else if (choice==2){
                    image=OriginalImage;
                    image.saveImage(filename);
                    cout<<"Goodbye!!!";
                }
                break;

            default:
                cout<<"Invaild choice!!";
                break;
        }
    }
    return 0;
}
