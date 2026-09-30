#include "Image_class.h"


void blackAndWhite(Image& image)
{
    int threshold = 128;

    for (int _y = 0; _y < image.height; _y++)
    {
        for (int _x = 0; _x < image.width; _x++)
        {
            int red = image.getPixel(_x, _y, 0);
            int green = image.getPixel(_x, _y, 1);
            int blue = image.getPixel(_x, _y, 2);

            int gray = (red + green + blue) / 3;

            int value;

            if (gray < threshold)
                value = 0;
            else
                value = 255;

            image.setPixel(_x, _y, 0, value);
            image.setPixel(_x, _y, 1, value);
            image.setPixel(_x, _y, 2, value);
        }
    }
}
int main()
{
    Image image("building.jpg");

    blackAndWhite(image);

    image.saveImage("building_bw.jpg");
}