#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){

}
BitcoinExchange::~BitcoinExchange(){

}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy){
	*this = copy;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy){
	this->mp = copy.mp;
	return *this;
}

void BitcoinExchange::read_data(){
        std::ifstream input("data.csv");
		std::string line;

		if (input.is_open())
		{
			getline(input, line);
			while(getline(input, line)){
				size_t index = line.find(","); 
				if(index != std::string::npos){
					std::string key = line.substr(0,index);
					std::string value = line.substr(++index);
					mp[key] = value;
				}
				else{
					std::cout << "Error" << std::endl;
					exit(2);
				}
			}
		}
		else{
			std::cerr << "Error open file data.csv "<< std::endl;
			exit(2);
		}
}
static int check_line(std::string key){
	if(key.length() != 10 || (key[4] != '-' || key[7] != '-'))
		return 1;
	for(size_t i = 0; i < key.length(); i++){
		if (i == 4 || i == 7)
			i++;
		if(key[i] > '9' || key[i] < '0'){
			return 1;
		}
	}
	int yr = std::strtod(key.substr(0, 4).c_str(), NULL);
	int mo = std::strtod(key.substr(5, 2).c_str(), NULL);
	int dy = std::strtod(key.substr(8, 2).c_str(), NULL);
	if (!(yr >= 2009 && yr <= 2024 && mo >=1 && mo <= 12 && dy >= 1 && dy <= 31))
		return (1);
	return 0;
}

static size_t	ft_strlen(char *str){
	size_t i = 0;
	while (str[i])
		i++;
	return i;
}
static double check_value(std::string value){
	for (size_t i = 0; i < value.length(); i++){
		if(value[i] != ' ' && !isdigit(value[i]) && value[i] != '.' && value[i] != '-'){
			std::cerr << "Error: bad input => " + value << std::endl;
			return(-1);
		}
	}
	char *end = NULL;
	double val = std::strtod(value.c_str(), &end);
	if (ft_strlen(end) != 0){
		std::cerr << "Error: bad input => " + value << std::endl;
		return(-1);
	}
	if (val < 0){
		std::cerr << "Error: not a positive number" << std::endl;
		return(-1);
	}
	if(val > 1000){
		std::cerr << "Error: too large a numbe" << std::endl;
		return(-1);
	}
	return(val);
}

void BitcoinExchange::read_input(std::string &av){
	std::ifstream input(av.c_str());
	std::string line;
	std::getline(input, line);
	if (line != "date | value"){
		std::cerr << "Error: input file" << std::endl;
		exit(2);
	}
	while(getline(input, line)){
		size_t pos = line.find('|');
		if(pos == std::string::npos){
			std::cerr << "Error: bad input => " + line << std::endl;
			continue;
		}
		std::string key = line.substr(0, pos - 1);
		std::string value = line.substr(pos + 2);
		if(check_line(key)){
			std::cerr << "Error: bad input => " + key << std::endl;
			continue;
		}
		if (check_value(value) == -1)
			continue;
		std::map<std::string, std::string>::iterator it = mp.lower_bound(key);
		if (it->first == key)
		{
			double sec = std::strtod(it->second.c_str() , NULL);
			double vl = std::strtod(value.c_str() , NULL);
			std::cout << key << " => " << value << " = " << sec * vl << std::endl;
		}
		else{
			--it;
			double sec = std::strtod(it->second.c_str() , NULL);
			double vl = std::strtod(value.c_str() , NULL);
			std::cout << key << " => " << value << " = " << sec * vl << std::endl;
		}	
	}
}

