#ifndef ROBOBREW_H
#define ROBOBREW_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class robobrew;
}

class robobrew : public QMainWindow
{
    Q_OBJECT

public:
    explicit robobrew(QWidget *parent = nullptr);
    ~robobrew() override;

private:
    QScopedPointer<Ui::robobrew> m_ui;
};

#endif // ROBOBREW_H
