#include "PmergeMe.hpp"

int main(int ac, char **av){
	if (ac > 1){
		try{
			std::vector<int> vec;
			check_errors(ac, av, vec);
		}
		catch(std::exception &e){
			std::cout << e.what() << std::endl;
		}
	}
}