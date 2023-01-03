#include "MainWindow.h"

#include "XoView.h"
#include "XoModel.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	setMinimumSize(200, 200);

	auto *lo = new QVBoxLayout(this);

	view_ = new XoView(this);
	lo->addWidget(view_);

	model_ = new XoModel(this);

	view_->setButtonClickCallback([this](const Position &indexes) {
		model_->addWinner(indexes, "X");
	});

	connect(model_, &XoModel::changed, [this](){
		const auto &winners = model_->getWinners();

		for (const auto& w : winners)
		{
			view_->setWinner(w.first, w.second);
		}
	});
}
