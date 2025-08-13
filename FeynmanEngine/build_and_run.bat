@echo off
echo [Compiling with SFML 3.0 + ImGui-SFML...]

REM === EDIT THESE PATHS IF NEEDED ===
set SFML_INC=C:\Libraries\SFML-3.0.0-sources\include
set SFML_LIB=C:\Libraries\SFML-3.0.0-build\lib\Release
set IMGUI_DIR=C:\Libraries\imgui
set IMGUI_SFML_DIR=C:\Libraries\imgui-sfml
set IMGUI_USER_CFG=imconfig-SFML.h

REM pick the imgui-sfml source
set IMGUI_SFML_SRC=%IMGUI_SFML_DIR%\imgui-SFML.cpp
if not exist "%IMGUI_SFML_SRC%" set IMGUI_SFML_SRC=%IMGUI_SFML_DIR%\src\imgui-SFML.cpp

REM quick checks
for %%F in ("%IMGUI_DIR%\imgui.cpp" "%IMGUI_DIR%\imgui_draw.cpp" "%IMGUI_DIR%\imgui_tables.cpp" "%IMGUI_DIR%\imgui_widgets.cpp" "%IMGUI_SFML_SRC%" "%IMGUI_SFML_DIR%\%IMGUI_USER_CFG%") do (
  if not exist "%%~F" (
    echo [ERROR] Missing: %%~F
    echo Fix paths above or download the repos to those folders.
    pause
    exit /b 1
  )
)

REM clean stale objs so new flags actually take effect
del /q imgui*.obj 2>nul
del /q main.obj Vector2D.obj RigidBody.obj PhysicsWorld.obj 2>nul
del /q "%~dp0*.pdb" 2>nul

cl /std:c++17 /EHsc /Fe:main.exe ^
  /I"%SFML_INC%" ^
  /I"%IMGUI_DIR%" ^
  /I"%IMGUI_SFML_DIR%" ^
  /D IMGUI_USER_CONFIG=\"%IMGUI_USER_CFG%\" ^
  /D IMGUI_SFML_USE_LEGACY_TEXTURE_ID=1 ^
  /FI"%IMGUI_SFML_DIR%\%IMGUI_USER_CFG%" ^
  main.cpp Vector2D.cpp RigidBody.cpp PhysicsWorld.cpp ^
  "%IMGUI_DIR%\imgui.cpp" ^
  "%IMGUI_DIR%\imgui_draw.cpp" ^
  "%IMGUI_DIR%\imgui_tables.cpp" ^
  "%IMGUI_DIR%\imgui_widgets.cpp" ^
  "%IMGUI_DIR%\imgui_demo.cpp" ^
  "%IMGUI_SFML_SRC%" ^
  /link /MACHINE:X64 /LIBPATH:"%SFML_LIB%" ^
  sfml-graphics.lib sfml-window.lib sfml-system.lib ^
  opengl32.lib imm32.lib user32.lib gdi32.lib shell32.lib ole32.lib oleaut32.lib winmm.lib dwmapi.lib version.lib

if exist main.exe (
  echo [Build Successful. Running...]
  main
) else (
  echo [Build Failed.]
)
pause
