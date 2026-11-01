/* Array extension; registration follows the SDK Triangle tool contract.
   COPYRIGHT (C) 2001. All Rights Reserved. auto*des*sys, Inc., Columbus, Ohio, USA.
   New implementation: see repository LICENSE and ../AUTODESSYS_NOTICE.txt. */
#include "array.h"
#include "fz_plugin_glue_api.h"
#include "fz_cmnd_model_ids.h"

static const fzpl_fset_glue_fset *host;
static fz_fzrt_file_fset files;
static fzrt_floc_ptr location;
static fzrt_unsigned_int runtime_id;
static fzrt_boolean acquired, registered;

static fzrt_error_td tool_init(void) { return FZRT_NOERR; }
static fzrt_error_td tool_info(fz_tool_kind_enum *kind, fz_proj_level_enum *level)
{
    *kind = FZ_TOOL_KIND_OPERATOR;
    *level = FZ_PROJ_LEVEL_MODEL;
    return FZRT_NOERR;
}
static fzrt_error_td tool_name(char *name, fzrt_int max_len)
{
    if (max_len > 0) snprintf(name, max_len, "Array");
    return FZRT_NOERR;
}
static fzrt_error_td tool_uuid(fzrt_UUID_td uuid)
{
    memcpy(uuid, ARRAY_TOOL_ID, sizeof(fzrt_UUID_td));
    return FZRT_NOERR;
}
static fzrt_error_td tool_icon(fzrt_floc_ptr floc)
{
    fzrt_error_td err = files.fzrt_file_floc_copy(location, floc);
    if (err == FZRT_NOERR) err = files.fzrt_file_floc_set_name(floc, "array.bmp");
    return err;
}
static fzrt_error_td tool_adjacent(const fzrt_UUID_td toolbar,
    fzrt_UUID_td adjacent, fz_fuim_icon_adjacent_enum *where)
{
    memcpy(adjacent, FZ_CMND_MODEL_RECT3, sizeof(fzrt_UUID_td));
    *where = FZ_FUIM_ICON_ADJACENT_RIGHT;
    return FZRT_NOERR;
}
static fzrt_error_td callbacks(const fzpl_fset_def_ptr def, fzpl_fset_td *const fset)
{
    fzrt_error_td err = host->fzpl_fset_def_check(def, FZ_TOOL_CBAK_FSET_VERSION,
        FZPL_TYPE_STRING(fz_tool_cbak_fset), sizeof(fz_tool_cbak_fset), FZPL_VERSION_OP_NEWER);
    if (err == FZRT_NOERR) {
        fz_tool_cbak_fset *cb = (fz_tool_cbak_fset *)fset;
        cb->fz_tool_cbak_init = tool_init;
        cb->fz_tool_cbak_info = tool_info;
        cb->fz_tool_cbak_name = tool_name;
        cb->fz_tool_cbak_uuid = tool_uuid;
        cb->fz_tool_cbak_icon_file = tool_icon;
        cb->fz_tool_cbak_icon_menu_adjacent = tool_adjacent;
    }
    return err;
}
static void release_services(void)
{
    if (location) files.fzrt_file_floc_finit(&location);
    if (acquired) {
        host->fzpl_fset_release((fzpl_fset_td *)&files);
        acquired = FALSE;
    }
}
FZPL_PLUGIN_FUNC(fzrt_error_td) fz_plugin_entry(const fzpl_fset_glue_fset *const fsf,
    fzpl_command_td command, const fzpl_host_config_td *const config)
{
    fzrt_error_td err = FZRT_NOERR;
    switch (command) {
    case FZPL_PLUGIN_CHECK:
        host = fsf;
        err = host->fzpl_fset_acquire(FZ_FZRT_FILE_FSET_TYPE, FZ_FZRT_FILE_FSET_VERSION,
            FZRT_UUID_NULL, FZPL_TYPE_STRING(fz_fzrt_file_fset), sizeof(files), (fzpl_fset_td *)&files);
        if (err == FZRT_NOERR) {
            acquired = TRUE;
            err = files.fzrt_file_floc_init(&location);
            if (err == FZRT_NOERR) err = host->fzpl_plugin_file_get_floc(location);
        }
        if (err != FZRT_NOERR) release_services();
        break;
    case FZPL_PLUGIN_INITIALIZE:
        err = host->fzpl_plugin_register(ARRAY_PLUGIN_ID, "Array", FZPL_VERS_MAKE(0,1,0,0),
            "formZ-dev", "https://github.com/jedt3d/formz-extensions",
            FZ_TOOL_EXTS_TYPE, FZ_TOOL_EXTS_VERSION, NULL, 0, NULL, &runtime_id);
        if (err == FZRT_NOERR) {
            registered = TRUE;
            err = host->fzpl_plugin_add_fset(runtime_id, FZ_TOOL_CBAK_FSET_TYPE,
                FZ_TOOL_CBAK_FSET_VERSION, FZ_TOOL_CBAK_FSET_NAME,
                FZPL_TYPE_STRING(fz_tool_cbak_fset), sizeof(fz_tool_cbak_fset), callbacks, FALSE);
        }
        if (err != FZRT_NOERR && registered) {
            host->fzpl_plugin_unregister(runtime_id);
            registered = FALSE;
        }
        break;
    case FZPL_PLUGIN_EXIT:
        if (registered) {
            err = host->fzpl_plugin_unregister(runtime_id);
            registered = FALSE;
        }
        release_services();
        break;
    }
    return err;
}
