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

    // XFormats::getHighlights()
}

QModelIndex XRegionsModel::index(int nRow, int nColumn, const QModelIndex &parent) const
{
    QModelIndex result;

    if (hasIndex(nRow, nColumn, parent)) {
        // XFileInfoItem *pItemParent = nullptr;

        // if (!parent.isValid()) {
        //     pItemParent = g_pRootItem;
        // } else {
        //     pItemParent = static_cast<XFileInfoItem *>(parent.internalPointer());
        // }

        // XFileInfoItem *pItemChild = pItemParent->child(nRow);

        // if (pItemChild) {
        //     result = createIndex(nRow, nColumn, pItemChild);
        // }
    }

    return result;
}

QModelIndex XRegionsModel::parent(const QModelIndex &index) const
{
    QModelIndex result;

    if (index.isValid()) {
        // XFileInfoItem *pItemChild = static_cast<XFileInfoItem *>(index.internalPointer());
        // XFileInfoItem *pParentItem = pItemChild->getParentItem();

        // if (pParentItem != g_pRootItem) {
        //     result = createIndex(pParentItem->row(), 0, pParentItem);
        // }
    }

    return result;
}

int XRegionsModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int XRegionsModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant XRegionsModel::data(const QModelIndex &index, int nRole) const
{
    return QVariant();
}
