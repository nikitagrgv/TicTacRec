#pragma once

#include "../Common/Index.h"

#include <QList>
#include <QObject>

class XoModel : public QObject
{
	Q_OBJECT

public:
	explicit XoModel(QObject *parent = nullptr);

	void addWinner(const Position &indexes, const QString &winner);

	QString getWinner(const Position &indexes) const;

	const QList<std::pair<Position, QString>> &getWinners() const;

signals:
	void changed();

private:
	void update();

	QList<Position> get_all_indexes() const;

	static bool is_container_same(const Position &first, const Position &second);
	static QString get_winner(const QList<Index> &winners);
	static QList<QList<Position>> get_all_in_same_container(const QList<Position>& indexes);

private:
	QList<std::pair<Position, QString>> winners_;
};
