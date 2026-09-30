#include "Image_Class.h"
#include <iostream>
#include <cstdlib>

using namespace std;

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

int main()
{
    Image img("night3.jpg");

    detectEdges(img);

    img.saveImage("night3_edges.jpg");

    cout << "Edge detection completed." << endl;

    return 0;
}
