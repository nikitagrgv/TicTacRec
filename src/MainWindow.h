#pragma once

#include <QWidget>

class XoView;
class XoModel;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	XoView* view_;
	XoModel* model_;
};


