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
	XoIndexes(const XoIndexes &other)
		: indexes_(other.indexes_)
	{}

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

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow();

	void setButtonClickCallback(std::function<void(const XoIndexes &indexes)> callback);

	void setWinner(const XoIndexes &indexes, QString text);
	QString getText(const XoIndexes &indexes);

private:
	void add_r(QWidget *parent, const XoIndexes &indexes, int depth);

	void on_button_clicked(const XoIndexes &indexes);

	QPushButton *get_button(const XoIndexes &indexes);

private:
	QList<std::pair<XoIndexes, QPushButton*>> buttons_;

	std::function<void (const XoIndexes& indexes)> button_click_callback_;
};
