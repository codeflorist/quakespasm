#include "openvr.h"
extern "C" {
typedef vr::glSharedTextureHandle_t glSharedTextureHandle_t;
typedef vr::glInt_t glInt_t;
typedef vr::glUInt_t glUInt_t;
typedef vr::HmdMatrix34_t HmdMatrix34_t;
typedef vr::HmdMatrix44_t HmdMatrix44_t;
typedef vr::HmdVector3_t HmdVector3_t;
typedef vr::HmdVector4_t HmdVector4_t;
typedef vr::HmdVector3d_t HmdVector3d_t;
typedef vr::HmdVector2_t HmdVector2_t;
typedef vr::HmdQuaternion_t HmdQuaternion_t;
typedef vr::HmdColor_t HmdColor_t;
typedef vr::HmdQuad_t HmdQuad_t;
typedef vr::HmdRect2_t HmdRect2_t;
typedef vr::DistortionCoordinates_t DistortionCoordinates_t;
typedef vr::EVREye EVREye;
//typedef vr::EGraphicsAPIConvention EGraphicsAPIConvention;
typedef vr::ETextureType ETextureType;
typedef vr::EColorSpace EColorSpace;
typedef vr::Texture_t Texture_t;
typedef vr::ETrackingResult ETrackingResult;
typedef vr::TrackedDeviceIndex_t TrackedDeviceIndex_t;
typedef vr::ETrackedDeviceClass ETrackedDeviceClass;
typedef vr::ETrackedControllerRole ETrackedControllerRole;
typedef vr::TrackedDevicePose_t TrackedDevicePose_t;
typedef vr::ETrackingUniverseOrigin ETrackingUniverseOrigin;
typedef vr::ETrackedDeviceProperty ETrackedDeviceProperty;
typedef vr::ETrackedPropertyError ETrackedPropertyError;
typedef vr::VRTextureBounds_t VRTextureBounds_t;
typedef vr::EVRSubmitFlags EVRSubmitFlags;
typedef vr::EVRState EVRState;
typedef vr::EVREventType EVREventType;
typedef vr::EDeviceActivityLevel EDeviceActivityLevel;
typedef vr::EVRButtonId EVRButtonId;
uint64_t ButtonMaskFromId(EVRButtonId id) {
    return vr::ButtonMaskFromId(id);
}

typedef vr::VREvent_Controller_t VREvent_Controller_t;
typedef vr::EVRMouseButton EVRMouseButton;
typedef vr::VREvent_Mouse_t VREvent_Mouse_t;
typedef vr::VREvent_Scroll_t VREvent_Scroll_t;
typedef vr::VREvent_TouchPadMove_t VREvent_TouchPadMove_t;
typedef vr::VREvent_Notification_t VREvent_Notification_t;
typedef vr::VREvent_Process_t VREvent_Process_t;
typedef vr::VREvent_Overlay_t VREvent_Overlay_t;
typedef vr::VREvent_Status_t VREvent_Status_t;
typedef vr::VREvent_Keyboard_t VREvent_Keyboard_t;
typedef vr::VREvent_Ipd_t VREvent_Ipd_t;
typedef vr::VREvent_Chaperone_t VREvent_Chaperone_t;
typedef vr::VREvent_Reserved_t VREvent_Reserved_t;
typedef vr::VREvent_PerformanceTest_t VREvent_PerformanceTest_t;
typedef vr::VREvent_SeatedZeroPoseReset_t VREvent_SeatedZeroPoseReset_t;
typedef vr::VREvent_Data_t VREvent_Data_t;
typedef vr::VREvent_t VREvent_t;
typedef vr::HiddenAreaMesh_t HiddenAreaMesh_t;
typedef vr::EVRControllerAxisType EVRControllerAxisType;
typedef vr::VRControllerAxis_t VRControllerAxis_t;
typedef vr::VRControllerState001_t VRControllerState001_t;
typedef vr::VRControllerState_t VRControllerState_t;
typedef vr::EVRControllerEventOutputType EVRControllerEventOutputType;
typedef vr::ECollisionBoundsStyle ECollisionBoundsStyle;
typedef vr::Compositor_OverlaySettings Compositor_OverlaySettings;
typedef vr::VROverlayHandle_t VROverlayHandle_t;
typedef vr::EVROverlayError EVROverlayError;
typedef vr::EVRApplicationType EVRApplicationType;
typedef vr::EVRFirmwareError EVRFirmwareError;
typedef vr::EVRNotificationError EVRNotificationError;
typedef vr::EVRInitError EVRInitError;
typedef vr::IVRSystem IVRSystem;
void IVRSystem_GetRecommendedRenderTargetSize(IVRSystem * this_, uint32_t * pnWidth, uint32_t * pnHeight) {
    return this_->GetRecommendedRenderTargetSize(pnWidth, pnHeight);
}

HmdMatrix44_t IVRSystem_GetProjectionMatrix(IVRSystem * this_, EVREye eEye, float fNearZ, float fFarZ) {
    return this_->GetProjectionMatrix(eEye, fNearZ, fFarZ);
}

void IVRSystem_GetProjectionRaw(IVRSystem * this_, EVREye eEye, float * pfLeft, float * pfRight, float * pfTop, float * pfBottom) {
    return this_->GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom);
}

bool IVRSystem_ComputeDistortion(IVRSystem * this_, EVREye eEye, float fU, float fV, DistortionCoordinates_t *pDistortionCoordinates) {
    return this_->ComputeDistortion(eEye, fU, fV, pDistortionCoordinates);
}

HmdMatrix34_t IVRSystem_GetEyeToHeadTransform(IVRSystem * this_, EVREye eEye) {
    return this_->GetEyeToHeadTransform(eEye);
}

bool IVRSystem_GetTimeSinceLastVsync(IVRSystem * this_, float * pfSecondsSinceLastVsync, uint64_t * pulFrameCounter) {
    return this_->GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter);
}

int32_t IVRSystem_GetD3D9AdapterIndex(IVRSystem * this_) {
    return this_->GetD3D9AdapterIndex();
}

void IVRSystem_GetDXGIOutputInfo(IVRSystem * this_, int32_t * pnAdapterIndex) {
    return this_->GetDXGIOutputInfo(pnAdapterIndex);
}

bool IVRSystem_IsDisplayOnDesktop(IVRSystem * this_) {
    return this_->IsDisplayOnDesktop();
}

