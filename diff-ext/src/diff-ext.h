#pragma once

#include <KAbstractFileItemActionPlugin>
#include <KFileItemListProperties>
#include <QAction>
#include <QMenu>
#include <QStringList>
#include <QUrl>
#include <QWidget>

#include "config.h"


class DiffPlugin : public KAbstractFileItemActionPlugin {
    Q_OBJECT

    public:
        DiffPlugin(QObject *parent, const QVariantList&);
        DiffPlugin(QObject *parent = nullptr);
        ~DiffPlugin() override;

        QList<QAction*> actions(const KFileItemListProperties& fileItemInfos, QWidget* parentWidget) override;

    private:        
        void launchDiffTool(const QUrl& file1, const QUrl& file2) const;

    private:
        static Config _config;
};
