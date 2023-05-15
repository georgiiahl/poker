#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QMessageBox>
#include <QSet>
#include <QTextEdit>
#include <QLabel>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCardCheckboxClicked();
    void onSaveButtonClicked(QLineEdit *lineEdit, QLabel *label);

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QSpacerItem *rightSpacer;
    QLabel *selectedCardsLabel;
    QList<QCheckBox*> cardCheckboxes;
    QSet<QString> selectedCards;
    QTextEdit *messageBox; // added for MessageBox
    QPushButton *messageBoxButton; // added for MessageBox button
    QPushButton *button1; // added for the first additional button
    QPushButton *button2; // added for the second additional button
};

#endif // MAINWINDOW_H
