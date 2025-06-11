#include "diff-ext-config.h"
#include "aboutdialog.h"
#include "ui_diff-ext-config.h"

#include <KConfig>
#include <KConfigGroup>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QTimer>

DiffExtConfig::DiffExtConfig(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DiffExtConfig)
{
    ui->setupUi(this);

    connect(ui->browseButton, &QPushButton::clicked,
            this, &DiffExtConfig::browseDiffTool);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &DiffExtConfig::accept);

    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &DiffExtConfig::reject);

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, &DiffExtConfig::saveConfig);

    connect(ui->buttonBox->button(QDialogButtonBox::Help), &QPushButton::clicked,
            this, &DiffExtConfig::showAboutDialog); 

    loadConfig();
}

DiffExtConfig::~DiffExtConfig()
{
    delete ui;
}

void DiffExtConfig::browseDiffTool()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select Diff Tool"));
    if (!path.isEmpty()) {
        ui->diffToolLineEdit->setText(path);
    }
}

void DiffExtConfig::loadConfig()
{
    KConfig config(QStringLiteral("diff-extrc"));
    KConfigGroup group = config.group("DiffTool");
    ui->diffToolLineEdit->setText(group.readEntry("DiffToolPath", "meld"));

    KConfigGroup mru = config.group("MRU");
    ui->mruLimitSpinBox->setValue(mru.readEntry("Limit", 16));
}

void DiffExtConfig::saveConfig()
{
    KConfig config(QStringLiteral("diff-extrc"));

    KConfigGroup group = config.group("DiffTool");
    group.writeEntry("DiffToolPath", ui->diffToolLineEdit->text());

    KConfigGroup mru = config.group("MRU");
    mru.writeEntry("Limit", ui->mruLimitSpinBox->value());

    config.sync();
}

void DiffExtConfig::accept()
{
    saveConfig();
    QDialog::accept();
}

void DiffExtConfig::showAboutDialog() {
    AboutDialog about(this);
    about.exec();
}
