#pragma once

#include <QList>

struct Index
{
	int x = 0;
	int y = 0;

	bool operator==(const Index &rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Index &rhs) const { return !(rhs == *this); }
};

class Position
{
public:
	Position(const Position &other) = default;

	Position(Position &&other) noexcept
		: indexes_(std::move(other.indexes_))
	{}

	explicit Position(const QList<Index> &indexes)
		: indexes_(indexes)
	{}

	explicit Position()
		: indexes_{}
	{}

	bool operator==(const Position &rhs) const
	{
		if (this->getNumIndexes() != rhs.getNumIndexes())
			return false;

		for (int i = 0; i < rhs.getNumIndexes(); i++)
		{
			if (this->getIndex(i) != rhs.getIndex(i))
				return false;
		}

		return true;
	}

	bool operator!=(const Position &rhs) const { return !(rhs == *this); }

	const QList<Index> &getIndexes() const { return indexes_; }
	const Index &getIndex(int depth) const { return indexes_[depth]; }
	const Index &getDeepestIndex() const { return indexes_.last(); }
	void removeDeepestIndex() { indexes_.removeLast(); }
	void addIndexToDepth(const Index &index) { indexes_.append(index); }
	int getNumIndexes() const { return indexes_.size(); }

private:
	QList<Index> indexes_;
};
