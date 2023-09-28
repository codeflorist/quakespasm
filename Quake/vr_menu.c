#include "quakedef.h"
#include "vr.h"
#include "vr_menu.h"
#include <string>
#include <array>
#include "cmd.h"

extern cvar_t vr_enabled;
extern cvar_t vr_crosshair;
extern cvar_t vr_crosshair_depth;
extern cvar_t vr_crosshair_size;
extern cvar_t vr_crosshair_alpha;
extern cvar_t vr_aimmode;
extern cvar_t vr_deadzone;
extern cvar_t vr_world_scale;
extern cvar_t vr_snap_turn;
extern cvar_t vr_turn_speed;

static int	vr_options_cursor = 0;

#define VR_MAX_TURN_SPEED 10.0f
#define VR_MAX_FLOOR_OFFSET 200.0f
#define VR_MAX_GUNANGLE 180.0f

extern void M_DrawSlider (int x, int y, float range);

void VR_Menu_Init()
{
    // VR menu function pointers
    vr_menucmdfn = VR_Menu_f;
    vr_menudrawfn = VR_MenuDraw;
    vr_menukeyfn = VR_MenuKey;
}

static void VR_MenuPlaySound(const char *sound, float fvol)
{
    sfx_t *sfx = S_PrecacheSound( sound );

    if ( sfx ) {
        S_StartSound( cl.viewentity, 0, sfx, vec3_origin, fvol, 1 );
    }
}

static void VR_MenuPrintOptionValue(int cx, int cy, int option)
{
    char value_buffer[32] = {0};
    const char *value_string = NULL;

    const auto printAsStr = [&](const auto& cvar)
    {
        snprintf(value_buffer, sizeof(value_buffer), "%.4f", cvar.value);
        M_Print(cx, cy, value_buffer);
    };

#ifdef _MSC_VER
#define snprintf sprintf_s
#endif
    switch ( option ) {
        default: break;

        case VR_OPTION_ENABLED:
            M_DrawCheckbox( cx, cy, (int)vr_enabled.value );
            break;
        /*case VR_OPTION_PERFHUD:
            if (vr_perfhud.value == 1) value_string = "Latency Timing";
            else if (vr_perfhud.value == 2) value_string = "Render Timing";
            else if (vr_perfhud.value == 3) value_string = "Perf Headroom";
            else if (vr_perfhud.value == 4) value_string = "Version Info";
            else value_string = "off";
            break;*/
        case VR_OPTION_AIMMODE:
            switch ( (int)vr_aimmode.value ) {
                case VR_AIMMODE_HEAD_MYAW:
                    value_string = "HEAD_MYAW";
                    break;
                case VR_AIMMODE_HEAD_MYAW_MPITCH:
                    value_string = "HEAD_MYAW_MPITCH";
                    break;
                case VR_AIMMODE_MOUSE_MYAW:
                    value_string = "MOUSE_MYAW";
                    break;
                case VR_AIMMODE_MOUSE_MYAW_MPITCH:
                    value_string = "MOUSE_MYAW_MPITCH";
                    break;
                default:
                case VR_AIMMODE_BLENDED:
                    value_string = "BLENDED";
                    break;
                case VR_AIMMODE_BLENDED_NOPITCH:
                    value_string = "BLENDED_NOPITCH";
                    break;
                case VR_AIMMODE_CONTROLLER:
                    value_string = "CONTROLLER";
                    break;
            }
            break;
        case VR_OPTION_DEADZONE:
            if ( vr_deadzone.value > 0 ) {
                snprintf( value_buffer, sizeof(value_buffer), "%.0f degrees", vr_deadzone.value );
                value_string = value_buffer;
            } else {
                value_string = "off";
            }
            break;
        case VR_OPTION_CROSSHAIR:
            if ( (int)vr_crosshair.value == 2 ) {
                value_string = "line";
            } else if ( (int)vr_crosshair.value == 1 ) {
                value_string = "point";
            } else {
                value_string = "off";
            }
            break;
        case VR_OPTION_CROSSHAIR_DEPTH:
            if ( vr_crosshair_depth.value > 0 ) {
                snprintf( value_buffer, sizeof(value_buffer), "%.0f units", vr_crosshair_depth.value );
                value_string = value_buffer;
            } else {
                value_string = "off";
            }
            break;
        case VR_OPTION_CROSSHAIR_SIZE:
            if ( vr_crosshair_size.value > 0 ) {
                snprintf( value_buffer, sizeof(value_buffer), "%.0f pixels", vr_crosshair_size.value );
                value_string = value_buffer;
            } else {
                value_string = "off";
            }
            break;
        case VR_OPTION_CROSSHAIR_ALPHA:
            M_DrawSlider( cx, cy, vr_crosshair_alpha.value );
            break;
        case VR_OPTION_WORLD_SCALE:
            M_DrawSlider(cx, cy, vr_world_scale.value / 2.0f);
            break;
        case VR_OPTION_MOVEMENT_MODE:
            switch ((int)vr_movement_mode.value)
            {
            case VR_MOVEMENT_MODE_FOLLOW_HEAD: value_string = "Follow head"; break;
            case VR_MOVEMENT_MODE_FOLLOW_HAND: value_string = "Follow hand"; break;
            case VR_MOVEMENT_MODE_RAW_INPUT: value_string = "Raw input"; break;
            }
            break;
        case VR_OPTION_SNAP_TURN:
            if (vr_snap_turn.value == 0)
            {
                value_string = "Smooth";
            }
            else
            {
                snprintf(value_buffer, sizeof(value_buffer), "%d Degrees", (int)vr_snap_turn.value);
                value_string = value_buffer;
            }
            break;
        case VR_OPTION_TURN_SPEED:
            M_DrawSlider(cx, cy, vr_turn_speed.value / VR_MAX_TURN_SPEED);
            break;
        case VR_OPTION_MSAA:
            if (vr_msaa.value == 0)
            {
                value_string = "Off";
            }
            else 
            {
                snprintf(value_buffer, sizeof(value_buffer), "%d Samples", (int)vr_msaa.value);
                value_string = value_buffer;
            }
            break;
        case VR_OPTION_GUNMODELOFFSETS:
            switch ((int)vr_gunmodeloffsets.value)
            {
            case VR_GUNMODELOFFSETS_VANILLA: value_string = "Vanilla"; break;
            case VR_GUNMODELOFFSETS_ENHANCED: value_string = "Enhanced"; break;
            }
            break;
        case VR_OPTION_GUNANGLE:                 printAsStr(vr_gunangle); break;
        case VR_OPTION_FLOOR_OFFSET:             printAsStr(vr_floor_offset); break;
        case VR_OPTION_GUNMODELPITCH:            printAsStr(vr_gunmodelpitch); break;
        case VR_OPTION_GUNMODELSCALE:            printAsStr(vr_gunmodelscale); break;
        case VR_OPTION_GUNMODELY:                printAsStr(vr_gunmodely); break;
        case VR_OPTION_CROSSHAIRY:               printAsStr(vr_crosshairy); break;
        case VR_OPTION_PROJECTILESPAWN_Z_OFFSET: printAsStr(vr_projectilespawn_z_offset); break;
        case VR_OPTION_HUD_SCALE:                printAsStr(vr_hud_scale); break;
        case VR_OPTION_MENU_SCALE:               printAsStr(vr_menu_scale); break;
        case VR_OPTION_IMPULSE9:                 break;
        case VR_OPTION_GOD:                      break;
        case VR_OPTION_NOCLIP:                   break;
        case VR_OPTION_FLY:                      break;
    }
#ifdef _MSC_VER
#undef snprintf
#endif
    if ( value_string ) {
        M_Print( cx, cy, value_string );
    }
}

