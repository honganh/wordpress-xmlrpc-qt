/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#ifndef __USER_H
#define __USER_H
#include "userblog.h"

class User:public QObject
{
	Q_OBJECT
private:
    QString userid;
    QString username;
    QString firstname;
    QString lastname;
    QString bio;
    QString email;
    QString nickname;
    QString nicename;
    QString url;
    QString displayname;
    QString registered;
    QString roles; 
        
    Wordpress *User_wp;
	Database  *User_db;
	int size;
	QString tablename;
public:
	User();
	virtual ~User();
	//get
	QString User_get_user_id();
	QString User_get_user_name();
	QString User_get_first_name();
	QString User_get_last_name();
	QString User_get_bio();
	QString User_get_email();
	QString User_get_nick_name();
	QString User_get_nice_name();
	QString User_get_url();
	QString User_get_display_name();
	QString User_get_registered();
	QString User_get_roles();
	//set
	void User_set_user_id(QString user_id);
	void User_set_user_name(QString user_name);
	void User_set_first_name(QString first_name);
	void User_set_last_name(QString last_name);
	void User_set_bio(QString bio);
	void User_set_email(QString email);
	void User_set_nick_name(QString nick_name);
	void User_set_nice_name(QString nice_name);
	void User_set_url(QString url);
	void User_set_display_name(QString display_name);
	void User_set_registered(QString registered);
	void User_set_roles(QString roles);
	void User_get_users();
public slots:
	void User_get_users_ok(QVariant);
	void User_get_users_failed(int,QString);
};
#endif
