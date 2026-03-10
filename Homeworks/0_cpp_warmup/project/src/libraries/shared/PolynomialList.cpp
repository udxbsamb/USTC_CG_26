#include "PolynomialList.h"
#include <iostream>
#include <algorithm>
#include <fstream>//file input output stream
#include <cmath>

using namespace std;

//#define EPSILON 1e-10;// zero

PolynomialList::PolynomialList(const PolynomialList& other) {
    m_Polynomial = other.m_Polynomial;// allocating done by list
}

PolynomialList::PolynomialList(const string& file) {
    if(!ReadFromFile(file)){//false -> failed
        cout << "Failed to read from file: " << file << endl;
    }
}

PolynomialList::PolynomialList(const double* cof, const int* deg, int n) {
//construction done by list
Term temp;
    for (int i = 0; i < n; i++) {
        temp=Term(deg[i], cof[i]);
        AddOneTerm(temp);
    }
}

PolynomialList::PolynomialList(const vector<int>& deg, const vector<double>& cof) {

    Term temp;
    for (size_t i = 0; i < deg.size(); i++) {
        temp=Term(deg[i], cof[i]);
        AddOneTerm(temp);
    }
}

double PolynomialList::coff(int i) const {
    for (const Term& temp : m_Polynomial) {
        if (temp.deg < i) 
            break;
        if (temp.deg == i)
            return temp.cof;
    }

    return 0.;
}

double& PolynomialList::coff(int i) {
    static double coff = 0.0;
    for (Term temp : m_Polynomial) {
        if (temp.deg == i) {
            coff=temp.cof;
            return coff;
        }
        else if (temp.deg < i) {
            break;// save some time ?
        }
    }
    static double coffDefault = 0.0;
    return coffDefault;
}
    

//get rid of zeroes. Combining is done in AddOneTerm
void PolynomialList::compress() {
    
    auto itr = m_Polynomial.begin();
    while (itr != m_Polynomial.end()) {
        if (fabs((*itr).cof) < 1e-10) // for unknown reason, using EPSILON here causes problems'
            itr = m_Polynomial.erase(itr);
        else
            itr++;
    }
}

PolynomialList PolynomialList::operator+(const PolynomialList& right) const {
    PolynomialList result(*this);
    for (const Term& term : right.m_Polynomial) {
        result.AddOneTerm(term);
    }   

    result.compress();  
    return result; // you should return a correct value
}

PolynomialList PolynomialList::operator-(const PolynomialList& right) const {
    PolynomialList result(*this);
    for (const Term& term : right.m_Polynomial) {
        
        result.AddOneTerm(Term(term.deg, -term.cof));
    }   

    result.compress();  
    return result; // you should return a correct value
}

PolynomialList PolynomialList::operator*(const PolynomialList& right) const {
    PolynomialList result;
    auto itr1 = m_Polynomial.begin();
    auto itr2 = right.m_Polynomial.begin();
    while (itr1 != m_Polynomial.end()) {
        itr2 = right.m_Polynomial.begin();
        while (itr2 != right.m_Polynomial.end()) {
            result.AddOneTerm(Term(itr1->deg + itr2->deg, itr1->cof * itr2->cof));
            itr2++;
        }
        itr1++;
        result.compress();
    }
    return result; // you should return a correct value
}

PolynomialList& PolynomialList::operator=(const PolynomialList& right) {
    m_Polynomial = right.m_Polynomial;
    return *this;
}

void PolynomialList::Print() const {
    int count = 0;
    for (Term term : m_Polynomial) {
        if (term.cof ==0) continue;// skip zero term
        if (count != 0 && term.cof > 0){
             cout << "+";
        }
        if (term.cof <0){
             cout << "-";
        }
        //first term doesn't need +.

        if (abs(term.cof) != 1 ) {
            cout << abs(term.cof);
        }
        if(abs(term.cof)==1&&term.deg==0){
            cout << abs(term.cof);
        }// if the coefficient is 1 or -1, we only print it when the degree is 0, otherwise we skip it.If it is zero then it will be skipped before


        if (term.deg ==1) {
            cout << "x";
        } else if (term.deg == 0) {
            // do nothing
        } else {
            cout << "x^" << term.deg;
        }


        count++;// count the number of non-zero terms, if it is not the first term, we need to add + or - before it.
    }
    cout << endl;
}

bool PolynomialList::ReadFromFile(const string& file) {
    m_Polynomial.clear();
    std::ifstream infile;
    infile.open(file);
    if (!infile.is_open()) {
    return false; 
    }// file open failed

    list<Term>::iterator i = m_Polynomial.begin();
    Term term;
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
        term.deg = deg;
        term.cof = cof;
        AddOneTerm(term);
    }

    infile.close();
    return true;

}//there should be checks on format and stuff, but it seems too complicated for me.

PolynomialList::Term& PolynomialList::AddOneTerm(const Term& term) {
    list<Term>::iterator i = m_Polynomial.begin();
    for (; i != m_Polynomial.end(); i++) {
        if (i->deg == term.deg) {
            i->cof += term.cof;
            return *i;
        } else if (i->deg < term.deg) {
            break;
        }    
    }
    m_Polynomial.insert(i, term);// function in list
        return *(--i);
}
//from high degree to low degree. If the degree already exists, we need to add the coefficient to the existing term. If the degree doesn't exist, we need to insert a new term into the list. After adding one term, we need to compress the polynomial to combine like terms and remove zero terms.