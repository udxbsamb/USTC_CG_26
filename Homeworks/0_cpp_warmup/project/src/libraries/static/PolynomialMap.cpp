#include "PolynomialMap.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

#define EPSILON 1e-10 // zero threshold

using namespace std;

PolynomialMap::PolynomialMap(const PolynomialMap& other) {
    m_Polynomial = other.m_Polynomial;
}

PolynomialMap::PolynomialMap(const string& file) {
    if(!ReadFromFile(file)){//false -> failed
        cout << "Failed to read from file: " << file << endl;
    }
}
PolynomialMap::PolynomialMap(const double* cof, const int* deg, int n) {

	for (int i = 0; i < n; ++i) {
		m_Polynomial[deg[i]] = cof[i]; 
	}
}

PolynomialMap::PolynomialMap(const vector<int>& deg, const vector<double>& cof) {
	assert(deg.size() == cof.size());
	for (size_t i = 0; i < deg.size(); i++) {
		m_Polynomial[deg[i]] = cof[i]; 
	}
}

double PolynomialMap::coff(int i) const {
	return m_Polynomial.count(i) ? m_Polynomial.at(i) : 0.0;
	/*
	auto it = m_Polynomial.find(i);
	if (it != m_Polynomial.end()) {
		return it->second; 
	}
	return 0; // you should return a correct value
	*/
}

double& PolynomialMap::coff(int i) {
	return m_Polynomial[i]; // this will create a new entry if i is not present, which is what we want for non-const version(!)
}

void PolynomialMap::compress() {
	for (auto it = m_Polynomial.begin(); it != m_Polynomial.end(); ) {
		if (abs(it->second) < EPSILON) { // treat as zero
			it = m_Polynomial.erase(it); // erase returns the next iterator
		} else {
			++it;
		}
	}
}

PolynomialMap PolynomialMap::operator+(const PolynomialMap& right) const {
	PolynomialMap result(*this); // start with a copy of the left operand
	for (const auto& pair : right.m_Polynomial) {
		result.m_Polynomial[pair.first] += pair.second; // add the right operand's terms
	}
	result.compress();
	return result; // you should return a correct value
}

PolynomialMap PolynomialMap::operator-(const PolynomialMap& right) const {
	PolynomialMap result(*this); // start with a copy of the left operand
	for (const auto& pair : right.m_Polynomial) {
		result.m_Polynomial[pair.first] -= pair.second; // subtract the right operand's terms
	}
	result.compress();
	return result; // you should return a correct value
}

PolynomialMap PolynomialMap::operator*(const PolynomialMap& right) const {
	PolynomialMap result;
	for (const auto& pair1 : m_Polynomial) {
		for (const auto& pair2 : right.m_Polynomial) {
			int new_deg = pair1.first + pair2.first;
			double new_cof = pair1.second * pair2.second;
			result.m_Polynomial[new_deg] += new_cof; // accumulate terms with the same degree
		}
		//result.compress();
	}
	result.compress();
	return result; // you should return a correct value
}

PolynomialMap& PolynomialMap::operator=(const PolynomialMap& right) {
	m_Polynomial = right.m_Polynomial;
	return *this;
}

void PolynomialMap::Print() const {
    int count = 0;
    // 不使用 structured bindings
    for (const auto& pair : m_Polynomial) {
        int deg = pair.first;
        double cof = pair.second;
        
        if (cof == 0.0) continue;
        
        if (count != 0 && cof > 0.0) {
            std::cout << "+";
        }
        if (cof < 0.0) {
            std::cout << "-";
        }

        double abs_cof = std::fabs(cof);
        
        if (abs_cof != 1.0) {
            std::cout << abs_cof;
        }
        if (abs_cof == 1.0 && deg == 0) {
            std::cout << abs_cof;
        }

        if (deg == 1) {
            std::cout << "x";
        } else if (deg == 0) {
            // do nothing
        } else {
            std::cout << "x^" << deg;
        }

        count++;
    }
}


bool PolynomialMap::ReadFromFile(const string& file) {
	m_Polynomial.clear();
    std::ifstream infile;
    infile.open(file);
    if (!infile.is_open()) {
    return false; 
    }// file open failed

    
    int deg;
    double cof;
    char ch;
    int length;

    infile >> ch; 
    if (ch != 'P') {
        return false; 
    }// the first character should be P
    infile >> length;
    for (int j = 0; j < length; j++) {
        infile >> deg >> cof;
        coff(deg) = cof; 
    }

    infile.close();
    return true;
}
