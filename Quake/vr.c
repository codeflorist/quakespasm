
#include "quakedef.h"
#include "vr.h"
#include "vr_menu.h"

#define UNICODE 1
#include <mmsystem.h>
#undef UNICODE

#include "openvr_c.h"

#if SDL_MAJOR_VERSION < 2
FILE *__iob_func() {
    FILE result[3] = { *stdin,*stdout,*stderr };
    return result;
}
#endif

extern void VID_Refocus();

typedef struct {
    GLuint framebuffer, depth_texture, texture;
    GLuint msaa_framebuffer, msaa_texture, msaa_depth_texture;
    int msaa;
    struct {
        float width, height;
    } size;
} fbo_t;

typedef struct {
    int index;
    fbo_t fbo;
    Hmd_Eye eye;
    HmdVector3_t position;
    HmdQuaternion_t orientation;
    float fov_x, fov_y;
} vr_eye_t;

typedef struct {
    VRControllerState_t state;
    VRControllerState_t lastState;
    vec3_t position;
    vec3_t orientation;
    HmdVector3_t rawvector;
    HmdQuaternion_t raworientation;
} vr_controller;

// OpenGL Extensions
#define GL_READ_FRAMEBUFFER_EXT 0x8CA8
#define GL_DRAW_FRAMEBUFFER_EXT 0x8CA9
#define GL_FRAMEBUFFER_SRGB_EXT 0x8DB9

typedef void (APIENTRYP PFNGLBLITFRAMEBUFFEREXTPROC) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
typedef BOOL(APIENTRYP PFNWGLSWAPINTERVALEXTPROC) (int);

static PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
static PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
static PFNGLBLITFRAMEBUFFEREXTPROC glBlitFramebufferEXT;
static PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
static PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
static PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
static PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisampleEXT;

struct {
    void *func; char *name;
} gl_extensions[] = {
    { &glBindFramebufferEXT, "glBindFramebufferEXT" },
    { &glBlitFramebufferEXT, "glBlitFramebufferEXT" },
    { &glDeleteFramebuffersEXT, "glDeleteFramebuffersEXT" },
    { &glGenFramebuffersEXT, "glGenFramebuffersEXT" },
    { &glTexImage2DMultisampleEXT, "glTexImage2DMultisample" },
    { &glFramebufferTexture2DEXT, "glFramebufferTexture2DEXT" },
    { &glFramebufferRenderbufferEXT, "glFramebufferRenderbufferEXT" },
    { &glCheckFramebufferStatusEXT, "glCheckFramebufferStatusEXT"},
    { &wglSwapIntervalEXT, "wglSwapIntervalEXT" },
{ NULL, NULL },
};

// main screen & 2D drawing
extern void SCR_SetUpToDrawConsole(void);
extern void SCR_UpdateScreenContent();
extern qboolean	scr_drawdialog;
extern void SCR_DrawNotifyString(void);
extern qboolean	scr_drawloading;
extern void SCR_DrawLoading(void);
extern void SCR_CheckDrawCenterString(void);
extern void SCR_DrawRam(void);
extern void SCR_DrawNet(void);
extern void SCR_DrawTurtle(void);
extern void SCR_DrawPause(void);
extern void SCR_DrawDevStats(void);
extern void SCR_DrawFPS(void);
extern void SCR_DrawClock(void);
extern void SCR_DrawConsole(void);

// rendering
extern void R_SetupView(void);
extern void R_RenderScene(void);
extern int glx, gly, glwidth, glheight;
extern refdef_t r_refdef;
extern vec3_t vright;

static float vrYaw;
static bool readbackYaw;

vec3_t vr_viewOffset;
vec3_t lastHudPosition{ 0.0, 0.0, 0.0 };
vec3_t lastMenuPosition{ 0.0, 0.0, 0.0 };

IVRSystem *ovrHMD;
TrackedDevicePose_t ovr_DevicePose[16]; //k_unMaxTrackedDeviceCount

static vr_eye_t eyes[2];
static vr_eye_t *current_eye = NULL;
static vr_controller controllers[2];
static vec3_t lastOrientation = { 0, 0, 0 };
static vec3_t lastAim = { 0, 0, 0 };

static qboolean vr_initialized = false;
static GLuint mirror_texture = 0;
static GLuint mirror_fbo = 0;
static int attempt_to_refocus_retry = 0;

static vec3_t headOrigin;
static vec3_t lastHeadOrigin;

vec3_t vr_room_scale_move;

// Wolfenstein 3D, DOOM and QUAKE use the same coordinate/unit system:
// 8 foot (96 inch) height wall == 64 units, 1.5 inches per pixel unit
// 1.0 pixel unit / 1.5 inch == 0.666666 pixel units per inch
#define meters_to_units (vr_world_scale.value / (1.5f * 0.0254f))

extern cvar_t gl_farclip;
extern int glwidth, glheight;
extern void SCR_UpdateScreenContent();
extern refdef_t r_refdef;

#define DEFINE_CVAR(name, defaultValue, type) \
    cvar_t name = { #name, #defaultValue, type }

DEFINE_CVAR(vr_enabled, 0, CVAR_NONE);
DEFINE_CVAR(vr_viewkick, 0, CVAR_NONE);
DEFINE_CVAR(vr_lefthanded, 0, CVAR_NONE);

DEFINE_CVAR(vr_crosshair, 1, CVAR_ARCHIVE);
DEFINE_CVAR(vr_crosshair_depth, 0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_crosshair_size, 3.0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_crosshair_alpha, 0.25, CVAR_ARCHIVE);
DEFINE_CVAR(vr_aimmode, 7, CVAR_ARCHIVE);
DEFINE_CVAR(vr_deadzone, 30, CVAR_ARCHIVE);
DEFINE_CVAR(vr_gunangle, 32, CVAR_ARCHIVE);
DEFINE_CVAR(vr_gunmodelpitch, 0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_gunmodelscale, 1.0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_gunmodely, 0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_projectilespawn_z_offset, 24, CVAR_ARCHIVE);
DEFINE_CVAR(vr_crosshairy, 0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_world_scale, 1.0, CVAR_ARCHIVE); 
DEFINE_CVAR(vr_floor_offset, -16, CVAR_ARCHIVE);
DEFINE_CVAR(vr_snap_turn, 0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_turn_speed, 1, CVAR_ARCHIVE);
DEFINE_CVAR(vr_msaa, 4, CVAR_ARCHIVE);
DEFINE_CVAR(vr_movement_mode, 0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_joystick_yaw_multi, 1.0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_joystick_axis_deadzone, 0.25, CVAR_ARCHIVE);
DEFINE_CVAR(vr_joystick_axis_menu_deadzone_extra, 0.25, CVAR_ARCHIVE);
DEFINE_CVAR(vr_joystick_axis_exponent, 1.0, CVAR_ARCHIVE);
DEFINE_CVAR(vr_joystick_deadzone_trunc, 1, CVAR_ARCHIVE);
DEFINE_CVAR(vr_hud_scale, 0.025, CVAR_ARCHIVE);
DEFINE_CVAR(vr_menu_scale, 0.13, CVAR_ARCHIVE);

static qboolean InitOpenGLExtensions()
{
    int i;
    static qboolean extensions_initialized;

    if (extensions_initialized)
        return true;

    for (i = 0; gl_extensions[i].func; i++) {
        void *func = SDL_GL_GetProcAddress(gl_extensions[i].name);
        if (!func)
            return false;

        *((void **)gl_extensions[i].func) = func;
    }

    extensions_initialized = true;
    return extensions_initialized;
}

void RecreateTextures(fbo_t* fbo, int width, int height)
{
    GLuint oldDepth = fbo->depth_texture;
    GLuint oldTexture = fbo->texture;

    glGenTextures(1, &fbo->depth_texture);
    glGenTextures(1, &fbo->texture);

    if (oldDepth)
    {
        glDeleteTextures(1, &oldDepth);
        glDeleteTextures(1, &oldTexture);
    }

    glBindTexture(GL_TEXTURE_2D, fbo->depth_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

    glBindTexture(GL_TEXTURE_2D, fbo->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    fbo->size.width = width;
    fbo->size.height = height;

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo->framebuffer);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, fbo->texture, 0);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, fbo->depth_texture, 0);
}


