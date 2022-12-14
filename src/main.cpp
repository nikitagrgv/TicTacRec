#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow window;
	window.show();

	window.setButtonClickCallback([&window](const XoIndexes& indexes){
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

		window.setWinner(indexes, "X");
	});

	return QApplication::exec();
}
