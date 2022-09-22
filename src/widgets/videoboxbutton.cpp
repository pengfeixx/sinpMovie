/*
 * Copyright (C) 2020 ~ 2021, Deepin Technology Co., Ltd. <support@deepin.org>
 *
 * Author:     zhuyuliang <zhuyuliang@uniontech.com>
 *
 * Maintainer: xiepengfei <xiepengfei@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "videoboxbutton.h"
#include <QDebug>
#include <QPainter>

#include <DHiDPIHelper>
#include <DPalette>

DGUI_USE_NAMESPACE
VideoBoxButton::VideoBoxButton(const QString &text, QWidget *parent)
    : DButtonBoxButton(text, parent)
{
}

VideoBoxButton::VideoBoxButton(const QString &text, const QString &normalPic, const QString &hoverPic,
                               const QString &pressPic, const QString &checkedPic, QWidget *parent)
    : DButtonBoxButton(text, parent)
{
    defaultPicPath.normalPicPath = normalPic;
    defaultPicPath.hoverPicPath = hoverPic;
    defaultPicPath.pressPicPath = pressPic;
    defaultPicPath.checkedPicPath = checkedPic;

    auto pl = this->palette();
    QColor sbcolor("#000000");
    sbcolor.setAlphaF(0.05);
    pl.setColor(DPalette::Shadow, sbcolor);
    setPalette(pl);
    QIcon icon;
    icon.addFile(normalPic);

    this->setIconSize(QSize(36, 36));
    this->setIcon(icon);
}

// cppcheck修改
//void VideoBoxButton::setPropertyPic(QString propertyName, const QVariant &value,
//                                    const QString &normalPic, const QString &hoverPic, const QString &pressPic, const QString &checkedPic)
//{
//    VideoPicPathInfo curPicPath;
//    curPicPath.normalPicPath = normalPic;
//    curPicPath.hoverPicPath = hoverPic;
//    curPicPath.pressPicPath = pressPic;
//    curPicPath.checkedPicPath = checkedPic;

//    if (propertyPicPaths.first == propertyName && propertyPicPaths.second.contains(value)) {
//        propertyPicPaths.second[value] = curPicPath;
//    } else {
//        QMap<QVariant, VideoPicPathInfo> curPicPathInfo;
//        curPicPathInfo.insert(value, curPicPath);
//        propertyPicPaths.first = propertyName;
//        propertyPicPaths.second = curPicPathInfo;
//    }
//    QIcon icon;
//    icon.addFile(normalPic);

//    this->setIconSize(QSize(36, 36));
//    this->setIcon(icon);
//}

//void VideoBoxButton::setPropertyPic(const QString &normalPic, const QString &hoverPic, const QString &pressPic, const QString &checkedPic)
//{
//    defaultPicPath.normalPicPath = normalPic;
//    defaultPicPath.hoverPicPath = hoverPic;
//    defaultPicPath.pressPicPath = pressPic;
//    defaultPicPath.checkedPicPath = checkedPic;
//    QIcon icon;
//    icon.addFile(normalPic);

//    this->setIconSize(QSize(36, 36));
//    this->setIcon(icon);
//}

/*void VideoBoxButton::setTransparent(bool flag)
{
    transparent = flag;
}*/

/*void VideoBoxButton::setAutoChecked(bool flag)
{
    autoChecked = flag;
}*/



void VideoBoxButton::enterEvent(QEvent *event)
{
//    status = 1;
//    QString curPicPath = defaultPicPath.normalPicPath;
//    if (propertyPicPaths.first.isEmpty() || !propertyPicPaths.second.contains(property(propertyPicPaths.first.toStdString().data()))) {
//        QString curPropertyPicPathStr;
//        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
//            curPropertyPicPathStr = defaultPicPath.checkedPicPath;
//        } else {
//            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
//                curPropertyPicPathStr = defaultPicPath.hoverPicPath;
//            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
//                curPropertyPicPathStr = defaultPicPath.pressPicPath;
//            }
//        }

//        if (!curPropertyPicPathStr.isEmpty()) {
//            curPicPath = curPropertyPicPathStr;
//        }
//    } else {
//        QVariant value = property(propertyPicPaths.first.toStdString().data());
//        VideoPicPathInfo curPropertyPicPath = propertyPicPaths.second[value];
//        QString curPropertyPicPathStr;
//        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
//            curPropertyPicPathStr = curPropertyPicPath.checkedPicPath;
//        } else {
//            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
//                curPropertyPicPathStr = curPropertyPicPath.hoverPicPath;
//            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
//                curPropertyPicPathStr = curPropertyPicPath.pressPicPath;
//            } else {
//                curPropertyPicPathStr = curPropertyPicPath.normalPicPath;
//            }
//        }
//        if (!curPropertyPicPathStr.isEmpty()) {
//            curPicPath = curPropertyPicPathStr;
//        }
//    }


//    QIcon icon;
//    icon.addFile(curPicPath);

//    this->setIconSize(QSize(36, 36));
//    this->setIcon(icon);
//    DButtonBoxButton::enterEvent(event);
//    if (autoChecked) {
//        setChecked(true);
//    }

    DButtonBoxButton::enterEvent(event);
}

