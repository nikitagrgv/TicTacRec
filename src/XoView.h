#pragma once

#include "XoIndex.h"

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

	void setButtonClickCallback(const std::function<void(const XoIndexes &indexes)> &callback);

	void setWinner(const XoIndexes &indexes, const QString &winner);
	QString getText(const XoIndexes &indexes);

private:
	void add_r(QWidget *parent, const XoIndexes &indexes, int depth);

	void on_button_clicked(const XoIndexes &indexes);

	QPushButton *get_button(const XoIndexes &indexes);

private:
	QList<std::pair<XoIndexes, QPushButton *>> buttons_;

	std::function<void(const XoIndexes &indexes)> button_click_callback_;
};
