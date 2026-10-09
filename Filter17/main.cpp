
#include "Image_Class.h"
#include <iostream>
using namespace std;

int main()
{
    string filename;
    cout << "Enter image name: ";
    getline(cin, filename);

    Image image(filename);

    int angle;
    cout << "Enter skew angle: ";
    cin >> angle;

    int width = image.width;
    int height = image.height;

    Image result(width + height, height);

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

    result.saveImage("skew_result.jpg");

    cout << "Skew filter applied successfully!" << endl;

    return 0;
}