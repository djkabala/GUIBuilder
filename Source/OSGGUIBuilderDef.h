#ifndef _KEGUIBUILDERDEF_H_
#define _KEGUIBUILDERDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(KE_BUILD_DLL)
#   ifdef KE_COMPILEGUIBUILDERLIB
#       define KE_GUIBUILDER_DLLMAPPING     __declspec(dllexport)
#       define KE_GUIBUILDER_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define KE_GUIBUILDER_DLLMAPPING     __declspec(dllimport)
#       define KE_GUIBUILDER_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define KE_GUIBUILDER_DLLMAPPING
#define KE_GUIBUILDER_DLLTMPLMAPPING
#endif

#endif /* _KEGUIBUILDERDEF_H_ */

