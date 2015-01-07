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

#include "VkMessage.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "VkCache.h"

VkMessage::VkMessage(const QString& id) : _id(id) {
}

void VkMessage::parse(const QJsonObject& json) {
	_body = json.value("body").toString();
	_from = VkCache::get().getUser(json.value("user_id").toString());
	_date = json.value("date").toString().toLong();
	_isRead = json.value("read_state").toInt() == 1;
	_forwardedMessages.clear();
	for (QJsonValue item : json.value("fwd_messages").toArray()) {
		VkMessage* fwdMessage = VkCache::get().getMessage("");
		fwdMessage->parse(item.toObject());
		_forwardedMessages.append(fwdMessage);
	}
}

void VkMessage::reload() {
	sendApiRequest("messages.getById", "message_ids=" + _id, [this](QJsonObject& json) {
		parse(json.value("response").toObject().value("items").toArray().at(0).toObject());
	});
}
