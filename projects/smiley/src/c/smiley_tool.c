/* Smiley tool: click the center, click again to set the radius.
   Builds one flat face (the head) with three holes (two eyes and a mouth).
   Derived from the formZ SDK sample Samples/Tools/Triangle. */

#include "smiley.h"
#include "fz_tool_api.h"
#include "fz_cmnd_model_ids.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Proportions, all relative to the head radius. Tweak these to restyle the face. */
#define SMILEY_HEAD_SEGS	48
#define SMILEY_EYE_SEGS		16
#define SMILEY_MOUTH_SEGS	12		/* segments per mouth curve */
#define SMILEY_EYE_X		0.35	/* eye center offset left/right */
#define SMILEY_EYE_Y		0.30	/* eye center offset up */
#define SMILEY_EYE_R		0.12
#define SMILEY_MOUTH_R		0.60	/* radius of the lower lip arc */
#define SMILEY_MOUTH_A0		200.0	/* lower lip arc start and end angles, degrees */
#define SMILEY_MOUTH_A1		340.0
#define SMILEY_MOUTH_OPEN	0.60	/* 0 = closed line, 1 = upper lip is straight */

#define SMILEY_MAX_PNTS		(SMILEY_HEAD_SEGS + 2*SMILEY_EYE_SEGS + 2*(SMILEY_MOUTH_SEGS+1))

typedef struct
{
	fz_objt_ptr			obj;
	fz_xyz_td			center;
} smiley_track_data_td;

smiley_track_data_td		smiley_track_data;


static fzrt_error_td smiley_tool_info(fz_tool_kind_enum *kind, fz_proj_level_enum *level)
{
	*kind = FZ_TOOL_KIND_OPERATOR;
	*level = FZ_PROJ_LEVEL_MODEL;
	return (FZRT_NOERR);
}

static fzrt_error_td smiley_tool_name(char *name, fzrt_int max_len)
{
	char	str[256];

	plugin_stuff.fzrt_base_funcs.fzrt_fzr_get_string(plugin_stuff.fz_rsrc_ref_func, SMILEY_STR_ID, SMILEY_STR_TOOL_NAME, str);
	strncpy(name, str, max_len);
	return (FZRT_NOERR);
}

static fzrt_error_td smiley_tool_uuid(fzrt_UUID_td uuid)
{
	plugin_stuff.fzrt_base_funcs.fzrt_UUID_copy( SMILEY_TOOL_ID, uuid );
	return (FZRT_NOERR);
}

static fzrt_error_td smiley_tool_icon_file(fzrt_floc_ptr floc)
{
	fzrt_error_td	err;

	err = plugin_stuff.fzrt_file_funcs.fzrt_file_floc_copy(plugin_stuff.floc,floc);
	err = plugin_stuff.fzrt_file_funcs.fzrt_file_floc_set_name(floc,"smiley.bmp");
	return(err);
}

static fzrt_boolean smiley_tool_info2(
									fzrt_int				windex,
									fz_tool_info_enum	which,
									fz_type_td			*info_data,
									fz_type_td			*data
									)
{
	fzrt_boolean		rv = TRUE;
	fzrt_int				value;

	switch(which)
	{
		case FZ_TOOL_INFO_PICK_STATE :
			value = 0;
			plugin_stuff.type_funcs.fz_type_set_int(&value, data);
			break;

		case FZ_TOOL_INFO_DRAW_STATE:
			/* AUTOPLANE ONLY FOR FIRST CLICK POINT */
			value = 1;
			plugin_stuff.type_funcs.fz_type_set_int(&value, data);
			break;

		default:
			rv = FALSE;
			break;
	}
	return(rv);
}

/* place the icon to the right of the 3D rectangle tool, as the Triangle sample does */
static fzrt_error_td smiley_tool_icon_adjacent(const fzrt_UUID_td tool_bar_id, fzrt_UUID_td adjacent_id, fz_fuim_icon_adjacent_enum *where)
{
	plugin_stuff.fzrt_base_funcs.fzrt_UUID_copy(FZ_CMND_MODEL_RECT3, adjacent_id);
	*where = FZ_FUIM_ICON_ADJACENT_RIGHT;
	return(FZRT_NOERR);
}


/************************************************************************
	geometry
*************************************************************************/

/* World-space unit axes of the drawing plane. Taken as differences of mapped
   points so it holds whether or not the plane mapping includes a translation. */
static void smiley_plane_axes(fz_map_plane_td *map_plane, fz_xyz_td *xaxis, fz_xyz_td *yaxis)
{
	fz_xyz_td	o = {0.0, 0.0, 0.0}, x = {1.0, 0.0, 0.0}, y = {0.0, 1.0, 0.0};

	plugin_stuff.math_funcs.fz_math_3d_map_plane_to_world(map_plane, &o);
	plugin_stuff.math_funcs.fz_math_3d_map_plane_to_world(map_plane, &x);
	plugin_stuff.math_funcs.fz_math_3d_map_plane_to_world(map_plane, &y);
	xaxis->x = x.x - o.x;	xaxis->y = x.y - o.y;	xaxis->z = x.z - o.z;
	yaxis->x = y.x - o.x;	yaxis->y = y.y - o.y;	yaxis->z = y.z - o.z;
}

