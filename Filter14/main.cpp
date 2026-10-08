#include "Image_Class.h"

void oldTV(Image& image)
{
    for (int _y = 0; _y < image.height; _y++)
    {
        for (int _x = 0; _x < image.width; _x++)
        {
            int red = image.getPixel(_x, _y, 0);
            int green = image.getPixel(_x, _y, 1);
            int blue = image.getPixel(_x, _y, 2);

            int gray = (red + green + blue) / 3;

            if (_y % 2 == 0)
            {
                gray = gray * 7 / 10;
            }

            image.setPixel(_x, _y, 0, gray);
            image.setPixel(_x, _y, 1, gray);
            image.setPixel(_x, _y, 2, gray);
        }
    }
}

int main()
{
    Image image("night3.jpg");

    oldTV(image);

    image.saveImage("night3_oldTV.jpg");
}