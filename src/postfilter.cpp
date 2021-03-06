/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#include "postfilter.h"
Postfilter::Postfilter(){}
Postfilter::~Postfilter(){}
void Postfilter::Postfilter_set_post_type(QString post_type){this->Postfilter_post_type = post_type ;} 
void Postfilter::Postfilter_set_post_status(QString post_status){this->Postfilter_post_status = post_status ;}
void Postfilter::Postfilter_set_post_number(int number){this->Postfilter_number = number ;}
void Postfilter::Postfilter_set_post_offset(int offset){this->Postfilter_offset = offset ;}
void Postfilter::Postfilter_set_post_ordeby(QString orderby){this->Postfilter_orderby = orderby ;}
void Postfilter::Postfilter_set_post_order(QString order){this->Postfilter_order = order ;}
void Postfilter::Postfilter_set_all(QString type,QString status,int number,int offset,QString orderby,QString order){
this->Postfilter_post_type = type ;
this->Postfilter_post_status = status;
this->Postfilter_number = number ;
this->Postfilter_offset = offset ;
this->Postfilter_orderby = orderby ;
this->Postfilter_order = order ;
}
QString Postfilter::Postfilter_get_post_type(){return this->Postfilter_post_type ;}
QString Postfilter::Postfilter_get_post_status(){return this->Postfilter_post_status ;}
int Postfilter::Postfilter_get_post_number(){return this->Postfilter_number ;}
int Postfilter::Postfilter_get_post_offset(){return this->Postfilter_offset ;}
QString Postfilter::Postfilter_get_post_orderby(){return this->Postfilter_orderby ;}
QString Postfilter::Postfilter_get_post_order(){return this->Postfilter_order ;}
QStringList Postfilter::Postfilter_map_to_qstringlist(){
QStringList list;
list<<this->Postfilter_post_type<<this->Postfilter_post_status \
<<QString::number(this->Postfilter_number)<<QString::number(this->Postfilter_offset) \
<<this->Postfilter_orderby<<this->Postfilter_order ;
return list;
}
