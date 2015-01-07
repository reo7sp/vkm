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

#include "UserConfig.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "../Utils.h"

UserConfig& UserConfig::get() {
	static UserConfig instance;
	return instance;
}

UserConfig::UserConfig() {
	reload();
}

void UserConfig::reload() {
	QFile file(Utils::getDataDirectory() + "user.json");
	if (!file.open(QFile::ReadOnly | QFile::Text)) return;
	auto mainJsonObject = QJsonDocument::fromJson(file.readAll()).object();
	file.close();

	_accessToken = Utils::xorCrypt(mainJsonObject.value("accessToken").toString());
	_userId = Utils::xorCrypt(mainJsonObject.value("userId").toString());
}

void UserConfig::rewrite() {
	QFile file(Utils::getDataDirectory() + "user.json");
	if (!file.open(QFile::WriteOnly | QFile::Text)) return;
	QJsonObject mainJsonObject;

	mainJsonObject.insert("accessToken", Utils::xorCrypt(_accessToken));
	mainJsonObject.insert("userId", Utils::xorCrypt(_userId));

	file.write(QJsonDocument(mainJsonObject).toJson());
	file.close();
}
