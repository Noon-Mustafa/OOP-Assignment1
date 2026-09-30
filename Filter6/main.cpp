#include "Image_Class.h"

void edgeDetection(Image& image)
{
    // تحويل الصورة إلى Grayscale
    for (int _y = 0; _y < image.height; _y++)
    {
        for (int _x = 0; _x < image.width; _x++)
        {
            int red = image.getPixel(_x, _y, 0);
            int green = image.getPixel(_x, _y, 1);
            int blue = image.getPixel(_x, _y, 2);

            int gray = (red + green + blue) / 3;

            image.setPixel(_x, _y, 0, gray);
            image.setPixel(_x, _y, 1, gray);
            image.setPixel(_x, _y, 2, gray);
        }
    }

    // اكتشاف الحواف
    for (int _y = 1; _y < image.height - 1; _y++)
    {
        for (int _x = 1; _x < image.width - 1; _x++)
        {
            int current = image.getPixel(_x, _y, 0);

            int right = image.getPixel(_x + 1, _y, 0);
            int bottom = image.getPixel(_x, _y + 1, 0);

            int differenceX = abs(current - right);
            int differenceY = abs(current - bottom);

            int difference = differenceX + differenceY;

            if (difference > 40)
            {
                image.setPixel(_x, _y, 0, 0);
                image.setPixel(_x, _y, 1, 0);
                image.setPixel(_x, _y, 2, 0);
            }
            else
            {
                image.setPixel(_x, _y, 0, 255);
                image.setPixel(_x, _y, 1, 255);
                image.setPixel(_x, _y, 2, 255);
            }
        }
    }
}

int main()
{
    Image image("night3.jpg");

    edgeDetection(image);

    image.saveImage("night3_edges.jpg");
}