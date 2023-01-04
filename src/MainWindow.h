#pragma once

#include "Common/Player.h"

#include <QWidget>

class View;
class ContaineredTicTac;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *position = nullptr);

private:
	Player current_player_ = "X";

	View *view_;
	ContaineredTicTac *model_;
};
