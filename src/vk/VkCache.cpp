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

#include "VkCache.h"

VkCache& VkCache::get() {
	static VkCache instance;
	return instance;
}

VkCache::~VkCache() {
	while (!_users.isEmpty()) {
		delete _users.takeFirst();
	}
	while (!_messages.isEmpty()) {
		delete _messages.takeFirst();
	}
	while (!_dialogs.isEmpty()) {
		delete _dialogs.takeFirst();
	}
}

VkUser* VkCache::getUser(const QString& id) {
	if (!id.isEmpty()) {
		for (int i = 0, len = _users.length(); i < len; ++i) {
			VkUser* item = _users.at(i);
			if (item->getId() == id) {
				return item;
			}
		}
	}
	auto newbie = new VkUser(id);
	_users.append(newbie);
	return newbie;
}

VkMessage* VkCache::getMessage(const QString& id) {
	if (!id.isEmpty()) {
		for (int i = 0, len = _messages.length(); i < len; ++i) {
			VkMessage* item = _messages.at(i);
			if (item->getId() == id) {
				return item;
			}
		}
	}
	auto newbie = new VkMessage(id);
	_messages.append(newbie);
	return newbie;
}

VkDialog* VkCache::getDialog(const QString& id, bool isChat) {
	if (!id.isEmpty()) {
		for (int i = 0, len = _dialogs.length(); i < len; ++i) {
			VkDialog* item = _dialogs.at(i);
			if (item->getId() == id && item->isChat() == isChat) {
				return item;
			}
		}
	}
	auto newbie = new VkDialog(id, isChat);
	_dialogs.append(newbie);
	return newbie;
}
