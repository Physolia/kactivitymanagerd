/*
 *   Copyright (C) 2011 Ivan Cukic <ivan.cukic(at)kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "ResourceScoreCache.h"

#include "ActivityManager.h"

#include "StatsPlugin.h"
#include "DatabaseConnection.h"

#include <KDebug>

/**
 *
 */
class ResourceScoreCachePrivate {
public:
    QString activity;
    QString application;
    QUrl resource;

};

ResourceScoreCache::ResourceScoreCache(const QString & activity, const QString & application, const QUrl & resource)
    : d(new ResourceScoreCachePrivate())
{
    kDebug() << "Going to update score for"
        << activity << application << resource;

    d->activity = activity;
    d->application = application;
    d->resource = resource;
}

ResourceScoreCache::~ResourceScoreCache()
{
    delete d;
}

void ResourceScoreCache::updateScore()
{
    QDateTime lastUpdate;
    qreal score;

    DatabaseConnection::self()->getResourceScoreCache(
            d->activity, d->application, d->resource,
            score, lastUpdate);

    // Forcing immediate sync of the score, in case of kamd being terminated improperly
    // {
    //     Nepomuk::Resource resource(d->self);
    //     resource.setProperty(KExt::cachedScore(), score);
    //     resource.setProperty(NAO::score(), score);
    // }

    Rankings::self()->resourceScoreUpdated(d->activity, d->application, d->resource, score);
}
