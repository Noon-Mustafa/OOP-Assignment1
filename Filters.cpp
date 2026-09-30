# include <iostream>
# include "Image_Class.h"
#include <stack>
using namespace std;

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


int main(){
    string imagename;
    cout<<"Please enter the image name: ";
    cin>>imagename;

     string Newimagename;
    
    Image image(imagename);

    stack<Image> undoStack;
    stack<Image> redoStack;
    int userchoice =-1;
    
    while(userchoice!=0){
        cout<<"Choose filter number: 1.Invert , 2.DarkenLighten , 3.Frame , 4.Resize ,5.Gray, 6.Flip , 9.Undo , 10.Redo , 0.Exit\n";
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
    
    case 9:
        if(!undoStack.empty()) {
            redoStack.push(image);
            image = undoStack.top();
            undoStack.pop();
        } else {
            cout << "No actions to undo." << endl;
        }
        break;

    case 10:
        if(!redoStack.empty()) {
            undoStack.push(image);
            image = redoStack.top();
            redoStack.pop();
        } else {
            cout << "No actions to redo." << endl;
        }
        break;
    
    case 0:
    cout<<"Please enter the new image name with extention to save: ";
    cin>>Newimagename;
    image.saveImage(Newimagename);
    break;

    default:
    cout<<"Invaild choice!!";
        break;
    }
    }
    
}
