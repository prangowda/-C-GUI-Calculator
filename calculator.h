#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>

class Calculator : public QMainWindow {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitPressed();
    void operationPressed();
    void equalsPressed();
    void clearPressed();

private:
    QLineEdit *display;
    QVBoxLayout *mainLayout;
    QGridLayout *buttonLayout;

    QString currentInput;
    QString lastOperation;
    double lastValue;
};

#endif // CALCULATOR_H
