// CircularArrayDemo.cpp
//

#include "CircularArray.h"
#include <deque>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

int main()
{
	int i, nLoopCount = 100000004;
	const size_t arraySize = 100;
	char szAlpha[26];
	for (i = 0; i < _countof(szAlpha); i++)
		szAlpha[i] = 'a' + i;

	auto start = chrono::system_clock::now();
	vector<char> vtChar;
	vtChar.reserve(arraySize);
	for (i = 0; i < nLoopCount; i++) {
		if (vtChar.size() == arraySize)
			vtChar.erase(vtChar.begin());
		vtChar.push_back(szAlpha[i % _countof(szAlpha)]);
		/*size_t vtSize = vtChar.size();
		if (vtSize < arraySize)
			vtChar.push_back(szAlpha[i % _countof(szAlpha)]);
		else {
			memmove(&vtChar[0], &vtChar[1], vtSize - 1);
			vtChar.back() = szAlpha[i % _countof(szAlpha)];
		}*/
	}
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);
	printf("vector size = %d, back = '%c': elapsed time: %llu ms.\n", vtChar.size(), vtChar.back(), ms.count());
	vtChar.push_back(0);
	printf("data: %s\n\n", &vtChar[0]);

	start = chrono::system_clock::now();
	deque<char> dqChar;
	for (i = 0; i < nLoopCount; i++) {
		dqChar.push_back(szAlpha[i % _countof(szAlpha)]);
		if (dqChar.size() > arraySize)
			dqChar.pop_front();
	}
	ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);
	printf("deque size = %d, back = '%c': elapsed time: %llu ms.\n", dqChar.size(), dqChar.back(), ms.count());
	dqChar.push_back(0);
	printf("data: %s\n\n", &dqChar[0]);

	start = chrono::system_clock::now();
	CircularArray<char> arChar(arraySize, true);
	for (i = 0; i < nLoopCount; i++) {
		arChar.Add(szAlpha[i % _countof(szAlpha)]);
	}
	ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);
	printf("Array size = %d, Tail = '%c': elapsed time: %llu ms.\n", arChar.GetCount(), arChar.GetTail(), ms.count());
	arChar[arChar.GetCount()] = '\0';
	printf("data: %s\n", arChar.GetData());

	cout << endl;
	wchar_t wszAlpha[26];
	for (i = 0; i < _countof(wszAlpha); i++)
		wszAlpha[i] = 'A' + i;

	start = chrono::system_clock::now();
	deque<wchar_t> dqWChar;
	for (i = 0; i < nLoopCount; i++) {
		dqWChar.push_back(wszAlpha[i % _countof(wszAlpha)]);
		if (dqWChar.size() > arraySize)
			dqWChar.pop_front();
	}
	ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);
	wprintf(L"deque size = %d, back = '%c': elapsed time: %llu ms.\n", dqWChar.size(), dqWChar.back(), ms.count());
	dqWChar.push_back(0);
	wprintf(L"data: %s\n\n", &dqWChar[0]);

	start = chrono::system_clock::now();
	CircularArray<wchar_t> arWChar(arraySize, true);
	for (i = 0; i < nLoopCount; i++) {
		arWChar.Add(wszAlpha[i % _countof(wszAlpha)]);
	}
	ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);
	wprintf(L"Array size = %d, Tail = '%c': elapsed time: %llu ms.\n", arWChar.GetCount(), arWChar.GetTail(), ms.count());
	arWChar[arWChar.GetCount()] = '\0';
	wprintf(L"data: %s\n", arWChar.GetData());

	return 0;
}
