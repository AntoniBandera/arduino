#include<iostream>
void rotate(int z)
{
    int d = 4;
    int pos = 90;
    while (pos > 90 - z)
    {
        pos = pos-d;
        std::cout << pos << std::endl;
    }
    while (pos < 90 + z)
    {
        pos = pos+d;
        std::cout << pos << std::endl;
    }
    while (pos > 90)
    {
        pos = pos-d;
        std::cout << pos << std::endl;
    }
}

int main()
{
    char a;
    while (1)
    {
        std::cin >> a;
        int r = 90;
        if (a == 'z')
        {
            rotate(30);
            a = ' ';
        }
        if (a == 'q')
            break;
    }
    return 0;
}
