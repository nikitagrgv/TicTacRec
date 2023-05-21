#pragma once

#include "Common/Index.h"
#include "Common/Player.h"

#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QWidget>

class QSpinBox;

class View;
class ContaineredTicTac;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *position = nullptr);

private:
	void create_game(int depth);

	void go_to_next_player();
	bool is_bot_turn();
	void do_bot_turn();
	Position get_random_position(QList<Position> positions);

	void create_controls_ui();

	int get_depth() const;

private:
	Player current_player_ = "X";

	View *view_ = nullptr;
	ContaineredTicTac *model_ = nullptr;

	QSpinBox *depth_input_ = nullptr;
};
