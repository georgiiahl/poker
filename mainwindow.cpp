#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTextEdit>
#include <vector>
#include <stdio.h>
#include <omp.h>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);
    leftLayout = new QVBoxLayout();
    rightSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);

    QStringList cardNames = {
                             "2♠", "3♠", "4♠", "5♠", "6♠", "7♠", "8♠", "9♠", "10♠", "J♠", "Q♠", "K♠", "A♠",
                             "2♥", "3♥", "4♥", "5♥", "6♥", "7♥", "8♥", "9♥", "10♥", "J♥", "Q♥", "K♥", "A♥",
                             "2♦", "3♦", "4♦", "5♦", "6♦", "7♦", "8♦", "9♦", "10♦", "J♦", "Q♦", "K♦", "A♦",
                             "2♣", "3♣", "4♣", "5♣", "6♣", "7♣", "8♣", "9♣", "10♣", "J♣", "Q♣", "K♣", "A♣"
                            };

                              for (int deck = 0; deck < 2; ++deck) {
                                                                   QGridLayout *gridLayout = new QGridLayout;
    leftLayout->addLayout(gridLayout);

    for (int i = 0; i < cardNames.size(); ++i) {
        QCheckBox *cardCheckbox = new QCheckBox(cardNames[i], this);
        connect(cardCheckbox, &QCheckBox::clicked, this, &MainWindow::onCardCheckboxClicked);
        gridLayout->addWidget(cardCheckbox, i % 13, i / 13);
        cardCheckboxes.append(cardCheckbox);
    }
}

rightLayout = new QVBoxLayout();
QStringList settingsLabels = {"Blind:", "Chips:", "Players:"};

for (int i = 0; i < settingsLabels.size(); ++i) {
    QVBoxLayout *columnLayout = new QVBoxLayout();
    QLabel *label = new QLabel(settingsLabels[i], this);

    QHBoxLayout *rowLayout = new QHBoxLayout();
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setFixedWidth(200);
    QPushButton *button = new QPushButton("Save", this);
    button->setFixedWidth(100);

    rowLayout->addWidget(lineEdit);
    rowLayout->addWidget(button);

    columnLayout->addWidget(label);
    columnLayout->addLayout(rowLayout);

    rightLayout->addLayout(columnLayout);

    connect(button, &QPushButton::clicked, [this, lineEdit, label]() {
        onSaveButtonClicked(lineEdit, label);
    });
}


messageBox = new QTextEdit(this);
messageBoxButton = new QPushButton("Show Message", this);
connect(messageBoxButton, &QPushButton::clicked, [this]() {
    // KOLHOZ
    messageBox->setText("Sample Message");
});

rightLayout->addWidget(messageBox);
rightLayout->addWidget(messageBoxButton);

button1 = new QPushButton("Button 1", this);
button2 = new QPushButton("Button 2", this);

rightLayout->addWidget(button1);
rightLayout->addWidget(button2);

mainLayout->addLayout(leftLayout);
mainLayout->addItem(rightSpacer);
mainLayout->addLayout(rightLayout);

selectedCardsLabel = new QLabel(this);
mainLayout->addWidget(selectedCardsLabel);
}


void MainWindow::onSaveButtonClicked(QLineEdit *lineEdit, QLabel *label)
{
QString text = label->text() + " " + lineEdit->text() + "\n";
QMessageBox::information(this, "Info", text);
}

MainWindow::~MainWindow()
{
delete mainLayout;
delete centralWidget;
delete ui;
}


void MainWindow::onCardCheckboxClicked()
{
    QCheckBox *senderCheckbox = qobject_cast<QCheckBox*>(sender());
    if (senderCheckbox->isChecked()) {
    selectedCards.insert(senderCheckbox->text());
    }
    else {
    selectedCards.remove(senderCheckbox->text());
    }

    QString text = "Selected Cards: ";
    for (const QString &card : selectedCards) {
    text += card + " ";
    }

    selectedCardsLabel->setText(text);
}
