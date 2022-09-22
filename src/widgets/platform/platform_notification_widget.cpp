/*
 * Copyright (C) 2020 ~ 2021, Deepin Technology Co., Ltd. <support@deepin.org>
 *
 * Author:     zhuyuliang <zhuyuliang@uniontech.com>
 *
 * Maintainer: liuzheng <liuzheng@uniontech.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * is provided AS IS, WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, and
 * NON-INFRINGEMENT.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/**
 *@file 这个文件是实现影院左上角信息弹窗
 */
#include "platform_notification_widget.h"
#include "utils.h"

#include <DPlatformWindowHandle>
#include <dthememanager.h>
#include <dapplication.h>
#include <QPainterPath>

namespace dmr {
/**
 * @brief NotificationWidget 构造函数
 * @param parent 父窗口
 */
Platform_NotificationWidget::Platform_NotificationWidget(QWidget *parent)
    : QFrame(parent), m_pMainWindow(parent)
{
    initMember();
    setObjectName("NotificationFrame");

    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    m_pMainLayout = new QHBoxLayout();
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_pMainLayout);

    m_pMsgLabel = new DLabel();
    m_pMsgLabel->setFrameShape(QFrame::NoFrame);
    //添加在两种主题下文字效果，使其更加明显
    int nType = DGuiApplicationHelper::instance()->themeType();
    if (nType == 2) {
        m_pMsgLabel->setForegroundRole(DPalette::TextLively);
    } else {
        m_pMsgLabel->setForegroundRole(QPalette::ToolTipText);
    }

    m_pTimer = new QTimer(this);
    if (!utils::check_wayland_env()) {
        m_pTimer->setInterval(2000);
    } else {
        m_pTimer->setInterval(500);
    }
    m_pTimer->setSingleShot(true);
    connect(m_pTimer, &QTimer::timeout, this, &QWidget::hide);

    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, [=](int nType) {
        if (nType == 2) {
            m_pMsgLabel->setForegroundRole(DPalette::TextLively);
        } else {
            m_pMsgLabel->setForegroundRole(QPalette::ToolTipText);
        }
    });

}
/**
 * @brief showEvent 重载显示事件函数
 * @param pShowEvent 显示事件
 */
void Platform_NotificationWidget::showEvent(QShowEvent *event)
{
    ensurePolished();
    if (m_pMainLayout->indexOf(m_pIconLabel) == -1) {
        resize(m_pMsgLabel->sizeHint().width() + m_pMainLayout->contentsMargins().left()
               + m_pMainLayout->contentsMargins().right(), height());
        adjustSize();
    }
    syncPosition();

    QFrame::showEvent(event);
}
/**
 * @brief resizeEvent 重载大小变化事件函数
 * @param pResizeEvent 大小变化事件
 */
void Platform_NotificationWidget::resizeEvent(QResizeEvent *re)
{
    QFrame::resizeEvent(re);
}
/**
 * @brief syncPosition 同步控件位置
 */
void Platform_NotificationWidget::syncPosition()
{
    QRect geom = m_pMainWindow->geometry();
    switch (m_pAnchor) {
    case ANCHOR_BOTTOM:
        move(geom.center().x() - size().width() / 2, geom.bottom() - m_nAnchorDist - height());
        break;

    case ANCHOR_NORTH_WEST:
        move(geom.topLeft() + m_anchorPoint);
        break;

    case ANCHOR_NONE:
        move(geom.center().x() - size().width() / 2, geom.center().y() - size().height() / 2);
        break;
    }
}
/**
 * @brief syncPosition 同步控件位置
 * @param rect 控件的位置
 */