static void VR_MenuKeyOption(int key, int option)
{
#define _sizeofarray(x) ( ( sizeof(x) / sizeof(x[0]) ) )
#define _maxarray(x) ( _sizeofarray(x) - 1 )

    qboolean isLeft = (key == K_LEFTARROW);
    int intValue = 0;
    float floatValue = 0.0f;
    int i = 0;

    int debug[] = { 0, 1, 2, 3, 4 };
    float ipdDiff = 0.2f;
    int position[] = { 0, 1, 2 };
    float multisample[] = { 1.0f, 1.25f, 1.50f, 1.75f, 2.0f };
    int aimmode[] = { 1, 2, 3, 4, 5, 6, 7 };
    int deadzoneDiff = 5;
    int crosshair[] = { 0, 1, 2 };
    int crosshairDepthDiff = 32;
    int crosshairSizeDiff = 1;
    float crosshairAlphaDiff = 0.05f;

    const auto adjustF = [&isLeft](const cvar_t& cvar, auto incr, auto min, auto max) {
        Cvar_SetValue(cvar.name, CLAMP(min, isLeft ? cvar.value - incr : cvar.value + incr, max));
    };

    const auto adjustI = [&isLeft](const cvar_t& cvar, auto incr, auto min, auto max) {
        Cvar_SetValue(cvar.name, (int) CLAMP(min, isLeft ? cvar.value - incr : cvar.value + incr, max));
    };

    switch ( option ) {
        case VR_OPTION_ENABLED:
            // Cvar_SetValue( "vr_enabled", ! (int)vr_enabled.value );
            // if ( (int)vr_enabled.value ) {
            //    VR_MenuPlaySound( "items/r_item2.wav", 0.5 );
            // }
            break;
        /*case VR_OPTION_PERFHUD:
            intValue = (int)vr_perfhud.value;
            intValue = CLAMP( debug[0], isLeft ? intValue - 1 : intValue + 1, debug[_maxarray( debug )] );
            Cvar_SetValue( "vr_perfhud", intValue );
            break;*/
        case VR_OPTION_AIMMODE:
            intValue = (int)vr_aimmode.value;
            intValue = CLAMP( aimmode[0], isLeft ? intValue - 1 : intValue + 1, _sizeofarray( aimmode ) );
            intValue -= 1;
            Cvar_SetValue( "vr_aimmode", aimmode[intValue] );
            break;
        case VR_OPTION_DEADZONE:
            adjustF(vr_deadzone, deadzoneDiff, 0.f, 180.f);
            break;
        case VR_OPTION_CROSSHAIR:
            adjustI(vr_crosshair, 1, crosshair[0], crosshair[_maxarray( crosshair)  ]);
            break;
        case VR_OPTION_CROSSHAIR_DEPTH:
            adjustF(vr_crosshair_depth, crosshairDepthDiff, 0.f, 4096.f);
            break;
        case VR_OPTION_CROSSHAIR_SIZE:
            adjustF(vr_crosshair_size, crosshairSizeDiff, 0.f, 32.f);
            break;
        case VR_OPTION_CROSSHAIR_ALPHA:
            adjustF(vr_crosshair_alpha, crosshairAlphaDiff, 0.f, 1.f);
            break;
        case VR_OPTION_WORLD_SCALE:
            adjustF(vr_world_scale, crosshairAlphaDiff, 0.f, 2.f);
            break;
        case VR_OPTION_MOVEMENT_MODE:
            adjustI(vr_movement_mode, 1, 0.f, VR_MAX_MOVEMENT_MODE);
            break;
        case VR_OPTION_SNAP_TURN:
            adjustI(vr_snap_turn, 45, 0.f, 90.f);
            break;
        case VR_OPTION_TURN_SPEED:
            adjustF(vr_turn_speed, 0.25f, 0.f, VR_MAX_TURN_SPEED);
            break;
        case VR_OPTION_MSAA:
            int max;
            glGetIntegerv(GL_MAX_SAMPLES, &max);
            adjustI(vr_msaa, 1, 0, max);
            break;
        case VR_OPTION_GUNANGLE:
            adjustF(vr_gunangle, 2.5f, -VR_MAX_GUNANGLE, VR_MAX_GUNANGLE);
            break;
        case VR_OPTION_FLOOR_OFFSET:
            adjustF(vr_floor_offset, 2.5f, -VR_MAX_FLOOR_OFFSET, VR_MAX_FLOOR_OFFSET);
            break;
        case VR_OPTION_GUNMODELOFFSETS:
            adjustI(vr_gunmodeloffsets, 1, 0.f, VR_MAX_GUNMODELOFFSETS);
            break;
        case VR_OPTION_GUNMODELPITCH:
            adjustF(vr_gunmodelpitch, 0.5f, -90.f, 90.f);
            break;
        case VR_OPTION_GUNMODELSCALE:
            adjustF(vr_gunmodelscale, 0.05f, 0.1f, 2.f);
            break;
        case VR_OPTION_GUNMODELY:
            adjustF(vr_gunmodely, 0.1f, -5.0f, 5.f);
            break;
        case VR_OPTION_CROSSHAIRY:
            adjustF(vr_crosshairy, 0.05f, -10.0f, 10.f);
            break;
        case VR_OPTION_PROJECTILESPAWN_Z_OFFSET:
            adjustF(vr_projectilespawn_z_offset, 1.f, -24.0f, 24.f);
            break;
        case VR_OPTION_HUD_SCALE:
            adjustF(vr_hud_scale, 0.005f, 0.01f, 0.1f);
            break;
        case VR_OPTION_MENU_SCALE:
            adjustF(vr_menu_scale, 0.01f, 0.05f, 0.6f);
            break;
        case VR_OPTION_IMPULSE9:
            VR_MenuPlaySound("items/r_item2.wav", 0.5);
            Cmd_ExecuteString("impulse 9", cmd_source_t::src_command);
            break;
        case VR_OPTION_GOD:
            VR_MenuPlaySound("items/r_item2.wav", 0.5);
            Cmd_ExecuteString("god", cmd_source_t::src_command);
            break;
        case VR_OPTION_NOCLIP:
            VR_MenuPlaySound("items/r_item2.wav", 0.5);
            Cmd_ExecuteString("noclip", cmd_source_t::src_command);
            break;
        case VR_OPTION_FLY:
            VR_MenuPlaySound("items/r_item2.wav", 0.5);
            Cmd_ExecuteString("fly", cmd_source_t::src_command);
            break;
    }

#undef _maxarray
#undef _sizeofarray
}

