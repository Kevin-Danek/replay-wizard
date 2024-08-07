#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class VideoItem : public QWidget
{
    Q_OBJECT

public:
    VideoItem(const QString& thumbnailPath, const QString& fileName, const QString& filePath, QWidget* parent = nullptr);
    QString getFileName() const;
    QString getFilePath() const;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;

private:
    QLabel* thumbnailLabel;
    QLabel* nameLabel;
    QLabel* pathLabel;
    bool isHovered;
};

#endif // CLICKABLEWIDGET_H