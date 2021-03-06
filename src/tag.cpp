/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#include "tag.h"
#include "mvariant.h"
Tag::Tag(){
this->tablename = "tags";
this->size = 6;
this->Tag_db = new Database();

Userblog user;
QString host = user.Userblog_get_blog_host();
QString path = user.Userblog_get_blog_path();
int port = user.Userblog_get_blog_port();
QString blogid = user.Userblog_get_blog_id();
QString username = user.Userblog_get_blog_username();
QString password = user.Userblog_get_blog_password();
this->Tag_wp = new Wordpress(host,path ,port ,username ,password);
this->Tag_wp->Base_set_blog_id(blogid);
connect(this->Tag_wp,SIGNAL(Wordpress_OK(QVariant)),this,SLOT(Tag_get_ok(QVariant)));
connect(this->Tag_wp,SIGNAL(Wordpress_FAILED(int ,QString)),this,SLOT(Tag_get_failed(int ,QString)));
}
Tag::~Tag(){
delete this->Tag_db;
delete this->Tag_wp;	
}
void Tag::Tag_set_id(int id){this->tag_id = id;}
void Tag::Tag_set_name(QString name){this->name = name;}
void Tag::Tag_set_slug(QString slug){this->slug = slug;}
void Tag::Tag_set_count(int count){this->count = count;}
void Tag::Tag_set_html_url(QString htmlurl){this->html_url = htmlurl;}
void Tag::Tag_set_rss_url(QString rssurl){this->rss_url = rssurl;}
void Tag::Tag_set_all(int id ,QString name ,QString slug ,int count ,QString htmlurl ,QString rssurl){
this->tag_id = id;
this->name = name;
this->slug = slug;
this->count = count;
this->html_url = htmlurl;
this->rss_url = rssurl;
}
int Tag::Tag_get_id(){return this->tag_id;}
QString Tag::Tag_get_name(){return this->name;}
QString Tag::Tag_get_slug(){return this->slug;}
int Tag::Tag_get_count(){return this->count;}
QString Tag::Tag_get_html_url(){return this->html_url;}
QString Tag::Tag_get_rss_url(){return this->rss_url;}
QStringList Tag::Tag_map_to_qstringlist(){
QStringList list;
list<<QString::number(this->tag_id)<<this->name<<this->slug \
<<QString::number(this->count)<<this->html_url<<this->rss_url;
return list;
}
void Tag::Tag_get_tag()
{
	this->Tag_wp->Wordpress_gettags();
}
void Tag::Tag_get_ok(QVariant result)
{	
	MVariant res(result);
	QList<QStringList> list = res.get_qlistqstringlist();
	//qDebug()<<list;
	QStringList what;
	this->Tag_db->Database_select(this->tablename);
	int id = this->Tag_db->Database_num_rows();
	int i = 0;
	while(i < list.size()){
		QList<QStringList> sub = list.mid(i,this->size);
		foreach(QStringList item ,sub){
			if(item.at(0).compare("tag_id") == 0){
				this->tag_id = item.at(1).toInt();
			}
			if(item.at(0).compare("name") == 0){
				this->name = item.at(1);
			}
			if(item.at(0).compare("slug") == 0){
				this->slug = item.at(1);
			}
			if(item.at(0).compare("count") == 0){
				this->count = item.at(1).toInt();
			}
			if(item.at(0).compare("html_url") == 0){
				this->html_url = item.at(1);
			}
			if(item.at(0).compare("rss_url") == 0){
				this->rss_url = item.at(1);
			}
		}
	//count database
		id++;
		what<<QString::number(id)<<QString::number(this->tag_id)<<this->name \
		<<this->slug<<QString::number(this->count)<<this->html_url \
		<<this->rss_url;	
		if(!this->Tag_db->Database_insert(this->tablename,what)){
				id--;
		}
		what.clear();
		i = i + this->size;
	}
}
void Tag::Tag_get_failed(int code ,QString msg)
{
	
	QMessageBox::critical(NULL,"Error",QString::number(code) + " => " + msg);
}
void Tag::Tag_get_tag_from_db(int tag_id)
{
	QStringList what;
	QStringList where;
	where<<"tag_id = "+QString::number(tag_id);
	 if(this->Tag_db->Database_select(this->tablename,what,where)){
		if(this->Tag_db->Database_num_rows() == 0){
			QMessageBox::information(NULL,"Infomation","No record tag in database");
		}else{
			QStringList list = this->Tag_db->Database_fetch_row(0);
			//0 is id
			this->tag_id = list.at(1).toInt();
			this->name = list.at(2);
			this->slug = list.at(3);
			this->count = list.at(4).toInt();
			this->html_url = list.at(5);			
			this->rss_url = list.at(6);
				
		}
	 }else{
		 QMessageBox::critical(NULL,"Error","Database failed ,please try again !");
	 }
}


