#include "MainWindow.h"

#include "Model/ContaineredTicTac.h"
#include "View/View.h"

#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	setMinimumSize(200, 200);

	auto *main_lo = new QVBoxLayout(this);

	create_controls_ui();

	create_game(3);

	if (is_bot_turn())
		do_bot_turn();
}

void MainWindow::create_game(int depth)
{
	if (view_)
		view_->deleteLater();

	if (model_)
		model_->deleteLater();

	view_ = new View(depth, this);
	layout()->addWidget(view_);

	model_ = new ContaineredTicTac(depth, this);

	view_->setButtonClickCallback([this](const Position &position) {
		if (!is_bot_turn())
		{
			model_->setWinner(position, current_player_);
			go_to_next_player();
		}
	});

	connect(model_, &ContaineredTicTac::changed, [this](){
		const QList<std::pair<Position, Player>> &winners = model_->getWinners();

		for (const std::pair<Position, Player>& w : winners)
		{
			view_->setWinner(w.first, w.second);
		}
	});
}

void MainWindow::create_controls_ui()
{
	auto *controls_lo = new QHBoxLayout();
	dynamic_cast<QVBoxLayout*>(layout())->addLayout(controls_lo);

	{
		auto groupbox_depth = new QGroupBox("Depth");
		controls_lo->addWidget(groupbox_depth);
		groupbox_depth->setLayout(new QVBoxLayout);

		depth_input_ = new QSpinBox();
		groupbox_depth->layout()->addWidget(depth_input_);
		depth_input_->setMinimum(1);
		depth_input_->setValue(3);
	}

	{
		auto start_button = new QPushButton("Start");
		controls_lo->addWidget(start_button);

		connect(start_button, &QPushButton::clicked, [this]() {
			create_game(get_depth());
		});
	}
}

void MainWindow::go_to_next_player()
{
	if (model_->isGameEnded())
		return;

	current_player_ = current_player_ == "X" ? "O" : "X";

	if (is_bot_turn())
		do_bot_turn();
}

bool MainWindow::is_bot_turn()
{
	return current_player_ != "X";
}

void MainWindow::do_bot_turn()
{
	QList<Position> free_elementals = model_->getFreeElementals();

	Position position = get_random_position(free_elementals);

	model_->setWinner(position, current_player_);

	go_to_next_player();
}

Position MainWindow::get_random_position(QList<Position> positions)
{
	int rand_index = QRandomGenerator::global()->bounded(positions.count());
	return positions[rand_index];
}

int MainWindow::get_depth() const
{
	return depth_input_->value();
}
