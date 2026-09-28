# include <iostream>
# include "Image_Class.h"
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
void applyDarkenLighten(Image& image){
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

int main(){
    string imagename;
    cout<<"Please enter the image name";
    cin>>imagename;

     string Newimagename;
    
    Image image(imagename);
    int userchoice =-1;
    
    while(userchoice!=0){
        cout<<"Choose filter number: 1.Invert , 2.DarkenLighten , 0.Exit";
    cin>>userchoice;
        switch (userchoice)
    {
        
    case 1:
        applyInvert(image);
        break;
    
    case 2:
       applyDarkenLighten(image);
       break;
    
    case 0:
    cout<<"Please enter the new image name with extention to save:";
    cin>>Newimagename;
    image.saveImage(Newimagename);
    break;

    default:
    cout<<"Invaild choice!!";
        break;
    }
    }
    
}