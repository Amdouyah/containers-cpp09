#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

//m1.insert(pair<int, char>(1, 'c')):template class in part of the STL
//allow u to store heterogeneous objects as a single unit


#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange{
	public:
		std::map<std::string, std::string> mp;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);
		void read_data();
		void read_input(std::string &av);
		~BitcoinExchange();
};

#endif