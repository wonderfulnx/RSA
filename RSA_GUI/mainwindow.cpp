#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <ctime>
#include <QString>
#include "../src/BigInteger.h"
#include "../src/RSA.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set Style
    ui->public_widget->setStyleSheet(QString::fromUtf8("#public_widget {border: 1px solid black; border-radius: 5;}"));
    ui->private_widget->setStyleSheet(QString::fromUtf8("#private_widget {border: 1px solid black; border-radius: 5;}"));
    QFont bold_font("Microsoft YaHei", 9, QFont::Bold);
    QFont font("Microsoft YaHei", 9, QFont::Normal);
    ui->gen_label->setFont(bold_font);
    ui->public_label->setFont(bold_font);
    ui->private_label->setFont(bold_font);
    ui->e_label->setFont(font);
    ui->d_label->setFont(font);
    ui->p_label->setFont(font);
    ui->q_label->setFont(font);
    ui->n_label->setFont(font);
    ui->message_label->setFont(font);
    ui->cipher_label->setFont(font);
    ui->decrypted_label->setFont(font);

    // Set Read Only for edit
    ui->n_textEdit->setReadOnly(true);
    ui->p_textEdit->setReadOnly(true);
    ui->q_textEdit->setReadOnly(true);
    ui->e_textEdit->setReadOnly(true);
    ui->d_textEdit->setReadOnly(true);
    ui->c_textEdit->setReadOnly(true);
    ui->dec_textEdit->setReadOnly(true);

    // setup mt
    random_device rd;
    this->mt = mt19937(rd());

    // connect slots
    connect(ui->gen_btn, SIGNAL(clicked()), this, SLOT(click_generate_keys()));
    connect(ui->encrypt_btn, SIGNAL(clicked()), this, SLOT(click_encrypt()));
    connect(ui->decrypt_btn, SIGNAL(clicked()), this, SLOT(click_decrypt()));

    // btn enable
    ui->encrypt_btn->setEnabled(false);
    ui->decrypt_btn->setEnabled(false);
}

MainWindow::~MainWindow() {
    if (this->rsa) delete rsa;
    if (this->cipher) delete[] cipher;
    delete ui;
}

void MainWindow::click_generate_keys() {
    if (this->rsa) delete rsa;

    // set RSA bits
    int start_ts = clock();
    switch (ui->gen_level_choose->currentIndex()) {
    case 0:
        this->bit_n = 768;
        rsa = new RSA(bit_n, this->mt);
        break;
    case 1:
        this->bit_n = 1024;
        rsa = new RSA(bit_n, this->mt);
        break;
    case 2:
        this->bit_n = 2048;
        rsa = new RSA(bit_n, this->mt);
        break;
    }
    ui->statusbar->showMessage(QString("key generation used %1 ms.").arg(clock() - start_ts));

    // set text edit
    ui->n_textEdit->setText(QString::fromStdString(rsa->n.to_hex()));
    ui->e_textEdit->setText(QString::fromStdString(rsa->e.to_hex()));
    ui->p_textEdit->setText(QString::fromStdString(rsa->p.to_hex()));
    ui->q_textEdit->setText(QString::fromStdString(rsa->q.to_hex()));
    ui->d_textEdit->setText(QString::fromStdString(rsa->d.to_hex()));

    // enable btn
    ui->encrypt_btn->setEnabled(true);
    ui->decrypt_btn->setEnabled(false);
}

void MainWindow::click_encrypt() {
    ui->c_textEdit->setText("");
    // get text
    QString str = ui->m_textEdit->toPlainText();
    if (str == "" || rsa == NULL) return;
    if (str.length() > 100) QMessageBox::information(NULL, "String too long!", "message string too long...", QMessageBox::Yes);
    if (cipher) { delete[] cipher; }

    // encrypt
    cipher = rsa->encrypt_str(str.toStdString());
    cipher_len = str.length();

    // show encryption
    for (int i = 0; i < cipher_len; i++) {
        QString tmp = QString::fromStdString(cipher[i].to_hex(rsa->n.len));
        ui->c_textEdit->moveCursor(QTextCursor::End);
        ui->c_textEdit->insertPlainText(tmp);
    }

    ui->decrypt_btn->setEnabled(true);
}

void MainWindow::click_decrypt() {
    if (cipher == NULL || rsa == NULL) return;
    ui->dec_textEdit->setText("");
    std::string str = rsa->decrypt_str(cipher, cipher_len);
    ui->dec_textEdit->setText(QString::fromStdString(str));
}
