#pragma once

#include <QWidget>

class XoView;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	XoView* view_;
};