bool IVRSystem_SetDisplayVisibility(IVRSystem * this_, bool bIsVisibleOnDesktop) {
    return this_->SetDisplayVisibility(bIsVisibleOnDesktop);
}

void IVRSystem_GetDeviceToAbsoluteTrackingPose(IVRSystem * this_, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, TrackedDevicePose_t * pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount) {
    return this_->GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount);
}

void IVRSystem_ResetSeatedZeroPose(IVRSystem * this_) {
    return this_->ResetSeatedZeroPose();
}

HmdMatrix34_t IVRSystem_GetSeatedZeroPoseToStandingAbsoluteTrackingPose(IVRSystem * this_) {
    return this_->GetSeatedZeroPoseToStandingAbsoluteTrackingPose();
}

HmdMatrix34_t IVRSystem_GetRawZeroPoseToStandingAbsoluteTrackingPose(IVRSystem * this_) {
    return this_->GetRawZeroPoseToStandingAbsoluteTrackingPose();
}

uint32_t IVRSystem_GetSortedTrackedDeviceIndicesOfClass(IVRSystem * this_, ETrackedDeviceClass eTrackedDeviceClass, TrackedDeviceIndex_t * punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex) {
    return this_->GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex);
}

EDeviceActivityLevel IVRSystem_GetTrackedDeviceActivityLevel(IVRSystem * this_, TrackedDeviceIndex_t unDeviceId) {
    return this_->GetTrackedDeviceActivityLevel(unDeviceId);
}

void IVRSystem_ApplyTransform(IVRSystem * this_, TrackedDevicePose_t * pOutputPose, TrackedDevicePose_t * pTrackedDevicePose, HmdMatrix34_t * pTransform) {
    return this_->ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform);
}

TrackedDeviceIndex_t IVRSystem_GetTrackedDeviceIndexForControllerRole(IVRSystem * this_, ETrackedControllerRole unDeviceType) {
    return this_->GetTrackedDeviceIndexForControllerRole(unDeviceType);
}

ETrackedControllerRole IVRSystem_GetControllerRoleForTrackedDeviceIndex(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex) {
    return this_->GetControllerRoleForTrackedDeviceIndex(unDeviceIndex);
}

ETrackedDeviceClass IVRSystem_GetTrackedDeviceClass(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex) {
    return this_->GetTrackedDeviceClass(unDeviceIndex);
}

bool IVRSystem_IsTrackedDeviceConnected(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex) {
    return this_->IsTrackedDeviceConnected(unDeviceIndex);
}

bool IVRSystem_GetBoolTrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError) {
    return this_->GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError);
}

float IVRSystem_GetFloatTrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError) {
    return this_->GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError);
}

int32_t IVRSystem_GetInt32TrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError) {
    return this_->GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError);
}

uint64_t IVRSystem_GetUint64TrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError) {
    return this_->GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError);
}

HmdMatrix34_t IVRSystem_GetMatrix34TrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError * pError) {
    return this_->GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError);
}

uint32_t IVRSystem_GetStringTrackedDeviceProperty(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, char * pchValue, uint32_t unBufferSize, ETrackedPropertyError * pError) {
    return this_->GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError);
}

const char * IVRSystem_GetPropErrorNameFromEnum(IVRSystem * this_, ETrackedPropertyError error) {
    return this_->GetPropErrorNameFromEnum(error);
}

bool IVRSystem_PollNextEvent(IVRSystem * this_, VREvent_t * pEvent, uint32_t uncbVREvent) {
    return this_->PollNextEvent(pEvent, uncbVREvent);
}

bool IVRSystem_PollNextEventWithPose(IVRSystem * this_, ETrackingUniverseOrigin eOrigin, VREvent_t * pEvent, uint32_t uncbVREvent, TrackedDevicePose_t * pTrackedDevicePose) {
    return this_->PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose);
}

const char * IVRSystem_GetEventTypeNameFromEnum(IVRSystem * this_, EVREventType eType) {
    return this_->GetEventTypeNameFromEnum(eType);
}

HiddenAreaMesh_t IVRSystem_GetHiddenAreaMesh(IVRSystem * this_, EVREye eEye) {
    return this_->GetHiddenAreaMesh(eEye);
}

bool IVRSystem_GetControllerState(IVRSystem * this_, TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t * pControllerState) {
    return this_->GetControllerState(unControllerDeviceIndex, pControllerState, sizeof(VRControllerState_t));
}

bool IVRSystem_GetControllerStateWithPose(IVRSystem * this_, ETrackingUniverseOrigin eOrigin, TrackedDeviceIndex_t unControllerDeviceIndex, VRControllerState_t * pControllerState, TrackedDevicePose_t * pTrackedDevicePose) {
    return this_->GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, sizeof(VRControllerState_t), pTrackedDevicePose);
}

void IVRSystem_TriggerHapticPulse(IVRSystem * this_, TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec) {
    return this_->TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec);
}

const char * IVRSystem_GetButtonIdNameFromEnum(IVRSystem * this_, EVRButtonId eButtonId) {
    return this_->GetButtonIdNameFromEnum(eButtonId);
}

const char * IVRSystem_GetControllerAxisTypeNameFromEnum(IVRSystem * this_, EVRControllerAxisType eAxisType) {
    return this_->GetControllerAxisTypeNameFromEnum(eAxisType);
}

//bool IVRSystem_CaptureInputFocus(IVRSystem * this_) {
//    return this_->CaptureInputFocus();
//}
//
//void IVRSystem_ReleaseInputFocus(IVRSystem * this_) {
//    return this_->ReleaseInputFocus();
//}
//
//bool IVRSystem_IsInputFocusCapturedByAnotherProcess(IVRSystem * this_) {
//    return this_->IsInputFocusCapturedByAnotherProcess();
//}

uint32_t IVRSystem_DriverDebugRequest(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex, const char * pchRequest, char * pchResponseBuffer, uint32_t unResponseBufferSize) {
    return this_->DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize);
}

EVRFirmwareError IVRSystem_PerformFirmwareUpdate(IVRSystem * this_, TrackedDeviceIndex_t unDeviceIndex) {
    return this_->PerformFirmwareUpdate(unDeviceIndex);
}

void IVRSystem_AcknowledgeQuit_Exiting(IVRSystem * this_) {
    return this_->AcknowledgeQuit_Exiting();
}

