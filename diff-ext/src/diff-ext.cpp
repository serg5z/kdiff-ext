#include "diff-ext.h"
#include "logging.h"

#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <QAction>
#include <QFileInfo>
#include <QFontMetrics>
#include <QIcon>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QMimeDatabase>
#include <QMimeType>
#include <QProcess>
#include <KPluginFactory>


Config DiffPlugin::_config = Config();

DiffPlugin::DiffPlugin(QObject *parent, const QVariantList&) : DiffPlugin(parent) {
}

DiffPlugin::DiffPlugin(QObject *parent) : KAbstractFileItemActionPlugin(parent) {
}

DiffPlugin::~DiffPlugin() {
    _config.save();
}

QList<QAction*> DiffPlugin::actions(const KFileItemListProperties& fileItemInfos, QWidget* parentWidget) {
    QFontMetrics fm(parentWidget->font());
    int maxWidth = 250;
    QList<QAction*> actions;
    const QList<QUrl> urls = fileItemInfos.urlList();
    QAction* separator = new QAction(parentWidget);
    const QStringList& mru = _config.mruList();

    separator->setSeparator(true);

    actions << separator;

    if(urls.size() == 2) {
        QAction* compareAction = new QAction(QIcon(QStringLiteral(":/icons/compare.svg")), i18n("Compare"), parentWidget);
        QObject::connect(compareAction, &QAction::triggered, [this, urls]() {
            launchDiffTool(urls.at(0), urls.at(1));
        });
        actions << compareAction;
    }

    if(urls.size() == 1 && !mru.isEmpty()) {
        QUrl current = urls.first();
        QUrl head = QUrl(mru.first());
        if(head != current) {
            QAction* compareMRU = new QAction(QIcon(QStringLiteral(":/icons/compare.svg")), i18n("Compare with ") + fm.elidedText(head.toLocalFile(), Qt::ElideMiddle, maxWidth), parentWidget);
            QObject::connect(compareMRU, &QAction::triggered, [this, head, current]() {
                launchDiffTool(head, current);
            });
            actions << compareMRU;
        }
    }

    if(!urls.isEmpty()) {
        QAction* rememberAction = new QAction(QIcon(QStringLiteral(":/icons/remember.svg")), i18n("Remember"), parentWidget);
        QObject::connect(rememberAction, &QAction::triggered, [this, urls]() {
            for(const QUrl& file : urls) {
                _config.addToMru(file.toString());
            }
        });
        actions << rememberAction;
    }

    if(urls.size() == 1 && !mru.isEmpty()) {
        QUrl current = urls.first();
        QMenu* mruMenu = new QMenu(i18n("Compare with"), parentWidget);

        for(int i = 0; i < mru.size(); ++i) {
            QUrl mruUrl(mru[i]);
            QFileInfo info(mruUrl.toLocalFile());
            QMimeDatabase db;
            QMimeType mime = db.mimeTypeForFile(info);
            QIcon icon = QIcon::fromTheme(mime.iconName());

            QAction* mruAction = new QAction(icon, fm.elidedText(mruUrl.toLocalFile(), Qt::ElideMiddle, maxWidth), mruMenu);
            mruAction->setData(i);

            QObject::connect(mruAction, &QAction::triggered, [this, mru, mruAction, current]() {
                int index = mruAction->data().toInt();
                if(index >= 0 && index < mru.size()) {
                    launchDiffTool(QUrl(mru.at(index)), current);
                }
            });

            mruMenu->addAction(mruAction);
        }

        mruMenu->addSeparator();

        QAction* clearAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Clear MRU List"), mruMenu);
        QObject::connect(clearAction, &QAction::triggered, [this]() {
            _config.clearMru();
        });
        mruMenu->addAction(clearAction);

        QAction* submenuAction = new QAction(QIcon(QStringLiteral(":/icons/compare.svg")), i18n("Compare with MRU"), parentWidget);
        submenuAction->setMenu(mruMenu);
        actions << submenuAction;
    }

    return actions;
}

void DiffPlugin::launchDiffTool(const QUrl& file1, const QUrl& file2) const {
    QProcess::startDetached(_config.diffTool(), { file1.toLocalFile(), file2.toLocalFile() });
}

K_PLUGIN_FACTORY_WITH_JSON(DiffPluginFactory, "diff-ext.json", registerPlugin<DiffPlugin>();)

#include "diff-ext.moc"
