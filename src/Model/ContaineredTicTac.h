#pragma once

#include "../Common/Index.h"
#include "../Common/Player.h"

#include <QList>
#include <QObject>

class ContaineredTicTac : public QObject
{
	Q_OBJECT

public:
	explicit ContaineredTicTac(int depth, QObject *parent = nullptr);

	Player getWinner(const Index& index) const;

	Player getWinner(const Position &position) const;
	void setWinner(const Position &position, const Player &winner);

	QList<std::pair<Position, Player>> getWinners() const;

	bool isElemental() const;

signals:
	void changed();

private:
	void update();

	void add_winners_to_list(QList<std::pair<Position, Player>> &winners, Position position) const;

	ContaineredTicTac *get_child(Index index) const;

	bool is_winner(const Player& player);

private:
	QList<ContaineredTicTac *> children_;
	Player winner_ = NO_PLAYER;
};
