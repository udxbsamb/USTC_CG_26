// implementation of class DArray
#include "DArray.h"

#include <cassert>

#include <iostream>

using namespace std;

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) 
: m_nSize(nSize) , m_pData(new double[nSize]) ,m_nMax(nSize)
{
	for (size_t i = 0; i < m_nSize; i++)
		m_pData[i] = dValue;
}


DArray::DArray(const DArray& arr) 
	: m_nSize(arr.m_nSize), m_pData(new double[arr.m_nSize]),m_nMax(arr.m_nSize)
{
	for (size_t i = 0; i < m_nSize; i++)
	{
		m_pData[i] = arr.m_pData[i];
	}
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	for (size_t i = 0; i < m_nSize; i++)
	{
		cout<<GetAt(i)<<" ";
	}
	cout<<endl;
}

// initilize the array
void DArray::Init() {
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

// free the array
void DArray::Free() {
	if (m_pData) {
		delete[] m_pData;
		m_pData = nullptr;
	}
	m_nSize = 0;
	m_nMax = 0;
}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize; 
}

// if memory isn't enough, allocate double the memory until it is enough.
void DArray::Reserve(int nSize) {
	if (nSize <= m_nMax) return;
	while(m_nMax < nSize)
	{
	m_nMax=m_nMax== 0 ? 1 : m_nMax * 2;
	}
	double* pNewData = new double[m_nMax];
	for (size_t i = 0; i < m_nSize; i++)
	{
		pNewData[i] = m_pData[i];
	}//copy old data to new data

	delete[] m_pData;
	m_pData = pNewData;
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if (nSize <= m_nMax) 
	{
		m_nSize = nSize;
		return;
	}// enough memory, just set the size

	Reserve(nSize);// not enough memory, reserve more memory
		
	for (size_t i = m_nSize; i < nSize; i++)
	{
		m_pData[i] = 0;
	}// set new elements to default value

	m_nSize = nSize;
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

double& DArray::operator[](int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	Reserve(m_nSize + 1);
	m_pData[m_nSize] = dValue;
	m_nSize++;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex <= m_nSize);
	for (size_t i = nIndex; i < m_nSize - 1; i++)
	{
		m_pData[i] = m_pData[i + 1];
	}// move elements after nIndex to the left by one position
	m_nSize--;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex <= m_nSize);
	Reserve(m_nSize + 1);
	for (size_t i = m_nSize; i > nIndex; i--)
	{
		m_pData[i] = m_pData[i - 1];
	}// move elements after nIndex to the right by one position
	m_pData[nIndex] = dValue;
	m_nSize++;
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	if (this == &arr)
		return *this;// self-assignment, do nothing	
	delete[] m_pData;// free old data
	m_nSize = arr.m_nSize;
	m_nMax = arr.m_nMax;
	m_pData = new double[m_nSize];
	for (size_t i = 0; i < m_nSize; i++)	
	{
		m_pData[i] = arr.m_pData[i];
	}// copy new data to old data	

	return *this;
}
