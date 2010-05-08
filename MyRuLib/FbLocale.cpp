#include "FbLocale.h"
#include <wx/wfstream.h>
#include "FbDatabase.h"
#include "FbConst.h"

bool FbLocale::Init(int language, int flags)
{
	wxFileName filename = FbConfigDatabase::GetConfigName();

    #ifdef FB_INCLUDE_LOCALE

	filename.SetExt(wxT("mo"));

	if (language == wxLANGUAGE_DEFAULT) language = GetSystemLanguage();

    bool ok = false;
	switch (language) {
		case wxLANGUAGE_RUSSIAN: {
			#include "ru.inc"
			ok = Save(filename, locale_binary_file, sizeof(locale_binary_file));
		} break;
		case wxLANGUAGE_UKRAINIAN: {
			#include "uk.inc"
			ok = Save(filename, locale_binary_file, sizeof(locale_binary_file));
		} break;
		case wxLANGUAGE_BELARUSIAN: {
			#include "be.inc"
			ok = Save(filename, locale_binary_file, sizeof(locale_binary_file));
		} break;
		case wxLANGUAGE_CZECH: {
			#include "cs.inc"
			ok = Save(filename, locale_binary_file, sizeof(locale_binary_file));
		} break;
	}

	if (ok) AddCatalogLookupPathPrefix(filename.GetPath());

	#else

    bool ok = true;

    #endif //FB_INCLUDE_LOCALE

    bool res = wxLocale::Init(language, flags);

    if (ok) AddCatalog(filename.GetName());

    return res;
}

bool FbLocale::Save(const wxFileName &filename, const void *data, size_t size)
{
    wxLogNull log;
    wxFileOutputStream out(filename.GetFullPath());
    out.Write(data, size);
    return true;
}

int FbLocale::MenuToLang(wxWindowID id)
{
    switch ( id ) {
        case ID_LANG_DEFAULT:    return wxLANGUAGE_DEFAULT;
        case ID_LANG_ENGLISH:    return wxLANGUAGE_ENGLISH;
        case ID_LANG_RUSSIAN:    return wxLANGUAGE_RUSSIAN;
        case ID_LANG_UKRAINIAN:  return wxLANGUAGE_UKRAINIAN;
        case ID_LANG_BELARUSIAN: return wxLANGUAGE_BELARUSIAN;
        case ID_LANG_CZECH:      return wxLANGUAGE_CZECH;
        default: return wxLANGUAGE_DEFAULT;
    }
}
