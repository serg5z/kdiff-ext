#pragma once

#include <QDialog>

#include "config.h"


namespace Ui {
    class DiffExtConfig;
}

class DiffExtConfig : public QDialog {
    Q_OBJECT

    public:
        explicit DiffExtConfig(QWidget *parent = nullptr);
        ~DiffExtConfig();

    private Q_SLOTS:
        void browseDiffTool();
        void showAboutDialog();
        void apply();
        void accept() override;

    private:
        Ui::DiffExtConfig *ui;
        Config _config;
};
