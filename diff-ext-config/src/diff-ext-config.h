#pragma once

#include <QDialog>

namespace Ui {
    class DiffExtConfig;
}

class DiffExtConfig : public QDialog
{
    Q_OBJECT

    public:
        explicit DiffExtConfig(QWidget *parent = nullptr);
        ~DiffExtConfig();

    private Q_SLOTS:
        void loadConfig();
        void saveConfig();
        void browseDiffTool();
        void showAboutDialog();
        void accept() override;

    private:
        Ui::DiffExtConfig *ui;
};
