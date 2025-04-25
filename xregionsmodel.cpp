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

    {
        QList<XBinary::HREGION> listHRegionsTotal = XFormats::getHighlights(options.fileType, pDevice, XBinary::HLTYPE_TOTAL, options.bIsImage, options.nModuleAddress);

        qint32 nNumberOfRegionsTotal = listHRegionsTotal.count();

        if (nNumberOfRegionsTotal) {
            g_pMainItem = new XRegionItem(nullptr, listHRegionsTotal.at(0));
        } else {
            g_pMainItem = nullptr;
        }
    }

    QList<XBinary::HREGION> listHRegions = XFormats::getHighlights(options.fileType, pDevice, XBinary::HLTYPE_NATIVEREGIONS, options.bIsImage, options.nModuleAddress);

    qint32 nNumberOfRegions = listHRegions.count();

    for (qint32 i = 0; i < nNumberOfRegions; i++) {

    }
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
    return g_pMainItem->columnCount();;
}

QVariant XRegionsModel::data(const QModelIndex &index, int nRole) const
{
    QVariant result;

    if (index.isValid()) {
        if (nRole == Qt::DisplayRole) {
            result = "DATA";
        }
    }

    return result;
}
