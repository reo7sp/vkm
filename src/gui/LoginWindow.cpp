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

#include "LoginWindow.h"

#include <Qt>
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWebView>

#include "../fs/UserConfig.h"

LoginWindow::LoginWindow(QWidget* parent) : QMainWindow(parent) {
	setFixedSize(300, 480);
	setGeometry(QStyle::alignedRect( // center this window
		Qt::LeftToRight,
		Qt::AlignCenter,
		size(),
		qApp->desktop()->availableGeometry()
	));

	helloPanel = new QWidget();
	setCentralWidget(helloPanel);

	auto mainLayout = new QVBoxLayout();
	mainLayout->setContentsMargins(32, 64, 32, 64);
	helloPanel->setLayout(mainLayout);

	auto appNameLabel = new QLabel("<h1>VKM</h1>");
	appNameLabel->setAlignment(Qt::AlignHCenter);
	mainLayout->addWidget(appNameLabel);

	auto loginButton = new QPushButton("Войти");
	connect(loginButton, &QPushButton::clicked, this, &LoginWindow::showVkLoginPage);
	mainLayout->addWidget(loginButton);
}

void LoginWindow::showVkLoginPage() {
	auto loginWebView = new QWebView();
	connect(loginWebView, &QWebView::urlChanged, this, &LoginWindow::checkUrl);

	setCentralWidget(loginWebView);
	delete helloPanel;

	loginWebView->load(QUrl(
		"https://oauth.vk.com/authorize"
		"?client_id=4713446"
		"&scope=messages,offline"
		"&redirect_uri=https://oauth.vk.com/blank.html"
		"&display=mobile"
		"&v=5.27"
		"&response_type=token"
	));
}

void LoginWindow::checkUrl(const QUrl& url) {
	if (url.host() == "oauth.vk.com" && url.path() == "/blank.html") {
		if (!url.fragment().contains("error")) {
			QStringList params = url.fragment().split("&");
			UserConfig::get().setAll(params[0], params[2]);
		}
		close();
	}
};
