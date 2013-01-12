/*
 *   Copyright (C) 2011, 2012 Ivan Cukic <ivan.cukic@kde.org>
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PLUGINS_SQLITE_STATS_PLUGIN_H
#define PLUGINS_SQLITE_STATS_PLUGIN_H

#include <QObject>
#include <QSet>

#include <Plugin.h>

#include <utils/nullptr.h>
#include <utils/override.h>

class QFileSystemWatcher;

class NepomukPlugin: public Plugin {
    Q_OBJECT

public:
    explicit NepomukPlugin(QObject *parent = nullptr, const QVariantList & args = QVariantList());

    static NepomukPlugin * self();

    virtual bool init(const QHash < QString, QObject * > & modules) _override;

    QString currentActivity() const;

private Q_SLOTS:
    void setActivityName(const QString & activity, const QString & name);
    void setActivityIcon(const QString & activity, const QString & icon);
    void setCurrentActivity(const QString & activity);
    void addActivity(const QString & activity);
    void removeActivity(const QString & activity);

    void nepomukServiceStarted();
    void nepomukServiceStopped();

    // setResourceMimeType
    // setResourceTitle

private:
    void syncActivities(const QStringList & activities);

    QObject * m_activities;

    static NepomukPlugin * s_instance;
};

#endif // PLUGINS_SQLITE_STATS_PLUGIN_H
