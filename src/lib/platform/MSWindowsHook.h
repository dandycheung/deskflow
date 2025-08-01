/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2012 - 2016 Symless Ltd.
 * SPDX-FileCopyrightText: (C) 2011 Chris Schoeneman
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define DESKFLOW_MSG_MARK WM_APP + 0x0011         // mark id; <unused>
#define DESKFLOW_MSG_KEY WM_APP + 0x0012          // vk code; key data
#define DESKFLOW_MSG_MOUSE_BUTTON WM_APP + 0x0013 // button msg; <unused>
#define DESKFLOW_MSG_MOUSE_WHEEL WM_APP + 0x0014  // delta; <unused>
#define DESKFLOW_MSG_MOUSE_MOVE WM_APP + 0x0015   // x; y
#define DESKFLOW_MSG_POST_WARP WM_APP + 0x0016    // <unused>; <unused>
#define DESKFLOW_MSG_PRE_WARP WM_APP + 0x0017     // x; y
#define DESKFLOW_MSG_SCREEN_SAVER WM_APP + 0x0018 // activated; <unused>
#define DESKFLOW_MSG_DEBUG WM_APP + 0x0019        // data, data
#define DESKFLOW_MSG_INPUT_FIRST DESKFLOW_MSG_KEY
#define DESKFLOW_MSG_INPUT_LAST DESKFLOW_MSG_PRE_WARP
#define DESKFLOW_HOOK_LAST_MSG DESKFLOW_MSG_DEBUG

#define DESKFLOW_HOOK_FAKE_INPUT_VIRTUAL_KEY VK_CANCEL
#define DESKFLOW_HOOK_FAKE_INPUT_SCANCODE 0

enum EHookResult
{
  kHOOK_FAILED,
  kHOOK_OKAY,
  kHOOK_OKAY_LL
};

enum EHookMode
{
  kHOOK_DISABLE,
  kHOOK_WATCH_JUMP_ZONE,
  kHOOK_RELAY_EVENTS
};

//! Loads and provides functions for the Windows hook
class MSWindowsHook
{
public:
  MSWindowsHook() = default;
  ~MSWindowsHook();

  void loadLibrary();

  int init(DWORD threadID);

  int cleanup();

  void setSides(uint32_t sides);
  uint32_t getSides();

  void setZone(int32_t x, int32_t y, int32_t w, int32_t h, int32_t jumpZoneSize);

  void setMode(EHookMode mode);

  static EHookResult install();

  static int uninstall();

  static int installScreenSaver();

  static int uninstallScreenSaver();
};