void VideoBoxButton::leaveEvent(QEvent *event)
{
//    status = 0;
//    QString curPicPath = defaultPicPath.normalPicPath;
//    if (propertyPicPaths.first.isEmpty() || !propertyPicPaths.second.contains(property(propertyPicPaths.first.toStdString().data()))) {
//        QString curPropertyPicPathStr;
//        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
//            curPropertyPicPathStr = defaultPicPath.checkedPicPath;
//        } else {
//            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
//                curPropertyPicPathStr = defaultPicPath.hoverPicPath;
//            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
//                curPropertyPicPathStr = defaultPicPath.pressPicPath;
//            }
//        }

//        if (!curPropertyPicPathStr.isEmpty()) {
//            curPicPath = curPropertyPicPathStr;
//        }
//    } else {
//        QVariant value = property(propertyPicPaths.first.toStdString().data());
//        VideoPicPathInfo curPropertyPicPath = propertyPicPaths.second[value];
//        QString curPropertyPicPathStr;
//        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
//            curPropertyPicPathStr = curPropertyPicPath.checkedPicPath;
//        } else {
//            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
//                curPropertyPicPathStr = curPropertyPicPath.hoverPicPath;
//            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
//                curPropertyPicPathStr = curPropertyPicPath.pressPicPath;
//            } else {
//                curPropertyPicPathStr = curPropertyPicPath.normalPicPath;
//            }
//        }
//        if (!curPropertyPicPathStr.isEmpty()) {
//            curPicPath = curPropertyPicPathStr;
//        }
//    }


//    QIcon icon;
//    icon.addFile(curPicPath);

//    this->setIconSize(QSize(36, 36));
//    this->setIcon(icon);
//    DButtonBoxButton::leaveEvent(event);
//    if (autoChecked) {
//        setChecked(false);
//    }
    DButtonBoxButton::leaveEvent(event);
}

void VideoBoxButton::mousePressEvent(QMouseEvent *event)
{
    status = 2;
    QString curPicPath = defaultPicPath.normalPicPath;
    if (propertyPicPaths.first.isEmpty() || !propertyPicPaths.second.contains(property(propertyPicPaths.first.toStdString().data()))) {
        QString curPropertyPicPathStr;
        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
            curPropertyPicPathStr = defaultPicPath.checkedPicPath;
        } else {
            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
                curPropertyPicPathStr = defaultPicPath.hoverPicPath;
            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
                curPropertyPicPathStr = defaultPicPath.pressPicPath;
            }
        }

        if (!curPropertyPicPathStr.isEmpty()) {
            curPicPath = curPropertyPicPathStr;
        }
    } else {
        QVariant value = property(propertyPicPaths.first.toStdString().data());
        VideoPicPathInfo curPropertyPicPath = propertyPicPaths.second[value];
        QString curPropertyPicPathStr;
        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
            curPropertyPicPathStr = curPropertyPicPath.checkedPicPath;
        } else {
            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
                curPropertyPicPathStr = curPropertyPicPath.hoverPicPath;
            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
                curPropertyPicPathStr = curPropertyPicPath.pressPicPath;
            } else {
                curPropertyPicPathStr = curPropertyPicPath.normalPicPath;
            }
        }
        if (!curPropertyPicPathStr.isEmpty()) {
            curPicPath = curPropertyPicPathStr;
        }
    }


    QIcon icon;
    icon.addFile(curPicPath);

    this->setIconSize(QSize(36, 36));
    this->setIcon(icon);
    DButtonBoxButton::mousePressEvent(event);
}

void VideoBoxButton::mouseReleaseEvent(QMouseEvent *event)
{
    status = 0;
    QString curPicPath = defaultPicPath.normalPicPath;
    if (propertyPicPaths.first.isEmpty() || !propertyPicPaths.second.contains(property(propertyPicPaths.first.toStdString().data()))) {
        QString curPropertyPicPathStr;
        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
            curPropertyPicPathStr = defaultPicPath.checkedPicPath;
        } else {
            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
                curPropertyPicPathStr = defaultPicPath.hoverPicPath;
            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
                curPropertyPicPathStr = defaultPicPath.pressPicPath;
            }
        }

        if (!curPropertyPicPathStr.isEmpty()) {
            curPicPath = curPropertyPicPathStr;
        }
    } else {
        QVariant value = property(propertyPicPaths.first.toStdString().data());
        VideoPicPathInfo curPropertyPicPath = propertyPicPaths.second[value];
        QString curPropertyPicPathStr;
        if (isChecked() && !defaultPicPath.checkedPicPath.isEmpty()) {
            curPropertyPicPathStr = curPropertyPicPath.checkedPicPath;
        } else {
            if (status == 1 && !defaultPicPath.hoverPicPath.isEmpty()) {
                curPropertyPicPathStr = curPropertyPicPath.hoverPicPath;
            } else if (status == 2 && !defaultPicPath.pressPicPath.isEmpty()) {
                curPropertyPicPathStr = curPropertyPicPath.pressPicPath;
            } else {
                curPropertyPicPathStr = curPropertyPicPath.normalPicPath;
            }
        }
        if (!curPropertyPicPathStr.isEmpty()) {
            curPicPath = curPropertyPicPathStr;
        }
    }


    QIcon icon;
    icon.addFile(curPicPath);

    this->setIconSize(QSize(36, 36));
    this->setIcon(icon);
    DButtonBoxButton::mouseReleaseEvent(event);
}
