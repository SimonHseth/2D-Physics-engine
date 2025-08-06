@echo off
echo [Compiling with SFML 3.0 real build...]

cl /std:c++17 /EHsc /Fe:main.exe ^
  /I"C:\Libraries\SFML-3.0.0-sources\include" ^
  main.cpp Vector2D.cpp RigidBody.cpp PhysicsWorld.cpp ^
  /link /MACHINE:X64 /LIBPATH:"C:\Libraries\SFML-3.0.0-build\lib\Release" ^
  sfml-graphics.lib sfml-window.lib sfml-system.lib

if exist main.exe (
    echo [Build Successful. Running...]
    main
) else (
    echo [Build Failed.]
)
pause
