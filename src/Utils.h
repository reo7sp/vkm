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

#ifndef _VKM_UTILS_H
#define _VKM_UTILS_H

#include <QString>
#include <QDir>
#include <QStandardPaths>

namespace Utils {
	QString xorCrypt(const QString& data, const QString& key = "vmWsysghOiDBmMAirzm5WFZQlxMkWOulkPeDePorqXS51pfuEO");

	inline QString getParentDataDirectory() {
		return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QDir::separator();
	}
	inline QString getDataDirectory() {
		return getParentDataDirectory() + "vkm" + QDir::separator();
	}
}

#endif
