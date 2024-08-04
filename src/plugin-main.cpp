/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <plugin-support.h>
#include <obs-frontend-api.h>
#include <qmainwindow.h>
#include <qboxlayout.h>
#include <qboxlayout.h>
#include <qdockwidget.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>

#include <string>
#include <iostream>
#include <filesystem>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

QDockWidget *dock = nullptr;

bool obs_module_load(void)
{
	obs_log(LOG_INFO, "plugin loaded successfully (version %s)", PLUGIN_VERSION);
    obs_log(LOG_WARNING, "Qt version: %s", QT_VERSION_STR);

	obs_frontend_push_ui_translation(obs_module_get_string);

    QMainWindow* mainWindow = static_cast<QMainWindow*>(obs_frontend_get_main_window());

    // Path to recordings
    const auto recordingsPath = obs_frontend_get_current_record_output_path();

    // Create a simple dock widget
    dock = new QDockWidget("Replay Wizard", mainWindow);

    // Create a widget to hold the content
    QWidget* contentWidget = new QWidget(dock);
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);

    // Add a label with some text
    QLabel* label = new QLabel("Recording Path:", contentWidget);
    
    // Show path to recordings
    const auto input = new QLineEdit(contentWidget);
    input->setReadOnly(true);
    input->setText(recordingsPath);

    const auto textEdit = new QTextEdit(contentWidget);
    
    layout->addWidget(label);
    layout->addWidget(input);

    for (const auto & entry : std::filesystem::directory_iterator(recordingsPath)) {
        std::string filepath = entry.path().string();
        
        if (filepath.find("Replay") != std::string::npos) {

            QPushButton* button = new QPushButton(QString::fromStdString(filepath), contentWidget);
            button->setText(entry.path().string().c_str());
            layout->addWidget(button);
        }
    }
    
    layout->addWidget(textEdit);
    dock->setWidget(contentWidget);

    obs_log(LOG_INFO, recordingsPath);

    //obs_frontend_add_dock_by_id("ReaplyWWWWW", "RRRR", &dock);

	return true;
}

void obs_module_unload(void)
{
	obs_log(LOG_INFO, "plugin unloaded");
}
