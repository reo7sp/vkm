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

#ifndef _VKM_VK_VK_USER_H
#define _VKM_VK_VK_USER_H

#include <QString>
#include <QJsonObject>

#include "VkObject.h"

class VkUser : public VkObject {
friend class VkCache;

public:
	virtual void parse(const QJsonObject& json) override;
	virtual void reload() override;

	inline const QString& getId() const {
		return _id;
	}
	inline const QString& getName() const {
		return _name;
	}

private:
	explicit VkUser(const QString& id);

	QString _id;
	QString _name;
};

#endif
