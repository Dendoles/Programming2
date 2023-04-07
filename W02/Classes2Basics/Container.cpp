#include "pch.h"
#include "Container.h"

Container::Container(int capacity):
	m_Size{},
	m_Capacity{ capacity },
	m_pDynArray{ new int[capacity] } 
{
}

Container::~Container()
{
	delete[] m_pDynArray;
	m_pDynArray = nullptr;
}

int Container::Size() const
{
	return m_Size;
}

int Container::Capacity() const
{
	return m_Capacity;
}

int Container::Get(int index) const
{
	return m_pDynArray[index];
}

void Container::Set(int index, int newValue)
{
	m_pDynArray[index] = newValue;
}

void Container::PushBack(int element)
{
	if (m_Size == m_Capacity)
	{
		Reserve(CreateNewCapacity());
	}
	m_pDynArray[m_Size] = element;
	++m_Size;
}

void Container::Reserve(int newCapacity)
{
	int* pMemory{new int[newCapacity]};

	for (int i{}; i < m_Size; ++i)
	{
		pMemory[i] = m_pDynArray[i];
	}

	delete[] m_pDynArray;
	m_pDynArray = pMemory;

	m_Capacity = newCapacity;
}

int Container::CreateNewCapacity() const
{
	return m_Capacity * 2 + 1;
}