fbo_t CreateFBO(int width, int height) {
    fbo_t fbo;
    int swap_chain_length = 0;

    glGenFramebuffersEXT(1, &fbo.framebuffer);

    fbo.depth_texture = 0;

    RecreateTextures(&fbo, width, height);

    fbo.msaa = 0;
    fbo.msaa_framebuffer = 0;
    fbo.msaa_texture = 0;

    return fbo;
}

void CreateMSAA(fbo_t* fbo, int width, int height, int msaa)
{
    fbo->msaa = msaa;

    if (fbo->msaa_framebuffer)
    {
        glDeleteFramebuffersEXT(1, &fbo->msaa_framebuffer);
        glDeleteTextures(1, &fbo->msaa_texture);
        glDeleteTextures(1, &fbo->msaa_depth_texture);
    }

    glGenFramebuffersEXT(1, &fbo->msaa_framebuffer);
    glGenTextures(1, &fbo->msaa_texture);
    glGenTextures(1, &fbo->msaa_depth_texture);

    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, fbo->msaa_texture);
    glTexImage2DMultisampleEXT(GL_TEXTURE_2D_MULTISAMPLE, msaa, GL_RGBA8, width, height, false);

    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, fbo->msaa_depth_texture);
    glTexImage2DMultisampleEXT(GL_TEXTURE_2D_MULTISAMPLE, msaa, GL_DEPTH_COMPONENT24, width, height, false);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo->msaa_framebuffer);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D_MULTISAMPLE, fbo->msaa_texture, 0);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D_MULTISAMPLE, fbo->msaa_depth_texture, 0);

    GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        Con_Printf("Framebuffer incomplete %x", status);
    }
}

void DeleteFBO(fbo_t fbo) {
    glDeleteFramebuffersEXT(1, &fbo.framebuffer);
    glDeleteTextures(1, &fbo.depth_texture);
    glDeleteTextures(1, &fbo.texture);
}

void QuatToYawPitchRoll(HmdQuaternion_t q, vec3_t out) {
    auto sqw = q.w*q.w;
    auto sqx = q.x*q.x;
    auto sqy = q.y*q.y;
    auto sqz = q.z*q.z;

    out[ROLL] = -atan2(2 * (q.x*q.y + q.w*q.z), sqw - sqx + sqy - sqz) / M_PI_DIV_180;
    out[PITCH] = -asin(-2 * (q.y*q.z - q.w*q.x)) / M_PI_DIV_180;
    out[YAW] = atan2(2 * (q.x*q.z + q.w*q.y), sqw - sqx - sqy + sqz) / M_PI_DIV_180 + vrYaw;
}

void Vec3RotateZ(vec3_t in, float angle, vec3_t out) {
    out[0] = in[0] * cos(angle) - in[1] * sin(angle);
    out[1] = in[0] * sin(angle) + in[1] * cos(angle);
    out[2] = in[2];
}

HmdMatrix44_t TransposeMatrix(HmdMatrix44_t in) {
    HmdMatrix44_t out;
    int y, x;
    for (y = 0; y < 4; y++)
        for (x = 0; x < 4; x++)
            out.m[x][y] = in.m[y][x];

    return out;
}

HmdVector3_t AddVectors(HmdVector3_t a, HmdVector3_t b)
{
    HmdVector3_t out;

    out.v[0] = a.v[0] + b.v[0];
    out.v[1] = a.v[1] + b.v[1];
    out.v[2] = a.v[2] + b.v[2];

    return out;
}

// Rotates a vector by a quaternion and returns the results
// Based on math from https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
HmdVector3_t RotateVectorByQuaternion(HmdVector3_t v, HmdQuaternion_t q)
{
    HmdVector3_t u, result;
    u.v[0] = q.x;
    u.v[1] = q.y;
    u.v[2] = q.z;
    float s = q.w;

    // Dot products of u,v and u,u
    float uvDot = (u.v[0] * v.v[0] + u.v[1] * v.v[1] + u.v[2] * v.v[2]);
    float uuDot = (u.v[0] * u.v[0] + u.v[1] * u.v[1] + u.v[2] * u.v[2]);

    // Calculate cross product of u, v
    HmdVector3_t uvCross;
    uvCross.v[0] = u.v[1] * v.v[2] - u.v[2] * v.v[1];
    uvCross.v[1] = u.v[2] * v.v[0] - u.v[0] * v.v[2];
    uvCross.v[2] = u.v[0] * v.v[1] - u.v[1] * v.v[0];

    // Calculate each vectors' result individually because there aren't arthimetic functions for HmdVector3_t dsahfkldhsaklfhklsadh
    result.v[0] = u.v[0] * 2.0f * uvDot
        + (s*s - uuDot) * v.v[0]
        + 2.0f * s * uvCross.v[0];
    result.v[1] = u.v[1] * 2.0f * uvDot
        + (s*s - uuDot) * v.v[1]
        + 2.0f * s * uvCross.v[1];
    result.v[2] = u.v[2] * 2.0f * uvDot
        + (s*s - uuDot) * v.v[2]
        + 2.0f * s * uvCross.v[2];

    return result;
}

// Transforms a HMD Matrix34 to a Vector3
// Math borrowed from https://github.com/Omnifinity/OpenVR-Tracking-Example
HmdVector3_t Matrix34ToVector(HmdMatrix34_t in)
{
    HmdVector3_t vector;

    vector.v[0] = in.m[0][3];
    vector.v[1] = in.m[1][3];
    vector.v[2] = in.m[2][3];

    return vector;
}

// Transforms a HMD Matrix34 to a Quaternion
// Function logic nicked from https://github.com/Omnifinity/OpenVR-Tracking-Example
HmdQuaternion_t Matrix34ToQuaternion(HmdMatrix34_t in)
{
    HmdQuaternion_t q;

    q.w = sqrt(fmax(0, 1.0 + in.m[0][0] + in.m[1][1] + in.m[2][2])) / 2.0;
    q.x = sqrt(fmax(0, 1.0 + in.m[0][0] - in.m[1][1] - in.m[2][2])) / 2.0;
    q.y = sqrt(fmax(0, 1.0 - in.m[0][0] + in.m[1][1] - in.m[2][2])) / 2.0;
    q.z = sqrt(fmax(0, 1.0 - in.m[0][0] - in.m[1][1] + in.m[2][2])) / 2.0;
    q.x = copysign(q.x, static_cast<double>(in.m[2][1]) - static_cast<double>(in.m[1][2]));
    q.y = copysign(q.y, static_cast<double>(in.m[0][2]) - static_cast<double>(in.m[2][0]));
    q.z = copysign(q.z, static_cast<double>(in.m[1][0]) - static_cast<double>(in.m[0][1]));
    return q;
}

