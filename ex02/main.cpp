#include "PmergeMe.hpp"

int main(int ac, char **av){
	if (ac > 1){
		try{
			PmergeMe test;
			test.Llaunch(ac, av);
		}
		catch(std::exception &e){
			// std::cout << "here" << std::endl;
			std::cout << e.what() << std::endl;
		}
	}
}