void Platform_NotificationWidget::syncPosition(QRect rect)
{
    QRect geom = rect;
    switch (m_pAnchor) {
    case ANCHOR_BOTTOM:
        move(geom.center().x() - size().width() / 2, geom.bottom() - m_nAnchorDist - height());
        break;

    case ANCHOR_NORTH_WEST:
        move(geom.topLeft() + m_anchorPoint);
        break;

    case ANCHOR_NONE:
        move(geom.center().x() - size().width() / 2, geom.center().y() - size().height() / 2);
        break;
    }
}
/**
 * @brief popup 显示函数
 * @param msg 传入信息内容
 * @param flag 是否自动隐藏，默认为是
 */
void Platform_NotificationWidget::popup(const QString &msg, bool flag)
{
    m_pMainLayout->setContentsMargins(14, 4, 14, 4);
    if (m_pMainLayout->indexOf(m_pMsgLabel) == -1) {
        m_pMainLayout->addWidget(m_pMsgLabel);
    }
    setFixedHeight(30);
    m_pMsgLabel->setText(msg);
    show();
    raise();

    if (flag) {
        m_pTimer->start();
    }
}
/**
 * @brief updateWithMessage 更新显示信息
 * @param newMsg 显示信息
 * @param flag 是否自动隐藏，默认为是
 */
void Platform_NotificationWidget::updateWithMessage(const QString &newMsg, bool flag)
{
    if (m_pIconLabel) {
        m_pIconLabel->setVisible(false);
    }

    QFont font;
    font.setPixelSize(12);
    QFontMetrics fontMetrics(font);
    QString sMsg = fontMetrics.elidedText(newMsg, Qt::ElideMiddle, m_pMainWindow->width() - 12 - 12 - 60);

    if (isVisible()) {
        m_pMsgLabel->setText(sMsg);
        resize(m_pMsgLabel->sizeHint().width() + m_pMainLayout->contentsMargins().left()
               + m_pMainLayout->contentsMargins().right(), height());
        adjustSize();

        if (flag) {
            m_pTimer->start();
        }
        syncPosition();
    } else {
        popup(sMsg, flag);
    }
}
/**
 * @brief paintEvent 重载绘制事件函数
 * @param pPaintEvent 绘制事件
 */
void Platform_NotificationWidget::paintEvent(QPaintEvent *pPaintEvent)
{
    //参考设计图
    const float fRadius = 8;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    bool bLight = (DGuiApplicationHelper::LightType == DGuiApplicationHelper::instance()->themeType());

    //按照ui建议，突出文字
    QColor color = QColor(42, 42, 42, 255 * 0.95);
    QColor borderColor = QColor(0, 0, 0, 255 * 0.3);

    if (bLight) {
        color = QColor(247, 247, 247, 255 * 0.95);
        borderColor = QColor(0, 0, 0, 255 * 0.05);
    }

    if(m_bIsWM) {
        painter.fillRect(rect(), Qt::transparent);
        {
            QPainterPath painterPath;
            painterPath.addRoundedRect(rect(), static_cast<qreal>(fRadius), static_cast<qreal>(fRadius));
            painter.setPen(borderColor);
            painter.drawPath(painterPath);
        }

        QRect viewRect = rect().marginsRemoved(QMargins(1, 1, 1, 1));
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect(), static_cast<qreal>(fRadius), static_cast<qreal>(fRadius));
        painter.fillPath(painterPath, color);

        QFrame::paintEvent(pPaintEvent);
    } else {
        color.setAlpha(255);
        painter.fillRect(rect(), color);

        if(bLight)
            borderColor.setNamedColor("#F2F2F2");
        else
            borderColor.setNamedColor("#1C1C1C");
        painter.setPen(borderColor);
        painter.drawRect(rect());
    }
}
/**
 * @brief initMember 初始化成员变量
 */
void Platform_NotificationWidget::initMember()
{
    m_pMsgLabel = nullptr;
    m_pIconLabel = nullptr;
    m_pTimer = nullptr;
    m_pFrame = nullptr;
    m_pMainLayout = nullptr;
    m_pAnchor = ANCHOR_NONE;
    m_nAnchorDist = 10;
    m_bIsWheel = true;
}

}
