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

#include "VkObject.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

void VkObject::sendApiRequest(const QString& method, const QString& args, std::function<void(QJsonObject&)> action) {
	auto manager = new QNetworkAccessManager();
	QUrl url("https://api.vk.com/method/" + method + "?" + (args.isEmpty() ? "" : args + "&") + "v=" + getApiVersion() + "&access_token=" + getAccessToken());
	QObject::connect(manager, &QNetworkAccessManager::finished, [&action](QNetworkReply* reply) {
		auto json = QJsonDocument::fromJson(reply->readAll()).object();
		action(json);
	});
	manager->get(QNetworkRequest(url));
}
