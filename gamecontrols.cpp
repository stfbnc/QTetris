#include "gamecontrols.h"
#include "ui_gamecontrols.h"

GameControls::GameControls(QKeySequence r1, QKeySequence l1, QKeySequence d1, QKeySequence rot1,
                           QKeySequence r2, QKeySequence l2, QKeySequence d2, QKeySequence rot2,
                           QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameControls),
    right1(r1),
    left1(l1),
    down1(d1),
    rotate1(rot1),
    right2(r2),
    left2(l2),
    down2(d2),
    rotate2(rot2)
{
    ui->setupUi(this);
    setContentsMargins(0, 0, 0, 0);

    ui->right1->setText(right1.toString().toUpper());
    ui->left1->setText(left1.toString().toUpper());
    ui->down1->setText(down1.toString().toUpper());
    ui->rotate1->setText(rotate1.toString().toUpper());
    ui->right2->setText(right2.toString().toUpper());
    ui->left2->setText(left2.toString().toUpper());
    ui->down2->setText(down2.toString().toUpper());
    ui->rotate2->setText(rotate2.toString().toUpper());

    connect(ui->right1, &QLineEdit::textChanged, this, [&](QString text){
        ui->right1->setText(text.toUpper());
    });
    connect(ui->left1, &QLineEdit::textChanged, this, [&](QString text){
        ui->left1->setText(text.toUpper());
    });
    connect(ui->down1, &QLineEdit::textChanged, this, [&](QString text){
        ui->down1->setText(text.toUpper());
    });
    connect(ui->rotate1, &QLineEdit::textChanged, this, [&](QString text){
        ui->rotate1->setText(text.toUpper());
    });
    connect(ui->right2, &QLineEdit::textChanged, this, [&](QString text){
        ui->right2->setText(text.toUpper());
    });
    connect(ui->left2, &QLineEdit::textChanged, this, [&](QString text){
        ui->left2->setText(text.toUpper());
    });
    connect(ui->down2, &QLineEdit::textChanged, this, [&](QString text){
        ui->down2->setText(text.toUpper());
    });
    connect(ui->rotate2, &QLineEdit::textChanged, this, [&](QString text){
        ui->rotate2->setText(text.toUpper());
    });

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButton()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onOkButton()));
}

GameControls::~GameControls()
{
    delete ui;
}

QKeySequence GameControls::getPlayer1RightKey()
{
    return right1;
}

QKeySequence GameControls::getPlayer1LeftKey()
{
    return left1;
}

QKeySequence GameControls::getPlayer1DownKey()
{
    return down1;
}

QKeySequence GameControls::getPlayer1RotateKey()
{
    return rotate1;
}

QKeySequence GameControls::getPlayer2RightKey()
{
    return right2;
}

QKeySequence GameControls::getPlayer2LeftKey()
{
    return left2;
}

QKeySequence GameControls::getPlayer2DownKey()
{
    return down2;
}

QKeySequence GameControls::getPlayer2RotateKey()
{
    return rotate2;
}

void GameControls::onCancelButton()
{
    this->close();
}

void GameControls::onOkButton()
{
    QString r1 = ui->right1->text();
    QString l1 = ui->left1->text();
    QString d1 = ui->down1->text();
    QString rot1 = ui->rotate1->text();
    QString r2 = ui->right2->text();
    QString l2 = ui->left2->text();
    QString d2 = ui->down2->text();
    QString rot2 = ui->rotate2->text();

    if(!r1.isEmpty())
        right1 = QKeySequence::fromString(r1);
    if(!l1.isEmpty())
        left1 = QKeySequence::fromString(l1);
    if(!d1.isEmpty())
        down1 = QKeySequence::fromString(d1);
    if(!rot1.isEmpty())
        rotate1 = QKeySequence::fromString(rot1);
    if(!r2.isEmpty())
        right2 = QKeySequence::fromString(r2);
    if(!l2.isEmpty())
        left2 = QKeySequence::fromString(l2);
    if(!d2.isEmpty())
        down2 = QKeySequence::fromString(d2);
    if(!rot2.isEmpty())
        rotate2 = QKeySequence::fromString(rot2);

    emit okPressed(right1, left1, down1, rotate1, right2, left2, down2, rotate2);
    this->close();
}
