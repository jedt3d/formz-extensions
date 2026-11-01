/*------------------------------------------------------------------------*
  Filename....: smiley.h


		 COPYRIGHT (C) 2001.  All Rights Reserved.
		 auto*des*sys, Inc., Columbus, Ohio, USA.
 *------------------------------------------------------------------------*/

#ifndef _SMILEY_H
#define _SMILEY_H 1

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>

#include "fzrt_api.h"
#include "fz_api.h"

#include "fz_math_api.h"
#include "fz_objt_api.h"
#include "fz_type_api.h"
#include "fz_iost_api.h"
#include "fz_notf_api.h"

#include "formz_vendor.h"

#include "fzpl_plugin.h"



/*************************************************************************
						TOOL STUFF
**************************************************************************/
/* Star Tool Plugin Identification */

#define SMILEY_TOOL_PLUGIN_ID				"\x3e\xb7\xaf\x15\x39\xb4\x4b\x1a\xb7\xea\x6d\x70\x91\x7e\xe8\x75"
#define SMILEY_TOOL_PLUGIN_VERSION		FZPL_VERS_MAKE(1,0,0,0)
#define SMILEY_TOOL_PLUGIN_VENDOR			"formZ-dev"
#define SMILEY_TOOL_PLUGIN_ATTR_STR		""
#define SMILEY_TOOL_PLUGIN_URL			""

/* Star Tool Id */
#define SMILEY_TOOL_ID	"\x2c\xe4\x59\x63\x46\x8c\x45\x53\xb8\x72\x8e\xf3\xb5\x77\x6e\x46"

fzrt_error_td smiley_tool_get_callback_fset ( const fzpl_fset_def_ptr fset_def, fzpl_fset_td * const fset );

/*************************************************************************
						PLUGIN STUFF
**************************************************************************/
#define SMILEY_STR_ID			1
enum
{
	SMILEY_STR_PLUGIN_NAME=1,
	SMILEY_STR_TOOL_NAME,
	SMILEY_STR_P1,
	SMILEY_STR_P2,

	SMILEY_STR_MAX
};

typedef struct
{
	const fzpl_fset_glue_fset *fsf;

	/* application provided function sets to hold on to */
	
	fz_math_fset			math_funcs;
	fz_model_fset			model_funcs;
	fz_type_fset			type_funcs;
	fz_fuim_fset			fuim_funcs;
	fz_iost_fset			iost_funcs;

	fz_fzrt_base_fset		fzrt_base_funcs;
	fz_fzrt_mem_fset		fzrt_mem_funcs;
	fz_fzrt_file_fset		fzrt_file_funcs;
	fz_fzrt_graf_fset		fzrt_graf_funcs;
	fz_fzrt_ui_fset		fzrt_ui_funcs;

	fzrt_unsigned_int			smiley_tool_plugin_runtime_id;
	fzrt_fzr_ref_td			fz_rsrc_ref_func;
	fzrt_floc_ptr			floc;
		
}  smiley_plugin_stuff;

extern smiley_plugin_stuff		plugin_stuff;

#endif /* _SMILEY_H */
