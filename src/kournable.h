#ifndef KOURNABLE_H
#define KOURNABLE_H

#include <QWidget>

namespace Ui {
class Kournable;
}

class Kournable : public QWidget
{
    Q_OBJECT

public:
    explicit Kournable(QWidget *parent = nullptr);
    ~Kournable();

    void clear();
    void load(QJsonObject json);
    QJsonObject save();
    bool isModified();
    void setModified(bool modified);

signals:
    void contentsChanged();

private:
    Ui::Kournable *ui;
    void handleDocumentChanges();
};

#endif // KOURNABLE_H
