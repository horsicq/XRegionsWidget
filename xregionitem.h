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
#ifndef XREGIONITEM_H
#define XREGIONITEM_H

#include "xinfodb.h"

class XRegionItem {
public:
    enum COLUMN {
        COLUMN_VIRTUALADDRESS = 0,
        COLUMN_VIRTUALSIZE,
        COLUMN_FILEOFFSET,
        COLUMN_FILESIZE,
        COLUMN_RFLAGS,
        COLUMN_NAME,
        COLUMN_INFO,
        __COLUMN_SIZE
    };

    enum UR {
        UR_FILEOFFSET = 0,
        UR_FILESIZE,
        UR_VIRTUALADDRESS,
        UR_VIRTUALSIZE,
        UR_NAME,
    };

    XRegionItem(XRegionItem *pItemParent, const XBinary::HREGION &hregion);
    ~XRegionItem();

    void appendChild(XRegionItem *pItemChild);
    XRegionItem *child(int nRow);
    int childCount() const;
    int columnCount() const;
    int row() const;
    XRegionItem *getParentItem();
    QVariant data(int nRole, int nColumn) const;

private:
    QList<XRegionItem *> g_listChildItems;
    XRegionItem *g_pParentItem;
    XBinary::HREGION g_hregion;
};

#endif  // XREGIONITEM_H
