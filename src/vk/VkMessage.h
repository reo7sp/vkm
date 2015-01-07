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

#ifndef _VKM_VK_VK_MESSAGE_H
#define _VKM_VK_VK_MESSAGE_H

#include <QString>
#include <QList>

#include "VkObject.h"
#include "VkUser.h"

class VkMessage : public VkObject {
friend class VkCache;

public:
	virtual void parse(const QJsonObject& json) override;
	virtual void reload() override;

	inline const QString& getId() const {
		return _id;
	}
	inline const QString& getBody() const {
		return _body;
	}
	inline VkUser* getUserFrom() const {
		return _from;
	}
	inline long getDate() const {
		return _date;
	}
	inline bool isRead() const {
		return _isRead;
	}
	inline const QList<VkMessage*>& getForwarded() const {
		return _forwardedMessages;
	}

private:
	VkMessage(const QString& id);

	QString _id;
	QString _body;
	VkUser* _from = nullptr;
	long _date = 0;
	bool _isRead = true;
	QList<VkMessage*> _forwardedMessages;
};

#endif