static void smiley_put(fz_xyz_td *pts, fzrt_int *n, fz_xyz_td *xaxis, fz_xyz_td *yaxis, double u, double v)
{
	fz_xyz_td	*c = &smiley_track_data.center;

	pts[*n].x = c->x + u * xaxis->x + v * yaxis->x;
	pts[*n].y = c->y + u * xaxis->y + v * yaxis->y;
	pts[*n].z = c->z + u * xaxis->z + v * yaxis->z;
	(*n)++;
}

/* Rebuilds the tracked object as a smiley of the given radius. */
static fzrt_error_td smiley_build(fzrt_int windex, fz_map_plane_td *map_plane, double r)
{
	fzrt_error_td	err;
	fz_objt_ptr		obj = smiley_track_data.obj;
	fz_xyz_td		pts[SMILEY_MAX_PNTS], xaxis, yaxis;
	fzrt_int		pindx[SMILEY_MAX_PNTS];
	fzrt_int		n = 0, i, e, start, findx = 0;
	double			a, a0, a1, yend, u, v;

	smiley_plane_axes(map_plane, &xaxis, &yaxis);

	/* head outline, counter-clockwise */
	for(i = 0; i < SMILEY_HEAD_SEGS; i++)
	{	a = 2.0 * M_PI * i / SMILEY_HEAD_SEGS;
		smiley_put(pts, &n, &xaxis, &yaxis, r * cos(a), r * sin(a));
	}
	/* eyes, clockwise (holes run opposite to the outline) */
	for(e = -1; e <= 1; e += 2)
	{	for(i = 0; i < SMILEY_EYE_SEGS; i++)
		{	a = -2.0 * M_PI * i / SMILEY_EYE_SEGS;
			smiley_put(pts, &n, &xaxis, &yaxis,
					   r * (e * SMILEY_EYE_X + SMILEY_EYE_R * cos(a)),
					   r * (SMILEY_EYE_Y + SMILEY_EYE_R * sin(a)));
		}
	}
	/* mouth, clockwise: lower lip right to left, then upper lip left to right */
	a0 = SMILEY_MOUTH_A0 * M_PI / 180.0;
	a1 = SMILEY_MOUTH_A1 * M_PI / 180.0;
	yend = SMILEY_MOUTH_R * sin(a0);
	for(i = 0; i <= SMILEY_MOUTH_SEGS; i++)
	{	a = a1 + (a0 - a1) * i / SMILEY_MOUTH_SEGS;
		smiley_put(pts, &n, &xaxis, &yaxis, r * SMILEY_MOUTH_R * cos(a), r * SMILEY_MOUTH_R * sin(a));
	}
	for(i = 1; i < SMILEY_MOUTH_SEGS; i++)		/* end points are shared with the lower lip */
	{	a = a0 + (a1 - a0) * i / SMILEY_MOUTH_SEGS;
		u = SMILEY_MOUTH_R * cos(a);
		v = yend + (SMILEY_MOUTH_R * sin(a) - yend) * (1.0 - SMILEY_MOUTH_OPEN);
		smiley_put(pts, &n, &xaxis, &yaxis, r * u, r * v);
	}

	for(i = 0; i < n; i++) pindx[i] = i;

	plugin_stuff.model_funcs.fz_objt_fact_reset(windex, obj);
	if((err = plugin_stuff.model_funcs.fz_objt_fact_add_pnts(windex, obj, pts, n)) != FZRT_NOERR) return err;
	if((err = plugin_stuff.model_funcs.fz_objt_fact_create_face(windex, obj, pindx, SMILEY_HEAD_SEGS, &findx)) != FZRT_NOERR) return err;

	start = SMILEY_HEAD_SEGS;
	plugin_stuff.model_funcs.fz_objt_fact_create_hole_curv(windex, obj, findx, pindx + start, SMILEY_EYE_SEGS, NULL);
	start += SMILEY_EYE_SEGS;
	plugin_stuff.model_funcs.fz_objt_fact_create_hole_curv(windex, obj, findx, pindx + start, SMILEY_EYE_SEGS, NULL);
	start += SMILEY_EYE_SEGS;
	plugin_stuff.model_funcs.fz_objt_fact_create_hole_curv(windex, obj, findx, pindx + start, n - start, NULL);

	return FZRT_NOERR;
}

static double smiley_radius(fz_xyz_td *where_3d)
{
	fz_xyz_td	*c = &smiley_track_data.center;
	double		dx = where_3d->x - c->x, dy = where_3d->y - c->y, dz = where_3d->z - c->z;

	return sqrt(dx*dx + dy*dy + dz*dz);
}


/************************************************************************
	tool interaction
*************************************************************************/

