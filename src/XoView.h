#pragma once

#include "Index.h"

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

class XoView : public QWidget
{
	Q_OBJECT

public:
	explicit XoView(QWidget *parent = nullptr);

	void setButtonClickCallback(const std::function<void(const Position &indexes)> &callback);

	void setWinner(const Position &indexes, const QString &winner);

private:
	void add_r(QWidget *parent, const Position &indexes, int depth);

	void on_button_clicked(const Position &indexes);

private:
	QList<std::pair<Position, QPushButton *>> buttons_;

	std::function<void(const Position &indexes)> button_click_callback_;
};
