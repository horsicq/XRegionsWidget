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
#include "xregionswidget.h"
#include "ui_xregionswidget.h"

XRegionsWidget::XRegionsWidget(QWidget *pParent) : XShortcutsWidget(pParent), ui(new Ui::XRegionsWidget)
{
    ui->setupUi(this);

    m_pDevice = nullptr;
    g_pXInfoDB = nullptr;
    g_options = {};
}

XRegionsWidget::~XRegionsWidget()
{
    delete ui;
}

void XRegionsWidget::setData(QIODevice *pDevice, XInfoDB *pXInfoDB, const XRegionsModel::OPTIONS &options, bool bReload)
{
    m_pDevice = pDevice;
    g_pXInfoDB = pXInfoDB;
    g_options = options;

    XFormats::setFileTypeComboBox(options.fileType, m_pDevice, ui->comboBoxType);

    if (bReload) {
        reloadData(false);
    }
}

void XRegionsWidget::adjustView()
{
}

void XRegionsWidget::reloadData(bool bSaveSelection)
{
    Q_UNUSED(bSaveSelection)

    if (g_pXInfoDB) {
        XRegionsModel::OPTIONS _options = g_options;
        _options.fileType = (XBinary::FT)(ui->comboBoxType->currentData().toUInt());
        XRegionsModel *pModel = new XRegionsModel(m_pDevice, g_pXInfoDB, _options, this);

        ui->treeViewMain->setModel(pModel);
    }
}
