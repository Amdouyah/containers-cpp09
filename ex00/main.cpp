#include <iostream>
#include <map>
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        std::string str(av[1]);
        BitcoinExchange tst;
        tst.read_data();
        tst.read_input(str);
    }
}