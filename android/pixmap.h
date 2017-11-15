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
    Q_INVOKABLE void save(QString &imageFileName);

signals:
    void dataChanged();

public slots:
    void load(QString url);
    void clear();

private:
    QPixmap * pixmap;
    QString url;
};

#endif // PIXMAP_H
