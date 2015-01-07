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

#ifndef _VKM_VK_VK_CACHE_H
#define _VKM_VK_VK_CACHE_H

#include <QString>
#include <QList>

#include "VkUser.h"
#include "VkMessage.h"
#include "VkDialog.h"

class VkCache {
public:
	static VkCache& get();

	VkUser* getUser(const QString& id);
	VkMessage* getMessage(const QString& id);
	VkDialog* getDialog(const QString& id, bool isChat);

	inline const QList<VkUser*>& getAllUsers() const {
		return _users;
	}
	inline const QList<VkMessage*>& getAllMessages() const {
		return _messages;
	}
	inline const QList<VkDialog*>& getAllDialogs() const {
		return _dialogs;
	}

private:
	VkCache() { };
	VkCache(VkCache&) { };
	~VkCache();

	void operator=(VkCache&) { }

	QList<VkUser*> _users;
	QList<VkMessage*> _messages;
	QList<VkDialog*> _dialogs;
};

#endif
