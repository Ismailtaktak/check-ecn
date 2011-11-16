#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QFocusEvent>

namespace Ui {
    class CentralWidget;
}

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = 0);
    ~CentralWidget();
    QTextEdit * textEditA();
    QTextEdit * textEditB();
    QTextEdit * currentTextEdit();



public slots:
    void clear();
    void loadItem(int item);
    void saveItem(int item);
    void setEditable(bool editable);

protected slots:
    void setSavable();

signals:
    void savable(bool change);
protected:

private:
    Ui::CentralWidget *ui;
};

#endif // CENTRALWIDGET_H