/* first click: remember the center and start a placeholder object, as Triangle does */
static fzrt_error_td smiley_tool_click_first(fzrt_int windex, fz_xyz_td *where_3d)
{
	fzrt_error_td		err;
	fz_objt_ptr			obj;
	char				prompt_str[256];
	fz_xyz_td			pts[2];
	fzrt_int			pindx[2];

	if((err = plugin_stuff.model_funcs.fz_objt_cnstr_objt_new(windex,&obj)) == FZRT_NOERR )
	{
		smiley_track_data.center = *where_3d;
		pts[0] = *where_3d;
		pts[1] = *where_3d;
		plugin_stuff.model_funcs.fz_objt_fact_add_pnts(windex,obj,pts,2);

		pindx[0] = 0;
		pindx[1] = 1;
		plugin_stuff.model_funcs.fz_objt_fact_create_wire_face(windex,obj,pindx,2,NULL);

		err = plugin_stuff.model_funcs.fz_objt_add_objt_to_project(windex,obj);

		if ( err != FZRT_NOERR )
		{	plugin_stuff.model_funcs.fz_objt_edit_delete_objt(windex,obj);
		}
		else
		{
			plugin_stuff.fzrt_base_funcs.fzrt_fzr_get_string(plugin_stuff.fz_rsrc_ref_func, SMILEY_STR_ID, SMILEY_STR_P2, prompt_str);
			plugin_stuff.fuim_funcs.fz_fuim_prompt_line(prompt_str, FZ_FUIM_PROMPT_LINE_NEXT, FZ_FUIM_PROMPT_EDIT_XYZ);

			smiley_track_data.obj = obj;
		}
	}

	return err;
}

static fzrt_error_td smiley_tool_click(
		fzrt_int 						windex,
		fzrt_point 					*where,
		fz_xyz_td 					*where_3d,
		fz_map_plane_td 			*map_plane,
		fz_fuim_click_enum 			clicks,
		fzrt_int 						click_count,
		fzrt_boolean 				*click_handled,
		fz_fuim_click_wait_enum 	*click_next,
		fzrt_boolean 				*done)
{
	fzrt_error_td			err = FZRT_NOERR;
	double					r;

	switch(click_count)
	{	case 1 :
			err = smiley_tool_click_first(windex, where_3d);
		break;

		case 2 :
			r = smiley_radius(where_3d);
			if(r > 0.0)
			{	err = smiley_build(windex, map_plane, r);
			}
			else
			{	/* second click on the center: nothing to draw, drop the placeholder */
				plugin_stuff.model_funcs.fz_objt_edit_delete_objt(windex, smiley_track_data.obj);
			}
			*done = 1;
		break;
	}

	return (err);
}

static fzrt_error_td smiley_tool_track(
	fzrt_int				windex,
	fzrt_point 			*where,
	fz_xyz_td	 		*where_3d,
	fz_map_plane_td 	*map_plane,
	fzrt_int			 	click_count
	)
{
	fzrt_error_td			err = FZRT_NOERR;
	double					r;

	if(click_count == 1 && (r = smiley_radius(where_3d)) > 0.0)
	{	err = smiley_build(windex, map_plane, r);
	}
	return (err);
}

static fzrt_error_td smiley_tool_cancel(
	fzrt_int				windex,
	fzrt_int			 	click_count
	)
{
	if(click_count >= 1)
	{
		plugin_stuff.model_funcs.fz_objt_edit_delete_objt(windex,smiley_track_data.obj);
	}
	return (FZRT_NOERR);
}


/************************************************************************
	Fill the tool command function set with the smiley tool callbacks.
*************************************************************************/
fzrt_error_td smiley_tool_get_callback_fset ( const fzpl_fset_def_ptr fset_def, fzpl_fset_td * const fset )
{
	fzrt_error_td							err = FZRT_NOERR;
	fz_tool_cbak_fset 				*cmds_func;

	err = plugin_stuff.fsf->fzpl_fset_def_check ( fset_def, FZ_TOOL_CBAK_FSET_VERSION, FZPL_TYPE_STRING(fz_tool_cbak_fset), sizeof ( cmds_func ), FZPL_VERSION_OP_NEWER );
	if ( err == FZRT_NOERR )
	{
		cmds_func = (fz_tool_cbak_fset *)fset;

		cmds_func->fz_tool_cbak_info					= smiley_tool_info;
		cmds_func->fz_tool_cbak_name					= smiley_tool_name;
		cmds_func->fz_tool_cbak_uuid					= smiley_tool_uuid;
		cmds_func->fz_tool_cbak_icon_file				= smiley_tool_icon_file;
		cmds_func->fz_tool_cbak_icon_menu_adjacent		= smiley_tool_icon_adjacent;
		cmds_func->fz_tool_cbak_click					= smiley_tool_click;
		cmds_func->fz_tool_cbak_track					= smiley_tool_track;
		cmds_func->fz_tool_cbak_cancel					= smiley_tool_cancel;
		cmds_func->fz_tool_cbak_info2					= smiley_tool_info2;
	}

	return err;
}
