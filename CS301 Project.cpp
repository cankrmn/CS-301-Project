#include <iostream>
#include <vector>
#include <Bits.h>
#include <stdio.h>
#include <time.h>

using namespace std;

vector<int> randomVectorGenerator() { // generates random vectors of random sizes
	int size = rand() % 13;
	vector<int> v (size);
	for(int i = 0; i < size; i++) {
		v[i] = rand() % 50;
	}
	return v;
}

void vectorPrinter (vector<int> & v) { // prints the given vector
	for(int i = 0; i < v.size(); i++) {
		cout << v[i] << "  ";
	}
	cout << endl;
}

void subsetPrinter(vector< vector<int> > & v) { // prints the whole subset but for the "OLD" solution
	for(int i = 0; i < v.size(); i++) {
		vectorPrinter(v[i]);
	}
	cout << "Cardinality = " << v.size() << endl;
}

bool isIntersecting(vector<int> & a, vector<int> & b) { // returns true if given two sets are intersecting, returns false if they are disjoint
	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < b.size(); j++) {
			if(a[i] == b[j]) return true;
		}
	}
	return false;
}

void subsetFinder(vector< vector<int> > & v) { // finds the biggest subset that every set in it are disjoint
	bool flag = false;
	int subSetNumber = pow(2, v.size()); // number of possible subsets of C
	vector< vector<int> > subsetHolder; // holds the subset instance
	vector< vector<int> > bestSubset (0); // holds the biggest disjoint subset so far

	for(int i = 0; i < subSetNumber; i++) { // for every possible subset
		for(int j = 0; j < v.size(); j++) { // for every element in C
			if((i & (1 << j)) != 0) { // this part is for creating different subsets
				subsetHolder.push_back(v[j]); 
			} // subset holder is holding a subset instance
		}
		for(int i = 0; i + 1 < subsetHolder.size(); i++) { // for every element in subsetHolder index[0, length - 2]
			for(int j = i + 1; j < subsetHolder.size(); j++) { // for every element in subsetHolder index[1, length - 1]
				if(isIntersecting(subsetHolder[i], subsetHolder[j])) // compare each pair if they are intersecting
					flag = true;
			}
		}
		if(!flag && subsetHolder.size() > bestSubset.size()) // if given subset instance is disjoint and is bigger than bestSubset, define bestSubset as subsetHolder
			bestSubset = subsetHolder;


		subsetHolder.clear(); // clear SubsetHolder for new subset instance
		flag = false;
	}
	subsetPrinter(bestSubset); // print the bestSubset
}

int main() {
	srand(6); // random number generator seed
	int c_size = 3;  // size of the set C

	vector < vector<int> > c (c_size); // creating c which is a set of sets that holds integers in it
	for(int i = 0; i < c.size(); i++) { // initializing every element in C randomly and then printing each set
		c[i] = randomVectorGenerator();
		cout << "vector " << i + 1 << ":  ";
		vectorPrinter(c[i]); 
	}

	cout << endl << "Subset With the Best Cardinality:\n";
	
	time_t t1 = clock();
	subsetFinder(c); // function for basic solution

	cout.precision(10);
	cout << "Running time : " << double(clock() - t1)/CLOCKS_PER_SEC << " seconds\n";
	
	cout << "\nend\n";
	return 0;
}
