#include "PmergeMe.hpp"

void check_errors(int ac, char **av, std::vector<int> &vec){
	for(int i = 1; i < ac; i++){
			if(check_aruments(av[i]) == 1){
				if(std::atoi(av[i]) >= 0 && std::atoi(av[i]) <= INT_MAX)
					vec.push_back(std::atoi(av[i]));
				else
					throw std::invalid_argument("Error wrong argument");
			}
			else
				throw std::invalid_argument("Error wrong argument");
	}
	
}

int check_aruments(std::string av){
	for (size_t i = 0; i < av.length(); i++){
		if (!isdigit(av[i]) && av[i] != ' ')
			return 0;
	}
	return 1;
}
