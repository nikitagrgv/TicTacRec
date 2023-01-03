#include "XoModel.h"

#include <QDebug>

namespace
{
const char *NO_WINNER = " ";
}

XoModel::XoModel(QObject *parent)
	: QObject(parent)
{}

QString XoModel::getWinner(const Position &indexes) const
{
	for (const auto &w : winners_)
	{
		if (w.first == indexes)
			return w.second;
	}

	return NO_WINNER;
}

void XoModel::addWinner(const Position &indexes, const QString &winner)
{
	assert(getWinner(indexes) == NO_WINNER);

	winners_.append({indexes, winner});

	update();
}

const QList<std::pair<Position, QString>> &XoModel::getWinners() const
{
	return winners_;
}

void XoModel::update()
{
	const auto all = get_all_in_same_container(get_all_indexes());

	for (const auto &cont : all)
	{
		qDebug() << "-----CONTAINER:------";
		for (const auto &elements : all)
		{
			qDebug() << "ELEMENTS:";
			for (const auto &indexes : elements)
			{
				qDebug() << "INDEX:";
				QString strx;
				QString stry;
				qDebug() << "depth:" << indexes.getNumIndexes() ;
				for (int i = 0; i < indexes.getNumIndexes(); ++i)
				{
					const Index &index = indexes.getIndex(i);

					strx += QString::number(index.x);
					strx += " ";

					stry += QString::number(index.y);
					stry += " ";
				}

				qDebug() << strx;
				qDebug() << stry;
			}
		}
	}

	emit changed();
}

bool XoModel::is_container_same(const Position &first, const Position &second)
{
	if (first.getNumIndexes() != second.getNumIndexes())
		return false;

	for (int i = 0; i < first.getNumIndexes(); i++)
	{
		if (first.getIndex(i) != second.getIndex(i))
			return false;
	}

	return true;
}

QString XoModel::get_winner(const QList<Index> &winners)
{
	// TODO do normal logic
	if (winners.size() == 9)
		return "X";
	else
		return " ";
}

QList<QList<Position>> XoModel::get_all_in_same_container(const QList<Position>& indexes)
{
	QList<QList<Position>> all_in_same_container;

	QSet<int> ignored_indexes;

	for (int i = 0; i < indexes.size(); i++)
	{
		if (ignored_indexes.contains(i))
			continue;

		QList<Position> in_same_container_with_i;

		for (int j = 0; j < indexes.size(); j++)
		{
			if (ignored_indexes.contains(j))
				continue;

			// TODO or start with j = i ??
			if (i == j)
				continue;

			if (is_container_same(indexes[i], indexes[j]))
			{
				ignored_indexes.insert(j);
				in_same_container_with_i.append(indexes[j]);
			}
		}

		if (!in_same_container_with_i.empty())
			all_in_same_container.append(in_same_container_with_i);
	}

	return all_in_same_container;
}

QList<Position> XoModel::get_all_indexes() const
{
	QList<Position> all_indexes;

	for (const auto &w : winners_)
	{
		all_indexes.append(w.first);
	}

	return all_indexes;
}
