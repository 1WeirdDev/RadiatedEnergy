MF 		= mkdir -p
RF      = rd /s /q
CC = cl
LK = link
CFlags = /c /Fo$(INT_DIR) /std:c++17 /MD
Defines = /DPLATFORM=Windows /DGLEW_STATIC /DWINDOWS_IGNORE_PACKING_MISMATCH
VCPKG_PATH = "${VCPKG_ROOT}/installed/x64-windows/"
($ $(VCPKG_PATH))
IncludeDirs = /I$(SRC_DIR) /Ilibs/spdlog-1.14.1/include/ /I$(VCPKG_PATH)/include /Ilibs/Asio-1.30.2/include/ /Isrc/Shared/
LibDirs = /LibPath:$(VCPKG_PATH)/lib
Libs = GDI32.lib Shell32.lib kernel32.lib User32.lib
LFlags = $(INT_DIR)*.obj /out:$(OUTPUT_DIR)$(TargetName).exe
ProgramArgs =

#Configuration Only
ifeq ($(Configuration), Debug)
DEFINES += /DDEBUG
else
Defines += /DNDEBUG

ifeq ($(Configuration), Release)
Defines += /DRELEASE
CFlags += /Ot /Oi
LFLAGS += /LTCG /INCREMENTAL:NO /NODEFAULTLIB /Gy
else
Defines += /DDIST
LFLAGS += /LTCG /INCREMENTAL:NO /NODEFAULTLIB /OPT:REF /OPT:ICF /Gy /SUBSYSTEM:Windows
endif
endif

Files+= $(SRC_DIR)Main.cpp

ifeq ($(Type), Client)
#Client
IncludeDirs +=  /Ilibs/Freetype/include/ /Ilibs/glew-2.2.0/include/ /Ilibs/GLFW3.4/x64/include/ 
LibDirs += /LIBPATH:"libs/Freetype/libs/x64" /LibPath:"libs/glew-2.2.0/libs/$(Arch)/" /LibPath:"libs/GLFW3.4/x64/lib-vc2022/"
Libs += freetype.lib glfw3.lib glew32s.lib opengl32.lib
Defines += /DGLEW_STATIC

Files += $(SRC_DIR)Game.cpp

Files += $(SRC_DIR)Core/Logger.cpp
Files += $(SRC_DIR)Display/Window.cpp
Files += $(SRC_DIR)Networking/Client.cpp

#Input
Files += $(SRC_DIR)Input/Keyboard.cpp
Files += $(SRC_DIR)Input/Mouse.cpp
#Scenes
ScenesDir = $(SRC_DIR)Scene/Scenes/
Files += $(SRC_DIR)Scene/Scene.cpp
Files += $(SRC_DIR)Scene/SceneManager.cpp
Files += $(ScenesDir)MainMenuScene.cpp
else
#Server
Files += $(SRC_DIR)Core/Logger.cpp
Files += $(SRC_DIR)Server/GameServer.cpp
Files += $(SRC_DIR)Server/Client.cpp
endif