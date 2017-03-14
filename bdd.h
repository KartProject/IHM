#ifndef BDD_H
#define BDD_H

#include <QDialog>

namespace Ui {
class BDD;
}

class BDD : public QDialog
{
    Q_OBJECT

public:
    explicit BDD(QWidget *parent = 0);
    ~BDD();

private:
    Ui::BDD *ui;
};

#endif // BDD_H
