/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#ifndef __DATABASE_H
#define __DATABASE_H
#include <QtSql>
#include <QFile>
#include "inc/debug.h"
class Database
{
public:
        Database();
        virtual ~Database();
        void Database_init();
        bool Database_query(QString sql);
        bool Database_open();
        void Database_close();
        bool Database_is_error();
        int Database_error_num();
        int Database_num_rows();
        int Database_num_cols();
        QString Database_error_message();
        QSqlQuery Database_get_result();
        QList<QVariant> Database_fetch_rows();
        QList<QVariant> Database_fetch_cols();
        QStringList Database_fetch_row(int index);
        QStringList Database_fetch_col(int index);
        QStringList Database_fetch_col_name(QString name);
        bool Database_is_select();
        bool Database_select(QString tablename);
        bool Database_select(QString tablename,QStringList what,QStringList where);
        bool Database_insert(QString tablename,QStringList what);
        bool Database_update(QString tablename,QStringList what,QStringList where);
        bool Database_delete(QString tablename);
        bool Database_delete(QString tablename,QStringList where);
        bool Database_drop(QString tablename);
private:
        QString Database_dbname ;
        QSqlDatabase Database_db;
        bool Database_error_status;
        int Database_error_number;
        QSqlQueryModel Database_result;
        QString Database_error_msg;
        bool isselected;
};
#endif

