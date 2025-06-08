#pragma once

#include <KAbstractFileItemActionPlugin>
#include <KFileItemListProperties>
#include <QAction>
#include <QMenu>
#include <QStringList>
#include <QUrl>
#include <QWidget>

class DiffPlugin : public KAbstractFileItemActionPlugin {
    Q_OBJECT

    public:
        DiffPlugin(QObject *parent, const QVariantList&);
        DiffPlugin(QObject *parent = nullptr);
        ~DiffPlugin() override;

        QList<QAction*> actions(const KFileItemListProperties& fileItemInfos, QWidget* parentWidget) override;

    private:
        QString _diff_tool_path;
        QStringList _mru_list;
        int _mru_size_limit = 16;

        void loadConfig();
        void saveConfig();
        void update_mru_list(const QUrl& fileUrl);
        void launchDiffTool(const QUrl& file1, const QUrl& file2) const;
};
