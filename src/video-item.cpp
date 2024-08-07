#include "video-item.hpp"
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionButton>
#include <QStyle>
#include <qpushbutton.h>

VideoItem::VideoItem(const QString &thumbnailPath, const QString &fileName,
		     const QString &filePath, QWidget *parent)
	: QWidget(parent),
	  thumbnailLabel(new QLabel(this)),
	  nameLabel(new QLabel(fileName, this)),
	  pathLabel(new QLabel(filePath, this))
{
	// Set the thumbnail
	QPixmap pixmap(thumbnailPath);
	thumbnailLabel->setPixmap(
		pixmap.scaledToHeight(75)); // Adjust size as needed

	// Create layout

	QHBoxLayout *container = new QHBoxLayout(this);
	QVBoxLayout *labels = new QVBoxLayout();

    QFont font = nameLabel->font();
    font.setBold(true);
    nameLabel->setFont(font);

	container->setContentsMargins(10, 10, 10, 10);
	container->addWidget(thumbnailLabel);
	container->addLayout(labels);

	labels->setSpacing(5);
    labels->setAlignment(Qt::AlignLeft);
	labels->addWidget(nameLabel);
	labels->addWidget(pathLabel);

	setLayout(container);
}

QString VideoItem::getFileName() const
{
	return nameLabel->text();
}

QString VideoItem::getFilePath() const
{
	return pathLabel->text();
}

QSize VideoItem::sizeHint() const
{
	int height = thumbnailLabel->height();
	int width = thumbnailLabel->width() + nameLabel->width() +
		    pathLabel->width();
	return QSize(width, height);
}

void VideoItem::mousePressEvent(QMouseEvent *event)
{
	emit clicked();
	QWidget::mousePressEvent(event);
}

void VideoItem::enterEvent(QEnterEvent* event)
{
    QWidget::enterEvent(event);
    isHovered = true;
    setCursor(Qt::PointingHandCursor);
    update(); // Repaint the widget
}

void VideoItem::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    isHovered = false;
    setCursor(Qt::ArrowCursor);
    update(); // Repaint the widget
}

void VideoItem::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QStyleOptionButton option;
    option.initFrom(new QPushButton());

    QColor background = palette().color(QPalette::Button);

    option.state |= QStyle::State_Raised;

    if (isHovered) {
        option.state |= QStyle::State_MouseOver;
        background = palette().color(QPalette::Highlight);

    }

    painter.fillRect(rect(), background);
    //style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

    // Call the base class implementation to ensure the labels are drawn
    QWidget::paintEvent(event);
}
