// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerHardwareLibrary.h"

#if PLATFORM_WINDOWS

#include "Windows/AllowWindowsPlatformTypes.h"

#include <windows.h>
#include <hidsdi.h>
#include <setupapi.h>

#include "Windows/HideWindowsPlatformTypes.h"

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "setupapi.lib")

#endif

static bool ParseVIDPID(
    const FString& DevicePath,
    uint16& OutVID,
    uint16& OutPID)
{
    FString LowerPath = DevicePath.ToLower();

    int32 VIDIndex = LowerPath.Find(TEXT("vid_"));
    int32 PIDIndex = LowerPath.Find(TEXT("pid_"));

    if (VIDIndex == INDEX_NONE || PIDIndex == INDEX_NONE)
    {
        return false;
    }

    FString VIDString =
        LowerPath.Mid(VIDIndex + 4, 4);

    FString PIDString =
        LowerPath.Mid(PIDIndex + 4, 4);

    OutVID =
        FParse::HexNumber(*VIDString);

    OutPID =
        FParse::HexNumber(*PIDString);

    return true;
}

EMyControllerType UControllerHardwareLibrary::GetControllerType(int32 PlayerIndex)
{
#if PLATFORM_WINDOWS

    GUID HidGuid;
    HidD_GetHidGuid(&HidGuid);

    HDEVINFO DeviceInfo = SetupDiGetClassDevs(
        &HidGuid,
        nullptr,
        nullptr,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
    );

    if (DeviceInfo == INVALID_HANDLE_VALUE)
    {
        return EMyControllerType::Unknown;
    }

    for (DWORD Index = 0;; ++Index)
    {
        SP_DEVICE_INTERFACE_DATA InterfaceData;
        InterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

        if (!SetupDiEnumDeviceInterfaces(
            DeviceInfo,
            nullptr,
            &HidGuid,
            Index,
            &InterfaceData))
        {
            break;
        }

        DWORD RequiredSize = 0;

        SetupDiGetDeviceInterfaceDetail(
            DeviceInfo,
            &InterfaceData,
            nullptr,
            0,
            &RequiredSize,
            nullptr
        );

        if (RequiredSize == 0)
        {
            continue;
        }

        TArray<uint8> Buffer;
        Buffer.SetNumZeroed(RequiredSize);

        auto* DetailData =
            reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(
                Buffer.GetData()
                );

        DetailData->cbSize =
            sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        if (!SetupDiGetDeviceInterfaceDetail(
            DeviceInfo,
            &InterfaceData,
            DetailData,
            RequiredSize,
            nullptr,
            nullptr))
        {
            continue;
        }

        FString DevicePath =
            UTF8_TO_TCHAR(DetailData->DevicePath);

        uint16 VID;
        uint16 PID;

        if (!ParseVIDPID(DevicePath, VID, PID))
        {
            continue;
        }

        UE_LOG(
            LogTemp,
            Log,
            TEXT("Controller candidate: VID=%04X PID=%04X"),
            VID,
            PID
        );

        // Microsoft
        if (VID == 0x045E)
        {
            SetupDiDestroyDeviceInfoList(DeviceInfo);
            return EMyControllerType::Xbox;
        }

        // Sony
        if (VID == 0x054C)
        {
            // You can later use PID to distinguish
            // DualShock 4 vs DualSense.

            SetupDiDestroyDeviceInfoList(DeviceInfo);
            return EMyControllerType::PlayStation5;
        }

        // Nintendo
        if (VID == 0x057E)
        {
            SetupDiDestroyDeviceInfoList(DeviceInfo);
            return EMyControllerType::Switch;
        }
    }

    SetupDiDestroyDeviceInfoList(DeviceInfo);

#endif

    return EMyControllerType::Unknown;
}


FString UControllerHardwareLibrary::GetControllerVIDPID(int32 PlayerIndex)
{
#if PLATFORM_WINDOWS

    GUID HidGuid;
    HidD_GetHidGuid(&HidGuid);

    HDEVINFO DeviceInfo = SetupDiGetClassDevs(
        &HidGuid,
        nullptr,
        nullptr,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
    );

    if (DeviceInfo == INVALID_HANDLE_VALUE)
    {
        return TEXT("");
    }

    for (DWORD Index = 0;; ++Index)
    {
        SP_DEVICE_INTERFACE_DATA InterfaceData{};
        InterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

        if (!SetupDiEnumDeviceInterfaces(
            DeviceInfo,
            nullptr,
            &HidGuid,
            Index,
            &InterfaceData))
        {
            break;
        }

        DWORD RequiredSize = 0;

        SetupDiGetDeviceInterfaceDetailW(
            DeviceInfo,
            &InterfaceData,
            nullptr,
            0,
            &RequiredSize,
            nullptr
        );

        if (RequiredSize == 0)
        {
            continue;
        }

        TArray<uint8> Buffer;
        Buffer.SetNumZeroed(RequiredSize);

        auto* DetailData =
            reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA_W>(
                Buffer.GetData()
                );

        DetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);

        if (!SetupDiGetDeviceInterfaceDetailW(
            DeviceInfo,
            &InterfaceData,
            DetailData,
            RequiredSize,
            nullptr,
            nullptr))
        {
            continue;
        }

        FString DevicePath(DetailData->DevicePath);

        UE_LOG(
            LogTemp,
            Log,
            TEXT("HID Device: %s"),
            *DevicePath
        );
    }

    SetupDiDestroyDeviceInfoList(DeviceInfo);

#endif

    return TEXT("");
}