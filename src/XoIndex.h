#pragma once

#include <QDebug>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLayout>
#include <QList>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

struct XoIndex
{
	int x = 0;
	int y = 0;

	bool operator==(const XoIndex &rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const XoIndex &rhs) const { return !(rhs == *this); }
};

class XoIndexes
{
public:
	XoIndexes(const XoIndexes &other) = default;

	XoIndexes(XoIndexes &&other) noexcept
		: indexes_(std::move(other.indexes_))
	{}

	explicit XoIndexes(const QList<XoIndex> &indexes)
		: indexes_(indexes)
	{}

	explicit XoIndexes()
		: indexes_{}
	{}

	bool operator==(const XoIndexes &rhs) const
	{
		if (this->getDepth() != rhs.getDepth())
			return false;

		for (int i = 0; i < rhs.getDepth(); i++)
		{
			if (this->getIndex(i) != rhs.getIndex(i))
				return false;
		}

		return true;
	}

	bool operator!=(const XoIndexes &rhs) const { return !(rhs == *this); }

	QList<XoIndex> getIndexes() const { return indexes_; }
	const XoIndex &getIndex(int depth) const { return indexes_[depth]; }
	void addIndex(const XoIndex &index) { indexes_.append(index); }
	int getDepth() const { return indexes_.size(); }

private:
	QList<XoIndex> indexes_;
};
