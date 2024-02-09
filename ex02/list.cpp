#include "PmergeMe.hpp"

int _count = 0;

static void	print_list(PmergeMe::list2 arr) {
	  std::cout << "listo";
    for (PmergeMe::list2::iterator it = arr.begin(); it != arr.end(); ++it) {
        std::cout << " [";
        for (std::list<int>::iterator innerIt = it->begin(); innerIt != it->end(); ++innerIt) {
            std::cout << " " << *innerIt;
        }
        std::cout << " ]";
    }
    std::cout << std::endl;
    std::cerr << "count == " << _count << "\n";
}

static void check_dup_list(PmergeMe::list1 lst){

	for (PmergeMe::list1::iterator it1 = lst.begin(); it1 != lst.end(); ++it1) {
        for (PmergeMe::list1::iterator it2 = std::next(it1); it2 != lst.end(); ++it2) {
            if (*it1 == *it2)
                throw std::invalid_argument("Error wrong argument");
        }
    }
}
static int check_aruments_list(std::string av){
	for (size_t i = 0; i < av.length(); i++){
		if (!isdigit(av[i]) && av[i] != ' ')
			return 0;
	}
	return 1;
}

static void check_errors_list(int ac, char **av, std::list<int> &lst){
	for(int i = 1; i < ac; i++){
			if(check_aruments_list(av[i]) == 1){
				if(std::atoi(av[i]) >= 0 && std::atoi(av[i]) <= INT_MAX)
					lst.push_back(std::atoi(av[i]));
				else
					throw std::invalid_argument("Error wrong argument");
			}
			else
				throw std::invalid_argument("Error wrong argument");
	}

	
}
static	void mainfunc_list(PmergeMe::list1 &lst, PmergeMe::list2 &Seclst) {
	std::list<int>::iterator it;
	for(it = lst.begin(); it != lst.end(); ++it){
		std::list<int> tempvec;
		tempvec.push_back(*it);
		Seclst.push_back(tempvec);
	}
}
static PmergeMe::list1 swaplst(PmergeMe::list1 list1, PmergeMe::list1 list2){
	PmergeMe::list1 lst;
    if (list1.back() < list2.back()) {
		_count++;
        lst.insert(lst.end(), list1.begin(), list1.end());
        lst.insert(lst.end(), list2.begin(), list2.end());
    }
	else {
		_count++;
        lst.insert(lst.end(), list2.begin(), list2.end());
        lst.insert(lst.end(), list1.begin(), list1.end());
    }
    return lst;
}

PmergeMe::list1 PmergeMe::Lmerge() {
	list1 tmp;
	list2 newArr;

	if (Larr.size() % 2 != 0)
	{
		tmp = Larr.back();
		Larr.pop_back();
	}
	list2::iterator it = Larr.begin();
	while(it != Larr.end()){
		list1 tmp1 = swaplst(*it, *(std::next(it)));
		newArr.push_back(tmp1);
		std::advance(it, 2);
	}
	Larr = newArr;
	return(tmp);
}
static void spltlst(PmergeMe::list2 &arr){
	PmergeMe::list2 newlst;
	PmergeMe::list1 tmp1;
	PmergeMe::list1 tmp2;
	for(PmergeMe::list2::iterator it = arr.begin(); it != arr.end(); ++it){
		size_t midpoint = it->size() / 2;

		PmergeMe::list1::iterator it1 = it->begin();
		for(size_t j = 0 ; it1 != it->end(); j++, ++it1){
			if(j < midpoint)
				tmp1.push_back(*it1);
			else
				tmp2.push_back(*it1);
		}
		newlst.push_back(tmp1);
		newlst.push_back(tmp2);
		tmp1.clear();
		tmp2.clear();
	}
	arr = newlst;
}
static bool	compare(PmergeMe::list1 v1, PmergeMe::list1 v2){
	_count++;
	return (v1.back() < v2.back());
}

void PmergeMe::Linsert_(list1 tmp){
	list2 main;
	list2 pend;

	std::list< std::pair<list2::iterator, list1> > pend_pair;
	spltlst(Larr);

	main.push_back(*Larr.begin());
	main.push_back(*std::next(Larr.begin()));
	
	list2::iterator t;
	std::pair<list2::iterator, list1> tmp1;

	for(list2::iterator tt = std::next(Larr.begin(), 2); tt != Larr.end(); std::advance(tt ,2) ){
		t = main.insert(main.end(), *std::next(tt, 1));
		tmp1.first = t;
		tmp1.second = *tt;
		pend_pair.push_back(tmp1);

	}
	if (!tmp.empty()) {
		tmp1.first = main.end();
		tmp1.second = tmp;
		pend_pair.push_back(tmp1);
	}

	list2::iterator it;
	for (std::list<std::pair<list2::iterator, list1> >::iterator pendIt = pend_pair.begin(); pendIt != pend_pair.end(); ++pendIt) {
        it = std::lower_bound(main.begin(), pendIt->first , pendIt->second, compare);
        main.insert(it, pendIt->second);
    }
	Larr = main;
}

void PmergeMe::Lsort(){
	list1 tmp;
	tmp = Lmerge();
	print_list(Larr);
	if(Larr.size() > 1){
		Lsort();
	}
	Linsert_(tmp);
}

void	PmergeMe::Llaunch(int ac, char **av) {
	check_errors_list(ac, av, Ldata);
	check_dup_list(Ldata);
	mainfunc_list(Ldata, Larr);
	Lsort();
	print_list(Larr);
}