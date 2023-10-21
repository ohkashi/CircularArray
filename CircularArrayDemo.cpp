// CircularArrayDemo.cpp
//

#include <deque>
#include <vector>
#include "ringbuffer.hpp"
#include "CircularArray.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <conio.h>


using namespace std;

#define	CALC_ELAPSED_TIME	chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start)
#define	PUTS_ELAPSED_TIME	cout << ": elapsed time: " << ms.count() << " ms." << endl

template<typename C, typename T>
void print_data(C& out, T& obj, int iCount) {
	out << "data: ";
	for (int i = 0; i < iCount; ++i)
		out << obj[i] << " ";
	out << endl;
}

int main()
{
	setlocale(LC_ALL, "");

	int i, nLoopCount = 100000005;
#ifdef _DEBUG
	nLoopCount = 400011;
#endif // _DEBUG

	const size_t _arraySize = 26;
	char szAlpha[_arraySize];
	for (i = 0; i < _countof(szAlpha); i++)
		szAlpha[i] = 'a' + i;

	auto start = chrono::system_clock::now();
	vector<char> vtChar;
	vtChar.reserve(_arraySize);
	for (i = 0; i < nLoopCount; i++) {
		if (vtChar.size() == _arraySize)
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
	auto ms = CALC_ELAPSED_TIME;
	printf("std::vector: size = %d, back = '%c'", (int)vtChar.size(), vtChar.back());
	PUTS_ELAPSED_TIME;
	print_data(cout, vtChar, _arraySize);
	vtChar.push_back(0);
	printf("string: '%s'\n\n", &vtChar[0]);

	start = chrono::system_clock::now();
	deque<char> dqChar;
	for (i = 0; i < nLoopCount; i++) {
		dqChar.push_back(szAlpha[i % _countof(szAlpha)]);
		if (dqChar.size() > _arraySize)
			dqChar.pop_front();
	}
	ms = CALC_ELAPSED_TIME;
	printf("std::deque: size = %d, back = '%c'", (int)dqChar.size(), dqChar.back());
	PUTS_ELAPSED_TIME;
	print_data(cout, dqChar, _arraySize);
	printf("string: '%s'\n\n", &dqChar[0]);

	start = chrono::system_clock::now();
	CircularArray<char> arChar(_arraySize);
	for (i = 0; i < nLoopCount; i++) {
		arChar.Add(szAlpha[i % _countof(szAlpha)]);
	}
	ms = CALC_ELAPSED_TIME;
	printf("CircularArray: size = %d, Tail = '%c'", (int)arChar.GetCount(), arChar.GetTail());
	PUTS_ELAPSED_TIME;
	print_data(cout, arChar, _arraySize);
	arChar[_arraySize] = '\0';
	cout << "string: '" << arChar.GetData() << "'\n\n";

	cout << std::string(70, '-') << endl << endl;

	const size_t arraySize = 32;
	wchar_t wszAlpha[arraySize];
	for (i = 0; i < _countof(wszAlpha); i++)
		wszAlpha[i] = 'A' + i;

	start = chrono::system_clock::now();
	deque<wchar_t> dqWChar;
	for (i = 0; i < nLoopCount; i++) {
		dqWChar.push_back(wszAlpha[i % _countof(wszAlpha)]);
		if (dqWChar.size() > arraySize)
			dqWChar.pop_front();
	}
	ms = CALC_ELAPSED_TIME;
	wprintf(L"std::deque: size = %d, back = '%c'", (int)dqWChar.size(), dqWChar.back());
	PUTS_ELAPSED_TIME;
	print_data(wcout, dqWChar, arraySize);
	wprintf(L"string: '%s'\n\n", &dqWChar[0]);

	start = chrono::system_clock::now();
	jnk0le::Ringbuffer<wchar_t, arraySize> ringBuff;
	for (i = 0; i < nLoopCount; i++) {
		if (ringBuff.isFull())
			ringBuff.remove();
		ringBuff.insert(wszAlpha[i % _countof(wszAlpha)]);
	}
	ms = CALC_ELAPSED_TIME;
	wprintf(L"jnk0le::Ringbuffer: size = %d, Tail = '%c'", (int)ringBuff.readAvailable(), ringBuff[arraySize - 1]);
	PUTS_ELAPSED_TIME;
	print_data(wcout, ringBuff, arraySize);
	wprintf(L"string: '%s'\n\n", ringBuff.peek());

	start = chrono::system_clock::now();
	CircularArray<wchar_t> arWChar(arraySize);
	for (i = 0; i < nLoopCount; i++) {
		arWChar.Add(wszAlpha[i % _countof(wszAlpha)]);
	}
	ms = CALC_ELAPSED_TIME;
	wprintf(L"CircularArray: size = %d, Tail = '%c'", (int)arWChar.GetCount(), arWChar.GetTail());
	PUTS_ELAPSED_TIME;
	print_data(wcout, arWChar, arraySize);
	arWChar[arraySize] = '\0';
	wprintf(L"string: '%s'\n\n", arWChar.GetData());
	
	cout << "Press any key to test thread-safe.";
	int ch = _getch();
	cout << "\r" << std::string(70, '-') << endl << endl;

	CircularArray<char> arNum(31);
	vector<thread> threads;
	bool worker_start_flag = false;
	for (i = 0; i < 10; ++i) {
		threads.push_back(thread([&]() {
			while (!worker_start_flag) {
				this_thread::sleep_for(chrono::milliseconds(10));
			}
			int i = 0;
			for (; i < 1234567; ++i) {
				arNum.AddSync('0' + i % arNum.GetSize());
			}
			std::cout << "worker finished! i = " << i << endl;
		}));
	}

	start = chrono::system_clock::now();
	worker_start_flag = true;
	for (i = 0; i < 10; ++i) {
		threads[i].join();
	}

	chrono::duration<double> sec = chrono::system_clock::now() - start;
	printf("CircularArray: size = %d, Tail = '%c'", (int)arNum.GetCount(), arNum.GetTail());
	cout << ": elapsed time: " << sec.count() << " sec." << endl;
	print_data(cout, arNum, arNum.GetCount());
	arNum[arNum.GetCount()] = '\0';
	cout << "string: '" << arNum.GetData() << "'" << endl;

	return 0;
}
