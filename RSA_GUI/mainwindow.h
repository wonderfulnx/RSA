#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../src/RSA.h"
#include "../src/BigInteger.h"
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void click_generate_keys();
    void click_encrypt();
    void click_decrypt();

private:
    Ui::MainWindow *ui;
    RSA *rsa = NULL;
    BigInteger* cipher = NULL;
    int cipher_len;
    int bit_n;
    mt19937 mt;
};
#endif // MAINWINDOW_H
