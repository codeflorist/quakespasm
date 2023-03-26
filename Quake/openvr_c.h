#include <stdbool.h>
#include <stdint.h>

extern "C" {

#define VR_INTERFACE
#define VR_CALLTYPE

typedef void* glSharedTextureHandle_t;
typedef int32_t glInt_t;
typedef uint32_t glUInt_t;
struct HmdMatrix34_t
{
	float m[3][4];
};
typedef struct HmdMatrix34_t HmdMatrix34_t;

struct HmdMatrix44_t
{
	float m[4][4];
};
typedef struct HmdMatrix44_t HmdMatrix44_t;

struct HmdVector3_t
{
	float v[3];
};
typedef struct HmdVector3_t HmdVector3_t;

struct HmdVector4_t
{
	float v[4];
};
typedef struct HmdVector4_t HmdVector4_t;

struct HmdVector3d_t
{
	double v[3];
};
typedef struct HmdVector3d_t HmdVector3d_t;

struct HmdVector2_t
{
	float v[2];
};
typedef struct HmdVector2_t HmdVector2_t;

struct HmdQuaternion_t
{
	double w, x, y, z;
};
typedef struct HmdQuaternion_t HmdQuaternion_t;

struct HmdColor_t
{
	float r, g, b, a;
};
typedef struct HmdColor_t HmdColor_t;

struct HmdQuad_t
{
	HmdVector3_t vCorners[ 4 ];
};
typedef struct HmdQuad_t HmdQuad_t;

struct HmdRect2_t
{
	HmdVector2_t vTopLeft;
	HmdVector2_t vBottomRight;
};
typedef struct HmdRect2_t HmdRect2_t;

struct DistortionCoordinates_t
{
	float rfRed[2];
	float rfGreen[2];
	float rfBlue[2];
};
typedef struct DistortionCoordinates_t DistortionCoordinates_t;

enum EVREye
{
	Eye_Left = 0,
	Eye_Right = 1
};
typedef enum EVREye EVREye;

enum ETextureType
{
    TextureType_DirectX = 0, // Handle is an ID3D11Texture
    TextureType_OpenGL = 1,  // Handle is an OpenGL texture name or an OpenGL render buffer name, depending on submit flags
    TextureType_Vulkan = 2, // Handle is a pointer to a VRVulkanTextureData_t structure
    TextureType_IOSurface = 3, // Handle is a macOS cross-process-sharable IOSurface
    TextureType_DirectX12 = 4, // Handle is a pointer to a D3D12TextureData_t structure
};
typedef enum ETextureType ETextureType;

// ETextureType is the new EGraphicsAPIConvention
/*enum EGraphicsAPIConvention
{
	API_DirectX = 0, // Normalized Z goes from 0 at the viewer to 1 at the far clip plane
	API_OpenGL = 1,  // Normalized Z goes from 1 at the viewer to -1 at the far clip plane
};
typedef enum EGraphicsAPIConvention EGraphicsAPIConvention;*/

enum EColorSpace
{
	ColorSpace_Auto = 0,	// Assumes 'gamma' for 8-bit per component formats, otherwise 'linear'.  This mirrors the DXGI formats which have _SRGB variants.
	ColorSpace_Gamma = 1,	// Texture data can be displayed directly on the display without any conversion (a.k.a. display native format).
	ColorSpace_Linear = 2,	// Same as gamma but has been converted to a linear representation using DXGI's sRGB conversion algorithm.
};
typedef enum EColorSpace EColorSpace;

struct Texture_t
{
	void* handle; // Native d3d texture pointer or GL texture id.
    ETextureType eType;
	EColorSpace eColorSpace;
};
typedef struct Texture_t Texture_t;

enum ETrackingResult
{
	TrackingResult_Uninitialized			= 1,

	TrackingResult_Calibrating_InProgress	= 100,
	TrackingResult_Calibrating_OutOfRange	= 101,

	TrackingResult_Running_OK				= 200,
	TrackingResult_Running_OutOfRange		= 201,
};
typedef enum ETrackingResult ETrackingResult;

static const uint32_t k_unTrackingStringSize = 32;
static const uint32_t k_unMaxDriverDebugResponseSize = 32768;
typedef uint32_t TrackedDeviceIndex_t;
static const uint32_t k_unTrackedDeviceIndex_Hmd = 0;
static const uint32_t k_unMaxTrackedDeviceCount = 16;
static const uint32_t k_unTrackedDeviceIndexInvalid = 0xFFFFFFFF;
enum ETrackedDeviceClass
{
	TrackedDeviceClass_Invalid = 0,				// the ID was not valid.
	TrackedDeviceClass_HMD = 1,					// Head-Mounted Displays
	TrackedDeviceClass_Controller = 2,			// Tracked controllers
	TrackedDeviceClass_TrackingReference = 4,	// Camera and base stations that serve as tracking reference points

	TrackedDeviceClass_Other = 1000,
};
typedef enum ETrackedDeviceClass ETrackedDeviceClass;

enum ETrackedControllerRole
{
	TrackedControllerRole_Invalid = 0,					// Invalid value for controller type
	TrackedControllerRole_LeftHand = 1,					// Tracked device associated with the left hand
	TrackedControllerRole_RightHand = 2,				// Tracked device associated with the right hand
};
typedef enum ETrackedControllerRole ETrackedControllerRole;

struct TrackedDevicePose_t
{
	HmdMatrix34_t mDeviceToAbsoluteTracking;
	HmdVector3_t vVelocity;				// velocity in tracker space in m/s
	HmdVector3_t vAngularVelocity;		// angular velocity in radians/s (?)
	ETrackingResult eTrackingResult;
	bool bPoseIsValid;

	// This indicates that there is a device connected for this spot in the pose array.
	// It could go from true to false if the user unplugs the device.
	bool bDeviceIsConnected;
};
typedef struct TrackedDevicePose_t TrackedDevicePose_t;

enum ETrackingUniverseOrigin
{
	TrackingUniverseSeated = 0,		// Poses are provided relative to the seated zero pose
	TrackingUniverseStanding = 1,	// Poses are provided relative to the safe bounds configured by the user
	TrackingUniverseRawAndUncalibrated = 2,	// Poses are provided in the coordinate system defined by the driver. You probably don't want this one.
};
typedef enum ETrackingUniverseOrigin ETrackingUniverseOrigin;

enum ETrackedDeviceProperty
{
	// general properties that apply to all device classes
	Prop_TrackingSystemName_String				= 1000,
	Prop_ModelNumber_String						= 1001,
	Prop_SerialNumber_String					= 1002,
	Prop_RenderModelName_String					= 1003,
	Prop_WillDriftInYaw_Bool					= 1004,
	Prop_ManufacturerName_String				= 1005,
	Prop_TrackingFirmwareVersion_String			= 1006,
	Prop_HardwareRevision_String				= 1007,
	Prop_AllWirelessDongleDescriptions_String	= 1008,
	Prop_ConnectedWirelessDongle_String			= 1009,
	Prop_DeviceIsWireless_Bool					= 1010,
	Prop_DeviceIsCharging_Bool					= 1011,
	Prop_DeviceBatteryPercentage_Float			= 1012, // 0 is empty, 1 is full
	Prop_StatusDisplayTransform_Matrix34		= 1013,
	Prop_Firmware_UpdateAvailable_Bool			= 1014,
	Prop_Firmware_ManualUpdate_Bool				= 1015,
	Prop_Firmware_ManualUpdateURL_String		= 1016,
	Prop_HardwareRevision_Uint64				= 1017,
	Prop_FirmwareVersion_Uint64					= 1018,
	Prop_FPGAVersion_Uint64						= 1019,
	Prop_VRCVersion_Uint64						= 1020,
	Prop_RadioVersion_Uint64					= 1021,
	Prop_DongleVersion_Uint64					= 1022,
	Prop_BlockServerShutdown_Bool				= 1023,
	Prop_CanUnifyCoordinateSystemWithHmd_Bool	= 1024,
	Prop_ContainsProximitySensor_Bool			= 1025,
	Prop_DeviceProvidesBatteryStatus_Bool		= 1026,
	Prop_DeviceCanPowerOff_Bool					= 1027,
	Prop_Firmware_ProgrammingTarget_String		= 1028,
	Prop_DeviceClass_Int32						= 1029,
	Prop_HasCamera_Bool							= 1030,

	// Properties that are unique to TrackedDeviceClass_HMD
	Prop_ReportsTimeSinceVSync_Bool				= 2000,
	Prop_SecondsFromVsyncToPhotons_Float		= 2001,
	Prop_DisplayFrequency_Float					= 2002,
	Prop_UserIpdMeters_Float					= 2003,
	Prop_CurrentUniverseId_Uint64				= 2004, 
	Prop_PreviousUniverseId_Uint64				= 2005, 
	Prop_DisplayFirmwareVersion_Uint64			= 2006,
	Prop_IsOnDesktop_Bool						= 2007,
	Prop_DisplayMCType_Int32					= 2008,
	Prop_DisplayMCOffset_Float					= 2009,
	Prop_DisplayMCScale_Float					= 2010,
	Prop_EdidVendorID_Int32						= 2011,
	Prop_DisplayMCImageLeft_String              = 2012,
	Prop_DisplayMCImageRight_String             = 2013,
	Prop_DisplayGCBlackClamp_Float				= 2014,
	Prop_EdidProductID_Int32					= 2015,
	Prop_CameraToHeadTransform_Matrix34			= 2016,
	Prop_DisplayGCType_Int32					= 2017,
	Prop_DisplayGCOffset_Float					= 2018,
	Prop_DisplayGCScale_Float					= 2019,
	Prop_DisplayGCPrescale_Float				= 2020,
	Prop_DisplayGCImage_String					= 2021,
	Prop_LensCenterLeftU_Float					= 2022,
	Prop_LensCenterLeftV_Float					= 2023,
	Prop_LensCenterRightU_Float					= 2024,
	Prop_LensCenterRightV_Float					= 2025,
	Prop_UserHeadToEyeDepthMeters_Float			= 2026,
	Prop_CameraFirmwareVersion_Uint64			= 2027,
	Prop_CameraFirmwareDescription_String		= 2028,
	Prop_DisplayFPGAVersion_Uint64				= 2029,
	Prop_DisplayBootloaderVersion_Uint64		= 2030,
	Prop_DisplayHardwareVersion_Uint64			= 2031,
	Prop_AudioFirmwareVersion_Uint64			= 2032,
	Prop_CameraCompatibilityMode_Int32			= 2033,

	// Properties that are unique to TrackedDeviceClass_Controller
	Prop_AttachedDeviceId_String				= 3000,
	Prop_SupportedButtons_Uint64				= 3001,
	Prop_Axis0Type_Int32						= 3002, // Return value is of type EVRControllerAxisType
	Prop_Axis1Type_Int32						= 3003, // Return value is of type EVRControllerAxisType
	Prop_Axis2Type_Int32						= 3004, // Return value is of type EVRControllerAxisType
	Prop_Axis3Type_Int32						= 3005, // Return value is of type EVRControllerAxisType
	Prop_Axis4Type_Int32						= 3006, // Return value is of type EVRControllerAxisType

	// Properties that are unique to TrackedDeviceClass_TrackingReference
	Prop_FieldOfViewLeftDegrees_Float			= 4000,
	Prop_FieldOfViewRightDegrees_Float			= 4001,
	Prop_FieldOfViewTopDegrees_Float			= 4002,
	Prop_FieldOfViewBottomDegrees_Float			= 4003,
	Prop_TrackingRangeMinimumMeters_Float		= 4004,
	Prop_TrackingRangeMaximumMeters_Float		= 4005,
	Prop_ModeLabel_String						= 4006,

	// Vendors are free to expose private debug data in this reserved region
	Prop_VendorSpecific_Reserved_Start			= 10000,
	Prop_VendorSpecific_Reserved_End			= 10999,
};
typedef enum ETrackedDeviceProperty ETrackedDeviceProperty;

static const uint32_t k_unMaxPropertyStringSize = 32 * 1024;
enum ETrackedPropertyError
{
	TrackedProp_Success						= 0,
	TrackedProp_WrongDataType				= 1,
	TrackedProp_WrongDeviceClass			= 2,
	TrackedProp_BufferTooSmall				= 3,
	TrackedProp_UnknownProperty				= 4,
	TrackedProp_InvalidDevice				= 5,
	TrackedProp_CouldNotContactServer		= 6,
	TrackedProp_ValueNotProvidedByDevice	= 7,
	TrackedProp_StringExceedsMaximumLength	= 8,
	TrackedProp_NotYetAvailable				= 9, // The property value isn't known yet, but is expected soon. Call again later.
};
typedef enum ETrackedPropertyError ETrackedPropertyError;

struct VRTextureBounds_t
{
	float uMin, vMin;
	float uMax, vMax;
};
typedef struct VRTextureBounds_t VRTextureBounds_t;

enum EVRSubmitFlags
{
	// Simple render path. App submits rendered left and right eye images with no lens distortion correction applied.
	Submit_Default = 0x00,

	// App submits final left and right eye images with lens distortion already applied (lens distortion makes the images appear
	// barrel distorted with chromatic aberration correction applied). The app would have used the data returned by
	// vr::IVRSystem::ComputeDistortion() to apply the correct distortion to the rendered images before calling Submit().
	Submit_LensDistortionAlreadyApplied = 0x01,

	// If the texture pointer passed in is actually a renderbuffer (e.g. for MSAA in OpenGL) then set this flag.
	Submit_GlRenderBuffer = 0x02
};
typedef enum EVRSubmitFlags EVRSubmitFlags;

enum EVRState
{
	VRState_Undefined = -1,
	VRState_Off = 0,
	VRState_Searching = 1,
	VRState_Searching_Alert = 2,
	VRState_Ready = 3,
	VRState_Ready_Alert = 4,
	VRState_NotReady = 5,
};
typedef enum EVRState EVRState;

enum EVREventType
{
	VREvent_None = 0,

	VREvent_TrackedDeviceActivated		= 100,
	VREvent_TrackedDeviceDeactivated	= 101,
	VREvent_TrackedDeviceUpdated		= 102,
	VREvent_TrackedDeviceUserInteractionStarted		= 103,
	VREvent_TrackedDeviceUserInteractionEnded	= 104,
	VREvent_IpdChanged					= 105,
	VREvent_EnterStandbyMode			= 106,
	VREvent_LeaveStandbyMode			= 107,
	VREvent_TrackedDeviceRoleChanged	= 108,

	VREvent_ButtonPress					= 200, // data is controller
	VREvent_ButtonUnpress				= 201, // data is controller
	VREvent_ButtonTouch					= 202, // data is controller
	VREvent_ButtonUntouch				= 203, // data is controller

	VREvent_MouseMove					= 300, // data is mouse
	VREvent_MouseButtonDown				= 301, // data is mouse
	VREvent_MouseButtonUp				= 302, // data is mouse
	VREvent_FocusEnter					= 303, // data is overlay
	VREvent_FocusLeave					= 304, // data is overlay
	VREvent_Scroll						= 305, // data is mouse
	VREvent_TouchPadMove				= 306, // data is mouse

	VREvent_InputFocusCaptured			= 400, // data is process
	VREvent_InputFocusReleased			= 401, // data is process
	VREvent_SceneFocusLost				= 402, // data is process
	VREvent_SceneFocusGained			= 403, // data is process
	VREvent_SceneApplicationChanged		= 404, // data is process - The App actually drawing the scene changed (usually to or from the compositor)
	VREvent_SceneFocusChanged			= 405, // data is process - New app got access to draw the scene

	VREvent_HideRenderModels			= 410, // Sent to the scene application to request hiding render models temporarily
	VREvent_ShowRenderModels			= 411, // Sent to the scene application to request restoring render model visibility

	VREvent_OverlayShown				= 500,
	VREvent_OverlayHidden				= 501,
	VREvent_DashboardActivated		= 502,
	VREvent_DashboardDeactivated	= 503,
	VREvent_DashboardThumbSelected	= 504, // Sent to the overlay manager - data is overlay
	VREvent_DashboardRequested		= 505, // Sent to the overlay manager - data is overlay
	VREvent_ResetDashboard			= 506, // Send to the overlay manager
	VREvent_RenderToast				= 507, // Send to the dashboard to render a toast - data is the notification ID
	VREvent_ImageLoaded				= 508, // Sent to overlays when a SetOverlayRaw or SetOverlayFromFile call finishes loading
	VREvent_ShowKeyboard = 509, // Sent to keyboard renderer in the dashboard to invoke it
	VREvent_HideKeyboard = 510, // Sent to keyboard renderer in the dashboard to hide it
	VREvent_OverlayGamepadFocusGained		= 511, // Sent to an overlay when IVROverlay::SetFocusOverlay is called on it
	VREvent_OverlayGamepadFocusLost = 512, // Send to an overlay when it previously had focus and IVROverlay::SetFocusOverlay is called on something else
	VREvent_OverlaySharedTextureChanged = 513,

	VREvent_Notification_Shown				= 600,
	VREvent_Notification_Hidden				= 601,
	VREvent_Notification_BeginInteraction	= 602,
	VREvent_Notification_Destroyed			= 603,

	VREvent_Quit						= 700, // data is process
	VREvent_ProcessQuit					= 701, // data is process
	VREvent_QuitAborted_UserPrompt		= 702, // data is process
	VREvent_QuitAcknowledged			= 703, // data is process

	VREvent_ChaperoneDataHasChanged		= 800,
	VREvent_ChaperoneUniverseHasChanged	= 801,
	VREvent_ChaperoneTempDataHasChanged = 802,
	VREvent_ChaperoneSettingsHaveChanged = 803,
	VREvent_SeatedZeroPoseReset			= 804,

	VREvent_BackgroundSettingHasChanged	= 850,
	VREvent_CameraSettingsHaveChanged	= 851,

	VREvent_StatusUpdate				= 900,

	VREvent_MCImageUpdated				= 1000,

	VREvent_FirmwareUpdateStarted	= 1100,
	VREvent_FirmwareUpdateFinished	= 1101,

	VREvent_KeyboardClosed				= 1200,
	VREvent_KeyboardCharInput			= 1201,
	VREvent_KeyboardDone				= 1202, // Sent when DONE button clicked on keyboard

	VREvent_ApplicationTransitionStarted	= 1300,
	VREvent_ApplicationTransitionAborted	= 1301,
	VREvent_ApplicationTransitionNewAppStarted = 1302,

	VREvent_Compositor_MirrorWindowShown	= 1400,
	VREvent_Compositor_MirrorWindowHidden	= 1401,
	VREvent_Compositor_ChaperoneBoundsShown = 1410,
	VREvent_Compositor_ChaperoneBoundsHidden = 1411,

	VREvent_TrackedCamera_StartVideoStream  = 1500,
	VREvent_TrackedCamera_StopVideoStream   = 1501,
	VREvent_TrackedCamera_PauseVideoStream  = 1502,
	VREvent_TrackedCamera_ResumeVideoStream = 1503,

	VREvent_PerformanceTest_EnableCapture = 1600,
	VREvent_PerformanceTest_DisableCapture = 1601,
	VREvent_PerformanceTest_FidelityLevel = 1602,
	
	// Vendors are free to expose private events in this reserved region
	VREvent_VendorSpecific_Reserved_Start = 10000,
	VREvent_VendorSpecific_Reserved_End = 19999,
};
typedef enum EVREventType EVREventType;

enum EDeviceActivityLevel
{
	k_EDeviceActivityLevel_Unknown = -1,
	k_EDeviceActivityLevel_Idle = 0,
	k_EDeviceActivityLevel_UserInteraction = 1,
	k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
	k_EDeviceActivityLevel_Standby = 3,
};
typedef enum EDeviceActivityLevel EDeviceActivityLevel;

enum EVRButtonId
{
	k_EButton_System			= 0,
	k_EButton_ApplicationMenu	= 1,
	k_EButton_Grip				= 2,
	k_EButton_DPad_Left			= 3,
	k_EButton_DPad_Up			= 4,
	k_EButton_DPad_Right		= 5,
	k_EButton_DPad_Down			= 6,
	k_EButton_A					= 7,

	k_EButton_Axis0				= 32,
	k_EButton_Axis1				= 33,
	k_EButton_Axis2				= 34,
	k_EButton_Axis3				= 35,
	k_EButton_Axis4				= 36,

	// aliases for well known controllers
	k_EButton_SteamVR_Touchpad	= k_EButton_Axis0,
	k_EButton_SteamVR_Trigger	= k_EButton_Axis1,

	k_EButton_Dashboard_Back	= k_EButton_Grip,

	k_EButton_Max				= 64
};
typedef enum EVRButtonId EVRButtonId;

uint64_t ButtonMaskFromId(EVRButtonId id);
struct VREvent_Controller_t
{
	uint32_t button; // EVRButtonId enum
};
typedef struct VREvent_Controller_t VREvent_Controller_t;

enum EVRMouseButton
{
	VRMouseButton_Left					= 0x0001,
	VRMouseButton_Right					= 0x0002,
	VRMouseButton_Middle				= 0x0004,
};
typedef enum EVRMouseButton EVRMouseButton;

struct VREvent_Mouse_t
{
	float x, y; // co-ords are in GL space, bottom left of the texture is 0,0
	uint32_t button; // EVRMouseButton enum
};
typedef struct VREvent_Mouse_t VREvent_Mouse_t;

struct VREvent_Scroll_t
{
	float xdelta, ydelta; // movement in fraction of the pad traversed since last delta, 1.0 for a full swipe
	uint32_t repeatCount;
};
typedef struct VREvent_Scroll_t VREvent_Scroll_t;

struct VREvent_TouchPadMove_t
{
	// true if the users finger is detected on the touch pad
	bool bFingerDown;

	// How long the finger has been down in seconds
	float flSecondsFingerDown;

	// These values indicate the starting finger position (so you can do some basic swipe stuff)
	float fValueXFirst;
	float fValueYFirst;

	// This is the raw sampled coordinate without deadzoning
	float fValueXRaw;
	float fValueYRaw;
};
typedef struct VREvent_TouchPadMove_t VREvent_TouchPadMove_t;

struct VREvent_Notification_t
{
	uint64_t ulUserValue;
	uint32_t notificationId;
};
typedef struct VREvent_Notification_t VREvent_Notification_t;

struct VREvent_Process_t
{
	uint32_t pid;
	uint32_t oldPid;
	bool bForced;
};
typedef struct VREvent_Process_t VREvent_Process_t;

struct VREvent_Overlay_t
{
	uint64_t overlayHandle;
};
typedef struct VREvent_Overlay_t VREvent_Overlay_t;

struct VREvent_Status_t
{
	uint32_t statusState; // EVRState enum
};
typedef struct VREvent_Status_t VREvent_Status_t;

struct VREvent_Keyboard_t
{
	char cNewInput[8];	// Up to 11 bytes of new input
	uint64_t uUserValue;	// Possible flags about the new input
};
typedef struct VREvent_Keyboard_t VREvent_Keyboard_t;

struct VREvent_Ipd_t
{
	float ipdMeters;
};
typedef struct VREvent_Ipd_t VREvent_Ipd_t;

struct VREvent_Chaperone_t
{
	uint64_t m_nPreviousUniverse;
	uint64_t m_nCurrentUniverse;
};
typedef struct VREvent_Chaperone_t VREvent_Chaperone_t;

struct VREvent_Reserved_t
{
	uint64_t reserved0;
	uint64_t reserved1;
};
typedef struct VREvent_Reserved_t VREvent_Reserved_t;

struct VREvent_PerformanceTest_t
{
	uint32_t m_nFidelityLevel;
};
typedef struct VREvent_PerformanceTest_t VREvent_PerformanceTest_t;

struct VREvent_SeatedZeroPoseReset_t
{
	bool bResetBySystemMenu;
};
typedef struct VREvent_SeatedZeroPoseReset_t VREvent_SeatedZeroPoseReset_t;

typedef union
{
	VREvent_Reserved_t reserved;
	VREvent_Controller_t controller;
	VREvent_Mouse_t mouse;
	VREvent_Scroll_t scroll;
	VREvent_Process_t process;
	VREvent_Notification_t notification;
	VREvent_Overlay_t overlay;
	VREvent_Status_t status;
	VREvent_Keyboard_t keyboard;
	VREvent_Ipd_t ipd;
	VREvent_Chaperone_t chaperone;
	VREvent_PerformanceTest_t performanceTest;
	VREvent_TouchPadMove_t touchPadMove;
	VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
} VREvent_Data_t;
struct VREvent_t
{
	uint32_t eventType; // EVREventType enum
	TrackedDeviceIndex_t trackedDeviceIndex;
	float eventAgeSeconds;
	// event data must be the end of the struct as its size is variable
	VREvent_Data_t data;
};
typedef struct VREvent_t VREvent_t;

struct HiddenAreaMesh_t
{
	const HmdVector2_t *pVertexData;
	uint32_t unTriangleCount;
};
typedef struct HiddenAreaMesh_t HiddenAreaMesh_t;

enum EVRControllerAxisType
{
	k_eControllerAxis_None = 0,
	k_eControllerAxis_TrackPad = 1,
	k_eControllerAxis_Joystick = 2,
	k_eControllerAxis_Trigger = 3, // Analog trigger data is in the X axis
};
typedef enum EVRControllerAxisType EVRControllerAxisType;

struct VRControllerAxis_t
{
	float x; // Ranges from -1.0 to 1.0 for joysticks and track pads. Ranges from 0.0 to 1.0 for triggers were 0 is fully released.
	float y; // Ranges from -1.0 to 1.0 for joysticks and track pads. Is always 0.0 for triggers.
};
typedef struct VRControllerAxis_t VRControllerAxis_t;

static const uint32_t k_unControllerStateAxisCount = 5;
struct VRControllerState001_t
{
	// If packet num matches that on your prior call, then the controller state hasn't been changed since 
	// your last call and there is no need to process it
	uint32_t unPacketNum;

	// bit flags for each of the buttons. Use ButtonMaskFromId to turn an ID into a mask
	uint64_t ulButtonPressed;
	uint64_t ulButtonTouched;

	// Axis data for the controller's analog inputs
	VRControllerAxis_t rAxis[5]; //k_unControllerStateAxisCount
};
typedef struct VRControllerState001_t VRControllerState001_t;

typedef VRControllerState001_t VRControllerState_t;
enum EVRControllerEventOutputType
{
	ControllerEventOutput_OSEvents = 0,
	ControllerEventOutput_VREvents = 1,
};
typedef enum EVRControllerEventOutputType EVRControllerEventOutputType;

enum ECollisionBoundsStyle
{
	COLLISION_BOUNDS_STYLE_BEGINNER = 0,
	COLLISION_BOUNDS_STYLE_INTERMEDIATE,
	COLLISION_BOUNDS_STYLE_SQUARES,
	COLLISION_BOUNDS_STYLE_ADVANCED,
	COLLISION_BOUNDS_STYLE_NONE,

	COLLISION_BOUNDS_STYLE_COUNT
};
typedef enum ECollisionBoundsStyle ECollisionBoundsStyle;

struct Compositor_OverlaySettings
{
	uint32_t size; // sizeof(Compositor_OverlaySettings)
	bool curved, antialias;
	float scale, distance, alpha;
	float uOffset, vOffset, uScale, vScale;
	float gridDivs, gridWidth, gridScale;
	HmdMatrix44_t transform;
};
typedef struct Compositor_OverlaySettings Compositor_OverlaySettings;

typedef uint64_t VROverlayHandle_t;
static const VROverlayHandle_t k_ulOverlayHandleInvalid = 0;
enum EVROverlayError
{
	VROverlayError_None					= 0,

	VROverlayError_UnknownOverlay		= 10,
	VROverlayError_InvalidHandle		= 11,
	VROverlayError_PermissionDenied		= 12,
	VROverlayError_OverlayLimitExceeded = 13, // No more overlays could be created because the maximum number already exist
	VROverlayError_WrongVisibilityType	= 14,
	VROverlayError_KeyTooLong			= 15,
	VROverlayError_NameTooLong			= 16,
	VROverlayError_KeyInUse				= 17,
	VROverlayError_WrongTransformType	= 18,
	VROverlayError_InvalidTrackedDevice = 19,
	VROverlayError_InvalidParameter		= 20,
	VROverlayError_ThumbnailCantBeDestroyed = 21,
	VROverlayError_ArrayTooSmall		= 22,
	VROverlayError_RequestFailed		= 23,
	VROverlayError_InvalidTexture		= 24,
	VROverlayError_UnableToLoadFile		= 25,
	VROVerlayError_KeyboardAlreadyInUse = 26,
	VROverlayError_NoNeighbor			= 27,
};
typedef enum EVROverlayError EVROverlayError;

enum EVRApplicationType
{
	VRApplication_Other = 0,		// Some other kind of application that isn't covered by the other entries 
	VRApplication_Scene	= 1,		// Application will submit 3D frames 
	VRApplication_Overlay = 2,		// Application only interacts with overlays
	VRApplication_Background = 3,	// Application should not start SteamVR if it's not already running, and should not
									// keep it running if everything else quits.
	VRApplication_Utility = 4,		// Init should not try to load any drivers. The application needs access to utility
									// interfaces (like IVRSettings and IVRApplications) but not hardware.
};
typedef enum EVRApplicationType EVRApplicationType;

enum EVRFirmwareError
{
	VRFirmwareError_None = 0,
	VRFirmwareError_Success = 1,
	VRFirmwareError_Fail = 2,
};
typedef enum EVRFirmwareError EVRFirmwareError;

enum EVRNotificationError
{
	VRNotificationError_OK = 0,
	VRNotificationError_InvalidNotificationId = 100,
	VRNotificationError_NotificationQueueFull = 101,
	VRNotificationError_InvalidOverlayHandle = 102,
};
typedef enum EVRNotificationError EVRNotificationError;

enum EVRInitError
{
	VRInitError_None = 0,
	VRInitError_Unknown = 1,

	VRInitError_Init_InstallationNotFound	= 100,
	VRInitError_Init_InstallationCorrupt	= 101,
	VRInitError_Init_VRClientDLLNotFound	= 102,
	VRInitError_Init_FileNotFound			= 103,
	VRInitError_Init_FactoryNotFound		= 104,
	VRInitError_Init_InterfaceNotFound		= 105,
	VRInitError_Init_InvalidInterface		= 106,
	VRInitError_Init_UserConfigDirectoryInvalid = 107,
	VRInitError_Init_HmdNotFound			= 108,
	VRInitError_Init_NotInitialized		= 109,
	VRInitError_Init_PathRegistryNotFound	= 110,
	VRInitError_Init_NoConfigPath			= 111,
	VRInitError_Init_NoLogPath				= 112,
	VRInitError_Init_PathRegistryNotWritable = 113,
	VRInitError_Init_AppInfoInitFailed		= 114,
	VRInitError_Init_Retry					= 115, // Used internally to cause retries to vrserver
	VRInitError_Init_InitCanceledByUser	= 116, // The calling application should silently exit. The user canceled app startup
	VRInitError_Init_AnotherAppLaunching	= 117, 
	VRInitError_Init_SettingsInitFailed	= 118, 
	VRInitError_Init_ShuttingDown			= 119,
	VRInitError_Init_TooManyObjects		= 120,
	VRInitError_Init_NoServerForBackgroundApp = 121,
	VRInitError_Init_NotSupportedWithCompositor = 122,
	VRInitError_Init_NotAvailableToUtilityApps = 123,

	VRInitError_Driver_Failed				= 200,
	VRInitError_Driver_Unknown				= 201,
	VRInitError_Driver_HmdUnknown			= 202,
	VRInitError_Driver_NotLoaded			= 203,
	VRInitError_Driver_RuntimeOutOfDate	= 204,
	VRInitError_Driver_HmdInUse			= 205,
	VRInitError_Driver_NotCalibrated		= 206,
	VRInitError_Driver_CalibrationInvalid	= 207,
	VRInitError_Driver_HmdDisplayNotFound  = 208,
	
	VRInitError_IPC_ServerInitFailed		= 300,
	VRInitError_IPC_ConnectFailed			= 301,
	VRInitError_IPC_SharedStateInitFailed	= 302,
	VRInitError_IPC_CompositorInitFailed	= 303,
	VRInitError_IPC_MutexInitFailed		= 304,
	VRInitError_IPC_Failed					= 305,

	VRInitError_Compositor_Failed		= 400,
	VRInitError_Compositor_D3D11HardwareRequired = 401,

	VRInitError_VendorSpecific_UnableToConnectToOculusRuntime = 1000,

	VRInitError_VendorSpecific_HmdFound_CantOpenDevice 			= 1101,
	VRInitError_VendorSpecific_HmdFound_UnableToRequestConfigStart = 1102,
	VRInitError_VendorSpecific_HmdFound_NoStoredConfig 			= 1103,
	VRInitError_VendorSpecific_HmdFound_ConfigTooBig 				= 1104,
	VRInitError_VendorSpecific_HmdFound_ConfigTooSmall 			= 1105,
	VRInitError_VendorSpecific_HmdFound_UnableToInitZLib 			= 1106,
	VRInitError_VendorSpecific_HmdFound_CantReadFirmwareVersion 	= 1107,
	VRInitError_VendorSpecific_HmdFound_UnableToSendUserDataStart  = 1108,
	VRInitError_VendorSpecific_HmdFound_UnableToGetUserDataStart   = 1109,
	VRInitError_VendorSpecific_HmdFound_UnableToGetUserDataNext    = 1110,
	VRInitError_VendorSpecific_HmdFound_UserDataAddressRange       = 1111,
	VRInitError_VendorSpecific_HmdFound_UserDataError              = 1112,
	VRInitError_VendorSpecific_HmdFound_ConfigFailedSanityCheck    = 1113,

	VRInitError_Steam_SteamInstallationNotFound = 2000,

};
typedef enum EVRInitError EVRInitError;

// *********** 
// IVRSystem
// *********** 
typedef struct IVRSystem IVRSystem;
void	IVRSystem_GetRecommendedRenderTargetSize(IVRSystem * this_, uint32_t * pnWidth, uint32_t * pnHeight);
HmdMatrix44_t	IVRSystem_GetProjectionMatrix(IVRSystem * this_, EVREye eEye, float fNearZ, float fFarZ);
void	IVRSystem_GetProjectionRaw(IVRSystem * this_, EVREye eEye, float * pfLeft, float * pfRight, float * pfTop, float * pfBottom);
DistortionCoordinates_t	IVRSystem_ComputeDistortion(IVRSystem * this_, EVREye eEye, float fU, float fV);
HmdMatrix34_t	IVRSystem_GetEyeToHeadTransform(IVRSystem * this_, EVREye eEye);
bool	IVRSystem_GetTimeSinceLastVsync(IVRSystem * this_, float * pfSecondsSinceLastVsync, uint64_t * pulFrameCounter);
int32_t	IVRSystem_GetD3D9AdapterIndex(IVRSystem * this_);
void	IVRSystem_GetDXGIOutputInfo(IVRSystem * this_, int32_t * pnAdapterIndex);
bool	IVRSystem_IsDisplayOnDesktop(IVRSystem * this_);
bool	IVRSystem_SetDisplayVisibility(IVRSystem * this_, bool bIsVisibleOnDesktop);
void	IVRSystem_GetDeviceToAbsoluteTrackingPose(IVRSystem * this_, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
void	IVRSystem_ResetSeatedZeroPose(IVRSystem * this_);
HmdMatrix34_t	IVRSystem_GetSeatedZeroPoseToStandingAbsoluteTrackingPose(IVRSystem * this_);
HmdMatrix34_t	IVRSystem_GetRawZeroPoseToStandingAbsoluteTrackingPose(IVRSystem * this_);
uint32_t	IVRSystem_GetSortedTrackedDeviceIndicesOfClass(IVRSystem * this_, ETrackedDeviceClass eTrackedDeviceClass, TrackedDeviceIndex_t * punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
EDeviceActivityLevel	IVRSystem_GetTrackedDeviceActivityLevel(IVRSystem * this_, TrackedDeviceIndex_t unDeviceId);
void	IVRSystem_ApplyTransform(IVRSystem * this_, TrackedDevicePose_t * pOutputPose, TrackedDevicePose_t * pTrackedDevicePose, HmdMatrix34_t * pTransform);
TrackedDeviceIndex_t	IVRSystem_GetTrackedDeviceIndexForControllerRole(IVRSystem * this_, ETrackedControllerRole unDeviceType);
ETrackedControllerRole	IVRSystem_GetControllerRoleForTrackedDeviceIndex(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex);
ETrackedDeviceClass	IVRSystem_GetTrackedDeviceClass(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex);
bool	IVRSystem_IsTrackedDeviceConnected(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex);
bool	IVRSystem_GetBoolTrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
float	IVRSystem_GetFloatTrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
int32_t	IVRSystem_GetInt32TrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
uint64_t	IVRSystem_GetUint64TrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
HmdMatrix34_t	IVRSystem_GetMatrix34TrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError);
uint32_t	IVRSystem_GetStringTrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, char * pchValue, uint32_t unBufferSize, ETrackedPropertyError * pError);
const char *	IVRSystem_GetPropErrorNameFromEnum(IVRSystem * this_, ETrackedPropertyError error);
bool	IVRSystem_PollNextEvent(IVRSystem * this_, VREvent_t * pEvent, uint32_t uncbVREvent);
bool	IVRSystem_PollNextEventWithPose(IVRSystem * this_, ETrackingUniverseOrigin eOrigin, VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose);
const char *	IVRSystem_GetEventTypeNameFromEnum(IVRSystem * this_, EVREventType eType);
HiddenAreaMesh_t	IVRSystem_GetHiddenAreaMesh(IVRSystem * this_, EVREye eEye);
bool	IVRSystem_GetControllerState(IVRSystem * this_, TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t * pControllerState);
bool	IVRSystem_GetControllerStateWithPose(IVRSystem * this_, ETrackingUniverseOrigin eOrigin, TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t * pControllerState, TrackedDevicePose_t * pTrackedDevicePose);
void	IVRSystem_TriggerHapticPulse(IVRSystem * this_, TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec);
const char *	IVRSystem_GetButtonIdNameFromEnum(IVRSystem * this_, EVRButtonId eButtonId);
const char *	IVRSystem_GetControllerAxisTypeNameFromEnum(IVRSystem * this_, EVRControllerAxisType eAxisType);
bool	IVRSystem_CaptureInputFocus(IVRSystem * this_);
void	IVRSystem_ReleaseInputFocus(IVRSystem * this_);
bool	IVRSystem_IsInputFocusCapturedByAnotherProcess(IVRSystem * this_);
uint32_t	IVRSystem_DriverDebugRequest(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, const char * pchRequest, char * pchResponseBuffer, uint32_t unResponseBufferSize);
EVRFirmwareError	IVRSystem_PerformFirmwareUpdate(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex);
void	IVRSystem_AcknowledgeQuit_Exiting(IVRSystem * this_);
void	IVRSystem_AcknowledgeQuit_UserPrompt(IVRSystem * this_);



static const char * const IVRSystem_Version = "IVRSystem_012";
enum EVRApplicationError
	{
		VRApplicationError_None = 0,

		VRApplicationError_AppKeyAlreadyExists = 100,	// Only one application can use any given key
		VRApplicationError_NoManifest = 101,			// the running application does not have a manifest
		VRApplicationError_NoApplication = 102,			// No application is running
		VRApplicationError_InvalidIndex = 103,
		VRApplicationError_UnknownApplication = 104,	// the application could not be found
		VRApplicationError_IPCFailed = 105,				// An IPC failure caused the request to fail
		VRApplicationError_ApplicationAlreadyRunning = 106, 
		VRApplicationError_InvalidManifest = 107,
		VRApplicationError_InvalidApplication = 108,
		VRApplicationError_LaunchFailed = 109,			// the process didn't start
		VRApplicationError_ApplicationAlreadyStarting = 110, // the system was already starting the same application
		VRApplicationError_LaunchInProgress = 111,		// The system was already starting a different application
		VRApplicationError_OldApplicationQuitting = 112, 
		VRApplicationError_TransitionAborted = 113,
		VRApplicationError_IsTemplate = 114, // error when you try to call LaunchApplication() on a template type app (use LaunchTemplateApplication)

		VRApplicationError_BufferTooSmall = 200,		// The provided buffer was too small to fit the requested data
		VRApplicationError_PropertyNotSet = 201,		// The requested property was not set
		VRApplicationError_UnknownProperty = 202,
	};
typedef enum EVRApplicationError EVRApplicationError;

static const uint32_t k_unMaxApplicationKeyLength = 128;
enum EVRApplicationProperty
	{
		VRApplicationProperty_Name_String				= 0,

		VRApplicationProperty_LaunchType_String			= 11,
		VRApplicationProperty_WorkingDirectory_String	= 12,
		VRApplicationProperty_BinaryPath_String			= 13,
		VRApplicationProperty_Arguments_String			= 14,
		VRApplicationProperty_URL_String				= 15,

		VRApplicationProperty_Description_String		= 50,
		VRApplicationProperty_NewsURL_String			= 51,
		VRApplicationProperty_ImagePath_String			= 52,
		VRApplicationProperty_Source_String				= 53,

		VRApplicationProperty_IsDashboardOverlay_Bool	= 60,
		VRApplicationProperty_IsTemplate_Bool			= 61,
		VRApplicationProperty_IsInstanced_Bool			= 62,

		VRApplicationProperty_LastLaunchTime_Uint64		= 70,
	};
typedef enum EVRApplicationProperty EVRApplicationProperty;

enum EVRApplicationTransitionState
	{
		VRApplicationTransition_None = 0,

		VRApplicationTransition_OldAppQuitSent = 10,
		VRApplicationTransition_WaitingForExternalLaunch = 11,
		
		VRApplicationTransition_NewAppLaunched = 20,
	};
typedef enum EVRApplicationTransitionState EVRApplicationTransitionState;

struct AppOverrideKeys_t
	{
		const char *pchKey;
		const char *pchValue;
	};
typedef struct AppOverrideKeys_t AppOverrideKeys_t;

// *********** 
// IVRApplications
// *********** 
typedef struct IVRApplications IVRApplications;
EVRApplicationError	IVRApplications_AddApplicationManifest(IVRApplications * this_, const char * pchApplicationManifestFullPath, bool bTemporary);
EVRApplicationError	IVRApplications_RemoveApplicationManifest(IVRApplications * this_, const char * pchApplicationManifestFullPath);
bool	IVRApplications_IsApplicationInstalled(IVRApplications * this_, const char * pchAppKey);
uint32_t	IVRApplications_GetApplicationCount(IVRApplications * this_);
EVRApplicationError	IVRApplications_GetApplicationKeyByIndex(IVRApplications * this_, uint32_t unApplicationIndex, char * pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
EVRApplicationError	IVRApplications_GetApplicationKeyByProcessId(IVRApplications * this_, uint32_t unProcessId, char * pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
EVRApplicationError	IVRApplications_LaunchApplication(IVRApplications * this_, const char * pchAppKey);
EVRApplicationError	IVRApplications_LaunchTemplateApplication(IVRApplications * this_, const char * pchTemplateAppKey, const char * pchNewAppKey, AppOverrideKeys_t * pKeys, uint32_t unKeys);
EVRApplicationError	IVRApplications_LaunchDashboardOverlay(IVRApplications * this_, const char * pchAppKey);
bool	IVRApplications_CancelApplicationLaunch(IVRApplications * this_, const char * pchAppKey);
EVRApplicationError	IVRApplications_IdentifyApplication(IVRApplications * this_, uint32_t unProcessId, const char * pchAppKey);
uint32_t	IVRApplications_GetApplicationProcessId(IVRApplications * this_, const char * pchAppKey);
const char *	IVRApplications_GetApplicationsErrorNameFromEnum(IVRApplications * this_, EVRApplicationError error);
uint32_t	IVRApplications_GetApplicationPropertyString(IVRApplications * this_, const char * pchAppKey, EVRApplicationProperty eProperty, char * pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError * peError);
bool	IVRApplications_GetApplicationPropertyBool(IVRApplications * this_, const char * pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError * peError);
uint64_t	IVRApplications_GetApplicationPropertyUint64(IVRApplications * this_, const char * pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError * peError);
EVRApplicationError	IVRApplications_SetApplicationAutoLaunch(IVRApplications * this_, const char * pchAppKey, bool bAutoLaunch);
bool	IVRApplications_GetApplicationAutoLaunch(IVRApplications * this_, const char * pchAppKey);
EVRApplicationError	IVRApplications_GetStartingApplication(IVRApplications * this_, char * pchAppKeyBuffer, uint32_t unAppKeyBufferLen);
EVRApplicationTransitionState	IVRApplications_GetTransitionState(IVRApplications * this_);
EVRApplicationError	IVRApplications_PerformApplicationPrelaunchCheck(IVRApplications * this_, const char * pchAppKey);
const char *	IVRApplications_GetApplicationsTransitionStateNameFromEnum(IVRApplications * this_, EVRApplicationTransitionState state);
bool	IVRApplications_IsQuitUserPromptRequested(IVRApplications * this_);
EVRApplicationError	IVRApplications_LaunchInternalProcess(IVRApplications * this_, const char * pchBinaryPath, const char * pchArguments, const char * pchWorkingDirectory);



static const char * const IVRApplications_Version = "IVRApplications_005";
enum EVRSettingsError
	{
		VRSettingsError_None = 0,
		VRSettingsError_IPCFailed = 1,
		VRSettingsError_WriteFailed = 2,
		VRSettingsError_ReadFailed = 3,
	};
typedef enum EVRSettingsError EVRSettingsError;

static const uint32_t k_unMaxSettingsKeyLength = 128;
// *********** 
// IVRSettings
// *********** 
typedef struct IVRSettings IVRSettings;
const char *	IVRSettings_GetSettingsErrorNameFromEnum(IVRSettings * this_, EVRSettingsError eError);
bool	IVRSettings_Sync(IVRSettings * this_, bool bForce, EVRSettingsError * peError);
bool	IVRSettings_GetBool(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, bool bDefaultValue, EVRSettingsError * peError);
void	IVRSettings_SetBool(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, bool bValue, EVRSettingsError * peError);
int32_t	IVRSettings_GetInt32(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, int32_t nDefaultValue, EVRSettingsError * peError);
void	IVRSettings_SetInt32(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, int32_t nValue, EVRSettingsError * peError);
float	IVRSettings_GetFloat(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, float flDefaultValue, EVRSettingsError * peError);
void	IVRSettings_SetFloat(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, float flValue, EVRSettingsError * peError);
void	IVRSettings_GetString(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, char * pchValue, uint32_t unValueLen, const char * pchDefaultValue, EVRSettingsError * peError);
void	IVRSettings_SetString(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, const char * pchValue, EVRSettingsError * peError);
void	IVRSettings_RemoveSection(IVRSettings * this_, const char * pchSection, EVRSettingsError * peError);
void	IVRSettings_RemoveKeyInSection(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError);



static const char * const k_pch_SteamVR_Section = "steamvr";
static const char * const k_pch_SteamVR_RequireHmd_String = "requireHmd";
static const char * const k_pch_SteamVR_ForcedDriverKey_String = "forcedDriver";
static const char * const k_pch_SteamVR_ForcedHmdKey_String = "forcedHmd";
static const char * const k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
static const char * const k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
static const char * const k_pch_SteamVR_EnableDistortion_Bool = "enableDistortion";
static const char * const k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
static const char * const k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
static const char * const k_pch_SteamVR_SendSystemButtonToAllApps_Bool= "sendSystemButtonToAllApps";
static const char * const k_pch_SteamVR_LogLevel_Int32 = "loglevel";
static const char * const k_pch_SteamVR_IPD_Float = "ipd";
static const char * const k_pch_SteamVR_Background_String = "background";
static const char * const k_pch_SteamVR_GridColor_String = "gridColor";
static const char * const k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
static const char * const k_pch_SteamVR_ActivateMultipleDrivers_Bool = "activateMultipleDrivers";
static const char * const k_pch_SteamVR_PowerOffOnExit_Bool = "powerOffOnExit";
static const char * const k_pch_SteamVR_StandbyAppRunningTimeout_Float = "standbyAppRunningTimeout";
static const char * const k_pch_SteamVR_StandbyNoAppTimeout_Float = "standbyNoAppTimeout";
static const char * const k_pch_SteamVR_DirectMode_Bool = "directMode";
static const char * const k_pch_SteamVR_DirectModeEdidVid_Int32 = "directModeEdidVid";
static const char * const k_pch_SteamVR_DirectModeEdidPid_Int32 = "directModeEdidPid";
static const char * const k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
static const char * const k_pch_SteamVR_SpeakersForwardYawOffsetDegrees_Float = "speakersForwardYawOffsetDegrees";
static const char * const k_pch_SteamVR_BaseStationPowerManagement_Bool = "basestationPowerManagement";
static const char * const k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
static const char * const k_pch_Lighthouse_Section = "driver_lighthouse";
static const char * const k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
static const char * const k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
static const char * const k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
static const char * const k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
static const char * const k_pch_Lighthouse_LighthouseName_String = "lighthousename";
static const char * const k_pch_Lighthouse_MaxIncidenceAngleDegrees_Float = "maxincidenceangledegrees";
static const char * const k_pch_Lighthouse_UseLighthouseDirect_Bool = "uselighthousedirect";
static const char * const k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
static const char * const k_pch_Lighthouse_OriginOffsetX_Float = "originoffsetx";
static const char * const k_pch_Lighthouse_OriginOffsetY_Float = "originoffsety";
static const char * const k_pch_Lighthouse_OriginOffsetZ_Float = "originoffsetz";
static const char * const k_pch_Lighthouse_HeadingOffset_Float = "headingoffset";
static const char * const k_pch_Null_Section = "driver_null";
static const char * const k_pch_Null_EnableNullDriver_Bool = "enable";
static const char * const k_pch_Null_SerialNumber_String = "serialNumber";
static const char * const k_pch_Null_ModelNumber_String = "modelNumber";
static const char * const k_pch_Null_WindowX_Int32 = "windowX";
static const char * const k_pch_Null_WindowY_Int32 = "windowY";
static const char * const k_pch_Null_WindowWidth_Int32 = "windowWidth";
static const char * const k_pch_Null_WindowHeight_Int32 = "windowHeight";
static const char * const k_pch_Null_RenderWidth_Int32 = "renderWidth";
static const char * const k_pch_Null_RenderHeight_Int32 = "renderHeight";
static const char * const k_pch_Null_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
static const char * const k_pch_Null_DisplayFrequency_Float = "displayFrequency";
static const char * const k_pch_UserInterface_Section = "userinterface";
static const char * const k_pch_UserInterface_StatusAlwaysOnTop_Bool = "StatusAlwaysOnTop";
static const char * const k_pch_Notifications_Section = "notifications";
static const char * const k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";
static const char * const k_pch_Keyboard_Section = "keyboard";
static const char * const k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
static const char * const k_pch_Perf_Section = "perfcheck";
static const char * const k_pch_Perf_HeuristicActive_Bool = "heuristicActive";
static const char * const k_pch_Perf_NotifyInHMD_Bool = "warnInHMD";
static const char * const k_pch_Perf_NotifyOnlyOnce_Bool = "warnOnlyOnce";
static const char * const k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
static const char * const k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
static const char * const k_pch_Perf_TestData_Float = "perfTestData";
static const char * const k_pch_Camera_Section = "camera";
static const char * const IVRSettings_Version = "IVRSettings_001";
static const char * const k_pch_audio_Section = "audio";
static const char * const k_pch_audio_OnPlaybackDevice_String = "onPlaybackDevice";
static const char * const k_pch_audio_OnRecordDevice_String = "onRecordDevice";
static const char * const k_pch_audio_OffPlaybackDevice_String = "offPlaybackDevice";
static const char * const k_pch_audio_OffRecordDevice_String = "offRecordDevice";
static const char * const k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
enum ChaperoneCalibrationState
{
	// OK!
	ChaperoneCalibrationState_OK = 1,									// Chaperone is fully calibrated and working correctly

	// Warnings
	ChaperoneCalibrationState_Warning = 100,
	ChaperoneCalibrationState_Warning_BaseStationMayHaveMoved = 101,	// A base station thinks that it might have moved
	ChaperoneCalibrationState_Warning_BaseStationRemoved = 102,			// There are less base stations than when calibrated
	ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,		// Seated bounds haven't been calibrated for the current tracking center

	// Errors
	ChaperoneCalibrationState_Error = 200,								// The UniverseID is invalid
	ChaperoneCalibrationState_Error_BaseStationUninitalized = 201,		// Tracking center hasn't be calibrated for at least one of the base stations
	ChaperoneCalibrationState_Error_BaseStationConflict = 202,			// Tracking center is calibrated, but base stations disagree on the tracking space
	ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,				// Play Area hasn't been calibrated for the current tracking center
	ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,		// Collision Bounds haven't been calibrated for the current tracking center
};
typedef enum ChaperoneCalibrationState ChaperoneCalibrationState;

// *********** 
// IVRChaperone
// *********** 
typedef struct IVRChaperone IVRChaperone;
ChaperoneCalibrationState	IVRChaperone_GetCalibrationState(IVRChaperone * this_);
bool	IVRChaperone_GetPlayAreaSize(IVRChaperone * this_, float * pSizeX, float * pSizeZ);
bool	IVRChaperone_GetPlayAreaRect(IVRChaperone * this_, HmdQuad_t * rect);
void	IVRChaperone_ReloadInfo(IVRChaperone * this_);
void	IVRChaperone_SetSceneColor(IVRChaperone * this_, HmdColor_t color);
void	IVRChaperone_GetBoundsColor(IVRChaperone * this_, HmdColor_t * pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t * pOutputCameraColor);
bool	IVRChaperone_AreBoundsVisible(IVRChaperone * this_);
void	IVRChaperone_ForceBoundsVisible(IVRChaperone * this_, bool bForce);



static const char * const IVRChaperone_Version = "IVRChaperone_003";
enum EChaperoneConfigFile
{
	EChaperoneConfigFile_Live = 1,		// The live chaperone config, used by most applications and games
	EChaperoneConfigFile_Temp = 2,		// The temporary chaperone config, used to live-preview collision bounds in room setup
};
typedef enum EChaperoneConfigFile EChaperoneConfigFile;

enum EChaperoneImportFlags
{
	EChaperoneImport_BoundsOnly = 0x0001,
};
typedef enum EChaperoneImportFlags EChaperoneImportFlags;

// *********** 
// IVRChaperoneSetup
// *********** 
typedef struct IVRChaperoneSetup IVRChaperoneSetup;
bool	IVRChaperoneSetup_CommitWorkingCopy(IVRChaperoneSetup * this_, EChaperoneConfigFile configFile);
void	IVRChaperoneSetup_RevertWorkingCopy(IVRChaperoneSetup * this_);
bool	IVRChaperoneSetup_GetWorkingPlayAreaSize(IVRChaperoneSetup * this_, float * pSizeX, float * pSizeZ);
bool	IVRChaperoneSetup_GetWorkingPlayAreaRect(IVRChaperoneSetup * this_, HmdQuad_t * rect);
bool	IVRChaperoneSetup_GetWorkingCollisionBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t * punQuadsCount);
bool	IVRChaperoneSetup_GetLiveCollisionBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t * punQuadsCount);
bool	IVRChaperoneSetup_GetWorkingSeatedZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
bool	IVRChaperoneSetup_GetWorkingStandingZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pmatStandingZeroPoseToRawTrackingPose);
void	IVRChaperoneSetup_SetWorkingPlayAreaSize(IVRChaperoneSetup * this_, float sizeX, float sizeZ);
void	IVRChaperoneSetup_SetWorkingCollisionBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t unQuadsCount);
void	IVRChaperoneSetup_SetWorkingSeatedZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pMatSeatedZeroPoseToRawTrackingPose);
void	IVRChaperoneSetup_SetWorkingStandingZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pMatStandingZeroPoseToRawTrackingPose);
void	IVRChaperoneSetup_ReloadFromDisk(IVRChaperoneSetup * this_, EChaperoneConfigFile configFile);
bool	IVRChaperoneSetup_GetLiveSeatedZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose);
void	IVRChaperoneSetup_SetWorkingCollisionBoundsTagsInfo(IVRChaperoneSetup * this_, uint8_t * pTagsBuffer, uint32_t unTagCount);
bool	IVRChaperoneSetup_GetLiveCollisionBoundsTagsInfo(IVRChaperoneSetup * this_, uint8_t * pTagsBuffer, uint32_t * punTagCount);
bool	IVRChaperoneSetup_SetWorkingPhysicalBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t unQuadsCount);
bool	IVRChaperoneSetup_GetLivePhysicalBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t * punQuadsCount);
bool	IVRChaperoneSetup_ExportLiveToBuffer(IVRChaperoneSetup * this_, char * pBuffer, uint32_t * pnBufferLength);
bool	IVRChaperoneSetup_ImportFromBufferToWorking(IVRChaperoneSetup * this_, const char * pBuffer, uint32_t nImportFlags);



