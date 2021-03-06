/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#include "postcustomfield.h"
Postcustomfield::Postcustomfield(){}
Postcustomfield::~Postcustomfield(){}
QStringList Postcustomfield::Postcustomfield_map_to_qstringlist()
{
QStringList list;
list<<this->id<<this->key<<this->value;
return list;
}
void Postcustomfield::Postcustomfield_set_id(QString id){this->id = id ;}
void Postcustomfield::Postcustomfield_set_key(QString key){this->key = key ;}
void Postcustomfield::Postcustomfield_set_value(QString value){this->value = value ;}
void Postcustomfield::Postcustomfield_set_all(QString id ,QString key ,QString value){
this->id = id;this->key = key ;this->value = value ;
}
QString Postcustomfield::Postcustomfield_get_id(){return this->id ;}
QString Postcustomfield::Postcustomfield_get_key(){return this->key ;}
QString Postcustomfield::Postcustomfield_get_value(){return this->value ;}
