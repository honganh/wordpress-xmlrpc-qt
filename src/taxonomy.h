/*
 *	@Package : WODPRESS XMLRPC 
 *  @Author : Pham Van Diep
 * 	@Contact : pndhainam@hotmail.com
 */

#ifndef __TAXONOMY_H
#define __TAXONOMY_H
#include "userblog.h"
#include "cap.h"
#include "labels.h"
class Taxonomy:public QObject
{
	Q_OBJECT
	private:
	QString name;
    QString label;
    bool hierarchical;
    bool _public;
    bool show_ui;
    bool builtin;
    QString labels;
    QString cap;
    QString object_type;
	
	Wordpress *Taxonomy_wp;
	Database *Taxonomy_db;
	int size;
	QString tablename;
	public:
	Taxonomy();
	~Taxonomy();
	//get
	QString Taxonomy_get_name();
	QString Taxonomy_get_label();
	bool Taxonomy_get_hierarchical();
	bool Taxonomy_get_public();
	bool Taxonomy_get_show_ui();
	bool Taxonomy_get_builtin();
	QString Taxonomy_get_labels();
	QString Taxonomy_get_cap();
	QString Taxonomy_get_object_type();
	//set
	void Taxonomy_set_name(QString name);
	void Taxonomy_set_label(QString label);
	void Taxonomy_set_hierarchical(bool hierarchical);
	void Taxonomy_set_public(bool _public);
	void Taxonomy_set_show_ui(bool show_ui);
	void Taxonomy_set_builtin(bool builtin);
	void Taxonomy_set_labels(QString labels);
	void Taxonomy_set_cap(QString cap);
	void Taxonomy_set_object_type(QString object_type);
	
	void Taxonomy_get_taxonomy();
	public slots:
	void Taxonomy_get_taxonomy_ok(QVariant);
	void Taxonomy_get_taxonomy_failed(int ,QString);
};
#endif
