#include "config.h"
#include <KConfig>
#include <KConfigGroup>

Config::Config() {
    load();
}

void Config::load() {
    KConfig config(QStringLiteral("diff-extrc"));

    KConfigGroup general = config.group("General");
    _diffTool = general.readEntry("diff_tool", QStringLiteral("meld"));
    _mruLimit = general.readEntry("mru_limit", 10);

    KConfigGroup mru = config.group("MRU");
    _mruList.clear();
    for (int i = 1;; ++i) {
        QString key = QString("file%1").arg(i);
        QString val = mru.readEntry(key, QString());
        if (val.isEmpty()) break;
        _mruList << val;
    }
}

void Config::save() {
    KConfig config(QStringLiteral("diff-extrc"));

    KConfigGroup general = config.group("General");
    general.writeEntry("diff_tool", _diffTool);
    general.writeEntry("mru_size_limit", _mruLimit);

    KConfigGroup mru = config.group("MRU");
    mru.deleteGroup();
    for (int i = 0; i < _mruList.size(); ++i) {
        mru.writeEntry(QString("file%1").arg(i + 1), _mruList.at(i));
    }

    config.sync();
}

QString Config::diffTool() const {
    return _diffTool;
}

void Config::setDiffTool(const QString& path) {
    _diffTool = path;
}

int Config::mruLimit() const {
    return _mruLimit;
}

void Config::setMruLimit(int limit) {
    _mruLimit = limit;
    
    while (_mruList.size() > _mruLimit) {
        _mruList.removeLast();
    }
}

const QStringList& Config::mruList() const {
    return _mruList;
}

void Config::addToMru(const QString& path) {
    _mruList.removeAll(path);

    _mruList.prepend(path);
    
    while (_mruList.size() > _mruLimit) {
        _mruList.removeLast();
    }
}

void Config::clearMru() {
    _mruList.clear();
}
