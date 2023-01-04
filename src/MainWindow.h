#pragma once

#include <QWidget>

class View;
class ContaineredTicTac;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *position = nullptr);

private:
	View * view_;
	ContaineredTicTac * model_;
};


