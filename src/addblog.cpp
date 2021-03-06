/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#include <QDialog>
#include "addblog.h"
#include <QMessageBox>
Addblog::Addblog(QWidget *parent):QDialog(parent)
{
        this->ui.setupUi(this);
        connect(this->ui.btn_add,SIGNAL(clicked()),this,SLOT(add()));
        connect(this->ui.btn_cancel,SIGNAL(clicked()),this,SLOT(cancel()));
        this->db = new Database;
}
void Addblog::add()
{
        QString host(this->ui.txt_host->text());
        QString path(this->ui.txt_path->text());
        QString user(this->ui.txt_username->text());
        QString pass(this->ui.txt_password->text());
        Base  *b = new Base(host,path,80,user,pass);
        QStringList params;
        b->Base_sent_request("wp.getUsersBlogs",params);
        QString blogid;
        QString blogname;
        #if(XMLRPC_DEBUG)
        qDebug()<<"Blog ID : "<<blogid<<" Blog Name : "<<blogname<<" Line :"<<__LINE__<<"File :"<<__FILE__;
        #endif
        delete b;
        
        int count = 0;
        QString q("SELECT * FROM `blog`");
        this->db->Database_query(q);
        count = this->db->Database_num_rows();
        if(count < 0){count = 0;}
        qDebug()<<"\nNumRow :"<<count;     
        QString sql("INSERT INTO `blog`(id,blogid,blogtype,blogname,blogurl,username,password) VALUES('");
        sql+=QString::number(count+1) ;
        sql += "','";
        sql += blogid;
        sql += "','"; 
        sql += QString::number(1);
        sql += "','";
        sql += blogname;
        sql +="','";
        sql += "http://";
        sql += host+path + "','" +user + "','" + pass + "')";
        this->db->Database_query(sql);
        if(this->db->Database_is_error()){
                QMessageBox::critical(this,"Error : ",QString::number(this->db->Database_error_num()) + this->db->Database_error_message());
        }else{
                QMessageBox::about(this,"About : ","Add blog " + host + path + "Success.");
        }

        
        
}
void Addblog::cancel()
{
        this->ui.txt_host->clear();
        this->ui.txt_path->clear();
        this->ui.txt_username->clear();
        this->ui.txt_password->clear();
}
