#include "Image_Class.h"
#include <iostream>

using namespace std;

void makeBlackWhite(Image& img)
{
    const int limit = 128;

    for (int row = 0; row < img.height; row++)
    {
        for (int col = 0; col < img.width; col++)
        {
            int r = img.getPixel(col, row, 0);
            int g = img.getPixel(col, row, 1);
            int b = img.getPixel(col, row, 2);

            int average = (r + g + b) / 3;

            if (average >= limit)
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

int main()
{
    Image img("building.jpg");

    int filterNumber;

    cout << "Choose a filter:" << endl;
    cout << "1 - Black and White" << endl;
    cout << "Enter number: ";
    cin >> filterNumber;

    if (filterNumber == 1)
    {
        makeBlackWhite(img);
        img.saveImage("building_bw.jpg");

        cout << "Filter completed." << endl;
    }

    return 0;
}