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
#include "xregionitem.h"

XRegionItem::XRegionItem(XRegionItem *pItemParent, const XBinary::HREGION &hregion)
{
    g_pParentItem = pItemParent;
    g_hregion = hregion;
}

XRegionItem::~XRegionItem()
{
    qDeleteAll(g_listChildItems);
}

void XRegionItem::appendChild(XRegionItem *pItemChild)
{
    g_listChildItems.append(pItemChild);
}

XRegionItem *XRegionItem::child(int nRow)
{
    return g_listChildItems.value(nRow);
}

int XRegionItem::childCount() const
{
    return g_listChildItems.count();
}

int XRegionItem::columnCount() const
{
    return __COLUMN_SIZE;
}

int XRegionItem::row() const
{
    int nResult = 0;

    if (g_pParentItem) {
        nResult = g_pParentItem->g_listChildItems.indexOf(const_cast<XRegionItem *>(this));
    }

    return nResult;
}

XRegionItem *XRegionItem::getParentItem()
{
    return g_pParentItem;
}

QVariant XRegionItem::data(int nRole, int nColumn) const
{
    QVariant result;

    if (nRole == Qt::DisplayRole) {
        if (nColumn == COLUMN_NAME) {
            result = g_hregion.sName;
        } else if (nColumn == COLUMN_PREFIX) {
            result = g_hregion.sPrefix;
        } else if (nColumn == COLUMN_VIRTUALADDRESS) {
            result = XBinary::valueToHex(g_hregion.nVirtualAddress);
        } else if (nColumn == COLUMN_VIRTUALSIZE) {
            result = XBinary::valueToHex(g_hregion.nVirtualSize);
        } else if (nColumn == COLUMN_FILEOFFSET) {
            result = XBinary::valueToHex(g_hregion.nFileOffset);
        } else if (nColumn == COLUMN_FILESIZE) {
            result = XBinary::valueToHex(g_hregion.nFileSize);
        } else if (nColumn == COLUMN_RFLAGS) {
            // TODO
        } else if (nColumn == COLUMN_INFO) {
            // TODO
        } else {
            result = QVariant();
        }
    } else if (nRole == Qt::TextAlignmentRole) {
        if ((nColumn == XRegionItem::COLUMN_FILEOFFSET) || (nColumn == XRegionItem::COLUMN_FILESIZE) || (nColumn == XRegionItem::COLUMN_VIRTUALADDRESS) ||
            (nColumn == XRegionItem::COLUMN_VIRTUALSIZE)) {
            result = (qint32)Qt::AlignVCenter + (qint32)Qt::AlignRight;
        } else {
            result = (qint32)Qt::AlignVCenter + (qint32)Qt::AlignLeft;
        }
    } else if (nRole == Qt::UserRole + XRegionItem::UR_FILEOFFSET) {
        result = g_hregion.nFileOffset;
    } else if (nRole == Qt::UserRole + XRegionItem::UR_FILESIZE) {
        result = g_hregion.nFileSize;
    } else if (nRole == Qt::UserRole + XRegionItem::UR_VIRTUALADDRESS) {
        result = g_hregion.nVirtualAddress;
    } else if (nRole == Qt::UserRole + XRegionItem::UR_VIRTUALSIZE) {
        result = g_hregion.nVirtualSize;
    } else if (nRole == Qt::UserRole + XRegionItem::UR_NAME) {
        result = g_hregion.sName;
    }

    return result;
}
