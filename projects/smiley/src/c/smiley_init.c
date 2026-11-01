/*------------------------------------------------------------------------*
  Filename....: smiley_init.c


		 COPYRIGHT (C) 2001.  All Rights Reserved.
		 auto*des*sys, Inc., Columbus, Ohio, USA.
 *------------------------------------------------------------------------*/

#include "smiley.h"

#include "fz_plugin_glue_api.h"
#include "fz_tool_api.h"

smiley_plugin_stuff		plugin_stuff;

/************************************************************************
	acquires all application provided service function sets.
*************************************************************************/
static fzrt_error_td smiley_acquire_fsets ( void )
{
	fzrt_error_td err = FZRT_NOERR;

	
	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_MATH_FSET_TYPE, FZ_MATH_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_math_fset), sizeof(plugin_stuff.math_funcs),
									 (fzpl_fset_td *)&plugin_stuff.math_funcs );
	}
	
	if(err == FZRT_NOERR)
	{
		err =(*plugin_stuff.fsf->fzpl_fset_acquire)(FZ_MODEL_FSET_TYPE, FZ_MODEL_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_model_fset), sizeof(plugin_stuff.model_funcs),
									(fzpl_fset_td *)&plugin_stuff.model_funcs);
	}

	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_TYPE_FSET_TYPE, FZ_TYPE_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_type_fset), sizeof(plugin_stuff.type_funcs),
									 (fzpl_fset_td *)&plugin_stuff.type_funcs );
	}

	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_FUIM_FSET_TYPE, FZ_FUIM_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_fuim_fset), sizeof(plugin_stuff.fuim_funcs),
									 (fzpl_fset_td *)&plugin_stuff.fuim_funcs );
	}
	
	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_FZRT_BASE_FSET_TYPE, FZ_FZRT_BASE_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_fzrt_base_fset), sizeof(plugin_stuff.fzrt_base_funcs),
									 (fzpl_fset_td *)&plugin_stuff.fzrt_base_funcs );
	}

	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_FZRT_MEM_FSET_TYPE, FZ_FZRT_MEM_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_fzrt_mem_fset), sizeof(plugin_stuff.fzrt_mem_funcs),
									 (fzpl_fset_td *)&plugin_stuff.fzrt_mem_funcs );
	}

	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_FZRT_FILE_FSET_TYPE, FZ_FZRT_FILE_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_fzrt_file_fset), sizeof(plugin_stuff.fzrt_file_funcs),
									 (fzpl_fset_td *)&plugin_stuff.fzrt_file_funcs );
	}

	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_FZRT_GRAF_FSET_TYPE, FZ_FZRT_GRAF_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_fzrt_graf_fset), sizeof(plugin_stuff.fzrt_graf_funcs),
									 (fzpl_fset_td *)&plugin_stuff.fzrt_graf_funcs );
	}
	
	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_FZRT_UI_FSET_TYPE, FZ_FZRT_UI_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_fzrt_ui_fset), sizeof(plugin_stuff.fzrt_ui_funcs),
									 (fzpl_fset_td *)&plugin_stuff.fzrt_ui_funcs );
	}

	if(err == FZRT_NOERR)
	{
		err = (*plugin_stuff.fsf->fzpl_fset_acquire) ( FZ_IOST_FSET_TYPE, FZ_IOST_FSET_VERSION, FZRT_UUID_NULL,
									 FZPL_TYPE_STRING(fz_iost_fset), sizeof(fz_iost_fset),
									 (fzpl_fset_td *)&plugin_stuff.iost_funcs );
	}
	
	return err;
}

/************************************************************************
	releases all application provided service function sets.
*************************************************************************/
static void smiley_release_fsets ( void )
{
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.math_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.model_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.type_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.fuim_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.iost_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.fzrt_base_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.fzrt_mem_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.fzrt_file_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.fzrt_graf_funcs );
	(*plugin_stuff.fsf->fzpl_fset_release) ( (fzpl_fset_td *)&plugin_stuff.fzrt_ui_funcs );
}




