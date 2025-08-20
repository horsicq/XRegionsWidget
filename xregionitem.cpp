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

XRegionItem::XRegionItem(XRegionItem *pItemParent, const XBinary::FPART &hregion)
{
    m_pParentItem = pItemParent;
    m_hregion = hregion;
}

XRegionItem::~XRegionItem()
{
    qDeleteAll(m_listChildItems);
}

void XRegionItem::appendChild(XRegionItem *pItemChild)
{
    m_listChildItems.append(pItemChild);
}

XRegionItem *XRegionItem::child(int nRow)
{
    return m_listChildItems.value(nRow);
}

int XRegionItem::childCount() const
{
    return m_listChildItems.count();
}

int XRegionItem::columnCount() const
{
    return __COLUMN_SIZE;
}

int XRegionItem::row() const
{
    int nResult = 0;

    if (m_pParentItem) {
        nResult = m_pParentItem->m_listChildItems.indexOf(const_cast<XRegionItem *>(this));
    }

    return nResult;
}

XRegionItem *XRegionItem::getParentItem()
{
    return m_pParentItem;
}

QVariant XRegionItem::data(int nRole, int nColumn) const
{
    QVariant result;

    if (nRole == Qt::DisplayRole) {
        if (nColumn == COLUMN_NAME) {
            result = m_hregion.sName;
        } else if (nColumn == COLUMN_PREFIX) {
            result = "";  // TODO
        } else if (nColumn == COLUMN_VIRTUALADDRESS) {
            if (m_hregion.nVirtualAddress != -1) {
                result = XBinary::valueToHex(m_hregion.nVirtualAddress);
            }
        } else if (nColumn == COLUMN_VIRTUALSIZE) {
            result = XBinary::valueToHex(m_hregion.nVirtualSize);
        } else if (nColumn == COLUMN_FILEOFFSET) {
            result = XBinary::valueToHex(m_hregion.nFileOffset);
        } else if (nColumn == COLUMN_FILESIZE) {
            result = XBinary::valueToHex(m_hregion.nFileSize);
        } else if (nColumn == COLUMN_RFLAGS) {
            // TODO
        } else if (nColumn == COLUMN_INFO) {
            // TODO
        }
    } else if (nRole == Qt::TextAlignmentRole) {
        if ((nColumn == XRegionItem::COLUMN_FILEOFFSET) || (nColumn == XRegionItem::COLUMN_FILESIZE) || (nColumn == XRegionItem::COLUMN_VIRTUALADDRESS) ||
            (nColumn == XRegionItem::COLUMN_VIRTUALSIZE)) {
            result = (qint32)Qt::AlignVCenter + (qint32)Qt::AlignRight;
        } else {
            result = (qint32)Qt::AlignVCenter + (qint32)Qt::AlignLeft;
        }
    } else if (nRole == Qt::UserRole + XRegionItem::UR_FILEOFFSET) {
        result = m_hregion.nFileOffset;
    } else if (nRole == Qt::UserRole + XRegionItem::UR_FILESIZE) {
        result = m_hregion.nFileSize;
    } else if (nRole == Qt::UserRole + XRegionItem::UR_VIRTUALADDRESS) {
        result = m_hregion.nVirtualAddress;
    } else if (nRole == Qt::UserRole + XRegionItem::UR_VIRTUALSIZE) {
        result = m_hregion.nVirtualSize;
    } else if (nRole == Qt::UserRole + XRegionItem::UR_NAME) {
        result = m_hregion.sName;
    }

    return result;
}
