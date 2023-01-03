#include "XoView.h"

#include "Index.h"

#include <QSpacerItem>

XoView::XoView(QWidget *parent)
	: QWidget(parent)
{
	auto *lo = new QGridLayout(this);
	lo->setSpacing(0);

	Position indexes;

	add_r(this, indexes, 3);
}

void XoView::add_r(QWidget *parent, const Position &indexes, int depth)
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

				auto button_indexes = indexes;
				button_indexes.addIndexToDepth({i, j});

				buttons_.append({button_indexes, button});

				QObject::connect(button, &QPushButton::clicked,
					[this, button_indexes]() { on_button_clicked(button_indexes); });

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
			auto next_indexes = indexes;
			next_indexes.addIndexToDepth({i, j});

			auto groupbox = new QGroupBox();
			auto lo = new QGridLayout(groupbox);
			lo->setSpacing(1);
			lo->setContentsMargins(3, 3, 3, 3);
			layout->addWidget(groupbox, i, j);

			add_r(groupbox, next_indexes, depth - 1);
		}
	}
}

void XoView::on_button_clicked(const Position &indexes)
{
	if (button_click_callback_)
		button_click_callback_(indexes);
}

static QWidget *find_widget_r(QWidget *parent, const Position &indexes, int depth_level)
{
	const auto &index = indexes.getIndex(depth_level);

	const int x = index.x;
	const int y = index.y;

	const auto item = parent->layout()->itemAt(3 * x + y);
	auto *const child_widget = item->widget();

	if (depth_level < indexes.getNumIndexes() - 1)
		return find_widget_r(child_widget, indexes, depth_level + 1);
	else
		return child_widget;
}

void XoView::setWinner(const Position &indexes, const QString &winner)
{
	auto w = find_widget_r(this, indexes, 0);

	auto *button = dynamic_cast<QPushButton *>(w);

	assert(button != nullptr);

	button->setEnabled(false); // TODO ?
	button->setText(winner);

	if (winner.toUpper() == "X")
		w->setStyleSheet("background-color: green");
	else
		w->setStyleSheet("background-color: red");
}

void XoView::setButtonClickCallback(const std::function<void(const Position &)> &callback)
{
	button_click_callback_ = callback;
}
