/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#include "base.h"
Base::Base(){
this->Base_cl = new Client;
//this->Base_init();	
}
Base::Base(QString host,QString path ,int port ,QString username , QString password)
{
        this->Base_cl = new Client;
        this->Base_host = host;
        this->Base_path = path;
        this->Base_port = port;
        this->Base_username = username;
        this->Base_password = password;
        this->Base_blog_id = "";
        this->Base_blog_name = "";
        this->Base_init();
}
Base::~Base()
{
        delete this->Base_cl;
}
void Base::Base_init()
{
	
     this->Base_cl->setHost(this->Base_host,this->Base_port,this->Base_path);
     connect( this->Base_cl, SIGNAL(done( int, QVariant )), \
     this, SLOT(Base_process_result( int, QVariant )) );
     connect( this->Base_cl, SIGNAL(failed( int, int ,QString )), \
     this, SLOT(Base_process_failed( int, int ,QString )) );   
}
//not used to method wp.getPage
void Base::Base_sent_request(QString method)
{
        
        this->Base_params.clear();
        this->Base_result.clear();
        if(method.compare("wp.getUsersBlogs") == 0){
                this->Base_params<<this->Base_username<<this->Base_password;
        }else{
                this->Base_params<<this->Base_blog_id<<this->Base_username<<this->Base_password;
        }
       
        #if(XMLRPC_DEBUG)
        qDebug()<<"\nMethod:"<<method<<"\nParams :"<<this->Base_params<<"\nLine :"<<__LINE__<<"File :"<<__FILE__;
        #endif
        this->Base_cl->request(method,xmlrpc::Variant(this->Base_params));
}

void Base::Base_sent_request(QString method ,QStringList params)
{
        
        this->Base_params.clear();
        this->Base_result.clear();
        if(method.compare("wp.getUsersBlogs") == 0){
                this->Base_params<<this->Base_username<<this->Base_password;
        }else if(method.compare("wp.getPage") == 0){
                QString page_id = params.at(0);
                this->Base_params<<this->Base_blog_id<<page_id<<this->Base_username<<this->Base_password;
                params.removeAt(0);
        }else{
                this->Base_params<<this->Base_blog_id<<this->Base_username<<this->Base_password;
        }
        int count = params.size();
        if(count > 0){
                int i = 0;
                for( ;i < count ;i++)
                {
                       this->Base_params<<params.at(i).toLocal8Bit().constData();
                }
        }
        #if(XMLRPC_DEBUG)
        qDebug()<<"\nMethod:"<<method<<"\nParams :"<<this->Base_params<<"\nLine :"<<__LINE__<<"File :"<<__FILE__;
        #endif
        this->Base_cl->request(method,xmlrpc::Variant(this->Base_params));

}

void Base::Base_process_result( int id, QVariant res ){
        this->Base_result = res;
        #if(XMLRPC_DEBUG)        
        qDebug()<<"\nResult : "<<this->Base_result;
        qDebug()<<"\nResult Type : "<<this->Base_result.type() \
        <<"\nLine :"<<__LINE__<<"File :"<<__FILE__;
        #endif
        //Q_UNUSED(id);

        emit Base_OK(id,this->Base_result);

}
void Base::Base_process_failed( int id, int errcode, QString errstring)
{
          
        #if(XMLRPC_DEBUG)      
        qDebug()<<"\nID : "<<QString::number(id) \
        <<" ,Error code : "<<QString::number(errcode)<<" ,Error message : "<<errstring \
        <<" Line :"<<__LINE__<<"File :"<<__FILE__;
        #else
                Q_UNUSED(id);
        #endif
        emit Base_FAILED(id, errcode, errstring);
}

//set
void Base::Base_set_host(QString host){this->Base_host = host ;}
void Base::Base_set_path(QString path){this->Base_path = path ;}
void Base::Base_set_port(int port){this->Base_port = port ;}
void Base::Base_set_username(QString username){this->Base_username = username ;}
void Base::Base_set_password(QString password){this->Base_password = password ;}
void Base::Base_set_blog_id(QString blogid){this->Base_blog_id = blogid ;}
void Base::Base_set_blog_name(QString blogname){this->Base_blog_name = blogname ;}
