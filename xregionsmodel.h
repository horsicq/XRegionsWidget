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
#ifndef XREGIONSMODEL_H
#define XREGIONSMODEL_H

#include <QAbstractItemModel>
#include "xregionitem.h"

// TODO finder like in MemoryMap
class XRegionsModel : public QAbstractItemModel {
    Q_OBJECT

public:
    struct OPTIONS {
        XBinary::FT fileType;
        bool bIsImage;
        XADDR nModuleAddress;
    };

    XRegionsModel(QIODevice *pDevice, XInfoDB *pXInfoDB, const OPTIONS &options, QObject *pParent = nullptr);
    ~XRegionsModel();

    QModelIndex index(int nRow, int nColumn, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int nRole = Qt::DisplayRole) const override;


private:
    QIODevice *g_pDevice;
    XInfoDB *g_pXInfoDB;
    OPTIONS g_options;
    XRegionItem *g_pMainItem;
};

#endif  // XREGIONSMODEL_H
