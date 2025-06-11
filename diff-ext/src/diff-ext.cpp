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


DiffPlugin::DiffPlugin(QObject *parent, const QVariantList&) : DiffPlugin(parent) {}

DiffPlugin::DiffPlugin(QObject *parent) : KAbstractFileItemActionPlugin(parent) {
    loadConfig();
}

DiffPlugin::~DiffPlugin() {
    saveConfig();
}

QList<QAction*> DiffPlugin::actions(const KFileItemListProperties& fileItemInfos, QWidget* parentWidget) {
    QFontMetrics fm(parentWidget->font());
    int maxWidth = 250;
    QList<QAction*> actions;
    const QList<QUrl> urls = fileItemInfos.urlList();
    QAction* separator = new QAction(parentWidget);

    separator->setSeparator(true);

    actions << separator;

    if(urls.size() == 2) {
        QAction* compareAction = new QAction(QIcon(QStringLiteral(":/icons/compare.svg")), i18n("Compare"), parentWidget);
        QObject::connect(compareAction, &QAction::triggered, [this, urls]() {
            launchDiffTool(urls.at(0), urls.at(1));
        });
        actions << compareAction;
    }

    if(urls.size() == 1 && !_mru_list.isEmpty()) {
        QUrl current = urls.first();
        QUrl head = QUrl(_mru_list.first());
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
            for(const QUrl& file : urls)
                update_mru_list(file);
        });
        actions << rememberAction;
    }

    if(urls.size() == 1 && !_mru_list.isEmpty()) {
        QUrl current = urls.first();
        QMenu* mruMenu = new QMenu(i18n("Compare with"), parentWidget);

        for(int i = 0; i < _mru_list.size(); ++i) {
            QUrl mruUrl(_mru_list[i]);
            QFileInfo info(mruUrl.toLocalFile());
            QMimeDatabase db;
            QMimeType mime = db.mimeTypeForFile(info);
            QIcon icon = QIcon::fromTheme(mime.iconName());

            QAction* mruAction = new QAction(icon, fm.elidedText(mruUrl.toLocalFile(), Qt::ElideMiddle, maxWidth), mruMenu);
            mruAction->setData(i);

            QObject::connect(mruAction, &QAction::triggered, [this, mruAction, current]() {
                int index = mruAction->data().toInt();
                if(index >= 0 && index < _mru_list.size())
                    launchDiffTool(QUrl(_mru_list.at(index)), current);
            });

            mruMenu->addAction(mruAction);
        }

        mruMenu->addSeparator();

        QAction* clearAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Clear MRU List"), mruMenu);
        QObject::connect(clearAction, &QAction::triggered, [this]() {
            _mru_list.clear();
        });
        mruMenu->addAction(clearAction);

        QAction* submenuAction = new QAction(QIcon(QStringLiteral(":/icons/compare.svg")), i18n("Compare with MRU"), parentWidget);
        submenuAction->setMenu(mruMenu);
        actions << submenuAction;
    }

    return actions;
}

void DiffPlugin::loadConfig() {
    KConfig config(QStringLiteral("diff-extrc"));
    KConfigGroup group = config.group("DiffTool");
    _diff_tool_path = group.readEntry("DiffToolPath", "meld");

    KConfigGroup mru = config.group("MRU");
    _mru_list = mru.readEntry("Files", QStringList());
    _mru_size_limit = mru.readEntry("Limit", 16);
}

void DiffPlugin::saveConfig() {
    KConfig config(QStringLiteral("diff-extrc"));
    KConfigGroup group = config.group("DiffTool");
    group.writeEntry("DiffToolPath", _diff_tool_path);

    KConfigGroup mru = config.group("MRU");
    mru.writeEntry("Files", _mru_list);
    mru.writeEntry("Limit", _mru_size_limit);

    config.sync();
}

void DiffPlugin::update_mru_list(const QUrl& fileUrl) {
    QString fileStr = fileUrl.toString();
    
    _mru_list.removeAll(fileStr);
    _mru_list.prepend(fileStr);

    while(_mru_list.size() > _mru_size_limit) {
        _mru_list.removeLast();
    }        
}

void DiffPlugin::launchDiffTool(const QUrl& file1, const QUrl& file2) const {
    QProcess::startDetached(_diff_tool_path, { file1.toLocalFile(), file2.toLocalFile() });
}

K_PLUGIN_FACTORY_WITH_JSON(DiffPluginFactory, "diff-ext.json", registerPlugin<DiffPlugin>();)

#include "diff-ext.moc"
