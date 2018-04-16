#ifndef QRDISPLAY_H
#define QRDISPLAY_H

#include <QtGui/QImage>
#include <QtWidgets/QWidget>

#include <vector>
#include "../qr/QrCode.hpp"
using qrcodegen::QrCode;

class QRDisplay : public QWidget
{
		Q_OBJECT

	public:
		explicit QRDisplay(QWidget *parent = 0);
		~QRDisplay();

		QSize imageSize() const;

		QImage *image() const;

		QPoint offset() const;
		QSize grid() const;
		QSize spacing() const;
		QColor color() const;
		QPointF scale() const;

	public slots:
		void setOffset(const QPoint &offset);
		void setOffset(const int x, const int y);

		void setGrid(const QSize &grid);
		void setGrid(const int w, const int h);

		void setSpacing(const QSize &spacing);
		void setSpacing(const int w, const int h);

		void setColor(const QColor &color);

		void setScale(const double x, const double y);
		void setScale(const QPointF &scale);

		void save(const QString &filename);
		void save(QImage &image, const QPoint &destPos);
		void load(const QString &filename);

		void setQRCode(std::vector<QrCode> &qr);

	protected:
		void paintEvent(QPaintEvent * event);

	private:
		void drawGrid(QPainter &painter);

		QPoint _offset;
		QSize _grid;
		QSize _spacing;
		QColor _color;
		QPointF _scale;

		QImage *_displayImage;
};

#endif // QRDISPLAY_H
