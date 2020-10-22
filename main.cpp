#include <iostream>
#include "sokuban.hpp"

int main() 
{
    Sokuban sokuban = Sokuban();
    std::string choice;
    while (true)
    {
        sokuban.solve();
        std:cout << "Press (q)uit to quit ";
        std::cin >> choice;
        if (choice == "quit" || choice == "q") break;
    }
}