void IVRSystem_AcknowledgeQuit_UserPrompt(IVRSystem * this_) {
    return this_->AcknowledgeQuit_UserPrompt();
}

typedef vr::EVRApplicationError EVRApplicationError;
typedef vr::EVRApplicationProperty EVRApplicationProperty;
typedef vr::EVRApplicationTransitionState EVRApplicationTransitionState;
typedef vr::AppOverrideKeys_t AppOverrideKeys_t;
typedef vr::IVRApplications IVRApplications;
EVRApplicationError IVRApplications_AddApplicationManifest(IVRApplications * this_, const char * pchApplicationManifestFullPath, bool bTemporary) {
    return this_->AddApplicationManifest(pchApplicationManifestFullPath, bTemporary);
}

EVRApplicationError IVRApplications_RemoveApplicationManifest(IVRApplications * this_, const char * pchApplicationManifestFullPath) {
    return this_->RemoveApplicationManifest(pchApplicationManifestFullPath);
}

bool IVRApplications_IsApplicationInstalled(IVRApplications * this_, const char * pchAppKey) {
    return this_->IsApplicationInstalled(pchAppKey);
}

uint32_t IVRApplications_GetApplicationCount(IVRApplications * this_) {
    return this_->GetApplicationCount();
}

EVRApplicationError IVRApplications_GetApplicationKeyByIndex(IVRApplications * this_, uint32_t unApplicationIndex, char * pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
    return this_->GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen);
}

EVRApplicationError IVRApplications_GetApplicationKeyByProcessId(IVRApplications * this_, uint32_t unProcessId, char * pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
    return this_->GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen);
}

EVRApplicationError IVRApplications_LaunchApplication(IVRApplications * this_, const char * pchAppKey) {
    return this_->LaunchApplication(pchAppKey);
}

EVRApplicationError IVRApplications_LaunchTemplateApplication(IVRApplications * this_, const char * pchTemplateAppKey, const char * pchNewAppKey, AppOverrideKeys_t * pKeys, uint32_t unKeys) {
    return this_->LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys);
}

EVRApplicationError IVRApplications_LaunchDashboardOverlay(IVRApplications * this_, const char * pchAppKey) {
    return this_->LaunchDashboardOverlay(pchAppKey);
}

bool IVRApplications_CancelApplicationLaunch(IVRApplications * this_, const char * pchAppKey) {
    return this_->CancelApplicationLaunch(pchAppKey);
}

EVRApplicationError IVRApplications_IdentifyApplication(IVRApplications * this_, uint32_t unProcessId, const char * pchAppKey) {
    return this_->IdentifyApplication(unProcessId, pchAppKey);
}

uint32_t IVRApplications_GetApplicationProcessId(IVRApplications * this_, const char * pchAppKey) {
    return this_->GetApplicationProcessId(pchAppKey);
}

const char * IVRApplications_GetApplicationsErrorNameFromEnum(IVRApplications * this_, EVRApplicationError error) {
    return this_->GetApplicationsErrorNameFromEnum(error);
}

uint32_t IVRApplications_GetApplicationPropertyString(IVRApplications * this_, const char * pchAppKey, EVRApplicationProperty eProperty, char * pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError * peError) {
    return this_->GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError);
}

bool IVRApplications_GetApplicationPropertyBool(IVRApplications * this_, const char * pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError * peError) {
    return this_->GetApplicationPropertyBool(pchAppKey, eProperty, peError);
}

uint64_t IVRApplications_GetApplicationPropertyUint64(IVRApplications * this_, const char * pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError * peError) {
    return this_->GetApplicationPropertyUint64(pchAppKey, eProperty, peError);
}

EVRApplicationError IVRApplications_SetApplicationAutoLaunch(IVRApplications * this_, const char * pchAppKey, bool bAutoLaunch) {
    return this_->SetApplicationAutoLaunch(pchAppKey, bAutoLaunch);
}

bool IVRApplications_GetApplicationAutoLaunch(IVRApplications * this_, const char * pchAppKey) {
    return this_->GetApplicationAutoLaunch(pchAppKey);
}

EVRApplicationError IVRApplications_GetStartingApplication(IVRApplications * this_, char * pchAppKeyBuffer, uint32_t unAppKeyBufferLen) {
    return this_->GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen);
}

EVRApplicationTransitionState IVRApplications_GetTransitionState(IVRApplications * this_) {
    return this_->GetTransitionState();
}

EVRApplicationError IVRApplications_PerformApplicationPrelaunchCheck(IVRApplications * this_, const char * pchAppKey) {
    return this_->PerformApplicationPrelaunchCheck(pchAppKey);
}

const char * IVRApplications_GetApplicationsTransitionStateNameFromEnum(IVRApplications * this_, EVRApplicationTransitionState state) {
    return this_->GetApplicationsTransitionStateNameFromEnum(state);
}

bool IVRApplications_IsQuitUserPromptRequested(IVRApplications * this_) {
    return this_->IsQuitUserPromptRequested();
}

EVRApplicationError IVRApplications_LaunchInternalProcess(IVRApplications * this_, const char * pchBinaryPath, const char * pchArguments, const char * pchWorkingDirectory) {
    return this_->LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory);
}

typedef vr::EVRSettingsError EVRSettingsError;
typedef vr::IVRSettings IVRSettings;
const char * IVRSettings_GetSettingsErrorNameFromEnum(IVRSettings * this_, EVRSettingsError eError) {
    return this_->GetSettingsErrorNameFromEnum(eError);
}

bool IVRSettings_Sync(IVRSettings * this_, bool bForce, EVRSettingsError * peError) {
    return this_->Sync(bForce, peError);
}

bool IVRSettings_GetBool(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError) {
    return this_->GetBool(pchSection, pchSettingsKey, peError);
}

void IVRSettings_SetBool(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, bool bValue, EVRSettingsError * peError) {
    return this_->SetBool(pchSection, pchSettingsKey, bValue, peError);
}

int32_t IVRSettings_GetInt32(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError) {
    return this_->GetInt32(pchSection, pchSettingsKey, peError);
}

void IVRSettings_SetInt32(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, int32_t nValue, EVRSettingsError * peError) {
    return this_->SetInt32(pchSection, pchSettingsKey, nValue, peError);
}

float IVRSettings_GetFloat(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError) {
    return this_->GetFloat(pchSection, pchSettingsKey, peError);
}

