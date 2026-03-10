#pragma once
#include <iostream>

#include <cassert>

using std::cout;
using std::endl;

// interfaces of Dynamic Array class DArray,using Template
template <typename datatype>
class DArray {
private:
	datatype* m_pData; // the pointer to the array memory
	int m_nSize; // the size of the array
	int m_nMax;

private:
	void Init(); // initilize the array
	void Free(); // free the array
	void Reserve(int nSize); // allocate enough memory

public:
	DArray(); // default constructor
	DArray(int nSize, datatype dValue = 0); // set an array with default values
	DArray(const DArray& arr); // copy constructor
	~DArray(); // deconstructor

	void Print() const; // print the elements of the array

	int GetSize() const; // get the size of the array
	void SetSize(int nSize); // set the size of the array

	const datatype& GetAt(int nIndex) const; // get an element at an index
	void SetAt(int nIndex, datatype dValue); // set the value of an element

	datatype& operator[](int nIndex); // overload operator '[]'
	const datatype& operator[](int nIndex) const; // overload operator '[]'

	void PushBack(datatype dValue); // add a new element at the end of the array
	void DeleteAt(int nIndex); // delete an element at some index
	void InsertAt(int nIndex, datatype dValue); // insert a new element at some index

	DArray<datatype>& operator = (const DArray<datatype>& arr); //overload operator '='

};

template <typename datatype>
// initilize the array
void DArray<datatype>::Init() {
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

template <typename datatype>
// free the array
void DArray<datatype>::Free() {
	if (m_pData) {
		delete[] m_pData;
		m_pData = nullptr;
	}
	m_nSize = 0;
	m_nMax = 0;
}

template <typename datatype>
// default constructor
DArray<datatype>::DArray() {
	Init();
}

template <typename datatype>
// set an array with default values
DArray<datatype>::DArray(int nSize, datatype dValue) 
: m_nSize(nSize) , m_pData(new datatype[nSize]) ,m_nMax(nSize)
{
	for (size_t i = 0; i < m_nSize; i++)
		m_pData[i] = dValue;
}

template <typename datatype>
// copy constructor
DArray<datatype>::DArray(const DArray& arr) 
	: m_nSize(arr.m_nSize), m_pData(new datatype[arr.m_nSize]),m_nMax(arr.m_nSize)
{
	for (size_t i = 0; i < m_nSize; i++)
	{
		m_pData[i] = arr.m_pData[i];
	}
}

template <typename datatype>
// deconstructor
DArray<datatype>::~DArray() {
	Free();
}

template <typename datatype>
// display the elements of the array
void DArray<datatype>::Print() const {
	for (size_t i = 0; i < m_nSize; i++)
	{
		cout<<GetAt(i)<<" ";
	}
	cout<<endl;
}

template <typename datatype>
// get the size of the array
int DArray<datatype>::GetSize() const {
	return m_nSize; 
}

template <typename datatype>
// if memory isn't enough, allocate double until enough.
void DArray<datatype>::Reserve(int nSize) {
	if (nSize <= m_nMax) return;
	while(m_nMax < nSize)
	{
	m_nMax=m_nMax== 0 ? 1 : m_nMax * 2;
	}
	datatype* pNewData = new datatype[m_nMax];
	for (size_t i = 0; i < m_nSize; i++)
	{
		pNewData[i] = m_pData[i];
	}//copy old data to new data

	delete[] m_pData;
	m_pData = pNewData;
}

template <typename datatype>
// set the size of the array
void DArray<datatype>::SetSize(int nSize) {
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

template <typename datatype>
// get an element at an index
const datatype& DArray<datatype>::GetAt(int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

template <typename datatype>
// overload operator '[]'
datatype& DArray<datatype>::operator[](int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

template <typename datatype>
// set the value of an element 
void DArray<datatype>::SetAt(int nIndex, datatype dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

template <typename datatype>
// overload operator '[]'
const datatype& DArray<datatype>::operator[](int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

template <typename datatype>
// add a new element at the end of the array
void DArray<datatype>::PushBack(datatype dValue) {
	Reserve(m_nSize + 1);
	m_pData[m_nSize] = dValue;
	m_nSize++;
}

template <typename datatype>
// delete an element at some index
void DArray<datatype>::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex <= m_nSize);
	for (size_t i = nIndex; i < m_nSize - 1; i++)
	{
		m_pData[i] = m_pData[i + 1];
	}// move elements after nIndex to the left by one position
	m_nSize--;
}

template <typename datatype>
// insert a new element at some index
void DArray<datatype>::InsertAt(int nIndex, datatype dValue) {
	assert(nIndex >= 0 && nIndex <= m_nSize);
	Reserve(m_nSize + 1);
	for (size_t i = m_nSize; i > nIndex; i--)
	{
		m_pData[i] = m_pData[i - 1];
	}// move elements after nIndex to the right by one position
	m_pData[nIndex] = dValue;
	m_nSize++;
}

template <typename datatype>
// overload operator '='
DArray<datatype>& DArray<datatype>::operator = (const DArray<datatype>& arr) {
	if (this == &arr) return *this;// self-assignment, do nothing	
	delete[] m_pData;// free old data
	m_nSize = arr.m_nSize;
	m_nMax = arr.m_nMax;
	m_pData = new datatype[m_nSize];
	for (size_t i = 0; i < m_nSize; i++)	
	{
		m_pData[i] = arr.m_pData[i];
	}// copy new data to old data	

	return *this;
}


