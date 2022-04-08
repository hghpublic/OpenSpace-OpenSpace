/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2022                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#ifndef __OPENSPACE_UI_LAUNCHER___SGCTEDIT___H__
#define __OPENSPACE_UI_LAUNCHER___SGCTEDIT___H__

#include <QDialog>

#include <sgctedit/displaywindowunion.h>
#include <sgctedit/filesupport.h>
#include <sgctedit/monitorbox.h>
#include <sgctedit/orientation.h>
#include <QApplication>
#include <QColor>
#include <QLayout>
#include <QScreen>
#include <memory>
#include <string>
#include <vector>

class QWidget;

class SgctEdit final : public QDialog {
Q_OBJECT
public:
    /**
     * Constructor for SgctEdit class, the underlying class for the full window
     * configuration editor
     *
     * \param parent The Qt QWidget parent object
     * \param windowList vector of sgct::config::Window objects which will be modified
     *                   by the user settings, and then used for writing to file in
     *                   the launcher code
     * \param cluster reference to sgct::config::Cluster object that contains sgct
     *                objects that will be modified by the window configuration settings
     * \param screenList A QList containing a QScreen object for each monitor in the
     *                   system
     * \param userConfigPath A string containing the file path of the user config
     *                       directory where all window configs are stored
    */
    SgctEdit(QWidget* parent, std::vector<sgct::config::Window>& windowList,
        sgct::config::Cluster& cluster, const QList<QScreen*>& screenList,
        const std::string userConfigPath);
    ~SgctEdit();
    /**
     * Used to determine if the window configuration was saved to file, or canceled
     *
     * \return true if configuration was saved to file
    */
    bool wasSaved() const;
    /**
     * Returns the saved filename
     *
     * \return saved filename in std::string
    */
    std::string saveFilename();

private:
    void addDisplayLayout(QHBoxLayout* layout);
    void createWidgets();
    void systemMonitorConfiguration(const QList<QScreen*>& screenList);

    std::shared_ptr<MonitorBox> _monBox = nullptr;
    std::vector<QRect> _monitorSizeList;
    QVBoxLayout* _displayLayout = nullptr;
    QFrame* _displayFrame = nullptr;
    std::shared_ptr<DisplayWindowUnion> _displayWidget = nullptr;
    QRect _monitorWidgetSize = {0, 0, 500, 500};
    FileSupport* _fileSupportWidget = nullptr;
    Orientation* _orientationWidget = nullptr;
    sgct::config::Cluster& _cluster;
    std::vector<sgct::config::Window>& _windowList;
    const std::string _userConfigPath;
    bool _saveSelected = false;
    unsigned int _nMaxWindows = 3;
    const std::array<QColor, 4> _colorsForWindows = {
        QColor(0x2B, 0x9E, 0xC3),
        QColor(0xFC, 0xAB, 0x10),
        QColor(0x44, 0xAF, 0x69),
        QColor(0xF8, 0x33, 0x3C)
    };
};

#endif // __OPENSPACE_UI_LAUNCHER___SGCTEDIT___H__