void IVRSettings_SetFloat(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, float flValue, EVRSettingsError * peError) {
    return this_->SetFloat(pchSection, pchSettingsKey, flValue, peError);
}

void IVRSettings_GetString(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, char * pchValue, uint32_t unValueLen, EVRSettingsError * peError) {
    return this_->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
}

void IVRSettings_SetString(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, const char * pchValue, EVRSettingsError * peError) {
    return this_->SetString(pchSection, pchSettingsKey, pchValue, peError);
}

void IVRSettings_RemoveSection(IVRSettings * this_, const char * pchSection, EVRSettingsError * peError) {
    return this_->RemoveSection(pchSection, peError);
}

void IVRSettings_RemoveKeyInSection(IVRSettings * this_, const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError) {
    return this_->RemoveKeyInSection(pchSection, pchSettingsKey, peError);
}

typedef vr::ChaperoneCalibrationState ChaperoneCalibrationState;
typedef vr::IVRChaperone IVRChaperone;
ChaperoneCalibrationState IVRChaperone_GetCalibrationState(IVRChaperone * this_) {
    return this_->GetCalibrationState();
}

bool IVRChaperone_GetPlayAreaSize(IVRChaperone * this_, float * pSizeX, float * pSizeZ) {
    return this_->GetPlayAreaSize(pSizeX, pSizeZ);
}

bool IVRChaperone_GetPlayAreaRect(IVRChaperone * this_, HmdQuad_t * rect) {
    return this_->GetPlayAreaRect(rect);
}

void IVRChaperone_ReloadInfo(IVRChaperone * this_) {
    return this_->ReloadInfo();
}

void IVRChaperone_SetSceneColor(IVRChaperone * this_, HmdColor_t color) {
    return this_->SetSceneColor(color);
}

void IVRChaperone_GetBoundsColor(IVRChaperone * this_, HmdColor_t * pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t * pOutputCameraColor) {
    return this_->GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor);
}

bool IVRChaperone_AreBoundsVisible(IVRChaperone * this_) {
    return this_->AreBoundsVisible();
}

void IVRChaperone_ForceBoundsVisible(IVRChaperone * this_, bool bForce) {
    return this_->ForceBoundsVisible(bForce);
}

typedef vr::EChaperoneConfigFile EChaperoneConfigFile;
typedef vr::EChaperoneImportFlags EChaperoneImportFlags;
typedef vr::IVRChaperoneSetup IVRChaperoneSetup;
bool IVRChaperoneSetup_CommitWorkingCopy(IVRChaperoneSetup * this_, EChaperoneConfigFile configFile) {
    return this_->CommitWorkingCopy(configFile);
}

void IVRChaperoneSetup_RevertWorkingCopy(IVRChaperoneSetup * this_) {
    return this_->RevertWorkingCopy();
}

bool IVRChaperoneSetup_GetWorkingPlayAreaSize(IVRChaperoneSetup * this_, float * pSizeX, float * pSizeZ) {
    return this_->GetWorkingPlayAreaSize(pSizeX, pSizeZ);
}

bool IVRChaperoneSetup_GetWorkingPlayAreaRect(IVRChaperoneSetup * this_, HmdQuad_t * rect) {
    return this_->GetWorkingPlayAreaRect(rect);
}

bool IVRChaperoneSetup_GetWorkingCollisionBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t * punQuadsCount) {
    return this_->GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
}

bool IVRChaperoneSetup_GetLiveCollisionBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t * punQuadsCount) {
    return this_->GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount);
}

bool IVRChaperoneSetup_GetWorkingSeatedZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose) {
    return this_->GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
}

bool IVRChaperoneSetup_GetWorkingStandingZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pmatStandingZeroPoseToRawTrackingPose) {
    return this_->GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose);
}

void IVRChaperoneSetup_SetWorkingPlayAreaSize(IVRChaperoneSetup * this_, float sizeX, float sizeZ) {
    return this_->SetWorkingPlayAreaSize(sizeX, sizeZ);
}

void IVRChaperoneSetup_SetWorkingCollisionBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t unQuadsCount) {
    return this_->SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount);
}

void IVRChaperoneSetup_SetWorkingSeatedZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pMatSeatedZeroPoseToRawTrackingPose) {
    return this_->SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose);
}

void IVRChaperoneSetup_SetWorkingStandingZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pMatStandingZeroPoseToRawTrackingPose) {
    return this_->SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose);
}

void IVRChaperoneSetup_ReloadFromDisk(IVRChaperoneSetup * this_, EChaperoneConfigFile configFile) {
    return this_->ReloadFromDisk(configFile);
}

bool IVRChaperoneSetup_GetLiveSeatedZeroPoseToRawTrackingPose(IVRChaperoneSetup * this_, HmdMatrix34_t * pmatSeatedZeroPoseToRawTrackingPose) {
    return this_->GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose);
}

void IVRChaperoneSetup_SetWorkingCollisionBoundsTagsInfo(IVRChaperoneSetup * this_, uint8_t * pTagsBuffer, uint32_t unTagCount) {
    return this_->SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount);
}

bool IVRChaperoneSetup_GetLiveCollisionBoundsTagsInfo(IVRChaperoneSetup * this_, uint8_t * pTagsBuffer, uint32_t * punTagCount) {
    return this_->GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount);
}

bool IVRChaperoneSetup_SetWorkingPhysicalBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t unQuadsCount) {
    return this_->SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount);
}

bool IVRChaperoneSetup_GetLivePhysicalBoundsInfo(IVRChaperoneSetup * this_, HmdQuad_t * pQuadsBuffer, uint32_t * punQuadsCount) {
    return this_->GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount);
}

bool IVRChaperoneSetup_ExportLiveToBuffer(IVRChaperoneSetup * this_, char * pBuffer, uint32_t * pnBufferLength) {
    return this_->ExportLiveToBuffer(pBuffer, pnBufferLength);
}

bool IVRChaperoneSetup_ImportFromBufferToWorking(IVRChaperoneSetup * this_, const char * pBuffer, uint32_t nImportFlags) {
    return this_->ImportFromBufferToWorking(pBuffer, nImportFlags);
}

typedef vr::EVRCompositorError EVRCompositorError;
typedef vr::Compositor_FrameTiming Compositor_FrameTiming;
typedef vr::IVRCompositor IVRCompositor;
void IVRCompositor_SetTrackingSpace(IVRCompositor * this_, ETrackingUniverseOrigin eOrigin) {
    return this_->SetTrackingSpace(eOrigin);
}

