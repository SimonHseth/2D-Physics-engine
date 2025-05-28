@echo off
echo [Compiling with SFML...]

cl /std:c++17 /EHsc main.cpp Vector2D.cpp RigidBody.cpp PhysicsWorld.cpp ^
  /I"/SFML-3.0.0/include" ^
  /link /LIBPATH:/SFML-3.0.0/lib/ sfml-graphics.lib sfml-window.lib sfml-system.lib

if exist main.exe (
    echo [Build Successful. Running...]
    main
) else (
    echo [Build Failed.]
)
pause
