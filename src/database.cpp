/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#include "database.h"
#include <QMessageBox>
Database::Database()
{
        this->Database_error_status = false;
        this->Database_error_number = 0;
        this->Database_error_msg = "";
        this->Database_result.clear();
        this->Database_dbname = "my.db";
        this->isselected = false;
        #if(XMLRPC_DEBUG)
        //separator linux
        qDebug()<<QDir("./").absoluteFilePath(this->Database_dbname) \
        <<" Line :"<<__LINE__<<"File :"<<__FILE__;
        #endif
        if(!QFile::exists(QDir("./").absoluteFilePath(this->Database_dbname))){               
                this->Database_init();
        }
}
Database::~Database()
{
        //this->myclose();
}
bool Database::Database_open()
{
				
                this->Database_db = QSqlDatabase::addDatabase("QSQLITE","default");
                if(!this->Database_db.isValid()){
                        this->Database_error_status = true;
                        this->Database_error_number = this->Database_db.lastError().number();
                        this->Database_error_msg = this->Database_db.lastError().text();
	                return false;
	       }
               this->Database_db.setDatabaseName(this->Database_dbname);
               if(!this->Database_db.open()){
                        this->Database_error_status = true ;
                        QSqlError err = this->Database_db.lastError();
                        this->Database_error_number = err.number();
                        this->Database_error_msg = err.text();
                        return false;
               }else{
                        this->Database_error_status = false;
                        return true;
               }
        
}
void Database::Database_init()
{
        if(this->Database_open()){
                if(!QFile::exists(QDir("src").absoluteFilePath("my.sql"))){
                      this->Database_error_status = true ;
                        this->Database_error_number = -1;
                        this->Database_error_msg = "Can not init database";
                        this->Database_close();
                        return ;  
                }
                QFile file(QDir("src").absoluteFilePath("my.sql"));
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                        this->Database_error_status = true ;
                        this->Database_error_number = -1;
                        this->Database_error_msg = "Can not init database";
                        this->Database_close();
			return;
                 }
		QString sql = file.readAll();
		QString line;
		int i = 0;
		int index = 0,len = 0;
		while((index) != -1)
		{
			index = sql.indexOf(";",i);
			len = index - i;
			line = sql.mid(i,len);					
			i = index+1;
                        this->Database_db.exec(line);
		}
                this->Database_close();
        }else{
                 this->Database_error_status = true;
                 this->Database_error_number = -1;
                 this->Database_error_msg = "Database not exists .";
        }
}
bool Database::Database_query(QString sql)
{
        if(this->Database_open()){
            this->Database_db.transaction();
            this->Database_result.setQuery(sql,this->Database_db);
                QSqlError err = this->Database_result.lastError();
                if(this->Database_result.query().isSelect()){
                        this->isselected = true;
                }else{
                        this->isselected = false;
                }
                #if(XMLRPC_DEBUG)
                qDebug()<<"\n> Query exec() : "<<sql << err\
                <<" Line :"<<__LINE__<<"File :"<<__FILE__;
                #endif
                if(err.isValid()){
                        
                        this->Database_error_status = true;
                        this->Database_error_number = err.number();
                        this->Database_error_msg = err.text();
                        //if happen err ->rollback database
                        this->Database_db.rollback();
                        this->Database_close();
                        #if(XMLRPC_DEBUG)
                        qDebug()<<"\n> Query failed :"<<err;
                        #endif
                        return false;
                }else{
                        this->Database_error_status = false;
                        this->Database_error_number = err.number();
                        this->Database_error_msg = err.text();
                        
                        //No err ->commit database
                        this->Database_db.commit();
                        this->Database_close();
                        #if(XMLRPC_DEBUG)
                        qDebug()<<"\n> Query success !";
                        #endif
                        return true;                   
                }
                
        }else{
		return false;
        }
}
void Database::Database_close()
{
       this->Database_db.close();
       this->Database_db = QSqlDatabase();
       QSqlDatabase::database().removeDatabase("default");      
}
bool Database::Database_is_error()
{
        return this->Database_error_status;
}
int Database::Database_error_num()
{
        return this->Database_error_number;
}
QString Database::Database_error_message()
{
        return this->Database_error_msg;
}
QSqlQuery Database::Database_get_result()
{
        return this->Database_result.query();
}
int Database::Database_num_rows()
{
        if(this->isselected){    
         return this->Database_result.rowCount();
        }else{
                return 0;
        }
    
}
int Database::Database_num_cols()
{
        if(this->isselected){
                return this->Database_result.columnCount();
        }else{
                return 0;        
        }
}
QList<QVariant> Database::Database_fetch_rows()
{
    QList<QVariant> ret;
    if(!this->isselected){
                return ret;
    }
    for (int row = 0; row < this->Database_result.rowCount(); ++row) {
            QVariant v;
            v.setValue(this->Database_fetch_row(row));
            ret.append(v);
        }
    return ret;
}
QStringList Database::Database_fetch_row(int index)
{
    QStringList ret;
    if(!this->isselected){
                return ret;
    }
    for (int col = 0; col < this->Database_result.columnCount(); ++col) {
            ret<<this->Database_result.data(this->Database_result.index(index, col)).toString();
     }
     #if(XMLRPC_DEBUG)
     qDebug()<<"\n"<<ret<<" LINE: "<<__LINE__<<" FILE : "<<__FILE__;
     #endif
    return ret;
}
QStringList Database::Database_fetch_col(int index)
{
    QStringList ret;
    if(!this->isselected){
                return ret;
    }
    for (int row = 0; row < this->Database_result.rowCount(); ++row) {
           ret<<this->Database_result.data(this->Database_result.index(row,index)).toString();
     }
    return ret;
}