ETrackingUniverseOrigin IVRCompositor_GetTrackingSpace(IVRCompositor * this_) {
    return this_->GetTrackingSpace();
}

EVRCompositorError IVRCompositor_WaitGetPoses(IVRCompositor * this_, TrackedDevicePose_t * pRenderPoseArray, uint32_t unRenderPoseArrayCount, TrackedDevicePose_t * pGamePoseArray, uint32_t unGamePoseArrayCount) {
    return this_->WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
}

EVRCompositorError IVRCompositor_GetLastPoses(IVRCompositor * this_, TrackedDevicePose_t * pRenderPoseArray, uint32_t unRenderPoseArrayCount, TrackedDevicePose_t * pGamePoseArray, uint32_t unGamePoseArrayCount) {
    return this_->GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount);
}

EVRCompositorError IVRCompositor_GetLastPoseForTrackedDeviceIndex(IVRCompositor * this_, TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t * pOutputPose, TrackedDevicePose_t * pOutputGamePose) {
    return this_->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose);
}

EVRCompositorError IVRCompositor_Submit(IVRCompositor * this_, EVREye eEye, Texture_t * pTexture) {
    return this_->Submit(eEye, pTexture);
}

EVRCompositorError IVRCompositor_Submit_Bounds(IVRCompositor * this_, EVREye eEye, Texture_t * pTexture, VRTextureBounds_t * pBounds, EVRSubmitFlags nSubmitFlags) {
    return this_->Submit(eEye, pTexture, pBounds, nSubmitFlags);
}

void IVRCompositor_ClearLastSubmittedFrame(IVRCompositor * this_) {
    return this_->ClearLastSubmittedFrame();
}

void IVRCompositor_PostPresentHandoff(IVRCompositor * this_) {
    return this_->PostPresentHandoff();
}

bool IVRCompositor_GetFrameTiming(IVRCompositor * this_, Compositor_FrameTiming * pTiming, uint32_t unFramesAgo) {
    return this_->GetFrameTiming(pTiming, unFramesAgo);
}

float IVRCompositor_GetFrameTimeRemaining(IVRCompositor * this_) {
    return this_->GetFrameTimeRemaining();
}

void IVRCompositor_FadeToColor(IVRCompositor * this_, float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) {
    return this_->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
}

void IVRCompositor_FadeGrid(IVRCompositor * this_, float fSeconds, bool bFadeIn) {
    return this_->FadeGrid(fSeconds, bFadeIn);
}

EVRCompositorError IVRCompositor_SetSkyboxOverride(IVRCompositor * this_, Texture_t * pTextures, uint32_t unTextureCount) {
    return this_->SetSkyboxOverride(pTextures, unTextureCount);
}

void IVRCompositor_ClearSkyboxOverride(IVRCompositor * this_) {
    return this_->ClearSkyboxOverride();
}

void IVRCompositor_CompositorBringToFront(IVRCompositor * this_) {
    return this_->CompositorBringToFront();
}

void IVRCompositor_CompositorGoToBack(IVRCompositor * this_) {
    return this_->CompositorGoToBack();
}

void IVRCompositor_CompositorQuit(IVRCompositor * this_) {
    return this_->CompositorQuit();
}

bool IVRCompositor_IsFullscreen(IVRCompositor * this_) {
    return this_->IsFullscreen();
}

uint32_t IVRCompositor_GetCurrentSceneFocusProcess(IVRCompositor * this_) {
    return this_->GetCurrentSceneFocusProcess();
}

uint32_t IVRCompositor_GetLastFrameRenderer(IVRCompositor * this_) {
    return this_->GetLastFrameRenderer();
}

bool IVRCompositor_CanRenderScene(IVRCompositor * this_) {
    return this_->CanRenderScene();
}

void IVRCompositor_ShowMirrorWindow(IVRCompositor * this_) {
    return this_->ShowMirrorWindow();
}

void IVRCompositor_HideMirrorWindow(IVRCompositor * this_) {
    return this_->HideMirrorWindow();
}

bool IVRCompositor_IsMirrorWindowVisible(IVRCompositor * this_) {
    return this_->IsMirrorWindowVisible();
}

void IVRCompositor_CompositorDumpImages(IVRCompositor * this_) {
    return this_->CompositorDumpImages();
}

bool IVRCompositor_ShouldAppRenderWithLowResources(IVRCompositor * this_) {
    return this_->ShouldAppRenderWithLowResources();
}

void IVRCompositor_ForceInterleavedReprojectionOn(IVRCompositor * this_, bool bOverride) {
    return this_->ForceInterleavedReprojectionOn(bOverride);
}

typedef vr::NotificationBitmap_t NotificationBitmap_t;
typedef vr::EVRNotificationType EVRNotificationType;
typedef vr::EVRNotificationStyle EVRNotificationStyle;
typedef vr::VRNotificationId VRNotificationId;
typedef vr::IVRNotifications IVRNotifications;
EVRNotificationError IVRNotifications_CreateNotification(IVRNotifications * this_, VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char * pchText, EVRNotificationStyle style, NotificationBitmap_t * pImage, VRNotificationId * pNotificationId) {
    return this_->CreateNotification(ulOverlayHandle, ulUserValue, type, pchText, style, pImage, pNotificationId);
}

EVRNotificationError IVRNotifications_RemoveNotification(IVRNotifications * this_, VRNotificationId notificationId) {
    return this_->RemoveNotification(notificationId);
}

typedef vr::VROverlayInputMethod VROverlayInputMethod;
typedef vr::VROverlayTransformType VROverlayTransformType;
typedef vr::VROverlayFlags VROverlayFlags;
typedef vr::VROverlayIntersectionParams_t VROverlayIntersectionParams_t;
typedef vr::VROverlayIntersectionResults_t VROverlayIntersectionResults_t;
typedef vr::EGamepadTextInputMode EGamepadTextInputMode;
typedef vr::EGamepadTextInputLineMode EGamepadTextInputLineMode;
typedef vr::EOverlayDirection EOverlayDirection;
typedef vr::IVROverlay IVROverlay;
EVROverlayError IVROverlay_FindOverlay(IVROverlay * this_, const char * pchOverlayKey, VROverlayHandle_t * pOverlayHandle) {
    return this_->FindOverlay(pchOverlayKey, pOverlayHandle);
}