/************************************************************************
	A first pass check to see if the plugin can be loaded.
	Checks licensing.
	Checks that application defined function sets which are
		needed by the plugins are available.
	Verifies that plugin and application are compatible.
	Verifies that plugin type is expected by application.
	Informs the application if this plugin is dependent on
	function sets from other plugins.
*************************************************************************/
static fzrt_error_td smiley_check_config ( const fzpl_fset_glue_fset * const fsf, const fzpl_host_config_td * const hostConfig )
{
	fzrt_error_td					err = FZRT_NOERR;

	plugin_stuff.fsf = fsf;
	plugin_stuff.fz_rsrc_ref_func = -1;
	plugin_stuff.floc = NULL;

	/*  Make sure required application defined function sets are available */
	/*  Release the function sets at unload. */

	err = smiley_acquire_fsets();

	/* Make sure the plugin's resource file is available and load it */
	if ( err == FZRT_NOERR )
	{
		plugin_stuff.fzrt_file_funcs.fzrt_file_floc_init(&plugin_stuff.floc);
		err = (*fsf->fzpl_plugin_file_get_floc)(plugin_stuff.floc);
		if(err == FZRT_NOERR)
		{
			err = plugin_stuff.fzrt_base_funcs.fzrt_fzr_open(plugin_stuff.floc, "smiley", &plugin_stuff.fz_rsrc_ref_func);
		}
	}	

	if ( err != FZRT_NOERR )
	{
		smiley_release_fsets();
	}

	return err;
}


/************************************************************************
	Generates error strings for any errors created by the plugin
*************************************************************************/
static fzrt_boolean smiley_error_str_func(fzrt_int err, char *str, short str_len)
{
	/* ADD ERROR STRINGS, IF ANY */
	
	return(FALSE);
}




/************************************************************************
	Registers plugins and their assocoated function sets.
*************************************************************************/
static fzrt_error_td smiley_register_plugins ( const fzpl_fset_glue_fset * const fsf, const fzpl_host_config_td * const hostConfig )
{
	fzrt_error_td					err = FZRT_NOERR;
	fzrt_int							num_failed = 0;
	char							pname[FZPL_NAME_SIZE];

			
	/* REGISTER SMILEY TOOL */
	if(err == FZRT_NOERR)
	{				
		/* Register the tool plugin */
		plugin_stuff.fzrt_base_funcs.fzrt_fzr_get_string(plugin_stuff.fz_rsrc_ref_func, SMILEY_STR_ID, SMILEY_STR_TOOL_NAME, pname);
		err = (*fsf->fzpl_plugin_register)( SMILEY_TOOL_PLUGIN_ID, pname, SMILEY_TOOL_PLUGIN_VERSION,
							SMILEY_TOOL_PLUGIN_VENDOR,
							SMILEY_TOOL_PLUGIN_URL,
							FZ_TOOL_EXTS_TYPE, FZ_TOOL_EXTS_VERSION,
							smiley_error_str_func, 0, NULL,
							&plugin_stuff.smiley_tool_plugin_runtime_id);
		
		if ( err != FZRT_NOERR )
		{
			err = FZRT_NOERR;
			num_failed++;
		}
		else
		{
			
			/* Add the function sets implemented by the tool plugin */
			err = (*fsf->fzpl_plugin_add_fset)( plugin_stuff.smiley_tool_plugin_runtime_id, FZ_TOOL_CBAK_FSET_TYPE,
					  FZ_TOOL_CBAK_FSET_VERSION, FZ_TOOL_CBAK_FSET_NAME,
					  FZPL_TYPE_STRING(fz_tool_cbak_fset), sizeof ( fz_tool_cbak_fset ),
					  smiley_tool_get_callback_fset, FALSE);
			
		}
	}

	return err;
}

/************************************************************************
	Unregisters plugins.
*************************************************************************/
static fzrt_error_td smiley_unregister_plugins ( const fzpl_fset_glue_fset * const fsf )
{
	fzrt_error_td					err = FZRT_NOERR;

	if(plugin_stuff.fz_rsrc_ref_func !=-1)
	{	plugin_stuff.fzrt_base_funcs.fzrt_fzr_close(plugin_stuff.fz_rsrc_ref_func);
	}

	/* Unregister the plugins */
	err = (*fsf->fzpl_plugin_unregister)( plugin_stuff.smiley_tool_plugin_runtime_id );

	if (plugin_stuff.floc) plugin_stuff.fzrt_file_funcs.fzrt_file_floc_finit(&plugin_stuff.floc);

	/* Release application implemented function sets */
	smiley_release_fsets();

	return err;
}

/************************************************************************
	The main plugin file entry point.  Plugin initialization
	happens via this function.
*************************************************************************/
FZPL_PLUGIN_FUNC(fzrt_error_td) fz_plugin_entry( const fzpl_fset_glue_fset * const fsf, fzpl_command_td cmd, const fzpl_host_config_td * const hostConfig )
{
	fzrt_error_td err = FZRT_NOERR;

	switch ( cmd )
	{
		case FZPL_PLUGIN_CHECK:
			err = smiley_check_config ( fsf, hostConfig );
		break;
		
		case FZPL_PLUGIN_INITIALIZE:
			err = smiley_register_plugins ( fsf, hostConfig );
		break;
		
		case FZPL_PLUGIN_EXIT:
			err = smiley_unregister_plugins ( fsf );
		break;
	}

	return ( err );
}

