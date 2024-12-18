#include <sstream>
#include "CppUnitTest.h"
#include "../HeapLib/Heap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<>
inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Heap<int, int>::KeyValueType>(const Heap<int, int>::KeyValueType& t)
{
	std::wstring result;
	result += L"(";
	result += ToString(t.first);
	result += L",";
	result += ToString(t.second);
	result += L")";
	return result;
}

template<>
inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<std::vector<Heap<int, int>::KeyValueType>>(const std::vector<Heap<int, int>::KeyValueType>& t)
{
	std::wstring result;
	result += L"[";
	for (auto i = t.begin(); i != t.end(); ++i)
	{
		if (i != t.begin())
			result += L",";
		result += ToString(*i);
	}
	result += L"]";
	return result;
}


namespace HeapUnitTest
{
	TEST_CLASS(HeapUnitTest)
	{
	public:
		TEST_METHOD(construktor_parametrless)
		{
			Heap<int, int> heap;
			Assert::AreEqual(size_t{ 0 }, heap.size());
		}
		TEST_METHOD(construktor_with_parameter)
		{
			Heap<int, int> heap({ {1,10},{2,20},{3,30},{4,40},{5,50},{6,60},{7,70} });
			Assert::AreEqual({ {7,70},{5,50},{6,60},{4,40},{2,20},{1,10},{3,30} }, heap.getVector());
		}
		TEST_METHOD(insert_into_empty_heap)
		{
			Heap<int, int> heap;
			heap.insert({ 5,50 });
			Assert::AreEqual(size_t{ 1 }, heap.size());
			Assert::AreEqual({ {5,50} }, heap.getVector());
		}
		TEST_METHOD(insert_greatest1)
		{
			Heap<int, int> heap({ {1,10}, {2,20}, {3,30}, {4,40}, {5,50}, {6,60}, {7,70} });
			heap.insert({ 10,100 });
			Assert::AreEqual(size_t{ 8 }, heap.size());
			Assert::AreEqual({ {10,100},{7,70},{6,60},{5,50},{2,20},{1,10},{3,30}, {4,40} }, heap.getVector());
		}
		TEST_METHOD(insert_greatest2)
		{
			Heap<int, int> heap({ {1,10}, {2,20}, {3,30}, {4,40}, {5,50}, {6,60} });
			heap.insert({ 10,100 });
			Assert::AreEqual(size_t{ 7 }, heap.size());
			Assert::AreEqual({ {10,100},{5,50},{6,60},{4,40},{2,20},{1,10},{3,30} }, heap.getVector());
		}
		TEST_METHOD(insert_greatest3)
		{
			Heap<int, int> heap({ {1,10}, {2,20}, {3,30}, {4,40}, {5,50} });
			heap.insert({ 10,100 });
			Assert::AreEqual(size_t{ 6 }, heap.size());
			Assert::AreEqual({ {10,100},{4,40},{5,50},{1,10},{2,20},{3,30} }, heap.getVector());
		}
		TEST_METHOD(insert_doesnt_move_up1)
		{
			Heap<int, int> heap({ {1,10}, {2,20}, {3,30}, {5,50}, {6,60}, {7,70}, {8,80} });
			heap.insert({ 4,40 });
			Assert::AreEqual(size_t{ 8 }, heap.size());
			Assert::AreEqual({ {8,80},{6,60},{7,70},{5,50},{2,20},{1,10},{3,30}, {4,40} }, heap.getVector());
		}
		TEST_METHOD(insert_doesnt_move_up2)
		{
			Heap<int, int> heap({ {1,10}, {3,30}, {4,40}, {5,50}, {6,60}, {7,70} });
			heap.insert({ 2,20 });
			Assert::AreEqual(size_t{ 7 }, heap.size());
			Assert::AreEqual({ {7,70},{6,60},{4,40},{5,50},{3,30},{1,10},{2,20} }, heap.getVector());
		}
		TEST_METHOD(insert_doesnt_move_up3)
		{
			Heap<int, int> heap({ {1,10}, {2,20}, {3,30}, {4,40}, {5,50} });
			heap.insert({ 0,0 });
			Assert::AreEqual(size_t{ 6 }, heap.size());
			Assert::AreEqual({ {5,50},{4,40},{3,30},{1,10},{2,20},{0,00} }, heap.getVector());
		}
		TEST_METHOD(insert_moves_up1)
		{
			Heap<int, int> heap({ {1,10}, {2,20}, {3,30}, {5,50}, {7,70}, {8,80}, {9,90} });
			heap.insert({ 6,60 });
			Assert::AreEqual(size_t{ 8 }, heap.size());
			Assert::AreEqual({ {9,90},{7,70},{8,80},{6,60},{2,20},{1,10},{3,30}, {5,50} }, heap.getVector());
		}
		TEST_METHOD(insert_moves_up2)
		{
			Heap<int, int> heap({ {1,10}, {3,30}, {4,40}, {6,60}, {7,70}, {8,80} });
			heap.insert({ 5,50 });
			Assert::AreEqual(size_t{ 7 }, heap.size());
			Assert::AreEqual({ {8,80},{7,70},{5,50},{6,60},{3,30},{1,10},{4,40} }, heap.getVector());
		}
		TEST_METHOD(insert_moves_up3)
		{
			Heap<int, int> heap({ {1,10}, {2,20}, {3,30}, {5,50}, {6,60} });
			heap.insert({ 4,40 });
			Assert::AreEqual(size_t{ 6 }, heap.size());
			Assert::AreEqual({ {6,60},{5,50},{4,40},{1,10},{2,20},{3,30} }, heap.getVector());
		}
		TEST_METHOD(peek_from_empty_heap)
		{
			Heap<int, int> heap;
			
			Assert::ExpectException<std::runtime_error>([&heap](){heap.peek();});
		}
		TEST_METHOD(peek_1)
		{
			Heap<int, int> heap({ {3,30} });
			Assert::AreEqual({ 3,30 }, heap.peek());
		}
		TEST_METHOD(peek_2)
		{
			Heap<int, int> heap({ {7,70}, {5,50}, {6,60}, {4,40}, {2,20}, {1,10}, {3,30} });
			Assert::AreEqual({ 7,70 }, heap.peek());
		}
		TEST_METHOD(print0)
		{
			Heap<int, int> heap;
			std::ostringstream stream;
			heap.print(stream);
			auto s = stream.str();
			std::string s1 = "";
			Assert::AreEqual(s1, s);
		}
		TEST_METHOD(print1)
		{
			Heap<int, int> heap({ {1,1} });
			std::ostringstream stream;
			heap.print(stream);
			auto s = stream.str();
			std::string s1 = "[1, 1]\n";
			Assert::AreEqual(s1, s);
		}
		TEST_METHOD(print3)
		{
			Heap<int, int> heap({ {1,1}, {2,2}, {3,3} });
			std::ostringstream stream;
			heap.print(stream);
			auto s = stream.str();
			std::string s1 = "[3, 3]\n    L: [2, 2]\n    R: [1, 1]\n";
			Assert::AreEqual(s1, s);
		}

		TEST_METHOD(print7)
		{
			Heap<int, int> heap({ {1,1}, {2,2}, {3,3}, {4,4},{5,5},{6,6},{7,7} });
			std::ostringstream stream;
			heap.print(stream);
			auto s = stream.str();
			std::string s1 = "[7, 7]\n    L: [5, 5]\n        L: [4, 4]\n        R: [2, 2]\n    R: [6, 6]\n        L: [1, 1]\n        R: [3, 3]\n";
			Assert::AreEqual(s1, s);
		}
	};
}
