#include "mainwindow.h"
#include "../src/BigInteger.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // RSA Init
    if (!BigInteger::load_prime()) {
        QMessageBox::critical(NULL, "No Primes File Found!", "primes.txt not found, please put it in excute folder.", QMessageBox::Yes);
        return a.exec();
    }
    MainWindow w;
    w.show();
    return a.exec();
}
