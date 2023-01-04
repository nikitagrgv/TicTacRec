#include "MainWindow.h"

#include "Model/ContaineredTicTac.h"
#include "View/View.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	setMinimumSize(200, 200);

	auto *lo = new QVBoxLayout(this);

	view_ = new View(3, this);
	lo->addWidget(view_);

	model_ = new ContaineredTicTac(3, this);

	view_->setButtonClickCallback([this](const Position &position) {
		model_->setWinner(position, "X");
	});

	connect(model_, &ContaineredTicTac::changed, [this](){
		const QList<std::pair<Position, Player>> &winners = model_->getWinners();

		for (const std::pair<Position, Player>& w : winners)
		{
			view_->setWinner(w.first, w.second);
		}
	});
}