EVROverlayError IVROverlay_CreateOverlay(IVROverlay * this_, const char * pchOverlayKey, const char * pchOverlayFriendlyName, VROverlayHandle_t * pOverlayHandle) {
    return this_->CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle);
}

EVROverlayError IVROverlay_DestroyOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->DestroyOverlay(ulOverlayHandle);
}

EVROverlayError IVROverlay_SetHighQualityOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->SetHighQualityOverlay(ulOverlayHandle);
}

VROverlayHandle_t IVROverlay_GetHighQualityOverlay(IVROverlay * this_) {
    return this_->GetHighQualityOverlay();
}

uint32_t IVROverlay_GetOverlayKey(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, char * pchValue, uint32_t unBufferSize, EVROverlayError * pError) {
    return this_->GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError);
}

uint32_t IVROverlay_GetOverlayName(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, char * pchValue, uint32_t unBufferSize, EVROverlayError * pError) {
    return this_->GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError);
}

EVROverlayError IVROverlay_GetOverlayImageData(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, void * pvBuffer, uint32_t unBufferSize, uint32_t * punWidth, uint32_t * punHeight) {
    return this_->GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight);
}

const char * IVROverlay_GetOverlayErrorNameFromEnum(IVROverlay * this_, EVROverlayError error) {
    return this_->GetOverlayErrorNameFromEnum(error);
}

EVROverlayError IVROverlay_SetOverlayRenderingPid(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, uint32_t unPID) {
    return this_->SetOverlayRenderingPid(ulOverlayHandle, unPID);
}

uint32_t IVROverlay_GetOverlayRenderingPid(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->GetOverlayRenderingPid(ulOverlayHandle);
}

EVROverlayError IVROverlay_SetOverlayFlag(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled) {
    return this_->SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled);
}

EVROverlayError IVROverlay_GetOverlayFlag(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool * pbEnabled) {
    return this_->GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled);
}

EVROverlayError IVROverlay_SetOverlayColor(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue) {
    return this_->SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue);
}

EVROverlayError IVROverlay_GetOverlayColor(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float * pfRed, float * pfGreen, float * pfBlue) {
    return this_->GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue);
}

EVROverlayError IVROverlay_SetOverlayAlpha(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float fAlpha) {
    return this_->SetOverlayAlpha(ulOverlayHandle, fAlpha);
}

EVROverlayError IVROverlay_GetOverlayAlpha(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float * pfAlpha) {
    return this_->GetOverlayAlpha(ulOverlayHandle, pfAlpha);
}

EVROverlayError IVROverlay_SetOverlayWidthInMeters(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float fWidthInMeters) {
    return this_->SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters);
}

EVROverlayError IVROverlay_GetOverlayWidthInMeters(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float * pfWidthInMeters) {
    return this_->GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters);
}

EVROverlayError IVROverlay_SetOverlayAutoCurveDistanceRangeInMeters(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters) {
    return this_->SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters);
}

EVROverlayError IVROverlay_GetOverlayAutoCurveDistanceRangeInMeters(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, float * pfMinDistanceInMeters, float * pfMaxDistanceInMeters) {
    return this_->GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters);
}

EVROverlayError IVROverlay_SetOverlayTextureColorSpace(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace) {
    return this_->SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace);
}

EVROverlayError IVROverlay_GetOverlayTextureColorSpace(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, EColorSpace * peTextureColorSpace) {
    return this_->GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace);
}

EVROverlayError IVROverlay_SetOverlayTextureBounds(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t * pOverlayTextureBounds) {
    return this_->SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
}

EVROverlayError IVROverlay_GetOverlayTextureBounds(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t * pOverlayTextureBounds) {
    return this_->GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds);
}

EVROverlayError IVROverlay_GetOverlayTransformType(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayTransformType * peTransformType) {
    return this_->GetOverlayTransformType(ulOverlayHandle, peTransformType);
}

EVROverlayError IVROverlay_SetOverlayTransformAbsolute(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdMatrix34_t * pmatTrackingOriginToOverlayTransform) {
    return this_->SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform);
}

EVROverlayError IVROverlay_GetOverlayTransformAbsolute(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin * peTrackingOrigin, HmdMatrix34_t * pmatTrackingOriginToOverlayTransform) {
    return this_->GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform);
}

EVROverlayError IVROverlay_SetOverlayTransformTrackedDeviceRelative(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform) {
    return this_->SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform);
}

EVROverlayError IVROverlay_GetOverlayTransformTrackedDeviceRelative(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t * punTrackedDevice, HmdMatrix34_t * pmatTrackedDeviceToOverlayTransform) {
    return this_->GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform);
}

EVROverlayError IVROverlay_SetOverlayTransformTrackedDeviceComponent(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char * pchComponentName) {
    return this_->SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName);
}

EVROverlayError IVROverlay_GetOverlayTransformTrackedDeviceComponent(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t * punDeviceIndex, char * pchComponentName, uint32_t unComponentNameSize) {
    return this_->GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize);
}

EVROverlayError IVROverlay_ShowOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->ShowOverlay(ulOverlayHandle);
}

EVROverlayError IVROverlay_HideOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->HideOverlay(ulOverlayHandle);
}

bool IVROverlay_IsOverlayVisible(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->IsOverlayVisible(ulOverlayHandle);
}

EVROverlayError IVROverlay_GetTransformForOverlayCoordinates(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t * pmatTransform) {
    return this_->GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform);
}

bool IVROverlay_PollNextOverlayEvent(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VREvent_t * pEvent, uint32_t uncbVREvent) {
    return this_->PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent);
}

EVROverlayError IVROverlay_GetOverlayInputMethod(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod * peInputMethod) {
    return this_->GetOverlayInputMethod(ulOverlayHandle, peInputMethod);
}

EVROverlayError IVROverlay_SetOverlayInputMethod(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod) {
    return this_->SetOverlayInputMethod(ulOverlayHandle, eInputMethod);
}

EVROverlayError IVROverlay_GetOverlayMouseScale(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, HmdVector2_t * pvecMouseScale) {
    return this_->GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
}

EVROverlayError IVROverlay_SetOverlayMouseScale(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, HmdVector2_t * pvecMouseScale) {
    return this_->SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale);
}

bool IVROverlay_ComputeOverlayIntersection(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, VROverlayIntersectionParams_t * pParams, VROverlayIntersectionResults_t * pResults) {
    return this_->ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults);
}

