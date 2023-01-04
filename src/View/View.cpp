#include "View.h"

#include "../Common/Index.h"
#include "../Common/Player.h"

#include <QSpacerItem>

View::View(int depth, QWidget *parent)
	: QWidget(parent)
{
	auto *lo = new QGridLayout(this);
	lo->setSpacing(0);

	Position position{};

	add_r(this, position, depth);
}

void View::add_r(QWidget *parent, const Position &position, int depth)
{
	auto layout = dynamic_cast<QGridLayout *>(parent->layout());
	layout->setSpacing(1);

	if (depth <= 1)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				auto button = new QPushButton(" ");

				auto button_position = position;
				button_position.addIndexToDepth({j, i});

				buttons_.append({button_position, button});

				QObject::connect(button, &QPushButton::clicked,
					[this, button_position]() { on_button_clicked(button_position); });

				button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
				layout->addWidget(button, i, j);
			}
		}
		return;
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			auto next_position = position;
			next_position.addIndexToDepth({j, i});

			auto groupbox = new QGroupBox();
			auto lo = new QGridLayout(groupbox);
			lo->setSpacing(1);
			lo->setContentsMargins(3, 3, 3, 3);
			layout->addWidget(groupbox, i, j);

			add_r(groupbox, next_position, depth - 1);
		}
	}
}

void View::on_button_clicked(const Position &position)
{
	if (button_click_callback_)
		button_click_callback_(position);
}

static QWidget *find_widget_r(QWidget *parent, const Position &position, int depth_level)
{
	if (position.getNumIndexes() == 0)
		return parent;

	const auto &index = position.getIndex(depth_level);

	const int x = index.x;
	const int y = index.y;

	const auto item = parent->layout()->itemAt(3 * y + x);
	auto *const child_widget = item->widget();

	if (depth_level < position.getNumIndexes() - 1)
		return find_widget_r(child_widget, position, depth_level + 1);
	else
		return child_widget;
}

void View::setWinner(const Position &position, const Player &winner)
{
	auto w = find_widget_r(this, position, 0);

	set_widget_winner_r(w, winner);
}

void View::set_widget_winner_r(QWidget *w, const Player &winner)
{
	if (auto *button = dynamic_cast<QPushButton *>(w))
	{
		button->setText(winner);
	}

	w->setEnabled(false);

	if (winner.toUpper() == "X")
		w->setStyleSheet("background-color: green");
	else
		w->setStyleSheet("background-color: red");

	// go recursive through all child widgets
	if (auto lo = w->layout())
	{
		for (int i = 0; i < lo->count(); i++)
		{
			const auto item = lo->itemAt(i);
			auto *const child_widget = item->widget();
			set_widget_winner_r(child_widget, winner);
		}
	}
}

void View::setButtonClickCallback(const std::function<void(const Position &)> &callback)
{
	button_click_callback_ = callback;
}