static void VR_MenuKey(int key)
{
    switch ( key ) {
        case K_ESCAPE:
            VID_SyncCvars(); // sync cvars before leaving menu. FIXME: there are other ways to leave menu
            S_LocalSound( "misc/menu1.wav" );
            M_Menu_Options_f();
            break;

        case K_UPARROW:
            S_LocalSound( "misc/menu1.wav" );
            vr_options_cursor--;
            if ( vr_options_cursor < 0 ) {
                vr_options_cursor = VR_OPTION_MAX - 1;
            }
            break;

        case K_DOWNARROW:
            S_LocalSound( "misc/menu1.wav" );
            vr_options_cursor++;
            if ( vr_options_cursor >= VR_OPTION_MAX ) {
                vr_options_cursor = 0;
            }
            break;

        case K_LEFTARROW:
            [[fallthrough]];
        case K_RIGHTARROW:
            S_LocalSound ("misc/menu3.wav");
            VR_MenuKeyOption( key, vr_options_cursor );
            break;

        case K_ENTER:
            m_entersound = true;
            VR_MenuKeyOption( key, vr_options_cursor );
            break;

        default: break;
    }
}

static void VR_MenuDraw (void)
{
    int y = 4;

    // plaque
    M_DrawTransPic (16, y, Draw_CachePic("gfx/qplaque.lmp"));

    // customize header
    qpic_t* p = Draw_CachePic ("gfx/ttl_cstm.lmp");
    M_DrawPic ( (320-p->width)/2, y, p);

    y += 28;

    // title
    const char* title = "VR/HMD OPTIONS";
    M_PrintWhite ((320-8*strlen(title))/2, y, title);

    y += 16;

	int i;
	for ( i = 0; i < VR_OPTION_MAX; i++ ) {
		switch ( i ) {
			case VR_OPTION_ENABLED:
				M_Print(16, y, "               VR Enabled" );
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_AIMMODE:
				M_Print(16, y, "                 Aim Mode" );
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_DEADZONE:
				M_Print(16, y, "                 Deadzone" );
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_CROSSHAIR:
				M_Print(16, y, "                Crosshair" );
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_CROSSHAIR_DEPTH:
				M_Print(16, y, "          Crosshair Depth" );
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_CROSSHAIR_SIZE:
				M_Print(16, y, "           Crosshair Size" );
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_CROSSHAIR_ALPHA:
				M_Print(16, y, "          Crosshair Alpha" );
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_WORLD_SCALE:
				M_Print(16, y, "              World Scale");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_MOVEMENT_MODE:
				M_Print(16, y, "            Movement mode");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_SNAP_TURN:
				M_Print(16, y, "                     Turn");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_TURN_SPEED:
				M_Print(16, y, "               Turn Speed");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_MSAA:
				M_Print(16, y, "                     MSAA");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_GUNANGLE:
				M_Print(16, y, "                Gun Angle");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_FLOOR_OFFSET:
				M_Print(16, y, "             Floor Offset");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_GUNMODELOFFSETS:
				M_Print(16, y, "        Gun Model Offsets");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_GUNMODELPITCH:
				M_Print(16, y, "          Gun Model Pitch");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_GUNMODELSCALE:
				M_Print(16, y, "          Gun Model Scale");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_GUNMODELY:
				M_Print(16, y, "              Gun Model Y");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_CROSSHAIRY:
				M_Print(16, y, "              Crosshair Y");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_PROJECTILESPAWN_Z_OFFSET:
				M_Print(16, y, "       Projectile Spawn Z");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_HUD_SCALE:
				M_Print(16, y, "                HUD Scale");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_MENU_SCALE:
				M_Print(16, y, "               Menu Scale");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_IMPULSE9:
				M_Print(16, y, "         Give all weapons");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_GOD:
				M_Print(16, y, "                 God Mode");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_NOCLIP:
				M_Print(16, y, "             No Clip Mode");
		        VR_MenuPrintOptionValue(240, y, i);
				break;
			case VR_OPTION_FLY:
				M_Print(16, y, "                 Fly Mode");
		        VR_MenuPrintOptionValue(240, y, i);
				break;

			default: break;
		}

		// draw the blinking cursor
		if ( vr_options_cursor == i ) {
			M_DrawCharacter( 220, y, 12 + ((int)(realtime*4)&1) );
		}

		y += 8;
	}

}

void VR_Menu_f (void)
{
    const char *sound = "items/r_item1.wav";

    IN_Deactivate(modestate == MS_WINDOWED);
    key_dest = key_menu;
    m_state = m_vr;
    m_entersound = true;

    VR_MenuPlaySound( sound, 0.5 );
}
