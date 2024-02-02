#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {

}

// PmergeMe::PmergeMe(const PmergeMe& copy) {

// }

// PmergeMe& PmergeMe::operator=(const PmergeMe& copy) {

// }

PmergeMe::~PmergeMe() {

}


static int check_aruments(std::string av){
	for (size_t i = 0; i < av.length(); i++){
		if (!isdigit(av[i]) && av[i] != ' ')
			return 0;
	}
	return 1;
}

static void check_errors(int ac, char **av, std::vector<int> &vec){
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

static	void mainfunc(PmergeMe::vec1 &vec, PmergeMe::vec2 &Secvec) {
	std::vector<int>::iterator it;
	for(it = vec.begin(); it != vec.end(); ++it){
		std::vector<int> tempvec;
		tempvec.push_back(*it);
		Secvec.push_back(tempvec);
	}
}

void	PmergeMe::launch(int ac, char **av) {
	check_errors(ac, av, data);
	mainfunc(data, arr);

	sort();
}


PmergeMe::vec1 swapvec(PmergeMe::vec1 vec1, PmergeMe::vec1 vec2){
	PmergeMe::vec1 vec;
	if (vec1.back() < vec2.back()){
		for (size_t i = 0; i < vec1.size(); i++){
			vec.push_back(vec1[i]);
		}
		for (size_t i = 0; i < vec2.size(); i++){
			vec.push_back(vec2[i]);
		}
	}
	else{
		for (size_t i = 0; i < vec2.size(); i++){
			vec.push_back(vec2[i]);
		}
		for (size_t i = 0; i < vec1.size(); i++){
			vec.push_back(vec1[i]);
		}
	}
	return vec;
}

void	print(PmergeMe::vec2 arr) {
	std::cout << "VecofVec";
	for (int i = 0; i < (int)arr.size(); i++) {
		arr[i];
		arr[i+1];
		std::cout << " [";
		for (int j = 0; j < (int)arr[i].size(); j++) {
			std::cout << " " << arr[i][j];
		}
		std::cout << " ]";
	}
	std::cout << std::endl;
}

PmergeMe::vec1 PmergeMe::merge() {
	vec1 tmp;
	vec2 newArr;

	if (arr.size() % 2 != 0)
	{
		tmp = arr.back();
		arr.pop_back();
	}
	for(size_t i = 0; i < arr.size(); i+=2){
		vec1 tmp1 = swapvec(arr[i], arr[i+1]);
		newArr.push_back(tmp1);
	}
	arr = newArr;
	return(tmp);
}

void PmergeMe::sort(){
	print(arr);
	vec1 tmp;
	tmp = merge();
	if(arr.size() > 1){
		sort();
	}
	print(arr);
}