void HmdVec3RotateY(HmdVector3_t* pos, float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    float x = c * pos->v[0] - s * pos->v[2];
    float y = s * pos->v[0] + c * pos->v[2];

    pos->v[0] = x;
    pos->v[2] = y;
}

// ----------------------------------------------------------------------------
// Callbacks for cvars

static void VR_Enabled_f(cvar_t *var)
{
    VID_VR_Disable();

    if (!vr_enabled.value)
        return;

    if (!VR_Enable())
        Cvar_SetValueQuick(&vr_enabled, 0);
}



static void VR_Deadzone_f(cvar_t *var)
{
    // clamp the mouse to a max of 0 - 70 degrees
    float deadzone = CLAMP(0.0f, vr_deadzone.value, 70.0f);
    if (deadzone != vr_deadzone.value)
        Cvar_SetValueQuick(&vr_deadzone, deadzone);
}

//Weapon scale/position stuff
cvar_t vr_weapon_offset[MAX_WEAPONS * VARS_PER_WEAPON];

aliashdr_t* lastWeaponHeader;
int weaponCVarEntry;

void Mod_Weapon(const char* name, aliashdr_t* hdr)
{
    if (lastWeaponHeader != hdr)
    {
        lastWeaponHeader = hdr;
        weaponCVarEntry = -1;
        for (int i = 0; i < MAX_WEAPONS; i++)
        {
            if (!strcmp(vr_weapon_offset[i*VARS_PER_WEAPON + 4].string, name))
            {
                weaponCVarEntry = i;
                break;
            }
        }
        if (weaponCVarEntry == -1)
        {
            Con_Printf("No VR offset for weapon: %s\n", name);
        }
    }

    if (weaponCVarEntry != -1)
    {
        float scaleCorrect = (vr_world_scale.value / 0.75f) * vr_gunmodelscale.value; //initial version had 0.75 default world scale, so weapons reflect that
        VectorScale(hdr->original_scale, vr_weapon_offset[weaponCVarEntry * VARS_PER_WEAPON + 3].value * scaleCorrect, hdr->scale);

        vec3_t ofs = {
            vr_weapon_offset[weaponCVarEntry * VARS_PER_WEAPON].value,
            vr_weapon_offset[weaponCVarEntry * VARS_PER_WEAPON + 1].value,
            vr_weapon_offset[weaponCVarEntry * VARS_PER_WEAPON + 2].value + vr_gunmodely.value
        };

        VectorAdd(hdr->original_scale_origin, ofs, hdr->scale_origin);
        VectorScale(hdr->scale_origin, scaleCorrect, hdr->scale_origin);
    }
}

char* CopyWithNumeral(const char* str, int i)
{
    int len = strlen(str);
    char* ret = (char*) malloc(len + 1);
    strcpy(ret, str);
    ret[len - 1] = '0' + (i % 10);
    ret[len - 2] = '0' + (i / 10);
    return ret;
}

void InitWeaponCVar(cvar_t* cvar, const char* name, int i, const char* value)
{
    const char* cvarname = CopyWithNumeral(name, i + 1);
    if (!Cvar_FindVar(cvarname))
    {
        cvar->name = cvarname;
        cvar->string = value;
        cvar->flags = CVAR_NONE;
        Cvar_RegisterVariable(cvar);
    }
    else
    {
        Cvar_SetQuick(cvar, value);
    }
}

void InitWeaponCVars(int i, const char* id, const char* offsetX, const char* offsetY, const char* offsetZ, const char* scale)
{
    const char* nameOffsetX = "vr_wofs_x_nn";
    const char* nameOffsetY = "vr_wofs_y_nn";
    const char* nameOffsetZ = "vr_wofs_z_nn";
    const char* nameScale = "vr_wofs_scale_nn";
    const char* nameID = "vr_wofs_id_nn";
    InitWeaponCVar(&vr_weapon_offset[i * VARS_PER_WEAPON], nameOffsetX, i, offsetX);
    InitWeaponCVar(&vr_weapon_offset[i * VARS_PER_WEAPON + 1], nameOffsetY, i, offsetY);
    InitWeaponCVar(&vr_weapon_offset[i * VARS_PER_WEAPON + 2], nameOffsetZ, i, offsetZ);
    InitWeaponCVar(&vr_weapon_offset[i * VARS_PER_WEAPON + 3], nameScale, i, scale);
    InitWeaponCVar(&vr_weapon_offset[i * VARS_PER_WEAPON + 4], nameID, i, id);
}

void InitAllWeaponCVars()
{
    int i = 0;
    if (!strcmp(COM_SkipPath(com_gamedir), "ad"))
    {	//weapons for Arcane Dimensions mod; initially made for v1.70 + patch1
        InitWeaponCVars(i++, "progs/v_shadaxe0.mdl", "-1.5", "43.1", "41", "0.25"); //shadow axe
        InitWeaponCVars(i++, "progs/v_shadaxe3.mdl", "-1.5", "43.1", "41", "0.25"); //shadow axe upgrade, same numbers
        InitWeaponCVars(i++, "progs/v_shot.mdl", "1.5", "1.7", "17.5", "0.33"); //shotgun
        InitWeaponCVars(i++, "progs/v_shot2.mdl", "-3.5", "0.4", "8.5", "0.8"); //double barrel shotgun
        InitWeaponCVars(i++, "progs/v_shot3.mdl", "-3.5", "0.4", "8.5", "0.8"); //triple barrel shotgun ("Widowmaker")
        InitWeaponCVars(i++, "progs/v_nail.mdl", "-9.5", "3", "17", "0.5"); //nailgun
        InitWeaponCVars(i++, "progs/v_nail2.mdl", "-6", "3.5", "20", "0.4"); //supernailgun
        InitWeaponCVars(i++, "progs/v_rock.mdl", "-3", "1.25", "17", "0.5"); //grenade
        InitWeaponCVars(i++, "progs/v_rock2.mdl", "0", "5.55", "22.5", "0.45"); //rocket
        InitWeaponCVars(i++, "progs/v_light.mdl", "-4", "3.1", "13", "0.5"); //lightning
        InitWeaponCVars(i++, "progs/v_plasma.mdl", "2.8", "1.8", "22.5", "0.5"); //plasma
    }
    else
    {	//weapons for vanilla Quake, Scourge of Armagon, Dissolution of Eternity
        //vanilla quake weapons
        InitWeaponCVars(i++, "progs/v_axe.mdl", "-4", "24", "37", "0.33");
        InitWeaponCVars(i++, "progs/v_shot.mdl", "1.5", "1", "10", "0.5"); //gun
        InitWeaponCVars(i++, "progs/v_shot2.mdl", "-3.5", "1", "8.5", "0.8"); //shotgun
        InitWeaponCVars(i++, "progs/v_nail.mdl", "-5", "3", "15", "0.5"); //nailgun
        InitWeaponCVars(i++, "progs/v_nail2.mdl", "0", "3", "19", "0.5"); //supernailgun
        InitWeaponCVars(i++, "progs/v_rock.mdl", "10", "1.5", "13", "0.5"); //grenade
        InitWeaponCVars(i++, "progs/v_rock2.mdl", "10", "7", "19", "0.5"); //rocket
        InitWeaponCVars(i++, "progs/v_light.mdl", "3", "4", "13", "0.5"); //lightning
        //hipnotic weapons
        InitWeaponCVars(i++, "progs/v_hammer.mdl", "-4", "18", "37", "0.33"); //mjolnir hammer
        InitWeaponCVars(i++, "progs/v_laserg.mdl", "65", "3.7", "17", "0.33"); //laser
        InitWeaponCVars(i++, "progs/v_prox.mdl", "10", "1.5", "13", "0.5"); //proximity - same as grenade
        //rogue weapons
        InitWeaponCVars(i++, "progs/v_lava.mdl", "-5", "3", "15", "0.5"); //lava nailgun - same as nailgun
        InitWeaponCVars(i++, "progs/v_lava2.mdl", "0", "3", "19", "0.5"); //lava supernailgun - same as supernailgun
        InitWeaponCVars(i++, "progs/v_multi.mdl", "10", "1.5", "13", "0.5"); //multigrenade - same as grenade
        InitWeaponCVars(i++, "progs/v_multi2.mdl", "10", "7", "19", "0.5"); //multirocket - same as rocket
        InitWeaponCVars(i++, "progs/v_plasma.mdl", "3", "4", "13", "0.5"); //plasma - same as lightning
    }

    while (i < MAX_WEAPONS)
    {
        InitWeaponCVars(i++, "-1", "1.5", "1", "10", "0.5");
    }
}

