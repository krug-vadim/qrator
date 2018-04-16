#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>

#include "../qr/QrCode.hpp"

using qrcodegen::QrCode;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->generateButton, &QPushButton::clicked,
	        this, &MainWindow::generateQRCode);
}

MainWindow::~MainWindow()
{
	delete ui;
}

#include <QDebug>
void MainWindow::generateQRCode()
{
	int n = ui->maxCharsSpinBox->value();
	QString qrText = ui->qrText->document()->toPlainText();

	std::vector<QrCode> qr;
	for(int pos = 0; pos < qrText.size(); pos += n)
	{
		QString chunk = qrText.mid(pos, n);
		qDebug() << chunk;
		qr.push_back( QrCode::encodeText(chunk.toUtf8().constData(), QrCode::Ecc::HIGH) );
	}

	ui->widget->setQRCode(qr);
}
