#include "Image_Class.h"
#include <iostream>
using namespace std;

void rotate(Image& image, int angle)
{
    int times = angle / 90;

    for (int i = 0; i < times; i++)
    {
        Image rotated(image.height, image.width);

        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
                for (int c = 0; c < 3; c++)
                {
                    rotated.setPixel(
                        image.height - 1 - y,
                        x,
                        c,
                        image.getPixel(x, y, c)
                    );
                }
            }
        }

        image = rotated;
    }
}

int main()
{
    Image image("night3.jpg");

    int angle;
    cout << "Enter angle (90, 180, 270): ";
    cin >> angle;

    rotate(image, angle);

    image.saveImage("night3_rotated.jpg");

    cout << "Image rotated successfully!";
}