// ----------------------------------------------------------------------------
// Public vars and functions

void VID_VR_Init()
{
    // This is only called once at game start
    Cvar_RegisterVariable(&vr_enabled);
    Cvar_SetCallback(&vr_enabled, VR_Enabled_f);
    Cvar_RegisterVariable(&vr_aimmode);
    Cvar_RegisterVariable(&vr_crosshair_alpha);
    Cvar_RegisterVariable(&vr_crosshair_depth);
    Cvar_RegisterVariable(&vr_crosshair_size);
    Cvar_RegisterVariable(&vr_crosshair);
    Cvar_RegisterVariable(&vr_deadzone);
    Cvar_RegisterVariable(&vr_floor_offset);
    Cvar_RegisterVariable(&vr_gunangle);
    Cvar_RegisterVariable(&vr_gunmodelpitch);
    Cvar_RegisterVariable(&vr_gunmodelscale);
    Cvar_RegisterVariable(&vr_gunmodely);
    Cvar_RegisterVariable(&vr_crosshairy);
    Cvar_RegisterVariable(&vr_joystick_axis_deadzone);
    Cvar_RegisterVariable(&vr_joystick_axis_exponent);
    Cvar_RegisterVariable(&vr_joystick_deadzone_trunc);
    Cvar_RegisterVariable(&vr_joystick_yaw_multi);
    Cvar_RegisterVariable(&vr_joystick_axis_menu_deadzone_extra);
    Cvar_RegisterVariable(&vr_lefthanded);
    Cvar_RegisterVariable(&vr_movement_mode);
    Cvar_RegisterVariable(&vr_msaa);
    Cvar_RegisterVariable(&vr_snap_turn);
    Cvar_RegisterVariable(&vr_turn_speed);
    Cvar_RegisterVariable(&vr_world_scale);
    Cvar_RegisterVariable(&vr_projectilespawn_z_offset);
    Cvar_RegisterVariable(&vr_hud_scale);
    Cvar_RegisterVariable(&vr_menu_scale);
    Cvar_SetCallback(&vr_deadzone, VR_Deadzone_f);

    InitAllWeaponCVars();

    // Sickness stuff
    Cvar_RegisterVariable(&vr_viewkick);

    VR_Menu_Init();

    // Set the cvar if invoked from a command line parameter
    {
        //int i = COM_CheckParm("-vr");
        //if (i && i < com_argc - 1) {
        Cvar_SetQuick(&vr_enabled, "1");
        //}
    }
}

void VR_InitGame()
{
    InitAllWeaponCVars();
}

qboolean VR_Enable()
{
    EVRInitError eInit = VRInitError_None;
    ovrHMD = VR_Init(&eInit, VRApplication_Scene);

    if (eInit != VRInitError_None) {
        Con_Printf("%s\nFailed to Initialize Steam VR", VR_GetVRInitErrorAsEnglishDescription(eInit));
        return false;
    }

    if (!InitOpenGLExtensions()) {
        Con_Printf("Failed to initialize OpenGL extensions");
        return false;
    }

    eyes[0].eye = Eye_Left;
    eyes[1].eye = Eye_Right;

    for (int i = 0; i < 2; i++) {
        uint32_t vrwidth, vrheight;
        float LeftTan, RightTan, UpTan, DownTan;

        IVRSystem_GetRecommendedRenderTargetSize(ovrHMD, &vrwidth, &vrheight);
        IVRSystem_GetProjectionRaw(ovrHMD, eyes[i].eye, &LeftTan, &RightTan, &UpTan, &DownTan);

        eyes[i].index = i;
        eyes[i].fbo = CreateFBO(vrwidth, vrheight);
        eyes[i].fov_x = (atan(-LeftTan) + atan(RightTan)) / M_PI_DIV_180;
        eyes[i].fov_y = (atan(-UpTan) + atan(DownTan)) / M_PI_DIV_180;
    }

    VR_SetTrackingSpace(TrackingUniverseStanding);    // Put us into standing tracking position
    VR_ResetOrientation();     // Recenter the HMD

    wglSwapIntervalEXT(0); // Disable V-Sync

    Cbuf_AddText("exec vr_autoexec.cfg\n"); // Load the vr autosec config file incase the user has settings they want

    attempt_to_refocus_retry = 900; // Try to refocus our for the first 900 frames :/
    vr_initialized = true;
    return true;
}


void VR_PushYaw()
{
    readbackYaw = 1;
}

void VID_VR_Shutdown() {
    VID_VR_Disable();
}

void VID_VR_Disable()
{
    if (!vr_initialized)
        return;

    VR_Shutdown();
    ovrHMD = NULL;

    // Reset the view height
    cl.viewheight = DEFAULT_VIEWHEIGHT;

    // TODO: Cleanup frame buffers

    vr_initialized = false;
}

