#ifndef PIXMAP_H
#define PIXMAP_H

#include <QObject>

class Pixmap : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString data READ data NOTIFY dataChanged)
public:
    explicit Pixmap(QObject *parent = nullptr);
    ~Pixmap();
    QString data();
    Q_INVOKABLE void crop(const float x, const float y, const float width, const float height);
    Q_INVOKABLE void save();
    Q_INVOKABLE void reset();

signals:
    void dataChanged();

public slots:
    void load(QString url);
    void clear();

private:
    QPixmap * pixmap;
    QString original_url;
    QString temp_url;
    void saveFileAs(QString &imageFileName);
};

#endif // PIXMAP_H
