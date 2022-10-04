#ifndef KOURNABLE_H
#define KOURNABLE_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class kournable;
}

class kournable : public QMainWindow
{
    Q_OBJECT

public:
    explicit kournable(QWidget *parent = nullptr);
    ~kournable() override;

private:
    QScopedPointer<Ui::kournable> m_ui;
};

#endif // KOURNABLE_H
