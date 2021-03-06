/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#ifndef __USERBLOG_H
#define __USERBLOG_H
#include "wordpress.h"
#include "database.h"
#include "mvariant.h"
#include "inc/debug.h"
class Userblog:public QObject
{
	Q_OBJECT
private:
    QString Userblog_blogid;
    QString Userblog_blogname;
    QString Userblog_url;
    QString Userblog_xmlrpc;
    bool Userblog_isadmin;
    QString Userblog_username;
    QString Userblog_password;
    int Userblog_port;
    
    Wordpress *Userblog_wp;
	Database  *Userblog_db;
	QString Userblog_tablename;
public:
	Userblog();
	virtual ~Userblog();
	QString Userblog_get_blog_id();
	QString Userblog_get_blog_name();
	QString Userblog_get_blog_host();
	QString Userblog_get_blog_path();
	bool Userblog_get_blog_is_admin();
	QString Userblog_get_blog_username();
	QString Userblog_get_blog_password();
	int Userblog_get_blog_port();
	QString Userblog_base64_encode(QString string);
	QString Userblog_base64_decode(QString string);
	void Userblog_add_new();
	void Userblog_select_follow_id(int id);
public slots:
void Userblog_get_users_blogs_ok(QVariant);
void Userblog_get_users_blogs_failed(int ,QString);
};
#endif
