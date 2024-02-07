#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {

}

// PmergeMe::PmergeMe(const PmergeMe& copy) {

// }

// PmergeMe& PmergeMe::operator=(const PmergeMe& copy) {

// }

PmergeMe::~PmergeMe() {

}
int count = 0;

void	print(PmergeMe::vec2 arr);

// static int check_dup(std::string av){
// 	for(size_t i = 0; i < av.length(); i++){
// 		for(size_t j = i + 1; j < av.length(); j++){
// 			if(av[i] == av[j])
// 				return 0;
// 		}
// 	}
// 	return 1;
// }

void check_dup(PmergeMe::vec1 vc){
	for(size_t i = 0; i < vc.size(); i++){
		for(size_t j = i + 1; j < vc.size(); j++){
			if(vc[i] == vc[j])
				throw std::invalid_argument("Error wrong argument");
		}
	}
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
	check_dup(data);
	mainfunc(data, arr);
	sort();
	print(arr);
}


PmergeMe::vec1 swapvec(PmergeMe::vec1 vec1, PmergeMe::vec1 vec2){
	PmergeMe::vec1 vec;
	if (vec1.back() < vec2.back()){
		count++;
		for (size_t i = 0; i < vec1.size(); i++){
			vec.push_back(vec1[i]);
		}
		for (size_t i = 0; i < vec2.size(); i++){
			vec.push_back(vec2[i]);
		}
	}
	else{
		count++;
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
	std::cerr << "count == " << count << "\n";
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
	vec1 tmp;
	tmp = merge();
	if(arr.size() > 1){
		sort();
	}
	insert_(tmp);
}

static void spltvec(PmergeMe::vec2 &arr){
	PmergeMe::vec2 newarr;
	PmergeMe::vec1 tmp1;
	PmergeMe::vec1 tmp2;
	for(size_t i = 0; i < arr.size(); i++){
		for(size_t j = 0 ; j < (arr[i].size()); j++){
			if(j < arr[i].size() / 2)
				tmp1.push_back(arr[i][j]);
			else
				tmp2.push_back(arr[i][j]);
		}
		newarr.push_back(tmp1);
		newarr.push_back(tmp2);
		tmp1.clear();
		tmp2.clear();
	}
	arr = newarr;
}

bool	compare(PmergeMe::vec1 v1, PmergeMe::vec1 v2){
	count++;
	return (v1.back() < v2.back());
}
void update(PmergeMe::vec2::iterator& it, std::vector< std::pair<PmergeMe::vec2::iterator, PmergeMe::vec1> >& pend_pair){
	size_t i = 0;
    for (i = 0; i < pend_pair.size(); ++i) {
        if (pend_pair[i].first >= it)
            ++pend_pair[i].first;
    }
}

void PmergeMe::insert_(vec1 tmp){
	vec2 main;
	vec2 pend;

	std::vector< std::pair<vec2::iterator, vec1> > pend_pair;
	spltvec(arr);

	main.reserve(arr.size());
	main.push_back(arr[0]);
	main.push_back(arr[1]);
	
	vec2::iterator t;
	std::pair<vec2::iterator, vec1> tmp1;

	for(size_t i = 2; i < arr.size(); i += 2 ){
		t = main.insert(main.end(), arr[i+1]);
		tmp1.first = t;
		tmp1.second = arr[i];
		pend_pair.push_back(tmp1);
	}
	if (!tmp.empty()) {
		tmp1.first = main.end();
		tmp1.second = tmp;
		pend_pair.push_back(tmp1);
	}

	vec2::iterator it;
	for (size_t i = 0; i < pend_pair.size(); i++) {
		it = std::lower_bound(main.begin(), pend_pair[i].first, pend_pair[i].second, compare);
		main.insert(it, pend_pair[i].second);
		update(it, pend_pair);
	}
	arr = main;
} 

 