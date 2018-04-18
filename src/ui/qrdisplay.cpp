#include "qrdisplay.h"

#include <QtGui/QImage>
#include <QtGui/QPainter>

QRDisplay::QRDisplay(QWidget *parent) : QWidget(parent)
{
	_displayImage = new QImage(150, 150, QImage::Format_RGB32);
	_displayImage->fill(Qt::red);
	setMinimumSize(_displayImage->size());

	setOffset(0, 0);
	setGrid(8, 8);
	setSpacing(2, 2);
	setColor(QColor(0,255,0,64));
	setScale(5.0f, 5.0f);
}

QRDisplay::~QRDisplay()
{
	delete _displayImage;
}

QSize QRDisplay::imageSize() const
{
	return _displayImage->size();
}

QImage* QRDisplay::image() const
{
	return _displayImage;
}

QPoint QRDisplay::offset() const
{
	return _offset;
}

void QRDisplay::setOffset(const QPoint &offset)
{
	_offset = offset;
	repaint();
}

void QRDisplay::setOffset(const int x, const int y)
{
	setOffset( QPoint(x,y) );
}

QSize QRDisplay::grid() const
{
	return _grid;
}

QSize QRDisplay::spacing() const
{
	return _spacing;
}

QColor QRDisplay::color() const
{
	return _color;
}

QPointF QRDisplay::scale() const
{
	return _scale;
}

void QRDisplay::setGrid(const QSize &grid)
{
	_grid = grid;
	repaint();
}

void QRDisplay::setGrid(const int w, const int h)
{
	setGrid( QSize(w,h) );
}

void QRDisplay::setSpacing(const QSize &spacing)
{
	_spacing = spacing;
	repaint();
}

void QRDisplay::setSpacing(const int w, const int h)
{
	setSpacing( QSize(w,h) );
}

void QRDisplay::setColor(const QColor &color)
{
	_color = color;
	repaint();
}

void QRDisplay::setScale(const double x, const double y)
{
	setScale( QPointF(x,y) );
}

void QRDisplay::setScale(const QPointF &scale)
{
	_scale = scale;
	repaint();
}

void QRDisplay::save(const QString &filename)
{
	_displayImage->save(filename, "PNG");
}

void QRDisplay::save(QImage &image, const QPoint &destPos)
{
	QPainter painter(&image);
	painter.drawImage(destPos, *_displayImage);
	painter.end();
}

void QRDisplay::load(const QString& filename)
{
	_displayImage->load(filename);
	setMinimumSize(_displayImage->size());
}

void QRDisplay::setQRCode(std::vector<qrcodegen::QrCode> &qr)
{
	int offset_x = 0;
	int offset_y = 0;

	_displayImage->fill( qRgb(255,255,255) );

	for (const qrcodegen::QrCode &code : qr)
	{
		if ( (offset_x + code.getSize()) > _displayImage->width() )
		{
			offset_x = 0;
			offset_y += code.getSize() + spacing().height();
		}

		for(int y = 0; y < code.getSize(); y++)
		{
			for(int x = 0; x < code.getSize(); x++)
			{
				if ( code.getModule(x,y) )
					_displayImage->setPixel(offset_x + x, offset_y + y, qRgb(0,0,0));
			}
		}

		offset_x += code.getSize() + spacing().width();
	}

	repaint();
}

void QRDisplay::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);

	painter.save();
	painter.scale(scale().x(), scale().y());
	painter.drawImage(0, 0, *_displayImage);
	painter.restore();

//	drawGrid(painter);
}

void QRDisplay::drawGrid(QPainter &painter)
{
	int step;

	painter.setPen(color());

	if ( grid().width() != 0 )
	{
		step = grid().width() + spacing().width();

		for(int x = offset().x(); x < image()->width(); x += step)
			painter.drawLine(x, offset().y(), x, image()->height());

		for(int x = offset().x() + grid().width(); x < image()->width(); x += step)
			painter.drawLine(x, offset().y(), x, image()->height());
	}

	if ( grid().height() != 0 )
	{
		step = grid().height() + spacing().height();
		for(int y = offset().y(); y < image()->height(); y += step)
			painter.drawLine(offset().x(), y, image()->width(), y);
		for(int y = offset().y() + grid().height(); y < image()->height(); y += step)
			painter.drawLine(offset().x(), y, image()->width(), y);
	}
}