QList<QVariant> Database::Database_fetch_cols()
{
    QList<QVariant> ret;
    if(!this->isselected){
                return ret;
    }
    for (int col = 0; col < this->Database_result.columnCount(); ++col) {
            QVariant v;
            v.setValue(this->Database_fetch_col(col));
            ret.append(v);
        }
    return ret;
}
QStringList Database::Database_fetch_col_name(QString name)
{
    QStringList ret; 
    if(!this->isselected){
           return ret;
    }
    for (int i = 0; i < this->Database_result.rowCount(); ++i) {
         QString get = this->Database_result.record(i).value(name).toString();
         ret<<get;
     }
    return ret;
}
bool Database::Database_is_select()
{
        return this->isselected;
}
bool Database::Database_select(QString tablename){
        QString sql("SELECT ");
        sql += " * ";
        sql += " FROM ";sql += tablename ;sql +=" WHERE 1";
        if(this->Database_query(sql)){
                return true;
        }else{
                return false;
        }
}
bool Database::Database_select(QString tablename,QStringList what,QStringList where)
{
        QString sql("SELECT ");
        int size = what.size();
        if(size == 0){
                sql += " * ";
        }else{
                foreach(QString option ,what){
                        sql += option;sql += ",";
                }
                sql.remove(sql.length()-QString(",").length(),QString(",").length());
        }
        sql += " FROM ";sql += tablename ;sql +=" WHERE ";
        if(where.size() == 0){
                sql += " 1 ";
        }else{
                foreach(QString options ,where){
                        sql += options;sql += " AND ";
                }
                sql.remove(sql.length()-QString(" AND ").length(),QString(" AND ").length());
        }
        if(this->Database_query(sql)){
                return true;
        }else{
                return false;
        }
}
bool Database::Database_insert(QString tablename,QStringList what)
{
        QString sql("INSERT INTO ");
        sql += tablename;sql += " VALUES('";
        int size = what.size();
        if(size > 0){
                foreach(QString option ,what){
                        sql += option;
                        sql += "','";
                }
                sql.remove(sql.length()-QString(",'").length(),QString(",'").length());
        }
        sql += ")";
       if(this->Database_query(sql)){
                return true;
        }else{
                return false;
        }
}
bool Database::Database_update(QString tablename,QStringList what,QStringList where)
{
        QString sql("UPDATE ");
        sql += tablename; sql += " SET ";
        int size = what.size();
        if(size == 0){
                sql += "* ";
        }else{
                foreach(QString option ,what){
                        sql += option;sql += ",";
                }
                sql.remove(sql.length()-QString(",").length(),QString(",").length());
        }
        if(where.size() > 0){
             sql += " WHERE ";
            foreach(QString options ,where){
                        sql += options ;sql += " AND ";
             }
               sql.remove(sql.length()-QString(" AND ").length(),QString(" AND ").length());    
        }
        if(this->Database_query(sql)){
                return true;
        }else{
                return false;
        }
}
bool Database::Database_delete(QString tablename){
QString sql("DELETE FROM ");
        sql += tablename;
         sql += " WHERE 1";                 
        if(this->Database_query(sql)){
                return true;
        }else{
                return false;
        }
}
bool Database::Database_delete(QString tablename,QStringList where)
{
        QString sql("DELETE FROM ");
        sql += tablename;
        int size = where.size();
        if(size > 0){
            sql += " WHERE ";
            foreach(QString options ,where){
                        sql += options; sql += " AND ";
             }
             sql.remove(sql.length()-QString(" AND ").length(),QString(" AND ").length());
        }else{
                sql += " WHERE 1";
        }        
        if(this->Database_query(sql)){
                return true;
        }else{
                return false;
        }
}
bool Database::Database_drop(QString tablename)
{
        QString sql("DROP TABLE ");
        sql += tablename;
        if(this->Database_query(sql)){
                return true;
        }else{
                return false;
        }
}