static const char * const IVRChaperoneSetup_Version = "IVRChaperoneSetup_005";
enum EVRCompositorError
{
	VRCompositorError_None						= 0,
	VRCompositorError_IncompatibleVersion		= 100,
	VRCompositorError_DoNotHaveFocus			= 101,
	VRCompositorError_InvalidTexture			= 102,
	VRCompositorError_IsNotSceneApplication		= 103,
	VRCompositorError_TextureIsOnWrongDevice	= 104,
	VRCompositorError_TextureUsesUnsupportedFormat = 105,
	VRCompositorError_SharedTexturesNotSupported = 106,
	VRCompositorError_IndexOutOfRange			= 107,
};
typedef enum EVRCompositorError EVRCompositorError;

struct Compositor_FrameTiming
{
	uint32_t m_nSize; // Set to sizeof( Compositor_FrameTiming )
	uint32_t m_nFrameIndex;
	uint32_t m_nNumFramePresents; // number of times this frame was presented
	uint32_t m_nNumDroppedFrames; // number of additional times previous frame was scanned out

	/** Absolute time reference for comparing frames.  This aligns with the vsync that running start is relative to. */
	double m_flSystemTimeInSeconds;

	/** These times may include work from other processes due to OS scheduling.
	* The fewer packets of work these are broken up into, the less likely this will happen.
	* GPU work can be broken up by calling Flush.  This can sometimes be useful to get the GPU started
	* processing that work earlier in the frame. */
	float m_flSceneRenderGpuMs; // time spent rendering the scene
	float m_flTotalRenderGpuMs; // time between work submitted immediately after present (ideally vsync) until the end of compositor submitted work
	float m_flCompositorRenderGpuMs; // time spend performing distortion correction, rendering chaperone, overlays, etc.
	float m_flCompositorRenderCpuMs; // time spent on cpu submitting the above work for this frame
	float m_flCompositorIdleCpuMs; // time spent waiting for running start (application could have used this much more time)

