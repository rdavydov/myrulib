#include "FbFilterObj.h"
#include "FbParams.h"

IMPLEMENT_CLASS(FbFilterObj, wxObject)

FbFilterObj::FbFilterObj()
	: m_enabled(false), m_lib(false), m_usr(false), m_del(false)
{
}

FbFilterObj::FbFilterObj(const FbFilterObj & object) :
	m_enabled(object.m_enabled),
	m_lib(object.m_lib),
	m_usr(object.m_usr),
	m_del(object.m_del),
	m_lang(object.m_lang),
	m_type(object.m_type)
{
}

FbFilterObj & FbFilterObj::operator=(const FbFilterObj & object)
{
	m_enabled = object.m_enabled;
	m_lib = object.m_lib;
	m_usr = object.m_usr;
	m_del = object.m_del;
	m_lang = object.m_lang;
	m_type = object.m_type;
	return *this;
}

void FbFilterObj::Load()
{
	m_enabled = FbParams::GetInt(FB_USE_FILTER);
	m_lib = FbParams::GetInt(FB_FILTER_LIB);
	m_usr = FbParams::GetInt(FB_FILTER_USR);
	m_del = FbParams::GetInt(FB_FILTER_DEL);
	m_lang = FbParams::GetStr(FB_FILTER_LANG);
	m_type = FbParams::GetStr(FB_FILTER_TYPE);
}

void FbFilterObj::Save() const
{
	FbParams::Set(FB_USE_FILTER, m_enabled);
	FbParams::Set(FB_FILTER_LIB, m_lib);
	FbParams::Set(FB_FILTER_USR, m_usr);
	FbParams::Set(FB_FILTER_DEL, m_del);
	FbParams::Set(FB_FILTER_LANG, m_lang);
	FbParams::Set(FB_FILTER_TYPE, m_type);
}

wxString FbFilterObj::GetSQL() const
{
	const wxString addin = wxT(" AND books.");
	const wxString not_del = wxT("AND ((books.deleted IS NULL)OR(books.deleted<>1))");

	if (!m_enabled) return not_del;

	wxString sql;
	if (!m_del) sql << not_del;
	if (m_lib && !m_usr) sql << addin << wxT("id>0");
	if (!m_lib && m_usr) sql << addin << wxT("id<0");
	if (!m_lib && m_del) sql << addin << wxT("id<0");
	if (!m_lang.IsEmpty()) sql << addin << wxT("lang in (") << m_lang << wxT(')');
	if (!m_type.IsEmpty()) sql << addin << wxT("file_type in (") << m_type << wxT(')');

	return sql;
}

