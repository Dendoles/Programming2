#pragma once
class Container
{
public:
	Container(int capacity);
	~Container();

	int Size() const;
	int Capacity() const;
	int Get(int index) const;
	void Set(int index, int newValue);
	void PushBack(int element);

private:
	int m_Size;
	int m_Capacity;
	int* m_pDynArray;

	void Reserve(int newCapacity);
	int CreateNewCapacity() const;
};

