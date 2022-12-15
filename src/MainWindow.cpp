#include "MainWindow.h"

#include "XoView.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	setMinimumSize(200, 200);

	auto *lo = new QVBoxLayout(this);

	view_ = new XoView(this);
	lo->addWidget(view_);

	view_->setButtonClickCallback([view_=view_](const XoIndexes& indexes){
		QString strx;
		QString stry;

		qDebug() << "depth:" << indexes.getDepth() ;
		for (int i = 0; i < indexes.getDepth(); ++i)
		{
			const XoIndex &index = indexes.getIndex(i);

			strx += QString::number(index.x);
			strx += " ";

			stry += QString::number(index.y);
			stry += " ";
		}

		qDebug() << strx;
		qDebug() << stry;

		view_->setWinner(indexes, "X");
	});
}
