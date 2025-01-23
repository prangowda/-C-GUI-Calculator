#include "calculator.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), currentInput(""), lastValue(0.0), lastOperation("") {

    // Set up the main window
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Set up the display
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(50);
    display->setStyleSheet("font-size: 24px;");

    // Set up button layout
    buttonLayout = new QGridLayout();

    // Create digit buttons
    for (int i = 0; i < 10; ++i) {
        QPushButton *button = new QPushButton(QString::number(i), this);
        button->setFixedSize(60, 60);
        button->setStyleSheet("font-size: 18px;");
        connect(button, &QPushButton::clicked, this, &Calculator::digitPressed);

        int row = (9 - i) / 3;
        int col = (i - 1) % 3;
        if (i == 0) {
            buttonLayout->addWidget(button, 4, 1);
        } else {
            buttonLayout->addWidget(button, row, col);
        }
    }

    // Create operation buttons
    QStringList operations = {"+", "-", "*", "/"};
    for (int i = 0; i < operations.size(); ++i) {
        QPushButton *button = new QPushButton(operations[i], this);
        button->setFixedSize(60, 60);
        button->setStyleSheet("font-size: 18px;");
        connect(button, &QPushButton::clicked, this, &Calculator::operationPressed);
        buttonLayout->addWidget(button, i, 3);
    }

    // Create equals and clear buttons
    QPushButton *equalsButton = new QPushButton("=", this);
    equalsButton->setFixedSize(60, 60);
    equalsButton->setStyleSheet("font-size: 18px;");
    connect(equalsButton, &QPushButton::clicked, this, &Calculator::equalsPressed);
    buttonLayout->addWidget(equalsButton, 4, 2);

    QPushButton *clearButton = new QPushButton("C", this);
    clearButton->setFixedSize(60, 60);
    clearButton->setStyleSheet("font-size: 18px;");
    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearPressed);
    buttonLayout->addWidget(clearButton, 4, 0);

    // Set up main layout
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(display);
    mainLayout->addLayout(buttonLayout);

    centralWidget->setLayout(mainLayout);
}

Calculator::~Calculator() {}

void Calculator::digitPressed() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        currentInput += button->text();
        display->setText(currentInput);
    }
}

void Calculator::operationPressed() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        if (!currentInput.isEmpty()) {
            lastValue = currentInput.toDouble();
            currentInput.clear();
        }
        lastOperation = button->text();
    }
}

void Calculator::equalsPressed() {
    if (!currentInput.isEmpty() && !lastOperation.isEmpty()) {
        double currentValue = currentInput.toDouble();
        double result = 0.0;

        if (lastOperation == "+") {
            result = lastValue + currentValue;
        } else if (lastOperation == "-") {
            result = lastValue - currentValue;
        } else if (lastOperation == "*") {
            result = lastValue * currentValue;
        } else if (lastOperation == "/") {
            if (currentValue == 0) {
                QMessageBox::warning(this, "Error", "Division by zero!");
                return;
            }
            result = lastValue / currentValue;
        }

        display->setText(QString::number(result));
        currentInput.clear();
        lastOperation.clear();
    }
}

void Calculator::clearPressed() {
    currentInput.clear();
    lastOperation.clear();
    lastValue = 0.0;
    display->clear();
}
