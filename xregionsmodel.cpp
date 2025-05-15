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

    {
        qint32 nNumberOfRegionsTotal = g_listHRegionTotal.count();

        if (nNumberOfRegionsTotal) {
            g_pMainItem = new XRegionItem(nullptr, g_listHRegionTotal.at(0));
            g_mapItems.insert(g_listHRegionTotal.at(0).sGUID, g_pMainItem);
        } else {
            g_pMainItem = nullptr;
        }
    }
    {
        qint32 nNumberOfRegions = g_listHRegionsNative.count();

        for (qint32 i = 0; i < nNumberOfRegions; i++) {
            XRegionItem *pItem = new XRegionItem(g_pMainItem, g_listHRegionsNative.at(i));

            if (g_pMainItem) {
                g_pMainItem->appendChild(pItem);
            }

            g_mapItems.insert(g_listHRegionsNative.at(i).sGUID, pItem);
        }
    }
    {
        qint32 nNumberOfRegions = g_listHRegionsSubNative.count();

        for (qint32 i = 0; i < nNumberOfRegions; i++) {
            XRegionItem *pItem = new XRegionItem(g_pMainItem, g_listHRegionsSubNative.at(i));

            if (g_pMainItem) {
                g_pMainItem->appendChild(pItem);
            }

            g_mapItems.insert(g_listHRegionsSubNative.at(i).sGUID, pItem);
        }
    }

    // TODO invalids
}

XRegionsModel::~XRegionsModel()
{
    if (g_pMainItem) {
        delete g_pMainItem;
    }
}

QModelIndex XRegionsModel::index(int nRow, int nColumn, const QModelIndex &parent) const
{
    QModelIndex result;

    if (hasIndex(nRow, nColumn, parent)) {
        XRegionItem *pParentItem = nullptr;

        if (!parent.isValid()) {
            pParentItem = g_pMainItem;
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

        if (pParentItem != g_pMainItem) {
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
            pParentItem = g_pMainItem;
        } else {
            pParentItem = static_cast<XRegionItem *>(parent.internalPointer());
        }

        nResult = pParentItem->childCount();
    }

    return nResult;
}

int XRegionsModel::columnCount(const QModelIndex &parent) const
{
    return g_pMainItem->columnCount();
}

QVariant XRegionsModel::data(const QModelIndex &index, int nRole) const
{
    QVariant result;

    if (index.isValid()) {
        XRegionItem *pItem = static_cast<XRegionItem *>(index.internalPointer());

        if (nRole == Qt::DisplayRole) {
            result = pItem->data(index.column());
        }
    }

    return result;
}

QString XRegionsModel::toFormattedString()
{
    QString sResult;

    _toFormattedString(&sResult, g_pMainItem, 0);

    return sResult;
}

void XRegionsModel::_toFormattedString(QString *pString, XRegionItem *pItem, qint32 nLevel)
{
    QString sResult;
    sResult = sResult.leftJustified(4 * nLevel, ' ');  // TODO function !!!
    sResult.append(QString("%1 %2 %3 %4 %5 %6\n").arg(pItem->data(0).toString(), pItem->data(1).toString(), pItem->data(2).toString(), pItem->data(3).toString(), pItem->data(4).toString(), pItem->data(5).toString()));
    pString->append(sResult);

    qint32 nNumberOfChildren = pItem->childCount();

    for (qint32 i = 0; i < nNumberOfChildren; i++) {
        _toFormattedString(pString, pItem->child(i), nLevel + 1);
    }
}
