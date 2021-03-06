/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#include "comment.h"
Comment::Comment(){
        Userblog user;
	QString host = user.Userblog_get_blog_host();
	QString path = user.Userblog_get_blog_path();
	int port = user.Userblog_get_blog_port();
	QString blogid = user.Userblog_get_blog_id();
	QString username = user.Userblog_get_blog_username();
	QString pass = user.Userblog_get_blog_password();
	this->tablename = "comments";
	this->Comment_db = new Database();
	this->Comment_wp = new Wordpress(host,path,port,username,pass);
	this->Comment_wp->Base_set_blog_id(blogid);
	//class have 14 variable
	this->size = 14;
	connect(this->Comment_wp,SIGNAL(Wordpress_OK(QVariant)),this,SLOT(Comment_get_ok(QVariant)));
	connect(this->Comment_wp,SIGNAL(Wordpress_FAILED(int ,QString)),this,\
        SLOT(Comment_get_failed(int ,QString)));		
}
Comment::~Comment(){
		delete this->Comment_wp;
		delete this->Comment_db;
}
//set
void Comment::Comment_set_comment_id(QString comment_id){this->comment_id = comment_id ;}
void Comment::Comment_set_parent(QString parent){this->parent = parent ;}
void Comment::Comment_set_user_id(QString user_id){this->user_id = user_id ; }
void Comment::Comment_set_date_created(QString datecreated){this->datecreated = datecreated ;}
void Comment::Comment_set_status(QString status){this->status = status ;}
void Comment::Comment_set_content(QString content){this->content = content ;}
void Comment::Comment_set_link(QString link){this->link = link;}
void Comment::Comment_set_post_id(QString post_id){this->post_id = post_id ;}
void Comment::Comment_set_post_title(QString post_title){this->post_title = post_title ;}
void Comment::Comment_set_author(QString author){this->author = author ;}
void Comment::Comment_set_author_url(QString author_url){this->author_url = author_url ;}
void Comment::Comment_set_author_email(QString author_email){this->author_email = author_email ;}
void Comment::Comment_set_author_ip(QString author_ip){this->author_ip = author_ip ;}
void Comment::Comment_set_type(QString type){this->type = type ;}
//get
QString Comment::Comment_get_comment_id(){return this->comment_id ;}
QString Comment::Comment_get_parent(){return this->parent ;}
QString Comment::Comment_get_user_id(){return this->user_id ;}
QString Comment::Comment_get_date_created(){return this->datecreated ;}
QString Comment::Comment_get_status(){return this->status ;}
QString Comment::Comment_get_content(){return this->content ;}
QString Comment::Comment_get_link(){return this->link ;}
QString Comment::Comment_get_post_id(){return this->post_id ;}
QString Comment::Comment_get_post_title(){return this->post_title ;}
QString Comment::Comment_get_author(){return this->author ;}
QString Comment::Comment_get_author_url(){return this->author_url ;}
QString Comment::Comment_get_author_email(){return this->author_email ;}
QString Comment::Comment_get_author_ip(){return this->author_ip ;}
QString Comment::Comment_get_type(){return this->type ;}

//slots
void Comment::Comment_get_ok(QVariant result){
	
	QList<QStringList> list;
	list = MVariant(result).get_qlistqstringlist();
	QStringList what;
	this->Comment_db->Database_select(this->tablename);
	int id = this->Comment_db->Database_num_rows();
	int i = 0;
	while(i < list.size()){
		QList<QStringList> sublist = list.mid(i,this->size);
		foreach(QStringList item,sublist){
			if(item.at(0).compare("author") == 0){
				this->author = item.at(1);
			}
			if(item.at(0).compare("author_email") == 0){
				this->author_email = item.at(1);
			}
			if(item.at(0).compare("author_ip") == 0){
				this->author_ip = item.at(1);
			}
			if(item.at(0).compare("author_url") == 0){
				this->author_url = item.at(1);
			}
			if(item.at(0).compare("comment_id") == 0){
				this->comment_id = item.at(1);
			}
			if(item.at(0).compare("content") == 0){
				this->content = item.at(1);
			}
			if(item.at(0).compare("date_created_gmt") == 0){
				this->datecreated = item.at(1);
			}
			if(item.at(0).compare("link") == 0){
				this->link = item.at(1);
			}
			if(item.at(0).compare("parent") == 0){
				this->parent = item.at(1);
			}
			if(item.at(0).compare("post_id") == 0){
				this->post_id = item.at(1);
			}
			if(item.at(0).compare("post_title") == 0){
				this->post_title = item.at(1);
			}
			if(item.at(0).compare("status") == 0){
				this->status = item.at(1);
			}
			if(item.at(0).compare("type") == 0){
				this->type = item.at(1);
			}
			if(item.at(0).compare("user_id") == 0){
				this->user_id = item.at(1);
			}
		
		}
			
		what<<QString::number(++id)<<this->comment_id<<this->parent<<this->user_id\
		<<this->datecreated<<this->status<<this->content<<this->link<<this->post_id\
		<<this->post_title<<this->author<<this->author_url<<this->author_email\
		<<this->author_ip<<this->type;
		this->Comment_db->Database_insert(this->tablename,what);
		what.clear();
		i = i + this->size;
	}
}
void Comment::Comment_get_failed(int code ,QString msg){
        QMessageBox::critical(NULL,"Error",QString::number(code) + " => " + msg);

}
void Comment::Comment_get_comment(){
	this->Comment_wp->Wordpress_getcomment(10);
}
void Comment::Comment_get_all_comment(){
	QStringList list;
	this->Comment_wp->Wordpress_getcomments(list);
}
