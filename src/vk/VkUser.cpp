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

#include "VkUser.h"

#include <QJsonObject>
#include <QJsonArray>

VkUser::VkUser(const QString& id) : _id(id) {
	reload();
}

void VkUser::parse(const QJsonObject& json) {
	_name = json.value("first_name").toString() + " " + json.value("last_name").toString();
}

void VkUser::reload() {
	sendApiRequest("users.get", "user_ids=" + _id, [this](QJsonObject& json) {
		parse(json.value("response").toArray().at(0).toObject());
	});
}
