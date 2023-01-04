#include "ContaineredTicTac.h"

#include <QDebug>

ContaineredTicTac::ContaineredTicTac(int depth, QObject *parent)
	: QObject(parent)
{
	assert(depth >= 0);

	if (depth == 0)
		return;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			children_.append(new ContaineredTicTac(depth - 1, this));
		}
	}
}

Player ContaineredTicTac::getWinner(const Position &position) const
{
	if (position.getNumIndexes() == 0)
		return winner_;

	assert(!isElemental());

	auto child_tic_tac = get_child(position.getHighestIndex());

	Position more_deep_position = position;
	more_deep_position.removeHighestIndex();

	return child_tic_tac->getWinner(more_deep_position);
}

void ContaineredTicTac::setWinner(const Position &position, const Player &winner)
{
	if (position.getNumIndexes() == 0)
	{
		assert(isElemental());
		winner_ = winner;
		update();
		return;
	}

	assert(!isElemental());
	assert(winner_ == NO_PLAYER);

	auto child_tic_tac = get_child(position.getHighestIndex());

	Position more_deep_position = position;
	more_deep_position.removeHighestIndex();

	child_tic_tac->setWinner(more_deep_position, winner);

	update();
}

QList<std::pair<Position, Player>> ContaineredTicTac::getWinners() const
{
	QList<std::pair<Position, Player>> winners{};

	add_winners_to_list(winners, Position{});

	return winners;
}

void ContaineredTicTac::add_winners_to_list(QList<std::pair<Position, Player>> &winners, Position position) const
{
	if (winner_ != NO_PLAYER)
	{
		winners.append({position, winner_});
		return;
	}

	if (isElemental())
		return;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Position more_deep_position = position;
			more_deep_position.addDeepestIndex({j, i});

			auto child_tic_tac = get_child(more_deep_position.getDeepestIndex());
			child_tic_tac->add_winners_to_list(winners, more_deep_position);
		}
	}
}

bool ContaineredTicTac::isElemental() const
{
	return children_.isEmpty();
}

void ContaineredTicTac::update()
{
	if (isElemental())
		return;

	if (is_winner("X"))
		winner_ = "X";
	else if (is_winner("O"))
		winner_ = "O";

	emit changed();
}

bool ContaineredTicTac::is_winner(const Player &player)
{
	// TODO improve this stupid way to check winner

	// check horizontal lines
	for (int y = 0; y < 3; ++y)
	{
		bool is_win_in_line = true;
		for (int x = 0; x < 3; ++x)
		{
			if (getWinner({x, y}) != player)
			{
				is_win_in_line = false;
				break;
			}
		}
		if (is_win_in_line)
			return true;
	}

	// check vertical lines
	for (int x = 0; x < 3; ++x)
	{
		bool is_win_in_line = true;
		for (int y = 0; y < 3; ++y)
		{
			if (getWinner({x, y}) != player)
			{
				is_win_in_line = false;
				break;
			}
		}
		if (is_win_in_line)
			return true;
	}

	// check main diagonal line
	{
		bool is_win_in_line = true;
		for (int i = 0; i < 3; ++i)
		{
			if (getWinner({i, i}) != player)
			{
				is_win_in_line = false;
				break;
			}
		}
		if (is_win_in_line)
			return true;
	}

	// check main diagonal line
	{
		bool is_win_in_line = true;
		for (int i = 0; i < 3; ++i)
		{
			if (getWinner({i, 3 - i - 1}) != player)
			{
				is_win_in_line = false;
				break;
			}
		}
		if (is_win_in_line)
			return true;
	}

	return false;
}

ContaineredTicTac *ContaineredTicTac::get_child(Index index) const
{
	assert(!isElemental());

	return children_[3 * index.y + index.x];
}

Player ContaineredTicTac::getWinner(const Index &index) const
{
	return getWinner(Position{index});
}
