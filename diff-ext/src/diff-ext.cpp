#include <KConfig>
#include <KConfigGroup>
#include <KAbstractFileItemActionPlugin>
#include <KFileItemListProperties>
#include <KPluginFactory>
#include <KLocalizedString>
#include <QAction>
#include <QMenu>
#include <QProcess>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileIconProvider>
#include <QMimeDatabase>
#include <QMimeType>
#include <QFileInfo>
#include <QIcon>

class DiffPlugin : public KAbstractFileItemActionPlugin
{
    Q_OBJECT
public:
    DiffPlugin(QObject *parent, const QVariantList&) : DiffPlugin(parent) {
    }

    DiffPlugin(QObject *parent = nullptr) : KAbstractFileItemActionPlugin(parent) {
        // Load the stored configuration (if any)
        KConfig config(QStringLiteral("diffpluginrc"));
        KConfigGroup group = config.group("DiffTool");
        m_diffToolPath = group.readEntry("DiffToolPath", "meld"); // Default to "meld"
    }
    
    QList<QAction*> actions(const KFileItemListProperties& fileItemInfos, QWidget* parentWidget) override {
        QList<QAction*> actions;
        const QList<QUrl> urls = fileItemInfos.urlList();

        if (!urls.isEmpty()) {
            // Remember in MRU List (for 1+ files)
            QAction* rememberAction = new QAction(i18n("Remember in MRU List"), parentWidget);
            QObject::connect(rememberAction, &QAction::triggered, [this, urls]() {
                for (const QUrl& file : urls) {
                    updateMRUList(file);
                }
            });
            actions << rememberAction;
        }

        if (urls.size() == 2) {
            // Compare two selected files
            QAction* compareAction = new QAction(i18n("Compare Selected Files"), parentWidget);
            QObject::connect(compareAction, &QAction::triggered, [urls]() {
                QProcess::startDetached(QStringLiteral("meld"), { urls.at(0).toLocalFile(), urls.at(1).toLocalFile() });
            });
            actions << compareAction;
        }

        if (urls.size() == 1 && !mruList.isEmpty()) {
            // Compare with MRU Head
            QUrl current = urls.first();
            QUrl head = QUrl(mruList.first());
            if (head != current) {
                QAction* compareMRU = new QAction(i18n("Compare with MRU Head"), parentWidget);
                QObject::connect(compareMRU, &QAction::triggered, [head, current]() {
                    QProcess::startDetached(QStringLiteral("meld"), { head.toLocalFile(), current.toLocalFile() });
                });
                actions << compareMRU;
            }
        }

        // MRU Submenu
        if (!urls.isEmpty() && !mruList.isEmpty()) {
            QMenu* mruMenu = new QMenu(i18n("Compare with MRU"), parentWidget);

            for (const QString& path : mruList) {
                QUrl mruUrl(path);
                QFileInfo info(mruUrl.toLocalFile());
                QMimeDatabase db;
                QMimeType mime = db.mimeTypeForFile(info);
                QIcon icon = QIcon::fromTheme(mime.iconName());
                
                QAction* mruAction = new QAction(icon, mruUrl.fileName(), mruMenu);
                QObject::connect(mruAction, &QAction::triggered, [mruUrl, urls]() {
                    for (const QUrl& selected : urls) {
                        if (selected != mruUrl) {
                            QProcess::startDetached(QStringLiteral("meld"), { mruUrl.toLocalFile(), selected.toLocalFile() });
                        }
                    }
                });
                mruMenu->addAction(mruAction);
            }

            mruMenu->addSeparator();

            // Clear MRU List action
            QAction* clearAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Clear MRU List"), mruMenu);
            QObject::connect(clearAction, &QAction::triggered, [this]() {
                mruList.clear();
                saveMRUList();
            });
            mruMenu->addAction(clearAction);

            QAction* submenuAction = new QAction(i18n("Compare with MRU"), parentWidget);
            submenuAction->setMenu(mruMenu);
            actions << submenuAction;
        }

        return actions;
    }

private:
    QString m_diffToolPath; // Path to the diff tool executable
    QStringList mruList;

    void loadMRUList() {
        KConfig config(QStringLiteral("diffpluginrc"));
        KConfigGroup group = config.group("MRU");
        mruList = group.readEntry("Files", QStringList());
    }

    void saveMRUList() {
        KConfig config(QStringLiteral("diffpluginrc"));
        KConfigGroup group = config.group("MRU");
        group.writeEntry("Files", mruList);
        config.sync();
    }

    void updateMRUList(const QUrl& fileUrl) {
        QString fileStr = fileUrl.toString();
        mruList.removeAll(fileStr);
        mruList.prepend(fileStr);
        while (mruList.size() > 10)
            mruList.removeLast();
        saveMRUList();
    }
};

K_PLUGIN_FACTORY_WITH_JSON(DiffPluginFactory, "diff-ext.json", registerPlugin<DiffPlugin>();)

#include "diff-ext.moc"
