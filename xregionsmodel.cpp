/* Copyright (c) 2025 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "xregionsmodel.h"

XRegionsModel::XRegionsModel(QIODevice *pDevice, XInfoDB *pXInfoDB, const OPTIONS &options, QObject *pParent) : QAbstractItemModel(pParent)
{
    g_pDevice = pDevice;
    g_pXInfoDB = pXInfoDB;
    g_options = options;

    g_listHRegionTotal = XFormats::getHighlights(options.fileType, pDevice, XBinary::HLTYPE_TOTAL, options.bIsImage, options.nModuleAddress);
    g_listHRegionsNative = XFormats::getHighlights(options.fileType, pDevice, XBinary::HLTYPE_NATIVEREGIONS, options.bIsImage, options.nModuleAddress);
    g_listHRegionsSubNative = XFormats::getHighlights(options.fileType, pDevice, XBinary::HLTYPE_NATIVESUBREGIONS, options.bIsImage, options.nModuleAddress);
    g_listHRegionsData = XFormats::getHighlights(options.fileType, pDevice, XBinary::HLTYPE_DATA, options.bIsImage, options.nModuleAddress);

    {
        qint32 nNumberOfRegionsTotal = g_listHRegionTotal.count();

        if (nNumberOfRegionsTotal) {
            g_pTotalItem = new XRegionItem(nullptr, g_listHRegionTotal.at(0));
            g_mapItems.insert(g_listHRegionTotal.at(0).sGUID, g_pTotalItem);
        } else {
            g_pTotalItem = nullptr;
        }
    }
    {
        qint32 nNumberOfRegions = g_listHRegionsNative.count();

        for (qint32 i = 0; i < nNumberOfRegions; i++) {
            XRegionItem *pItem = new XRegionItem(g_pTotalItem, g_listHRegionsNative.at(i));

            if (g_pTotalItem) {
                g_pTotalItem->appendChild(pItem);
            }

            g_mapItems.insert(g_listHRegionsNative.at(i).sGUID, pItem);
        }
    }
    {
        qint32 nNumberOfRegions = g_listHRegionsSubNative.count();

        for (qint32 i = 0; i < nNumberOfRegions; i++) {
            XRegionItem *pParentItem = nullptr;

            QString sGUID = XBinary::findParentHRegion(g_listHRegionsNative, g_listHRegionsSubNative.at(i)).sGUID;

            if (sGUID != "") {
                pParentItem = g_mapItems.value(sGUID);
            } else {
                pParentItem = g_pTotalItem;
            }

            XRegionItem *pItem = new XRegionItem(pParentItem, g_listHRegionsSubNative.at(i));

            if (pParentItem) {
                pParentItem->appendChild(pItem);
            }

            g_mapItems.insert(g_listHRegionsSubNative.at(i).sGUID, pItem);
        }
    }

    {
        qint32 nNumberOfRegions = g_listHRegionsData.count();

        for (qint32 i = 0; i < nNumberOfRegions; i++) {
            XRegionItem *pParentItem = nullptr;

            QString sGUID = XBinary::findParentHRegion(g_listHRegionsSubNative, g_listHRegionsData.at(i)).sGUID;

            if (sGUID == "") {
                sGUID = XBinary::findParentHRegion(g_listHRegionsNative, g_listHRegionsData.at(i)).sGUID;
            }

            if (sGUID != "") {
                pParentItem = g_mapItems.value(sGUID);
            } else {
                pParentItem = g_pTotalItem;
            }

            XRegionItem *pItem = new XRegionItem(pParentItem, g_listHRegionsData.at(i));

            if (pParentItem) {
                pParentItem->appendChild(pItem);
            }

            g_mapItems.insert(g_listHRegionsData.at(i).sGUID, pItem);
        }
    }

    // TODO invalids
}

XRegionsModel::~XRegionsModel()
{
    if (g_pTotalItem) {
        delete g_pTotalItem;
    }
}

QModelIndex XRegionsModel::index(int nRow, int nColumn, const QModelIndex &parent) const
{
    QModelIndex result;

    if (hasIndex(nRow, nColumn, parent)) {
        XRegionItem *pParentItem = nullptr;

        if (!parent.isValid()) {
            pParentItem = g_pTotalItem;
        } else {
            pParentItem = static_cast<XRegionItem *>(parent.internalPointer());
        }

        XRegionItem *pItemChild = pParentItem->child(nRow);

        if (pItemChild) {
            result = createIndex(nRow, nColumn, pItemChild);
        }
    }

    return result;
}

QModelIndex XRegionsModel::parent(const QModelIndex &index) const
{
    QModelIndex result;

    if (index.isValid()) {
        XRegionItem *pItemChild = static_cast<XRegionItem *>(index.internalPointer());
        XRegionItem *pParentItem = pItemChild->getParentItem();

        if (pParentItem != g_pTotalItem) {
            result = createIndex(pParentItem->row(), 0, pParentItem);
        }
    }

    return result;
}

int XRegionsModel::rowCount(const QModelIndex &parent) const
{
    int nResult = 0;

    if (parent.column() <= 0) {
        XRegionItem *pParentItem = nullptr;

        if (!parent.isValid()) {
            pParentItem = g_pTotalItem;
        } else {
            pParentItem = static_cast<XRegionItem *>(parent.internalPointer());
        }

        nResult = pParentItem->childCount();
    }

    return nResult;
}

int XRegionsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return g_pTotalItem->columnCount();
}

QVariant XRegionsModel::data(const QModelIndex &index, int nRole) const
{
    QVariant result;

    if (index.isValid()) {
        XRegionItem *pItem = static_cast<XRegionItem *>(index.internalPointer());

        result = pItem->data(nRole, index.column());
    }

    return result;
}

QVariant XRegionsModel::headerData(int nSection, Qt::Orientation orientation, int nRole) const
{
    QVariant result;

    if (orientation == Qt::Horizontal) {
        if (nRole == Qt::DisplayRole) {
            if (nSection == XRegionItem::COLUMN_FILEOFFSET) {
                result = tr("File offset");
            } else if (nSection == XRegionItem::COLUMN_FILESIZE) {
                result = tr("File size");
            } else if (nSection == XRegionItem::COLUMN_VIRTUALADDRESS) {
                result = tr("Virtual address");
            } else if (nSection == XRegionItem::COLUMN_VIRTUALSIZE) {
                result = tr("Virtual size");
            } else if (nSection == XRegionItem::COLUMN_NAME) {
                result = tr("Name");
            } else if (nSection == XRegionItem::COLUMN_RFLAGS) {
                result = tr("Flags");
            } else if (nSection == XRegionItem::COLUMN_INFO) {
                result = tr("Info");
            } else {
                result = QString();
            }
        } else if (nRole == Qt::TextAlignmentRole) {
            if ((nSection == XRegionItem::COLUMN_FILEOFFSET) || (nSection == XRegionItem::COLUMN_FILESIZE) || (nSection == XRegionItem::COLUMN_VIRTUALADDRESS) ||
                (nSection == XRegionItem::COLUMN_VIRTUALSIZE)) {
                result = (qint32)Qt::AlignVCenter + (qint32)Qt::AlignRight;
            } else {
                result = (qint32)Qt::AlignVCenter + (qint32)Qt::AlignLeft;
            }
        }
    }

    return result;
}

QString XRegionsModel::toFormattedString()
{
    QString sResult;

    _toFormattedString(&sResult, g_pTotalItem, 0);

    return sResult;
}

void XRegionsModel::_toFormattedString(QString *pString, XRegionItem *pItem, qint32 nLevel)
{
    QString sResult;
    sResult = sResult.leftJustified(4 * nLevel, ' ');  // TODO function !!!
    sResult.append(QString("%1 %2 %3 %4 %5 %6\n")
                       .arg(pItem->data(Qt::DisplayRole, 0).toString(), pItem->data(Qt::DisplayRole, 1).toString(), pItem->data(Qt::DisplayRole, 2).toString(),
                            pItem->data(Qt::DisplayRole, 3).toString(), pItem->data(Qt::DisplayRole, 4).toString(), pItem->data(Qt::DisplayRole, 5).toString()));
    pString->append(sResult);

    qint32 nNumberOfChildren = pItem->childCount();

    for (qint32 i = 0; i < nNumberOfChildren; i++) {
        _toFormattedString(pString, pItem->child(i), nLevel + 1);
    }
}