	/** Miscellaneous measured intervals. */
	float m_flClientFrameIntervalMs; // time between calls to WaitGetPoses
	float m_flPresentCallCpuMs; // time blocked on call to present (usually 0.0, but can go long)
	float m_flWaitForPresentCpuMs; // time spent spin-waiting for frame index to change (not near-zero indicates wait object failure)
	float m_flSubmitFrameMs; // time spent in Submit (not near-zero indicates driver issue)

	/** The following are all relative to this frame's SystemTimeInSeconds */
	float m_flWaitGetPosesCalledMs;
	float m_flNewPosesReadyMs;
	float m_flNewFrameReadyMs; // second call to Submit
	float m_flCompositorUpdateStartMs;
	float m_flCompositorUpdateEndMs;
	float m_flCompositorRenderStartMs;

	TrackedDevicePose_t m_HmdPose; // pose used by app to render this frame
	int32_t m_nFidelityLevel; // app reported value
};
typedef struct Compositor_FrameTiming Compositor_FrameTiming;

// *********** 
// IVRCompositor
// *********** 
typedef struct IVRCompositor IVRCompositor;
void	IVRCompositor_SetTrackingSpace(IVRCompositor * this_, ETrackingUniverseOrigin eOrigin);
ETrackingUniverseOrigin	IVRCompositor_GetTrackingSpace(IVRCompositor * this_);
EVRCompositorError	IVRCompositor_WaitGetPoses(IVRCompositor * this_, TrackedDevicePose_t * pRenderPoseArray, uint32_t unRenderPoseArrayCount, TrackedDevicePose_t * pGamePoseArray, uint32_t unGamePoseArrayCount);
EVRCompositorError	IVRCompositor_GetLastPoses(IVRCompositor * this_, TrackedDevicePose_t * pRenderPoseArray, uint32_t unRenderPoseArrayCount, TrackedDevicePose_t * pGamePoseArray, uint32_t unGamePoseArrayCount);
EVRCompositorError	IVRCompositor_GetLastPoseForTrackedDeviceIndex(IVRCompositor * this_, TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t * pOutputPose, TrackedDevicePose_t * pOutputGamePose);
EVRCompositorError	IVRCompositor_Submit(IVRCompositor * this_, EVREye eEye, Texture_t * pTexture);
EVRCompositorError	IVRCompositor_Submit_Bounds(IVRCompositor * this_, EVREye eEye, Texture_t * pTexture, VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags);
void	IVRCompositor_ClearLastSubmittedFrame(IVRCompositor * this_);
void	IVRCompositor_PostPresentHandoff(IVRCompositor * this_);
bool	IVRCompositor_GetFrameTiming(IVRCompositor * this_, Compositor_FrameTiming * pTiming, uint32_t unFramesAgo);
float	IVRCompositor_GetFrameTimeRemaining(IVRCompositor * this_);
void	IVRCompositor_FadeToColor(IVRCompositor * this_, float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
void	IVRCompositor_FadeGrid(IVRCompositor * this_, float fSeconds, bool bFadeIn);
EVRCompositorError	IVRCompositor_SetSkyboxOverride(IVRCompositor * this_, Texture_t * pTextures, uint32_t unTextureCount);
void	IVRCompositor_ClearSkyboxOverride(IVRCompositor * this_);
void	IVRCompositor_CompositorBringToFront(IVRCompositor * this_);
void	IVRCompositor_CompositorGoToBack(IVRCompositor * this_);
void	IVRCompositor_CompositorQuit(IVRCompositor * this_);
bool	IVRCompositor_IsFullscreen(IVRCompositor * this_);
uint32_t	IVRCompositor_GetCurrentSceneFocusProcess(IVRCompositor * this_);
uint32_t	IVRCompositor_GetLastFrameRenderer(IVRCompositor * this_);
bool	IVRCompositor_CanRenderScene(IVRCompositor * this_);
void	IVRCompositor_ShowMirrorWindow(IVRCompositor * this_);
void	IVRCompositor_HideMirrorWindow(IVRCompositor * this_);
bool	IVRCompositor_IsMirrorWindowVisible(IVRCompositor * this_);
void	IVRCompositor_CompositorDumpImages(IVRCompositor * this_);
bool	IVRCompositor_ShouldAppRenderWithLowResources(IVRCompositor * this_);
void	IVRCompositor_ForceInterleavedReprojectionOn(IVRCompositor * this_, bool bOverride);



static const char * const IVRCompositor_Version = "IVRCompositor_013";
struct NotificationBitmap_t
{
	void *bytes;
	int32_t width;
	int32_t height;
	int32_t depth;
};
typedef struct NotificationBitmap_t NotificationBitmap_t;

enum EVRNotificationType
{
	/** Transient notifications are automatically hidden after a period of time set by the user. 
	* They are used for things like information and chat messages that do not require user interaction. */
	EVRNotificationType_Transient = 0,

	/** Persistent notifications are shown to the user until they are hidden by calling RemoveNotification().
	* They are used for things like phone calls and alarms that require user interaction. */
	EVRNotificationType_Persistent = 1,
};
typedef enum EVRNotificationType EVRNotificationType;

enum EVRNotificationStyle
{
	/** Creates a notification with minimal external styling. */
	EVRNotificationStyle_None = 0,

	/** Used for notifications about overlay-level status. In Steam this is used for events like downloads completing. */
	EVRNotificationStyle_Application = 100,

	/** Used for notifications about contacts that are unknown or not available. In Steam this is used for friend invitations and offline friends. */
	EVRNotificationStyle_Contact_Disabled = 200,

	/** Used for notifications about contacts that are available but inactive. In Steam this is used for friends that are online but not playing a game. */
	EVRNotificationStyle_Contact_Enabled = 201,

	/** Used for notifications about contacts that are available and active. In Steam this is used for friends that are online and currently running a game. */
	EVRNotificationStyle_Contact_Active = 202,
};
typedef enum EVRNotificationStyle EVRNotificationStyle;

static const uint32_t k_unNotificationTextMaxSize = 256;
typedef uint32_t VRNotificationId;
// *********** 
// IVRNotifications
// *********** 
typedef struct IVRNotifications IVRNotifications;
EVRNotificationError	IVRNotifications_CreateNotification(IVRNotifications * this_, VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char * pchText, EVRNotificationStyle style, NotificationBitmap_t * pImage, VRNotificationId * pNotificationId);
EVRNotificationError	IVRNotifications_RemoveNotification(IVRNotifications * this_, VRNotificationId notificationId);



static const char * const IVRNotifications_Version = "IVRNotifications_002";
static const uint32_t k_unVROverlayMaxKeyLength = 128;
static const uint32_t k_unVROverlayMaxNameLength = 128;
static const uint32_t k_unMaxOverlayCount = 32;
enum VROverlayInputMethod
	{
		VROverlayInputMethod_None		= 0, // No input events will be generated automatically for this overlay
		VROverlayInputMethod_Mouse		= 1, // Tracked controllers will get mouse events automatically
	};
typedef enum VROverlayInputMethod VROverlayInputMethod;

enum VROverlayTransformType
	{
		VROverlayTransform_Absolute					= 0,
		VROverlayTransform_TrackedDeviceRelative	= 1,
		VROverlayTransform_SystemOverlay			= 2,
		VROverlayTransform_TrackedComponent 		= 3,
	};
typedef enum VROverlayTransformType VROverlayTransformType;

enum VROverlayFlags
	{
		VROverlayFlags_None			= 0,

		// The following only take effect when rendered using the high quality render path (see SetHighQualityOverlay).
		VROverlayFlags_Curved		= 1,
		VROverlayFlags_RGSS4X		= 2,

		// Set this flag on a dashboard overlay to prevent a tab from showing up for that overlay
		VROverlayFlags_NoDashboardTab = 3,

		// Set this flag on a dashboard that is able to deal with gamepad focus events
		VROverlayFlags_AcceptsGamepadEvents = 4,

		// Indicates that the overlay should dim/brighten to show gamepad focus
		VROverlayFlags_ShowGamepadFocus = 5,

		// When in VROverlayInputMethod_Mouse you can optionally enable sending VRScroll_t 
		VROverlayFlags_SendVRScrollEvents = 6,
		VROverlayFlags_SendVRTouchpadEvents = 7,

		// If set this will render a vertical scroll wheel on the primary controller, 
		//  only needed if not using VROverlayFlags_SendVRScrollEvents but you still want to represent a scroll wheel
		VROverlayFlags_ShowTouchPadScrollWheel = 8,
	};
typedef enum VROverlayFlags VROverlayFlags;

struct VROverlayIntersectionParams_t
	{
		HmdVector3_t vSource;
		HmdVector3_t vDirection;
		ETrackingUniverseOrigin eOrigin;
	};
typedef struct VROverlayIntersectionParams_t VROverlayIntersectionParams_t;

struct VROverlayIntersectionResults_t
	{
		HmdVector3_t vPoint;
		HmdVector3_t vNormal;
		HmdVector2_t vUVs;
		float fDistance;
	};
typedef struct VROverlayIntersectionResults_t VROverlayIntersectionResults_t;

enum EGamepadTextInputMode
	{
		k_EGamepadTextInputModeNormal = 0,
		k_EGamepadTextInputModePassword = 1,
		k_EGamepadTextInputModeSubmit = 2,
	};
typedef enum EGamepadTextInputMode EGamepadTextInputMode;

enum EGamepadTextInputLineMode
	{
		k_EGamepadTextInputLineModeSingleLine = 0,
		k_EGamepadTextInputLineModeMultipleLines = 1
	};
typedef enum EGamepadTextInputLineMode EGamepadTextInputLineMode;

enum EOverlayDirection
	{
		OverlayDirection_Up = 0,
		OverlayDirection_Down = 1,
		OverlayDirection_Left = 2,
		OverlayDirection_Right = 3,
		
		OverlayDirection_Count = 4,
	};
typedef enum EOverlayDirection EOverlayDirection;

// *********** 
// IVROverlay
// *********** 
typedef struct IVROverlay IVROverlay;
EVROverlayError	IVROverlay_FindOverlay(IVROverlay * this_, const char * pchOverlayKey, VROverlayHandle_t * pOverlayHandle);
EVROverlayError	IVROverlay_CreateOverlay(IVROverlay * this_, const char * pchOverlayKey, const char * pchOverlayFriendlyName, VROverlayHandle_t * pOverlayHandle);
EVROverlayError	IVROverlay_DestroyOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
EVROverlayError	IVROverlay_SetHighQualityOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
VROverlayHandle_t	IVROverlay_GetHighQualityOverlay(IVROverlay * this_);
uint32_t	IVROverlay_GetOverlayKey(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, char * pchValue, uint32_t unBufferSize, EVROverlayError * pError);
uint32_t	IVROverlay_GetOverlayName(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, char * pchValue, uint32_t unBufferSize, EVROverlayError * pError);
EVROverlayError	IVROverlay_GetOverlayImageData(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, void * pvBuffer, uint32_t unBufferSize, uint32_t * punWidth, uint32_t * punHeight);
const char *	IVROverlay_GetOverlayErrorNameFromEnum(IVROverlay * this_, EVROverlayError error);
EVROverlayError	IVROverlay_SetOverlayRenderingPid(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, uint32_t unPID);
uint32_t	IVROverlay_GetOverlayRenderingPid(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
EVROverlayError	IVROverlay_SetOverlayFlag(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled);
EVROverlayError	IVROverlay_GetOverlayFlag(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled);
EVROverlayError	IVROverlay_SetOverlayColor(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue);
EVROverlayError	IVROverlay_GetOverlayColor(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float * pfRed, float * pfGreen, float * pfBlue);
EVROverlayError	IVROverlay_SetOverlayAlpha(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float fAlpha);
EVROverlayError	IVROverlay_GetOverlayAlpha(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float * pfAlpha);
EVROverlayError	IVROverlay_SetOverlayWidthInMeters(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float fWidthInMeters);
EVROverlayError	IVROverlay_GetOverlayWidthInMeters(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float * pfWidthInMeters);
EVROverlayError	IVROverlay_SetOverlayAutoCurveDistanceRangeInMeters(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters);
EVROverlayError	IVROverlay_GetOverlayAutoCurveDistanceRangeInMeters(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float * pfMinDistanceInMeters, float * pfMaxDistanceInMeters);
EVROverlayError	IVROverlay_SetOverlayTextureColorSpace(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace);
EVROverlayError	IVROverlay_GetOverlayTextureColorSpace(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace);
EVROverlayError	IVROverlay_SetOverlayTextureBounds(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t * pOverlayTextureBounds);
EVROverlayError	IVROverlay_GetOverlayTextureBounds(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t * pOverlayTextureBounds);
EVROverlayError	IVROverlay_GetOverlayTransformType(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType);
EVROverlayError	IVROverlay_SetOverlayTransformAbsolute(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
EVROverlayError	IVROverlay_GetOverlayTransformAbsolute(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, HmdMatrix34_t * pmatTrackingOriginToOverlayTransform);
EVROverlayError	IVROverlay_SetOverlayTransformTrackedDeviceRelative(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
EVROverlayError	IVROverlay_GetOverlayTransformTrackedDeviceRelative(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t * punTrackedDevice, HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform);
EVROverlayError	IVROverlay_SetOverlayTransformTrackedDeviceComponent(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char * pchComponentName);
EVROverlayError	IVROverlay_GetOverlayTransformTrackedDeviceComponent(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t * punDeviceIndex, char * pchComponentName, uint32_t unComponentNameSize);
EVROverlayError	IVROverlay_ShowOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
EVROverlayError	IVROverlay_HideOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
bool	IVROverlay_IsOverlayVisible(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
EVROverlayError	IVROverlay_GetTransformForOverlayCoordinates(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t * pmatTransform);
bool	IVROverlay_PollNextOverlayEvent(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VREvent_t * pEvent, uint32_t uncbVREvent);
EVROverlayError	IVROverlay_GetOverlayInputMethod(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod * peInputMethod);
EVROverlayError	IVROverlay_SetOverlayInputMethod(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod);
EVROverlayError	IVROverlay_GetOverlayMouseScale(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, HmdVector2_t * pvecMouseScale);
EVROverlayError	IVROverlay_SetOverlayMouseScale(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, HmdVector2_t * pvecMouseScale);
bool	IVROverlay_ComputeOverlayIntersection(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayIntersectionParams_t * pParams, VROverlayIntersectionResults_t * pResults);
bool	IVROverlay_HandleControllerOverlayInteractionAsMouse(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex);
bool	IVROverlay_IsHoverTargetOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
VROverlayHandle_t	IVROverlay_GetGamepadFocusOverlay(IVROverlay * this_);
EVROverlayError	IVROverlay_SetGamepadFocusOverlay(IVROverlay * this_, VROverlayHandle_t ulNewFocusOverlay);
EVROverlayError	IVROverlay_SetOverlayNeighbor(IVROverlay * this_, EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo);
EVROverlayError	IVROverlay_MoveGamepadFocusToNeighbor(IVROverlay * this_, EOverlayDirection eDirection, VROverlayHandle_t ulFrom);
EVROverlayError	IVROverlay_SetOverlayTexture(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, Texture_t * pTexture);
EVROverlayError	IVROverlay_ClearOverlayTexture(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
EVROverlayError	IVROverlay_SetOverlayRaw(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, void * pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth);
EVROverlayError	IVROverlay_SetOverlayFromFile(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, const char * pchFilePath);
EVROverlayError	IVROverlay_GetOverlayTexture(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, void ** pNativeTextureHandle, void * pNativeTextureRef, uint32_t * pWidth, uint32_t * pHeight, uint32_t * pNativeFormat, ETextureType * pAPI, EColorSpace * pColorSpace);
EVROverlayError	IVROverlay_ReleaseNativeOverlayHandle(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, void * pNativeTextureHandle);
EVROverlayError	IVROverlay_CreateDashboardOverlay(IVROverlay * this_, const char * pchOverlayKey, const char * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle);
bool	IVROverlay_IsDashboardVisible(IVROverlay * this_);
bool	IVROverlay_IsActiveDashboardOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle);
EVROverlayError	IVROverlay_SetDashboardOverlaySceneProcess(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId);
EVROverlayError	IVROverlay_GetDashboardOverlaySceneProcess(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId);
void	IVROverlay_ShowDashboard(IVROverlay * this_, const char * pchOverlayToShow);
TrackedDeviceIndex_t	IVROverlay_GetPrimaryDashboardDevice(IVROverlay * this_);
EVROverlayError	IVROverlay_ShowKeyboard(IVROverlay * this_, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char * pchDescription, uint32_t unCharMax, const char * pchExistingText, bool bUseMinimalMode, uint64_t uUserValue);
EVROverlayError	IVROverlay_ShowKeyboardForOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char * pchDescription, uint32_t unCharMax, const char * pchExistingText, bool bUseMinimalMode, uint64_t uUserValue);
uint32_t	IVROverlay_GetKeyboardText(IVROverlay * this_, char * pchText, uint32_t cchText);
void	IVROverlay_HideKeyboard(IVROverlay * this_);
void	IVROverlay_SetKeyboardTransformAbsolute(IVROverlay * this_, ETrackingUniverseOrigin eTrackingOrigin, HmdMatrix34_t * pmatTrackingOriginToKeyboardTransform);
void	IVROverlay_SetKeyboardPositionForOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect);



static const char * const IVROverlay_Version = "IVROverlay_011";
static const char * const k_pch_Controller_Component_GDC2015 = "gdc2015";
static const char * const k_pch_Controller_Component_Base = "base";
static const char * const k_pch_Controller_Component_Tip = "tip";
static const char * const k_pch_Controller_Component_HandGrip = "handgrip";
static const char * const k_pch_Controller_Component_Status = "status";
enum EVRRenderModelError
{
	VRRenderModelError_None = 0,
	VRRenderModelError_Loading = 100,
	VRRenderModelError_NotSupported = 200,
	VRRenderModelError_InvalidArg = 300,
	VRRenderModelError_InvalidModel = 301,
	VRRenderModelError_NoShapes = 302,
	VRRenderModelError_MultipleShapes = 303,
	VRRenderModelError_TooManyIndices = 304,
	VRRenderModelError_MultipleTextures = 305,
	VRRenderModelError_InvalidTexture = 400,
};
typedef enum EVRRenderModelError EVRRenderModelError;

typedef uint32_t VRComponentProperties;
enum EVRComponentProperty
{
	VRComponentProperty_IsStatic = (1 << 0),
	VRComponentProperty_IsVisible = (1 << 1),
	VRComponentProperty_IsTouched = (1 << 2),
	VRComponentProperty_IsPressed = (1 << 3),
	VRComponentProperty_IsScrolled = (1 << 4),
};
typedef enum EVRComponentProperty EVRComponentProperty;

struct RenderModel_ComponentState_t
{
	HmdMatrix34_t mTrackingToComponentRenderModel;  // Transform required when drawing the component render model
	HmdMatrix34_t mTrackingToComponentLocal;        // Transform available for attaching to a local component coordinate system (-Z out from surface )
	VRComponentProperties uProperties;
};
typedef struct RenderModel_ComponentState_t RenderModel_ComponentState_t;

struct RenderModel_Vertex_t
{
	HmdVector3_t vPosition;		// position in meters in device space
	HmdVector3_t vNormal;
	float rfTextureCoord[2];
};
typedef struct RenderModel_Vertex_t RenderModel_Vertex_t;

struct RenderModel_TextureMap_t
{
	uint16_t unWidth, unHeight; // width and height of the texture map in pixels
	const uint8_t *rubTextureMapData;	// Map texture data. All textures are RGBA with 8 bits per channel per pixel. Data size is width * height * 4ub
};
typedef struct RenderModel_TextureMap_t RenderModel_TextureMap_t;

typedef int32_t TextureID_t;
struct RenderModel_t
{
	const RenderModel_Vertex_t *rVertexData;	// Vertex data for the mesh
	uint32_t unVertexCount;						// Number of vertices in the vertex data
	const uint16_t *rIndexData;					// Indices into the vertex data for each triangle
	uint32_t unTriangleCount;					// Number of triangles in the mesh. Index count is 3 * TriangleCount
	TextureID_t diffuseTextureId;				// Session unique texture identifier. Rendermodels which share the same texture will have the same id. <0 == texture not present
};
typedef struct RenderModel_t RenderModel_t;

struct RenderModel_ControllerMode_State_t
{
	bool bScrollWheelVisible; // is this controller currently set to be in a scroll wheel mode
};
typedef struct RenderModel_ControllerMode_State_t RenderModel_ControllerMode_State_t;

// *********** 
// IVRRenderModels
// *********** 
typedef struct IVRRenderModels IVRRenderModels;
EVRRenderModelError	IVRRenderModels_LoadRenderModel_Async(IVRRenderModels * this_, const char * pchRenderModelName, RenderModel_t ** ppRenderModel);
void	IVRRenderModels_FreeRenderModel(IVRRenderModels * this_, RenderModel_t * pRenderModel);
EVRRenderModelError	IVRRenderModels_LoadTexture_Async(IVRRenderModels * this_, TextureID_t textureId, RenderModel_TextureMap_t ** ppTexture);
void	IVRRenderModels_FreeTexture(IVRRenderModels * this_, RenderModel_TextureMap_t * pTexture);
EVRRenderModelError	IVRRenderModels_LoadTextureD3D11_Async(IVRRenderModels * this_, TextureID_t textureId, void * pD3D11Device, void ** ppD3D11Texture2D);
EVRRenderModelError	IVRRenderModels_LoadIntoTextureD3D11_Async(IVRRenderModels * this_, TextureID_t textureId, void * pDstTexture);
void	IVRRenderModels_FreeTextureD3D11(IVRRenderModels * this_, void * pD3D11Texture2D);
uint32_t	IVRRenderModels_GetRenderModelName(IVRRenderModels * this_, uint32_t unRenderModelIndex, char * pchRenderModelName, uint32_t unRenderModelNameLen);
uint32_t	IVRRenderModels_GetRenderModelCount(IVRRenderModels * this_);
uint32_t	IVRRenderModels_GetComponentCount(IVRRenderModels * this_, const char * pchRenderModelName);
uint32_t	IVRRenderModels_GetComponentName(IVRRenderModels * this_, const char * pchRenderModelName, uint32_t unComponentIndex, char * pchComponentName, uint32_t unComponentNameLen);
uint64_t	IVRRenderModels_GetComponentButtonMask(IVRRenderModels * this_, const char * pchRenderModelName, const char * pchComponentName);
uint32_t	IVRRenderModels_GetComponentRenderModelName(IVRRenderModels * this_, const char * pchRenderModelName, const char * pchComponentName, char * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen);
bool	IVRRenderModels_GetComponentState(IVRRenderModels * this_, const char * pchRenderModelName, const char * pchComponentName, VRControllerState_t * pControllerState, RenderModel_ControllerMode_State_t * pState, RenderModel_ComponentState_t * pComponentState);
bool	IVRRenderModels_RenderModelHasComponent(IVRRenderModels * this_, const char * pchRenderModelName, const char * pchComponentName);



static const char * const IVRRenderModels_Version = "IVRRenderModels_005";
// *********** 
// IVRExtendedDisplay
// *********** 
typedef struct IVRExtendedDisplay IVRExtendedDisplay;
void	IVRExtendedDisplay_GetWindowBounds(IVRExtendedDisplay * this_, int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
void	IVRExtendedDisplay_GetEyeOutputViewport(IVRExtendedDisplay * this_, EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight);
void	IVRExtendedDisplay_GetDXGIOutputInfo(IVRExtendedDisplay * this_, int32_t * pnAdapterIndex, int32_t * pnAdapterOutputIndex);



static const char * const IVRExtendedDisplay_Version = "IVRExtendedDisplay_001";
IVRSystem * VR_Init(EVRInitError * peError, EVRApplicationType eApplicationType);
void VR_Shutdown();
VR_INTERFACE bool VR_CALLTYPE VR_IsHmdPresent();
VR_INTERFACE bool VR_CALLTYPE VR_IsRuntimeInstalled();
VR_INTERFACE const char *VR_CALLTYPE VR_RuntimePath();
VR_INTERFACE const char *VR_CALLTYPE VR_GetVRInitErrorAsSymbol( EVRInitError error );
VR_INTERFACE const char *VR_CALLTYPE VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );
VR_INTERFACE void *VR_CALLTYPE VR_GetGenericInterface( const char *pchInterfaceVersion, EVRInitError *peError );
VR_INTERFACE bool VR_CALLTYPE VR_IsInterfaceVersionValid( const char *pchInterfaceVersion );
VR_INTERFACE uint32_t VR_CALLTYPE VR_GetInitToken();
typedef EVRInitError HmdError;
typedef EVREye Hmd_Eye;
//typedef EGraphicsAPIConvention GraphicsAPIConvention;
typedef ETextureType ETextureType;
typedef EColorSpace ColorSpace;
typedef ETrackingResult HmdTrackingResult;
typedef ETrackedDeviceClass TrackedDeviceClass;
typedef ETrackingUniverseOrigin TrackingUniverseOrigin;
typedef ETrackedDeviceProperty TrackedDeviceProperty;
typedef ETrackedPropertyError TrackedPropertyError;
typedef EVRSubmitFlags VRSubmitFlags_t;
typedef EVRState VRState_t;
typedef ECollisionBoundsStyle CollisionBoundsStyle_t;
typedef EVROverlayError VROverlayError;
typedef EVRFirmwareError VRFirmwareError;
typedef EVRCompositorError VRCompositorError;
uint32_t * VRToken();
// *********** 
// COpenVRContext
// *********** 
typedef struct COpenVRContext COpenVRContext;
COpenVRContext *COpenVRContext_New();
void	COpenVRContext_Clear(COpenVRContext * this_);
void	COpenVRContext_CheckClear(COpenVRContext * this_);
IVRSystem *	COpenVRContext_VRSystem(COpenVRContext * this_);
IVRChaperone *	COpenVRContext_VRChaperone(COpenVRContext * this_);
IVRChaperoneSetup *	COpenVRContext_VRChaperoneSetup(COpenVRContext * this_);
IVRCompositor *	COpenVRContext_VRCompositor(COpenVRContext * this_);
IVROverlay *	COpenVRContext_VROverlay(COpenVRContext * this_);
IVRRenderModels *	COpenVRContext_VRRenderModels(COpenVRContext * this_);
IVRExtendedDisplay *	COpenVRContext_VRExtendedDisplay(COpenVRContext * this_);
IVRSettings *	COpenVRContext_VRSettings(COpenVRContext * this_);
IVRApplications *	COpenVRContext_VRApplications(COpenVRContext * this_);



COpenVRContext * OpenVRInternal_ModuleContext();
IVRSystem * VRSystem();
IVRChaperone * VRChaperone();
IVRChaperoneSetup * VRChaperoneSetup();
IVRCompositor * VRCompositor();
IVROverlay * VROverlay();
IVRRenderModels * VRRenderModels();
IVRApplications * VRApplications();
IVRSettings * VRSettings();
IVRExtendedDisplay * VRExtendedDisplay();
VR_INTERFACE uint32_t VR_CALLTYPE VR_InitInternal( EVRInitError *peError, EVRApplicationType eApplicationType );
VR_INTERFACE void VR_CALLTYPE VR_ShutdownInternal();

}