//bool IVROverlay_HandleControllerOverlayInteractionAsMouse(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex) {
//    return this_->HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex);
//}

bool IVROverlay_IsHoverTargetOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->IsHoverTargetOverlay(ulOverlayHandle);
}

VROverlayHandle_t IVROverlay_GetGamepadFocusOverlay(IVROverlay * this_) {
    return this_->GetGamepadFocusOverlay();
}

EVROverlayError IVROverlay_SetGamepadFocusOverlay(IVROverlay * this_, VROverlayHandle_t ulNewFocusOverlay) {
    return this_->SetGamepadFocusOverlay(ulNewFocusOverlay);
}

EVROverlayError IVROverlay_SetOverlayNeighbor(IVROverlay * this_, EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo) {
    return this_->SetOverlayNeighbor(eDirection, ulFrom, ulTo);
}

EVROverlayError IVROverlay_MoveGamepadFocusToNeighbor(IVROverlay * this_, EOverlayDirection eDirection, VROverlayHandle_t ulFrom) {
    return this_->MoveGamepadFocusToNeighbor(eDirection, ulFrom);
}

EVROverlayError IVROverlay_SetOverlayTexture(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, Texture_t * pTexture) {
    return this_->SetOverlayTexture(ulOverlayHandle, pTexture);
}

EVROverlayError IVROverlay_ClearOverlayTexture(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->ClearOverlayTexture(ulOverlayHandle);
}

EVROverlayError IVROverlay_SetOverlayRaw(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, void * pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth) {
    return this_->SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth);
}

EVROverlayError IVROverlay_SetOverlayFromFile(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, const char * pchFilePath) {
    return this_->SetOverlayFromFile(ulOverlayHandle, pchFilePath);
}

EVROverlayError IVROverlay_GetOverlayTexture(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, void ** pNativeTextureHandle, void * pNativeTextureRef, uint32_t * pWidth, uint32_t * pHeight, uint32_t * pNativeFormat, ETextureType * pAPI, EColorSpace * pColorSpace, VRTextureBounds_t *pTextureBounds) {
    return this_->GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPI, pColorSpace, pTextureBounds);
}

EVROverlayError IVROverlay_ReleaseNativeOverlayHandle(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, void * pNativeTextureHandle) {
    return this_->ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle);
}

EVROverlayError IVROverlay_CreateDashboardOverlay(IVROverlay * this_, const char * pchOverlayKey, const char * pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t * pThumbnailHandle) {
    return this_->CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle);
}

bool IVROverlay_IsDashboardVisible(IVROverlay * this_) {
    return this_->IsDashboardVisible();
}

bool IVROverlay_IsActiveDashboardOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle) {
    return this_->IsActiveDashboardOverlay(ulOverlayHandle);
}

EVROverlayError IVROverlay_SetDashboardOverlaySceneProcess(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId) {
    return this_->SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId);
}

EVROverlayError IVROverlay_GetDashboardOverlaySceneProcess(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, uint32_t * punProcessId) {
    return this_->GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId);
}

void IVROverlay_ShowDashboard(IVROverlay * this_, const char * pchOverlayToShow) {
    return this_->ShowDashboard(pchOverlayToShow);
}

TrackedDeviceIndex_t IVROverlay_GetPrimaryDashboardDevice(IVROverlay * this_) {
    return this_->GetPrimaryDashboardDevice();
}

EVROverlayError IVROverlay_ShowKeyboard(IVROverlay * this_, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char * pchDescription, uint32_t unCharMax, const char * pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) {
    return this_->ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
}

EVROverlayError IVROverlay_ShowKeyboardForOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char * pchDescription, uint32_t unCharMax, const char * pchExistingText, bool bUseMinimalMode, uint64_t uUserValue) {
    return this_->ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue);
}

uint32_t IVROverlay_GetKeyboardText(IVROverlay * this_, char * pchText, uint32_t cchText) {
    return this_->GetKeyboardText(pchText, cchText);
}

void IVROverlay_HideKeyboard(IVROverlay * this_) {
    return this_->HideKeyboard();
}

void IVROverlay_SetKeyboardTransformAbsolute(IVROverlay * this_, ETrackingUniverseOrigin eTrackingOrigin, HmdMatrix34_t * pmatTrackingOriginToKeyboardTransform) {
    return this_->SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform);
}

void IVROverlay_SetKeyboardPositionForOverlay(IVROverlay * this_, VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect) {
    return this_->SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect);
}

typedef vr::EVRRenderModelError EVRRenderModelError;
typedef vr::VRComponentProperties VRComponentProperties;
typedef vr::EVRComponentProperty EVRComponentProperty;
typedef vr::RenderModel_ComponentState_t RenderModel_ComponentState_t;
typedef vr::RenderModel_Vertex_t RenderModel_Vertex_t;
typedef vr::RenderModel_TextureMap_t RenderModel_TextureMap_t;
typedef vr::TextureID_t TextureID_t;
typedef vr::RenderModel_t RenderModel_t;
typedef vr::RenderModel_ControllerMode_State_t RenderModel_ControllerMode_State_t;
typedef vr::IVRRenderModels IVRRenderModels;
EVRRenderModelError IVRRenderModels_LoadRenderModel_Async(IVRRenderModels * this_, const char * pchRenderModelName, RenderModel_t ** ppRenderModel) {
    return this_->LoadRenderModel_Async(pchRenderModelName, ppRenderModel);
}

void IVRRenderModels_FreeRenderModel(IVRRenderModels * this_, RenderModel_t * pRenderModel) {
    return this_->FreeRenderModel(pRenderModel);
}

EVRRenderModelError IVRRenderModels_LoadTexture_Async(IVRRenderModels * this_, TextureID_t textureId, RenderModel_TextureMap_t ** ppTexture) {
    return this_->LoadTexture_Async(textureId, ppTexture);
}

void IVRRenderModels_FreeTexture(IVRRenderModels * this_, RenderModel_TextureMap_t * pTexture) {
    return this_->FreeTexture(pTexture);
}

EVRRenderModelError IVRRenderModels_LoadTextureD3D11_Async(IVRRenderModels * this_, TextureID_t textureId, void * pD3D11Device, void ** ppD3D11Texture2D) {
    return this_->LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D);
}

EVRRenderModelError IVRRenderModels_LoadIntoTextureD3D11_Async(IVRRenderModels * this_, TextureID_t textureId, void * pDstTexture) {
    return this_->LoadIntoTextureD3D11_Async(textureId, pDstTexture);
}

