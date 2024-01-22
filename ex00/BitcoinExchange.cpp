#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){

}
BitcoinExchange::~BitcoinExchange(){

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
					std::cout << "Error miroka" << std::endl;
					exit(2);
				}
			}
			// for (std::map<std::string, std::string>::iterator it = mp.begin(); it != mp.end(); ++it)
           	// 	 std::cout << "Date: " << it->first << ", Value: " << it->second << std::endl;
		}
		else{
			std::cerr << "Error open file data.csv "<< std::endl;
			exit(2);
		}
}
void check_line(std::string key, std::string __unused value){
	if(key.length() != 10 || (key[4] != '-' || key[7] != '-'))
		throw "Error bad argument ";
	for(size_t i = 0; i < key.length(); i++){
		if (i == 4 || i == 7)
			i++;
		if(key[i] > '9' || key[i] < '0'){
			throw "Error: bad input ";
		}
	}
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
		try{
			check_line(key, value);
		}
		catch(const char* e){
			std::cout << e << std::endl;
			continue;
		}
	}
}

