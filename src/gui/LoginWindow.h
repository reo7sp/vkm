/*
 * Copyright 2015 Reo_SP
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _VKM_GUI_LOGIN_WINDOW_H
#define _VKM_GUI_LOGIN_WINDOW_H

#include <QMainWindow>
#include <QUrl>

class LoginWindow : public QMainWindow {
Q_OBJECT

public:
	explicit LoginWindow(QWidget* parent = nullptr);

private:
	QWidget* helloPanel = nullptr;

private slots:
	void showVkLoginPage();
	void checkUrl(const QUrl& url);
};

#endif