static void RenderScreenForCurrentEye_OVR()
{
    // Remember the current glwidht/height; we have to modify it here for each eye
    int oldglheight = glheight;
    int oldglwidth = glwidth;

    IVRSystem_GetRecommendedRenderTargetSize(ovrHMD, reinterpret_cast<uint32_t*>(&glwidth), reinterpret_cast<uint32_t*>(&glheight));

    bool newTextures = glwidth != current_eye->fbo.size.width || glheight != current_eye->fbo.size.height;
    if (newTextures)
    {
        RecreateTextures(&current_eye->fbo, glwidth, glheight);
    }

    if (newTextures || vr_msaa.value != current_eye->fbo.msaa)
    {
        CreateMSAA(&current_eye->fbo, glwidth, glheight, vr_msaa.value);
    }

    // Set up current FBO
    if (current_eye->fbo.msaa > 0)
    {
        glEnable(GL_MULTISAMPLE);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, current_eye->fbo.msaa_framebuffer);
    }
    else
    {
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, current_eye->fbo.framebuffer);
    }

    glViewport(0, 0, current_eye->fbo.size.width, current_eye->fbo.size.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw everything
    srand((int)(cl.time * 1000)); //sync random stuff between eyes

    r_refdef.fov_x = current_eye->fov_x;
    r_refdef.fov_y = current_eye->fov_y;

    SCR_UpdateScreenContent();

    // Generate the eye texture and send it to the HMD

    if (current_eye->fbo.msaa > 0)
    {
        glDisable(GL_MULTISAMPLE);
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER, current_eye->fbo.framebuffer);
        glBindFramebufferEXT(GL_READ_FRAMEBUFFER, current_eye->fbo.msaa_framebuffer);
        glDrawBuffer(GL_BACK);
        glBlitFramebufferEXT(0, 0, glwidth, glheight, 0, 0, glwidth, glheight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

    Texture_t eyeTexture = { (void*)current_eye->fbo.texture, TextureType_OpenGL, ColorSpace_Gamma };
    IVRCompositor_Submit(VRCompositor(), current_eye->eye, &eyeTexture);

    // Reset
    glwidth = oldglwidth;
    glheight = oldglheight;

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void SetHandPos(int index, entity_t *player)
{
    vec3_t headLocalPreRot;
    _VectorSubtract(controllers[index].position, headOrigin, headLocalPreRot);
    vec3_t headLocal;
    Vec3RotateZ(headLocalPreRot, vrYaw * M_PI_DIV_180, headLocal);
    _VectorAdd(headLocal, headOrigin, headLocal);

    cl.handpos[index][0] = -headLocal[0] + player->origin[0];
    cl.handpos[index][1] = -headLocal[1] + player->origin[1];
    cl.handpos[index][2] = headLocal[2] + player->origin[2] + vr_floor_offset.value;
}

void IdentifyAxes(int device);

void VR_UpdateScreenContent()
{
    int i;
    vec3_t orientation;
    GLint w, h;

    // Last chance to enable VR Mode - we get here when the game already start up with vr_enabled 1
    // If enabling fails, unset the cvar and return.
    if (!vr_initialized && !VR_Enable())
    {
        Cvar_Set("vr_enabled", "0");
        return;
    }

    w = glwidth;
    h = glheight;

    entity_t *player = &cl_entities[cl.viewentity];

    // Update poses
    IVRCompositor_WaitGetPoses(VRCompositor(), ovr_DevicePose, k_unMaxTrackedDeviceCount, NULL, 0);

    // Get the VR devices' orientation and position
    for (int iDevice = 0; iDevice < k_unMaxTrackedDeviceCount; iDevice++)
    {
        // HMD vectors update
        if (ovr_DevicePose[iDevice].bPoseIsValid && IVRSystem_GetTrackedDeviceClass(ovrHMD, iDevice) == TrackedDeviceClass_HMD)
        {
            HmdVector3_t headPos = Matrix34ToVector(ovr_DevicePose->mDeviceToAbsoluteTracking);
            headOrigin[0] = headPos.v[2];
            headOrigin[1] = headPos.v[0];
            headOrigin[2] = headPos.v[1];

            vec3_t moveInTracking;
            _VectorSubtract(headOrigin, lastHeadOrigin, moveInTracking);
            moveInTracking[0] *= -meters_to_units;
            moveInTracking[1] *= -meters_to_units;
            moveInTracking[2] = 0;
            Vec3RotateZ(moveInTracking, vrYaw * M_PI_DIV_180, vr_room_scale_move);

            _VectorCopy(headOrigin, lastHeadOrigin);
            _VectorSubtract(headOrigin, lastHeadOrigin, headOrigin);
            headPos.v[0] -= lastHeadOrigin[1];
            headPos.v[2] -= lastHeadOrigin[0];

            HmdQuaternion_t headQuat = Matrix34ToQuaternion(ovr_DevicePose->mDeviceToAbsoluteTracking);
            HmdVector3_t leyePos = Matrix34ToVector(IVRSystem_GetEyeToHeadTransform(ovrHMD, eyes[0].eye));
            HmdVector3_t reyePos = Matrix34ToVector(IVRSystem_GetEyeToHeadTransform(ovrHMD, eyes[1].eye));

            leyePos = RotateVectorByQuaternion(leyePos, headQuat);
            reyePos = RotateVectorByQuaternion(reyePos, headQuat);

            HmdVec3RotateY(&headPos, -vrYaw * M_PI_DIV_180);

            HmdVec3RotateY(&leyePos, -vrYaw * M_PI_DIV_180);
            HmdVec3RotateY(&reyePos, -vrYaw * M_PI_DIV_180);

            eyes[0].position = AddVectors(headPos, leyePos);
            eyes[1].position = AddVectors(headPos, reyePos);
            eyes[0].orientation = headQuat;
            eyes[1].orientation = headQuat;
        }
        // Controller vectors update
        else if (ovr_DevicePose[iDevice].bPoseIsValid && IVRSystem_GetTrackedDeviceClass(ovrHMD, iDevice) == TrackedDeviceClass_Controller)
        {
            HmdVector3_t rawControllerPos = Matrix34ToVector(ovr_DevicePose[iDevice].mDeviceToAbsoluteTracking);
            HmdQuaternion_t rawControllerQuat = Matrix34ToQuaternion(ovr_DevicePose[iDevice].mDeviceToAbsoluteTracking);

            int controllerIndex = -1;

            if (IVRSystem_GetControllerRoleForTrackedDeviceIndex(ovrHMD, iDevice) == TrackedControllerRole_LeftHand)
            {
                // Swap controller values for our southpaw players
                controllerIndex = vr_lefthanded.value ? 1 : 0;
            }
            else if (IVRSystem_GetControllerRoleForTrackedDeviceIndex(ovrHMD, iDevice) == TrackedControllerRole_RightHand)
            {
                // Swap controller values for our southpaw players
                controllerIndex = vr_lefthanded.value ? 0 : 1;
            }

            if (controllerIndex != -1)
            {
                vr_controller* controller = &controllers[controllerIndex];

                IdentifyAxes(iDevice);

                controller->lastState = controller->state;
                IVRSystem_GetControllerState(VRSystem(), iDevice, &controller->state);
                controller->rawvector = rawControllerPos;
                controller->raworientation = rawControllerQuat;
                controller->position[0] = (rawControllerPos.v[2] - lastHeadOrigin[0]) * meters_to_units;
                controller->position[1] = (rawControllerPos.v[0] - lastHeadOrigin[1]) * meters_to_units;
                controller->position[2] = (rawControllerPos.v[1]) * meters_to_units;
                QuatToYawPitchRoll(rawControllerQuat, controller->orientation);
            }
        }
    }

    // Reset the aim roll value before calculation, incase the user switches aimmode from 7 to another.
    cl.aimangles[ROLL] = 0.0;

    QuatToYawPitchRoll(eyes[1].orientation, orientation);
    if (readbackYaw)
    {
        vrYaw = cl.viewangles[YAW] - (orientation[YAW] - vrYaw);
        readbackYaw = 0;
    }

    switch ((int)vr_aimmode.value)
    {
        // 1: (Default) Head Aiming; View YAW is mouse+head, PITCH is head
    default:
    case VR_AIMMODE_HEAD_MYAW:
        cl.viewangles[PITCH] = cl.aimangles[PITCH] = orientation[PITCH];
        cl.aimangles[YAW] = cl.viewangles[YAW] = cl.aimangles[YAW] + orientation[YAW] - lastOrientation[YAW];
        break;

        // 2: Head Aiming; View YAW and PITCH is mouse+head (this is stupid)
    case VR_AIMMODE_HEAD_MYAW_MPITCH:
        cl.viewangles[PITCH] = cl.aimangles[PITCH] = cl.aimangles[PITCH] + orientation[PITCH] - lastOrientation[PITCH];
        cl.aimangles[YAW] = cl.viewangles[YAW] = cl.aimangles[YAW] + orientation[YAW] - lastOrientation[YAW];
        break;

        // 3: Mouse Aiming; View YAW is mouse+head, PITCH is head
    case VR_AIMMODE_MOUSE_MYAW:
        cl.viewangles[PITCH] = orientation[PITCH];
        cl.viewangles[YAW] = cl.aimangles[YAW] + orientation[YAW];
        break;

        // 4: Mouse Aiming; View YAW and PITCH is mouse+head
    case VR_AIMMODE_MOUSE_MYAW_MPITCH:
        cl.viewangles[PITCH] = cl.aimangles[PITCH] + orientation[PITCH];
        cl.viewangles[YAW] = cl.aimangles[YAW] + orientation[YAW];
        break;

    case VR_AIMMODE_BLENDED:
    case VR_AIMMODE_BLENDED_NOPITCH:
    {
        float diffHMDYaw = orientation[YAW] - lastOrientation[YAW];
        float diffHMDPitch = orientation[PITCH] - lastOrientation[PITCH];
        float diffAimYaw = cl.aimangles[YAW] - lastAim[YAW];
        float diffYaw;

        // find new view position based on orientation delta
        cl.viewangles[YAW] += diffHMDYaw;

        // find difference between view and aim yaw
        diffYaw = cl.viewangles[YAW] - cl.aimangles[YAW];

        if (fabs(diffYaw) > vr_deadzone.value / 2.0f)
        {
            // apply the difference from each set of angles to the other
            cl.aimangles[YAW] += diffHMDYaw;
            cl.viewangles[YAW] += diffAimYaw;
        }
        if ((int)vr_aimmode.value == VR_AIMMODE_BLENDED) {
            cl.aimangles[PITCH] += diffHMDPitch;
        }
        cl.viewangles[PITCH] = orientation[PITCH];
    }
    break;

    // 7: Controller Aiming;
    case VR_AIMMODE_CONTROLLER:
        cl.viewangles[PITCH] = orientation[PITCH];
        cl.viewangles[YAW] = orientation[YAW];

        vec3_t contMat[3], gunMat[3];
        CreateRotMat(0, vr_gunangle.value, gunMat);

        for (int i = 0; i < 2; i++)
        {
            RotMatFromAngleVector(controllers[i].orientation, contMat);

            vec3_t mat[3];
            R_ConcatRotations(gunMat, contMat, mat);

            AngleVectorFromRotMat(mat, cl.handrot[i]);
        }

        if (cl.viewent.model)
        {
            aliashdr_t* hdr = (aliashdr_t *)Mod_Extradata(cl.viewent.model);
            Mod_Weapon(cl.viewent.model->name, hdr);
        }

        SetHandPos(0, player);
        SetHandPos(1, player);

        VectorCopy(cl.handrot[1], cl.aimangles); // Sets the shooting angle
        // TODO: what sets the shooting origin?

        break;
    }
    cl.viewangles[ROLL] = orientation[ROLL];

    VectorCopy(orientation, lastOrientation);
    VectorCopy(cl.aimangles, lastAim);

    VectorCopy(cl.viewangles, r_refdef.viewangles);
    VectorCopy(cl.aimangles, r_refdef.aimangles);

    // Render the scene for each eye into their FBOs
    for (i = 0; i < 2; i++) {
        current_eye = &eyes[i];

        vec3_t temp, orientation;

        // We need to scale the view offset position to quake units and rotate it by the current input angles (viewangle - eye orientation)
        QuatToYawPitchRoll(current_eye->orientation, orientation);
        temp[0] = -current_eye->position.v[2] * meters_to_units; // X
        temp[1] = -current_eye->position.v[0] * meters_to_units; // Y
        temp[2] = current_eye->position.v[1] * meters_to_units;  // Z
        Vec3RotateZ(temp, (r_refdef.viewangles[YAW] - orientation[YAW])*M_PI_DIV_180, vr_viewOffset);
        vr_viewOffset[2] += vr_floor_offset.value;

        RenderScreenForCurrentEye_OVR();
    }

    // Blit mirror texture to backbuffer
    glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, eyes[0].fbo.framebuffer);
    glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
    glBlitFramebufferEXT(0, eyes[0].fbo.size.width, eyes[0].fbo.size.height, 0, 0, h, w, 0, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, 0);
}

void VR_SetMatrices() {
    HmdMatrix44_t projection;

    // Calculate HMD projection matrix and view offset position
    projection = TransposeMatrix(IVRSystem_GetProjectionMatrix(ovrHMD, current_eye->eye, 4.f, gl_farclip.value));

    // Set OpenGL projection and view matrices
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((GLfloat*)projection.m);
}


void VR_AddOrientationToViewAngles(vec3_t angles)
{
    vec3_t orientation;
    QuatToYawPitchRoll(current_eye->orientation, orientation);

    angles[PITCH] = angles[PITCH] + orientation[PITCH];
    angles[YAW] = angles[YAW] + orientation[YAW];
    angles[ROLL] = orientation[ROLL];
}

void VR_ShowCrosshair()
{
    vec3_t forward, up, right;
    vec3_t start, end, impact;
    float size, alpha;

    if ((sv_player && (int)(sv_player->v.weapon) == IT_AXE))
        return;

    size = CLAMP(0.0, vr_crosshair_size.value, 32.0);
    alpha = CLAMP(0.0, vr_crosshair_alpha.value, 1.0);

    if (size <= 0 || alpha <= 0)
        return;

    // setup gl
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    GL_PolygonOffset(OFFSET_SHOWTRIS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);

    // calc the line and draw
    // TODO: Make the laser align correctly
    if (vr_aimmode.value == VR_AIMMODE_CONTROLLER)
    {
        VectorCopy(cl.handpos[1], start);

        vec3_t ofs = {
            vr_weapon_offset[weaponCVarEntry * VARS_PER_WEAPON].value,
            vr_weapon_offset[weaponCVarEntry * VARS_PER_WEAPON + 1].value,
            vr_weapon_offset[weaponCVarEntry * VARS_PER_WEAPON + 2].value + vr_gunmodely.value
        };

        AngleVectors(cl.handrot[1], forward, right, up);
        vec3_t fwd2; VectorCopy(forward, fwd2);
        fwd2[0] *= vr_gunmodelscale.value * ofs[2];
        fwd2[1] *= vr_gunmodelscale.value * ofs[2];
        fwd2[2] *= vr_gunmodelscale.value * ofs[2];
        VectorAdd(start, fwd2, start);
    }
    else
    {
        VectorCopy(cl.viewent.origin, start);
        start[2] -= cl.viewheight - 10;
        AngleVectors(cl.aimangles, forward, right, up);
    }


    switch ((int)vr_crosshair.value)
    {
    default:
    case VR_CROSSHAIR_POINT:
        if (vr_crosshair_depth.value <= 0) {
            // trace to first wall
            VectorMA(start, 4096, forward, end);

            end[2] += vr_crosshairy.value;
            TraceLine(start, end, impact);
        }
        else {
            // fix crosshair to specific depth
            VectorMA(start, vr_crosshair_depth.value * meters_to_units, forward, impact);
        }

        glEnable(GL_POINT_SMOOTH);
        glColor4f(1, 0, 0, alpha);
        glPointSize(size * glwidth / vid.width);

        glBegin(GL_POINTS);
        glVertex3f(impact[0], impact[1], impact[2]);
        glEnd();
        glDisable(GL_POINT_SMOOTH);
        break;

    case VR_CROSSHAIR_LINE:
        // trace to first entity
        VectorMA(start, 4096, forward, end);
        TraceLineToEntity(start, end, impact, sv_player);

        glColor4f(1, 0, 0, alpha);
        glLineWidth(size * glwidth / vid.width);
        glBegin(GL_LINES);
        impact[2] += vr_crosshairy.value * 10.f;
        glVertex3f(start[0], start[1], start[2]);
        glVertex3f(impact[0], impact[1], impact[2]);
        glEnd();
        break;
    }

    // cleanup gl
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    GL_PolygonOffset(OFFSET_NONE);
    glEnable(GL_DEPTH_TEST);
}


double lerp(double a, double b, double f)
{
    return (a * (1.0 - f)) + (b * f);
}

void vec3lerp(vec3_t out, vec3_t start, vec3_t end, double f)
{
    out[0] = lerp(start[0], end[0], f);
    out[1] = lerp(start[1], end[1], f);
    out[2] = lerp(start[2], end[2], f);
}

void VR_Draw2D()
{
    qboolean draw_sbar = false;
    vec3_t menu_angles, forward, right, up, target;
    float scale_hud = vr_menu_scale.value;

    int oldglwidth = glwidth,
        oldglheight = glheight,
        oldconwidth = vid.conwidth,
        oldconheight = vid.conheight;

    glwidth = 320;
    glheight = 200;

    vid.conwidth = 320;
    vid.conheight = 200;

    // draw 2d elements 1m from the users face, centered
    glPushMatrix();
    glDisable(GL_DEPTH_TEST); // prevents drawing sprites on sprites from interferring with one another
    glEnable(GL_BLEND);

    if (vr_aimmode.value == VR_AIMMODE_CONTROLLER)
    {
        AngleVectors(cl.handrot[1], forward, right, up);

        VectorCopy(cl.handrot[1], menu_angles);

        AngleVectors(menu_angles, forward, right, up);

        VectorMA(cl.handpos[1], 48, forward, target);
    }
    else
    {
        // TODO: Make the menus' position sperate from the right hand. Centered on last view dir?
        VectorCopy(r_refdef.aimangles, menu_angles)

            if (vr_aimmode.value == VR_AIMMODE_HEAD_MYAW || vr_aimmode.value == VR_AIMMODE_HEAD_MYAW_MPITCH)
                menu_angles[PITCH] = 0;

        AngleVectors(menu_angles, forward, right, up);

        VectorMA(r_refdef.vieworg, 48, forward, target);
    }

    vec3_t smoothedTarget;
    vec3lerp(smoothedTarget, lastMenuPosition, target, 0.03);
    VectorCopy(smoothedTarget, lastMenuPosition);

    glTranslatef(smoothedTarget[0], smoothedTarget[1], smoothedTarget[2]);

    glRotatef(menu_angles[YAW] - 90, 0, 0, 1); // rotate around z
    glRotatef(90 + menu_angles[PITCH], -1, 0, 0); // keep bar at constant angled pitch towards user
    glTranslatef(-(320.0 * scale_hud / 2), -(200.0 * scale_hud / 2), 0); // center the status bar
    glScalef(scale_hud, scale_hud, scale_hud);


    if (scr_drawdialog) //new game confirm
    {
        if (con_forcedup)
            Draw_ConsoleBackground();
        else
            draw_sbar = true; //Sbar_Draw ();
        Draw_FadeScreen();
        SCR_DrawNotifyString();
    }
    else if (scr_drawloading) //loading
    {
        SCR_DrawLoading();
        draw_sbar = true; //Sbar_Draw ();
    }
    else if (cl.intermission == 1 && key_dest == key_game) //end of level
    {
        Sbar_IntermissionOverlay();
    }
    else if (cl.intermission == 2 && key_dest == key_game) //end of episode
    {
        Sbar_FinaleOverlay();
        SCR_CheckDrawCenterString();
    }
    else
    {
        //SCR_DrawCrosshair (); //johnfitz
        SCR_DrawRam();
        SCR_DrawNet();
        SCR_DrawTurtle();
        SCR_DrawPause();
        SCR_CheckDrawCenterString();
        draw_sbar = true; //Sbar_Draw ();
        SCR_DrawDevStats(); //johnfitz
        SCR_DrawFPS(); //johnfitz
        SCR_DrawClock(); //johnfitz
        SCR_DrawConsole();
        M_Draw();
    }

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();

    if (draw_sbar)
        VR_DrawSbar();

    glwidth = oldglwidth;
    glheight = oldglheight;
    vid.conwidth = oldconwidth;
    vid.conheight = oldconheight;
}


void VR_DrawSbar()
{
    vec3_t sbar_angles, forward, right, up, target;
    float scale_hud = vr_hud_scale.value;

    glPushMatrix();
    glDisable(GL_DEPTH_TEST); // prevents drawing sprites on sprites from interferring with one another

    if (vr_aimmode.value == VR_AIMMODE_CONTROLLER)
    {
        AngleVectors(cl.handrot[1], forward, right, up);

        VectorCopy(cl.handrot[1], sbar_angles)

            AngleVectors(sbar_angles, forward, right, up);

        VectorMA(cl.handpos[1], -5, right, target);
    }
    else
    {
        VectorCopy(cl.aimangles, sbar_angles)

            if (vr_aimmode.value == VR_AIMMODE_HEAD_MYAW || vr_aimmode.value == VR_AIMMODE_HEAD_MYAW_MPITCH)
                sbar_angles[PITCH] = 0;

        AngleVectors(sbar_angles, forward, right, up);

        VectorMA(cl.viewent.origin, 1.0, forward, target);
    }

    vec3_t smoothedTarget;
    vec3lerp(smoothedTarget, lastHudPosition, target, 1.0);
    VectorCopy(smoothedTarget, lastHudPosition);

    glTranslatef(smoothedTarget[0], smoothedTarget[1], smoothedTarget[2]);

    glRotatef(sbar_angles[YAW] - 90, 0, 0, 1); // rotate around z
    glRotatef(90 + 45 + sbar_angles[PITCH], -1, 0, 0); // keep bar at constant angled pitch towards user
    glTranslatef(-(320.0 * scale_hud / 2), 0, 0); // center the status bar
    glTranslatef(0, 0, 10); // move hud down a bit
    glScalef(scale_hud, scale_hud, scale_hud);

    Sbar_Draw();

    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void VR_SetAngles(vec3_t angles)
{
    VectorCopy(angles, cl.aimangles);
    VectorCopy(angles, cl.viewangles);
    VectorCopy(angles, lastAim);
}

void VR_ResetOrientation()
{
    cl.aimangles[YAW] = cl.viewangles[YAW];
    cl.aimangles[PITCH] = cl.viewangles[PITCH];
    if (vr_enabled.value) {
        //IVRSystem_ResetSeatedZeroPose(ovrHMD);
        VectorCopy(cl.aimangles, lastAim);
    }
}

void VR_SetTrackingSpace(int n)
{
    if (n >= 0 || n < 3)
        IVRCompositor_SetTrackingSpace(VRCompositor(), (ETrackingUniverseOrigin) n);
}

int axisTrackpad = -1;
int axisJoystick = -1;
int axisTrigger = -1;
bool identified = false;

void IdentifyAxes(int device)
{
    if (identified)
        return;

    for (int i = 0; i < k_unControllerStateAxisCount; i++)
    {
        switch (IVRSystem_GetInt32TrackedDeviceProperty(VRSystem(), device, (ETrackedDeviceProperty) (Prop_Axis0Type_Int32 + i), nullptr))
        {
        case k_eControllerAxis_TrackPad:
            if (axisTrackpad == -1) axisTrackpad = i;
            break;
        case k_eControllerAxis_Joystick:
            if (axisJoystick == -1) axisJoystick = i;
            break;
        case k_eControllerAxis_Trigger:
            if (axisTrigger == -1) axisTrigger = i;
            break;
        }
    }

    identified = true;
}

float GetAxis(VRControllerState_t* state, int axis, double deadzoneExtra)
{
    float v = 0;

    if (axis == 0)
    {
        if (axisTrackpad != -1) v += state->rAxis[axisTrackpad].x;
        if (axisJoystick != -1) v += state->rAxis[axisJoystick].x;
    }
    else
    {
        if (axisTrackpad != -1) v += state->rAxis[axisTrackpad].y;
        if (axisJoystick != -1) v += state->rAxis[axisJoystick].y;
    }

    int sign = (v > 0) - (v < 0);
    v = fabsf(v);

    if (v < vr_joystick_axis_deadzone.value + deadzoneExtra)
    {
        return 0.0f;
    }

    if (vr_joystick_deadzone_trunc.value == 0)
    {
        v = (v - vr_joystick_axis_deadzone.value) / (1 - vr_joystick_axis_deadzone.value);
    }

    if (vr_joystick_axis_exponent.value >= 0)
    {
        v = powf(v, vr_joystick_axis_exponent.value);
    }

    return sign * v;
}

void DoKey(vr_controller* controller, EVRButtonId vrButton, int quakeKey)
{
    bool wasDown = (controller->lastState.ulButtonPressed & ButtonMaskFromId(vrButton)) != 0;
    bool isDown = (controller->state.ulButtonPressed & ButtonMaskFromId(vrButton)) != 0;
    if (isDown != wasDown)
    {
        Key_Event(quakeKey, isDown);
    }
}

void DoTrigger(vr_controller* controller, int quakeKey)
{
    if (axisTrigger != -1)
    {
        bool triggerWasDown = controller->lastState.rAxis[axisTrigger].x > 0.5f;
        bool triggerDown = controller->state.rAxis[axisTrigger].x > 0.5f;
        if (triggerDown != triggerWasDown)
        {
            Key_Event(quakeKey, triggerDown);
        }
    }
}

void DoAxis(vr_controller* controller, int axis, int quakeKeyNeg, int quakeKeyPos, double deadzoneExtra)
{
    float lastVal = GetAxis(&controller->lastState, axis, deadzoneExtra);
    float val = GetAxis(&controller->state, axis, deadzoneExtra);

    bool posWasDown = lastVal > 0.0f;
    bool posDown = val > 0.0f;
    if (posDown != posWasDown)
    {
        Key_Event(quakeKeyPos, posDown);
    }

    bool negWasDown = lastVal < 0.0f;
    bool negDown = val < 0.0f;
    if (negDown != negWasDown)
    {
        Key_Event(quakeKeyNeg, negDown);
    }
}

void VR_Move(usercmd_t *cmd)
{
    if (!vr_enabled.value)
        return;

    DoTrigger(&controllers[0], K_SPACE);

    DoKey(&controllers[0], k_EButton_Grip, K_MWHEELUP);
    DoKey(&controllers[1], k_EButton_Grip, K_MWHEELDOWN);

    DoKey(&controllers[0], k_EButton_SteamVR_Touchpad, K_SHIFT);
    DoKey(&controllers[1], k_EButton_SteamVR_Touchpad, K_ALT);

    DoKey(&controllers[0], k_EButton_ApplicationMenu, '1');
    DoKey(&controllers[0], k_EButton_A, '2');
    DoKey(&controllers[1], k_EButton_A, '3');

    DoKey(&controllers[1], k_EButton_ApplicationMenu, K_ESCAPE);
    if (key_dest == key_menu)
    {
        for (int i = 0; i < 2; i++)
        {
            DoAxis(&controllers[i], 0, K_LEFTARROW, K_RIGHTARROW, vr_joystick_axis_menu_deadzone_extra.value);
            DoAxis(&controllers[i], 1, K_DOWNARROW, K_UPARROW, vr_joystick_axis_menu_deadzone_extra.value);
            DoTrigger(&controllers[i], K_ENTER);
        }
    }
    else
    {
        DoTrigger(&controllers[1], K_MOUSE1);

        vec3_t lfwd, lright, lup;
        AngleVectors(cl.handrot[0], lfwd, lright, lup);

        if (vr_movement_mode.value == VR_MOVEMENT_MODE_RAW_INPUT)
        {
            cmd->forwardmove += cl_forwardspeed.value * GetAxis(&controllers[0].state, 1, 0.0);
            cmd->sidemove += cl_forwardspeed.value * GetAxis(&controllers[0].state, 0, 0.0);
        }
        else
        {
            vec3_t vfwd, vright, vup;
            vec3_t playerYawOnly = { 0, sv_player->v.v_angle[YAW], 0 };

            AngleVectors(playerYawOnly, vfwd, vright, vup);

            //avoid gimbal by using up if we are point up/down
            if (fabsf(lfwd[2]) > 0.8f)
            {
                if (lfwd[2] < -0.8f)
                {
                    lfwd[0] *= -1; lfwd[1] *= -1;	lfwd[2] *= -1;
                }
                else
                {
                    lup[0] *= -1; lup[1] *= -1;	lup[2] *= -1;
                }

                VectorSwap(lup, lfwd);
            }

            //Scale up directions so tilting doesn't affect speed
            float fac = 1.0f / lup[2];
            for (int i = 0; i < 3; i++)
            {
                lfwd[i] *= fac;
                lright[i] *= fac;
            }

            vec3_t move = { 0, 0, 0 };
            VectorMA(move, GetAxis(&controllers[0].state, 1, 0.0), lfwd, move);
            VectorMA(move, GetAxis(&controllers[0].state, 0, 0.0), lright, move);

            float fwd = DotProduct(move, vfwd);
            float right = DotProduct(move, vright);

            //Quake run doesn't affect the value of cl_sidespeed.value, so just use forward speed here for consistency
            cmd->forwardmove += cl_forwardspeed.value * fwd;
            cmd->sidemove += cl_forwardspeed.value * right;
        }

        AngleVectors(cl.handrot[0], lfwd, lright, lup);
        cmd->upmove += cl_upspeed.value * GetAxis(&controllers[0].state, 1, 0.0) * lfwd[2];

        if (cl_forwardspeed.value > 200 && cl_movespeedkey.value)
            cmd->forwardmove /= cl_movespeedkey.value;
        if ((cl_forwardspeed.value > 200) ^ (in_speed.state & 1))
        {
            cmd->forwardmove *= cl_movespeedkey.value;
            cmd->sidemove *= cl_movespeedkey.value;
            cmd->upmove *= cl_movespeedkey.value;
        }

        float yawMove = GetAxis(&controllers[1].state, 0, 0.0);

        if (vr_snap_turn.value != 0)
        {
            static int lastSnap = 0;
            int snap = yawMove > 0.0f ? 1 : yawMove < 0.0f ? -1 : 0;
            if (snap != lastSnap)
            {
                vrYaw -= snap * vr_snap_turn.value;
                lastSnap = snap;
            }
        }
        else
        {
            vrYaw -= (yawMove * host_frametime * 100.0f * vr_joystick_yaw_multi.value) * vr_turn_speed.value;
        }
    }
}