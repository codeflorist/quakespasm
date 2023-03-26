#include "quakedef.h"
#include "vr.h"

#ifndef __R_VR_MENU_H
#define __R_VR_MENU_H

typedef enum _vr_menu_options_t
{
	VR_OPTION_ENABLED,

	VR_OPTION_AIMMODE,
	VR_OPTION_DEADZONE,
	VR_OPTION_CROSSHAIR,
	VR_OPTION_CROSSHAIR_DEPTH,
	VR_OPTION_CROSSHAIR_SIZE,
	VR_OPTION_CROSSHAIR_ALPHA,
	VR_OPTION_WORLD_SCALE,
	VR_OPTION_MOVEMENT_MODE,
	VR_OPTION_SNAP_TURN,
	VR_OPTION_TURN_SPEED,
	VR_OPTION_MSAA,
	VR_OPTION_GUNANGLE,
	VR_OPTION_FLOOR_OFFSET,
	VR_OPTION_GUNMODELPITCH,
	VR_OPTION_GUNMODELSCALE,
	VR_OPTION_GUNMODELY,
	VR_OPTION_CROSSHAIRY,
	VR_OPTION_PROJECTILESPAWN_Z_OFFSET,
	VR_OPTION_HUD_SCALE,
	VR_OPTION_MENU_SCALE,
	VR_OPTION_IMPULSE9,

	VR_OPTION_MAX
} vr_menu_options_t;

void VR_Menu_Init ();
void VR_Menu_f (void);
void VR_MenuDraw (void);
void VR_MenuKey (int key);

extern void (*vr_menucmdfn)(void);
extern void (*vr_menudrawfn)(void);
extern void (*vr_menukeyfn)(int key);

#endif
