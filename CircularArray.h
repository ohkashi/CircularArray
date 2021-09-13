#pragma once

template <typename T>
class CircularArray {
public:
	CircularArray() : m_pArray(nullptr), m_index(0), m_length(0), m_buffSize(0), m_startPos(0), m_buffPos(0)
	{
	}
	CircularArray(int size, bool null_teminator = false) : m_index(0), m_startPos(0), m_buffPos(0)
	{
		m_length = size;
		m_buffSize = size << 1;
		m_pArray = new T[m_buffSize + null_teminator];
	}
	CircularArray(const T& arr, int len) : m_index(0), m_startPos(0), m_buffPos(0)
	{
		m_length = len;
		m_buffSize = len << 1;
		m_pArray = new T[m_buffSize];
		for (int i = 0; i < len; i++)
			m_pArray[i] = arr[i];
	}
	CircularArray(const CircularArray<T>& rhs)
	{
		m_length = rhs.m_length;
		m_buffSize = rhs.m_buffSize;
		m_startPos = rhs.m_startPos;
		m_buffPos = rhs.m_buffPos;
		m_index = rhs.m_index;
		m_pArray = new T[m_buffSize];
		for (int i = 0; i < m_length; i++)
			m_pArray[i] = rhs.m_pArray[i];
	}
	~CircularArray()
	{
		if (m_pArray) {
			delete[] m_pArray;
			m_pArray = nullptr;
		}
	}

	void Reserve(int nNewSize, bool null_teminator = false) {
		if (m_pArray)
			delete[] m_pArray;
		m_length = nNewSize;
		m_buffSize = nNewSize << 1;
		m_pArray = new T[m_buffSize + null_teminator];
		m_index = 0;
		m_startPos = 0;
		m_buffPos = 0;
	}

	T& operator[](int nIndex) { return m_pArray[m_startPos + nIndex]; }
	const T& operator[](int nIndex) const { return m_pArray[m_startPos + nIndex]; }
	T& GetAt(int nIndex) { return m_pArray[m_startPos + nIndex]; }
	const T& GetAt(int nIndex) const { return m_pArray[m_startPos + nIndex]; }
	int GetCount() const { return m_index; }
	bool IsEmpty() const { return !m_index; }
	T* GetData() { return &m_pArray[m_startPos]; }
	T& GetTail() { return m_pArray[m_buffPos - 1]; }
	const T& GetTail() const { return m_pArray[m_buffPos - 1]; }
	void RemoveAll() {
		m_index = 0;
		m_startPos = 0;
		m_buffPos = 0;
	}

	int Add(const T& newElement) {
		int index = m_index;
		if (++m_buffPos > m_length) {
			index = m_length + m_startPos++;
			if (m_buffPos >= m_buffSize) {
				m_buffPos = m_length;
				m_startPos = 0;
				index = m_buffPos - 1;
				m_pArray[m_startPos] = m_pArray[m_buffPos];
			} else
				m_pArray[m_startPos - 1] = newElement;
		} else
			++m_index;
		m_pArray[index] = newElement;
		return m_index - 1;
	}

private:
	T*		m_pArray;
	int		m_index, m_length, m_buffSize;
	int		m_startPos, m_buffPos;
};
