/*
 * Copyright (C) 2014  Vishesh Handa <vhanda@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "imagelocationmodel.h"
#include "imagestorage.h"

ImageLocationModel::ImageLocationModel(QObject* parent)
    : QAbstractListModel(parent)
{
    ImageStorage storage;
    QList<ImageInfo> list = storage.images();

    for (const ImageInfo& ii : list) {
        m_categorizer.addImage(ii);
    }
}

QHash<int, QByteArray> ImageLocationModel::roleNames() const
{
    auto hash = QAbstractItemModel::roleNames();
    hash.insert(FilePathRole, "filePath");

    return hash;
}

QVariant ImageLocationModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    QString country = m_categorizer.countries().at(index.row());

    switch (role) {
        case Qt::DisplayRole:
            return country;

        case FilePathRole:
            return country;
    }

    return QVariant();

}

int ImageLocationModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_categorizer.countries().size();
}