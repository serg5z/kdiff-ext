#include "diff-ext-config.h"
#include "aboutdialog.h"
#include "ui_diff-ext-config.h"

#include <KConfig>
#include <KConfigGroup>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QIcon>


DiffExtConfig::DiffExtConfig(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DiffExtConfig) {
    ui->setupUi(this);
    setWindowIcon(QIcon(QStringLiteral(":/icons/app-icon.svg")));

    connect(ui->browseButton, &QPushButton::clicked,
            this, &DiffExtConfig::browseDiffTool);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &DiffExtConfig::accept);

    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &DiffExtConfig::reject);

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, &DiffExtConfig::apply);

    connect(ui->buttonBox->button(QDialogButtonBox::Help), &QPushButton::clicked,
            this, &DiffExtConfig::showAboutDialog); 

    _config.load();

    ui->diffToolLineEdit->setText(_config.diffTool());
    ui->mruLimitSpinBox->setValue(_config.mruLimit());
}

DiffExtConfig::~DiffExtConfig() {
    delete ui;
}

void DiffExtConfig::browseDiffTool() {
    QString path = QFileDialog::getOpenFileName(this, tr("Select Diff Tool"));
    if(!path.isEmpty()) {
        ui->diffToolLineEdit->setText(path);
    }
}

void DiffExtConfig::apply() {
    _config.setDiffTool(ui->diffToolLineEdit->text());
    _config.setMruLimit(ui->mruLimitSpinBox->value());

    _config.save();
}

void DiffExtConfig::accept() {
    apply();
    QDialog::accept();
}

void DiffExtConfig::showAboutDialog() {
    AboutDialog about(this);
    about.exec();
}
