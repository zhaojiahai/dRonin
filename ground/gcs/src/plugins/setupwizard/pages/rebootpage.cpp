/**
 ******************************************************************************
 *
 * @file       rebootpage.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @see        The GNU Public License (GPL) Version 3
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup SetupWizard Setup Wizard
 * @{
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>
 */

#include "rebootpage.h"
#include "ui_rebootpage.h"

RebootPage::RebootPage(SetupWizard *wizard, QWidget *parent)
    : AbstractWizardPage(wizard, parent)
    , ui(new Ui::RebootPage)
    , m_toggl(false)
{
    ui->setupUi(this);
    ui->yellowLabel->setVisible(false);
    ui->redLabel->setVisible(true);
}

RebootPage::~RebootPage()
{
    disconnect(&m_timer, &QTimer::timeout, this, &RebootPage::toggleLabel);
    m_timer.stop();
    delete ui;
}

void RebootPage::initializePage()
{
    if (!m_timer.isActive()) {
        connect(&m_timer, &QTimer::timeout, this, &RebootPage::toggleLabel);
        m_timer.setInterval(500);
        m_timer.setSingleShot(false);
        m_timer.start();
    }
}

bool RebootPage::validatePage()
{
    return true;
}

void RebootPage::toggleLabel()
{
    m_toggl = !m_toggl;
    ui->yellowLabel->setVisible(m_toggl);
    ui->redLabel->setVisible(!m_toggl);
}