void IVRRenderModels_FreeTextureD3D11(IVRRenderModels * this_, void * pD3D11Texture2D) {
    return this_->FreeTextureD3D11(pD3D11Texture2D);
}

uint32_t IVRRenderModels_GetRenderModelName(IVRRenderModels * this_, uint32_t unRenderModelIndex, char * pchRenderModelName, uint32_t unRenderModelNameLen) {
    return this_->GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen);
}

uint32_t IVRRenderModels_GetRenderModelCount(IVRRenderModels * this_) {
    return this_->GetRenderModelCount();
}

uint32_t IVRRenderModels_GetComponentCount(IVRRenderModels * this_, const char * pchRenderModelName) {
    return this_->GetComponentCount(pchRenderModelName);
}

uint32_t IVRRenderModels_GetComponentName(IVRRenderModels * this_, const char * pchRenderModelName, uint32_t unComponentIndex, char * pchComponentName, uint32_t unComponentNameLen) {
    return this_->GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen);
}

uint64_t IVRRenderModels_GetComponentButtonMask(IVRRenderModels * this_, const char * pchRenderModelName, const char * pchComponentName) {
    return this_->GetComponentButtonMask(pchRenderModelName, pchComponentName);
}

uint32_t IVRRenderModels_GetComponentRenderModelName(IVRRenderModels * this_, const char * pchRenderModelName, const char * pchComponentName, char * pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen) {
    return this_->GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen);
}

bool IVRRenderModels_GetComponentState(IVRRenderModels * this_, const char * pchRenderModelName, const char * pchComponentName, VRControllerState_t * pControllerState, RenderModel_ControllerMode_State_t * pState, RenderModel_ComponentState_t * pComponentState) {
    return this_->GetComponentState(pchRenderModelName, pchComponentName, pControllerState, pState, pComponentState);
}

bool IVRRenderModels_RenderModelHasComponent(IVRRenderModels * this_, const char * pchRenderModelName, const char * pchComponentName) {
    return this_->RenderModelHasComponent(pchRenderModelName, pchComponentName);
}

typedef vr::IVRExtendedDisplay IVRExtendedDisplay;
void IVRExtendedDisplay_GetWindowBounds(IVRExtendedDisplay * this_, int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight) {
    return this_->GetWindowBounds(pnX, pnY, pnWidth, pnHeight);
}

void IVRExtendedDisplay_GetEyeOutputViewport(IVRExtendedDisplay * this_, EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight) {
    return this_->GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight);
}

void IVRExtendedDisplay_GetDXGIOutputInfo(IVRExtendedDisplay * this_, int32_t * pnAdapterIndex, int32_t * pnAdapterOutputIndex) {
    return this_->GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex);
}

IVRSystem * VR_Init(EVRInitError * peError, EVRApplicationType eApplicationType) {
    return vr::VR_Init(peError, eApplicationType);
}

void VR_Shutdown() {
    return vr::VR_Shutdown();
}

typedef vr::HmdError HmdError;
typedef vr::Hmd_Eye Hmd_Eye;
//typedef vr::GraphicsAPIConvention GraphicsAPIConvention;
typedef vr::ColorSpace ColorSpace;
typedef vr::HmdTrackingResult HmdTrackingResult;
typedef vr::TrackedDeviceClass TrackedDeviceClass;
typedef vr::TrackingUniverseOrigin TrackingUniverseOrigin;
typedef vr::TrackedDeviceProperty TrackedDeviceProperty;
typedef vr::TrackedPropertyError TrackedPropertyError;
typedef vr::VRSubmitFlags_t VRSubmitFlags_t;
typedef vr::VRState_t VRState_t;
typedef vr::CollisionBoundsStyle_t CollisionBoundsStyle_t;
typedef vr::VROverlayError VROverlayError;
typedef vr::VRFirmwareError VRFirmwareError;
typedef vr::VRCompositorError VRCompositorError;
uint32_t * VRToken() {
    return &vr::VRToken();
}

typedef vr::COpenVRContext COpenVRContext;
COpenVRContext * COpenVRContext_New() {
    return new COpenVRContext();
}

void COpenVRContext_Clear(COpenVRContext * this_) {
    return this_->Clear();
}

void COpenVRContext_CheckClear(COpenVRContext * this_) {
    return this_->CheckClear();
}

IVRSystem * COpenVRContext_VRSystem(COpenVRContext * this_) {
    return this_->VRSystem();
}

IVRChaperone * COpenVRContext_VRChaperone(COpenVRContext * this_) {
    return this_->VRChaperone();
}

IVRChaperoneSetup * COpenVRContext_VRChaperoneSetup(COpenVRContext * this_) {
    return this_->VRChaperoneSetup();
}

IVRCompositor * COpenVRContext_VRCompositor(COpenVRContext * this_) {
    return this_->VRCompositor();
}

IVROverlay * COpenVRContext_VROverlay(COpenVRContext * this_) {
    return this_->VROverlay();
}

IVRRenderModels * COpenVRContext_VRRenderModels(COpenVRContext * this_) {
    return this_->VRRenderModels();
}

IVRExtendedDisplay * COpenVRContext_VRExtendedDisplay(COpenVRContext * this_) {
    return this_->VRExtendedDisplay();
}

IVRSettings * COpenVRContext_VRSettings(COpenVRContext * this_) {
    return this_->VRSettings();
}

IVRApplications * COpenVRContext_VRApplications(COpenVRContext * this_) {
    return this_->VRApplications();
}

COpenVRContext * OpenVRInternal_ModuleContext() {
    return &vr::OpenVRInternal_ModuleContext();
}

IVRSystem * VRSystem() {
    return vr::VRSystem();
}

IVRChaperone * VRChaperone() {
    return vr::VRChaperone();
}

IVRChaperoneSetup * VRChaperoneSetup() {
    return vr::VRChaperoneSetup();
}

IVRCompositor * VRCompositor() {
    return vr::VRCompositor();
}

IVROverlay * VROverlay() {
    return vr::VROverlay();
}

IVRRenderModels * VRRenderModels() {
    return vr::VRRenderModels();
}

IVRApplications * VRApplications() {
    return vr::VRApplications();
}

IVRSettings * VRSettings() {
    return vr::VRSettings();
}

IVRExtendedDisplay * VRExtendedDisplay() {
    return vr::VRExtendedDisplay();
}

}
