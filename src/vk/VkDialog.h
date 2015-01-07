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

#ifndef _VKM_VK_VK_DIALOG_H
#define _VKM_VK_VK_DIALOG_H

#include "VkObject.h"

#include <QString>
#include <QList>

#include "VkUser.h"
#include "VkMessage.h"

class VkDialog : public VkObject {
friend class VkCache;

public:
	static void populateDialogList(int offset = 0, int count = 200);

	virtual void parse(const QJsonObject& json) override;
	virtual void reload() override;
	void populateMessageList(int offset = 0, int count = 200);

	inline const QString& getId() const {
		return _id;
	}
	inline const QString& getTitle() const {
		return _title;
	}
	inline const bool isChat() const {
		return _isChat;
	}
	inline const uint getUnreadCount() const {
		return _unreadCount;
	}
	inline const bool isSoundEnabled() const {
		return _isSoundEnabled;
	}
	inline const ulong getDisabledNotificationUntilTime() const {
		return _disabledNotificationsUntil;
	}
	inline const QList<VkUser*>& getParticipants() const {
		return _participants;
	}
	inline const QList<VkMessage*>& getMessages() const {
		return _messages;
	}

private:
	VkDialog(const QString& id, bool isChat);

	QString _id;
	bool _isChat;
	QString _title;
	int _unreadCount = 0;
	bool _isSoundEnabled = true;
	long _disabledNotificationsUntil = 0;
	QList<VkUser*> _participants;
	QList<VkMessage*> _messages;
	bool _isReady;
};

#endif
