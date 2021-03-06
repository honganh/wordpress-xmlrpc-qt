/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#ifndef __MVARIANT_H
#define __MVARIANT_H
#include "inc/debug.h"
#include <QtCore>
class MVariant
{
	public:
    MVariant();
	MVariant( const QVariant&);
    /*! Next constructors should be used to build xmlrpc::Variant
        values from users data, to be passed to the xmlrpc::Client::request call*/
    MVariant ( uint val );
    MVariant ( int val );
    MVariant ( bool val );
    MVariant ( double val );
    MVariant ( const QByteArray & val );
    MVariant ( const QString & val );
    MVariant ( const QStringList & val );
    MVariant ( const QDateTime & val );
    //MVariant ( const QList<MVariant> & val );
    //MVariant ( const QMap<QString, MVariant> & val );

    //! this variable is casted to string XML-RPC type
    MVariant ( const QChar & c );
	virtual ~MVariant();
    void tostring(QVariant params);
    QList<QStringList> get_qlistqstringlist();
    private:
    QVariant variable;
    QList<QStringList> ret;
    QStringList items;
};

#endif
