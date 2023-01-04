#pragma once

#include "../Common/Index.h"
#include "../Common/Player.h"

#include <QDebug>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLayout>
#include <QList>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

class View : public QWidget
{
	Q_OBJECT

public:
	View(int depth, QWidget *parent = nullptr);

	void setButtonClickCallback(const std::function<void(const Position &indexes)> &callback);

	void setWinner(const Position &position, const Player &winner);

private:
	void add_r(QWidget *parent, const Position &position, int depth);
	void set_widget_winner_r(QWidget *w, const Player &winner);

	void on_button_clicked(const Position &position);

private:
	QList<std::pair<Position, QPushButton *>> buttons_;

	std::function<void(const Position &position)> button_click_callback_;
};
