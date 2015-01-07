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

#include "VkDialog.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "VkCache.h"

VkDialog::VkDialog(const QString& id, bool isChat)
: _id(id)
, _isChat(isChat)
, _title((isChat ? "Chat #" : "User #") + id)
{ }

void VkDialog::populateDialogList(int offset, int count) {
	sendApiRequest("messages.getDialogs", "offset=" + QString::number(offset) + "&count=" + QString::number(count), [](QJsonObject& json) {
		QJsonArray dialogsJsonArray = json.value("response").toObject().value("items").toArray();
		for (QJsonValue item : dialogsJsonArray) {
			QJsonObject messageJson = item.toObject().value("message").toObject();
			bool isChat = messageJson.contains("chat_id");
			QString id = messageJson.value(isChat ? "chat_id" : "user_id").toString();
			VkDialog* dialog = VkCache::get().getDialog(id, isChat);
			dialog->parse(messageJson);
		}
	});
}

void VkDialog::reload() {
	if (_isChat) {
		sendApiRequest("messages.getChat", "chat_id=" + _id, [this](QJsonObject& json) {
			parse(json.value("response").toObject());
		});
	} else {
		_title = _participants.at(0)->getName();
	}
}

void VkDialog::parse(const QJsonObject& json) {
	if (_isChat) {
		_title = json.value("title").toString();
		QJsonArray usersJsonArray = json.value(json.contains("chat_active") ? "chat_active" : "users").toArray();
		_participants.clear();
		for (QJsonValue item : usersJsonArray) {
			_participants.append(VkCache::get().getUser(item.toString()));
		}
		_isSoundEnabled = json.value("push_settings").toObject().value("sound").toBool();
		_disabledNotificationsUntil = json.value("push_settings").toObject().value("disabled_until").toString().toLong();
	} else {
		_participants.clear();
		_participants.append(VkCache::get().getUser(json.value("user_id").toString()));
		_title = _participants.at(0)->getName();
	}
}

void VkDialog::populateMessageList(int offset, int count) {
	sendApiRequest("messages.getHistory", (_isChat ? "chat_id=" : "user_id=") + _id + "&offset=" + QString::number(offset) + "&count=" + QString::number(count), [this](QJsonObject& json) {
		_unreadCount = json.value("response").toObject().value("unread").toInt();
		QJsonArray dialogsJsonArray = json.value("response").toObject().value("items").toArray();
		for (QJsonValue item : dialogsJsonArray) {
			QJsonObject itemJson = item.toObject();
			QString id = itemJson.value("id").toString();
			VkMessage* message = VkCache::get().getMessage(id);
			message->parse(itemJson);
		}
	});
}
