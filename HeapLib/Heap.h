#pragma once
#include <vector>
#include <iomanip>

template<typename KeyType, typename ValueType>
class Heap
{
public:
	using KeyValueType = std::pair<KeyType, ValueType>;
private:
	std::vector<KeyValueType> table;

	size_t parentIndex(size_t index) const noexcept
	{
		return (index - 1) / 2;
	}

	size_t leftChildIndex(size_t index) const noexcept
	{
		return index * 2 + 1;
	}

	size_t rightChildIndex(size_t index) const noexcept
	{
		return index * 2 + 2;
	}

	size_t getLargestFromParentAndHisChildren(size_t parent)
	{
		auto largest = parent;
		auto leftChild = leftChildIndex(parent);
		if (leftChild < size() && table[leftChild].first > table[largest].first)
			largest = leftChild;
		auto rightChild = rightChildIndex(parent);
		if (rightChild < size() && table[rightChild].first > table[largest].first)
			largest = rightChild;
		return largest;
	}

	void heapify(size_t index)
	{
		auto previous_index = index;
		do
		{
			previous_index = index;
			auto largest = getLargestFromParentAndHisChildren(index);
			if (index != largest)
			{
				std::swap(table[index], table[largest]);
				index = largest;
			}
		} while (index != previous_index);
	}

	template<typename StreamType>
	void print(StreamType& stream, size_t index, int indent, std::string prefix) const
	{
		if (index < table.size())
		{
			if (indent > 0)
				stream << std::setw(indent) << " ";
			stream << prefix;
			stream << "[" << table[index].first << ", " << table[index].second << "]" << std::endl;
			print(stream, leftChildIndex(index), indent + 4, "L: ");
			print(stream, rightChildIndex(index), indent + 4, "R: ");
		}
	}
public:
	Heap()
	{
	}

	Heap(std::vector<KeyValueType> keyValues) : table(keyValues)
	{
		for (auto i = table.size(); i > 0; --i)
			heapify(i - 1);
	}

	bool empty() const noexcept
	{
		return table.empty();
	}

	size_t size() const noexcept
	{
		return table.size();
	}

	void insert(KeyValueType const& keyValue)
	{
		//TODO Implement insert methods that insert the key value pair into the heap

	}

	KeyValueType& peek()
	{
		if (empty())
			throw std::runtime_error("Peek from an empty heap.");
		return table[0];
	}

	template<typename StreamType>
	void print(StreamType& stream) const
	{
		print(stream, 0, 0, "");
	}

	std::vector<KeyValueType> const& getVector() const
	{
		return table;
	}
};

template<typename KeyType, typename ValueType>
std::ostream& operator <<(std::ostream& stream, Heap<KeyType, ValueType> const& heap)
{
	heap.print<std::ostream>(stream);
	return stream;
}
