#include <iostream>
#include <map>
#include "BitcoinExchange.hpp"

struct data
{
    int year;
    int mounth;
    int day;
};


bool check_date(data *t){
    return (t->year >= 2009 && t->year <=2023 && t->mounth >=1 && t->mounth <= 12 && t->day >= 1 && t->day <= 30);
}
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