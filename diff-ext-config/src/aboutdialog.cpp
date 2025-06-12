#include "aboutdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("About KDiff Ext Config"));
    setModal(true);

    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel(tr(
        "<h3>kdiff-ext Config</h3>"
        "<p>Version 1.0</p>"
        "<p>Configure your diff tool and MRU list settings.</p>"
        "<p>Copyright © 2025</p>"
    ), this);
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(true);
    layout->addWidget(label);

    auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    layout->addWidget(buttonBox);
}
