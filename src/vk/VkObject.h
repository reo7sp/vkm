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

#ifndef _VKM_VK_VK_OBJECT_H
#define _VKM_VK_VK_OBJECT_H

#include <functional>

#include <QString>
#include <QJsonObject>

#include "../fs/UserConfig.h"

class VkObject {
friend class VkCache;

public:
	virtual void parse(const QJsonObject& json) = 0;
	virtual void reload() = 0;

protected:
	VkObject() { }
	virtual ~VkObject() { }

	static void sendApiRequest(const QString& method, const QString& args, std::function<void(QJsonObject&)> action);

	static inline const QString& getAccessToken() {
		return UserConfig::get().getAccessToken();
	}
	static inline const QString getApiVersion() {
		return "5.27";
	}

private:
	VkObject(VkObject&) { }

	void operator=(VkObject&) { }
};

#endif
