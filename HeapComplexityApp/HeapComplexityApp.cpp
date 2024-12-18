#include <iostream>
#include <ostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <thread>
#include "benchmark.h"
#include "../HeapLib/Heap.h"


class Key
{
private:
	unsigned long value = 0UL;
	static bool performDelay;
	void delay() const
	{
		if (performDelay)
			std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
public:
	Key() = default;

	Key(Key const&) = default;

	Key(unsigned long v) : value(v)
	{
	}

	unsigned long getKey() const
	{
		return value;
	}

	static void delayOn()
	{
		performDelay = true;
	}

	static void delayOff()
	{
		performDelay = false;
	}


	bool operator==(Key const& v) const
	{
		delay();
		return value == v.value;
	}

	bool operator!=(Key const& v) const
	{
		delay();
		return value != v.value;
	}

	bool operator<(Key const& v) const
	{
		delay();
		return value < v.value;
	}
	bool operator<=(Key const& v) const
	{
		delay();
		return value <= v.value;
	}
	bool operator>(Key const& v) const
	{
		delay();
		return value > v.value;
	}
	bool operator>=(Key const& v) const
	{
		delay();
		return value >= v.value;
	}

};

std::ostream& operator<<(std::ostream& stream, Key const& key)
{
	stream << key.getKey();
	return stream;
}

bool Key::performDelay = false;


int main()
{
	size_t n = 0;
	do
	{
		Key::delayOff();
		std::cout << "Size:";
		std::cin >> n;

		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator((unsigned int)seed);

		std::vector<std::pair<Key, int>> v;
		for (size_t i = 0; i < n; i++)
		{
			Key key(generator() % 100000L);
			v.push_back({ key,0 });
		}
		Heap<Key, int> heap(v);

		if (n > 0)
		{
			// insert, average case (random)
			Key key(generator() % 100000L);

			// insert, the worst case (greater)
			//Key key(generator() % 100000L + 100000L);

			Key::delayOn();
			Benchmark<std::chrono::milliseconds> b;

			heap.insert({ key,0 });
			
			auto t = b.elapsed();

			std::cout << "insert time (size: " << n << "):" << t << " ms" << std::endl;
		}
	} while (n > 0);
















}
