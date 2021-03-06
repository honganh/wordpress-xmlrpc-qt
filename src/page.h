/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#ifndef __PAGE_H
#define __PAGE_H
#include "wordpress.h"
#include "category.h"
#include "postcustomfield.h"
#include "inc/debug.h"
class Page:public Wordpress
{
Q_OBJECT
private:
    int page_id;
    QString title;
    QDateTime date_created;
    QDateTime date_created_gmt;
    QString status;
    QString slug;
    int user_id;
    QString author_id;
    QString author;
    QString author_display_name;
    QString password;
    QString excerpt;
    QString description;
    QString text_more;
    QString permalink;
    int mt_allow_comments;
    int mt_allow_pings;
    int parent_id;
    QString parent_title;
    int order;
    QString page_template;
    Category *category;// Names of categories assigned to the page.
    Postcustomfield *custom_fields;
    
public:
Page(QString host,QString path ,int port ,QString username , QString password);
virtual ~Page();
//set
void Page_set_id(int id);
void Page_set_title(QString title);
void Page_set_date_created(QDateTime datecreated);
void Page_set_date_created_gmt(QDateTime datecreatedgmt);
void Page_set_status(QString status);
void Page_set_slug(QString slug);
void Page_set_user_id(int userid);
void Page_set_author_id(QString author_id);
void Page_set_author(QString author);
void Page_set_author_display_name(QString authordisplayname);
void Page_set_password(QString password);
void Page_set_excerpt(QString excerpt);
void Page_set_description(QString description);
void Page_set_text_more(QString textmore);
void Page_set_permalink(QString permalink);
void Page_set_mt_allow_comments(int mt_allow_comments);
void Page_set_mt_allow_pings(int mt_allow_pings);
void Page_set_parent_id(int page_parent_id);
void Page_set_parent_title(QString page_parent_title);
void Page_set_order(int page_order);
void Page_set_template(QString page_template);
void Page_set_category(Category *category);
void Page_set_custom_fields(Postcustomfield *custom_fields);
//get
int Page_get_id();
QString Page_get_title();
QDateTime Page_get_date_created();
QDateTime Page_get_date_created_gmt();
QString Page_get_status();
QString Page_get_slug();
int Page_get_user_id();
QString Page_get_author_id();
QString Page_get_author();
QString Page_get_author_display_name();
QString Page_get_password();
QString Page_get_excerpt();
QString Page_get_description();
QString Page_get_text_more();
QString Page_get_permalink();
int Page_get_mt_allow_comments();
int Page_get_mt_allow_pings();
int Page_get_parent_id();
QString Page_get_parent_title();
int Page_get_order();
QString Page_get_template();
Category* Page_get_category();
Postcustomfield* Page_get_custom_fields();
QStringList Page_map_to_qstringlist();
public slots:
void Page_map_from_result();
void Page_map_from_error();

};
#endif
