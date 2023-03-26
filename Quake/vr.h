// 2016 Dominic Szablewski - phoboslab.org

#include "quakedef.h"

#ifndef __R_VR_H
#define __R_VR_H

#define VR_AIMMODE_HEAD_MYAW 1 // Head Aiming; View YAW is mouse+head, PITCH is head
#define VR_AIMMODE_HEAD_MYAW_MPITCH 2 // Head Aiming; View YAW and PITCH is mouse+head
#define VR_AIMMODE_MOUSE_MYAW 3 // Mouse Aiming; View YAW is mouse+head, PITCH is head
#define VR_AIMMODE_MOUSE_MYAW_MPITCH 4 // Mouse Aiming; View YAW and PITCH is mouse+head
#define VR_AIMMODE_BLENDED 5 // Blended Aiming; Mouse aims, with YAW decoupled for limited area
#define VR_AIMMODE_BLENDED_NOPITCH 6 // Blended Aiming; Mouse aims, with YAW decoupled for limited area, pitch decoupled entirely
#define VR_AIMMODE_CONTROLLER 7 // Controller Aiming

#define	VR_CROSSHAIR_NONE 0 // No crosshair
#define	VR_CROSSHAIR_POINT 1 // Point crosshair projected to depth of object it is in front of
#define	VR_CROSSHAIR_LINE 2 // Line crosshair

#define VR_MOVEMENT_MODE_FOLLOW_HAND 0
#define VR_MOVEMENT_MODE_RAW_INPUT 1
#define VR_MAX_MOVEMENT_MODE VR_MOVEMENT_MODE_RAW_INPUT

void VID_VR_Init();
void VID_VR_Shutdown();
qboolean VR_Enable();
void VID_VR_Disable();

void VR_UpdateScreenContent();
void VR_ShowCrosshair();
void VR_Draw2D();
void VR_Move(usercmd_t *cmd);
void VR_InitGame();
void VR_PushYaw();
void VR_DrawSbar();
void VR_AddOrientationToViewAngles(vec3_t angles);
void VR_SetAngles(vec3_t angles);
void VR_ResetOrientation();
void VR_SetMatrices();
void VR_SetTrackingSpace(int n);

extern cvar_t vr_enabled;
extern cvar_t vr_crosshair;
extern cvar_t vr_msaa;
extern cvar_t vr_movement_mode;
extern cvar_t vr_gunangle;
extern cvar_t vr_gunmodelpitch;
extern cvar_t vr_gunmodelscale;
extern cvar_t vr_gunmodely;
extern cvar_t vr_crosshairy;
extern cvar_t vr_floor_offset;
extern cvar_t vr_projectilespawn_z_offset;
extern cvar_t vr_hud_scale;
extern cvar_t vr_menu_scale;

#define MAX_WEAPONS 20 //not sure what this number should actually be...
#define VARS_PER_WEAPON 5

extern cvar_t vr_weapon_offset[MAX_WEAPONS * VARS_PER_WEAPON];
extern int weaponCVarEntry;

#endif