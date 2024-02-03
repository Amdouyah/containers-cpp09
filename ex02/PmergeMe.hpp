#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>


class PmergeMe {
	public:
		typedef std::vector<int>	vec1;
		typedef	std::vector< vec1 >	vec2;

	private:
		vec1 data;
		vec2 arr;
	public:
		PmergeMe();
		// PmergeMe(const PmergeMe& copy);
		// PmergeMe& operator=(const PmergeMe& copy);
		~PmergeMe();

		void	launch(int ac, char **av);
		vec1	merge();
		void	sort();
		void 	insert(vec1 tmp);
};

#endif