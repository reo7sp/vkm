#ifndef _VKM_FS_USER_CONFIG_H
#define _VKM_FS_USER_CONFIG_H

#include <QString>

class UserConfig {
public:
	static UserConfig& get();

	inline void setAll(const QString& accessToken, const QString& userId) {
		_accessToken = accessToken;
		_userId = userId;
		rewrite();
	}
	inline const QString& getAccessToken() const {
		return _accessToken;
	}
	inline void setAccessToken(const QString& accessToken) {
		_accessToken = accessToken;
		rewrite();
	}
	inline const QString& getUserId() const {
		return _userId;
	}
	inline void setUserId(const QString& userId) {
		_userId = userId;
		rewrite();
	}

private:
	UserConfig();
	UserConfig(UserConfig&) { }
	~UserConfig() { }

	void reload();
	void rewrite();

	void operator=(UserConfig&) { }

	QString _accessToken;
	QString _userId;
};

#endif
