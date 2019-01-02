@echo off
:: Copyright (c) 2018 The Zoom Authors. All rights reserved.
:: Use of this source code is governed by a BSD-style license that can be
:: found in the LICENSE file.
setlocal

:: Ensure that "git" and "python" is somewhere in PATH so this tool can be used
:: standalone, but allow other PATH manipulations to take priority.
set PATH=%PATH%;%~dp0

:: Defer control.
python "%~dp0\pull.py" %*

pause
