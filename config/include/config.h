#pragma once

#include <QString>
#include <QStringList>

class Config {
    public:
        Config();

        void load();
        void save();

        QString diffTool() const;
        void setDiffTool(const QString& path);

        int mruLimit() const;
        void setMruLimit(int limit);

        const QStringList& mruList() const;
        void addToMru(const QString& path);
        void clearMru();

    private:
        QString _diffTool;
        int _mruLimit;
        QStringList _mruList;
};
