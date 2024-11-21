MF 		= mkdir -p
RF      = rd /s /q
CC = cl
LK = link
CFlags = /c /Fo$(INT_DIR) /std:c++17 /MD
Defines = /DPLATFORM=Windows /DGLEW_STATIC /DWINDOWS_IGNORE_PACKING_MISMATCH
VCPKG_PATH = "${VCPKG_ROOT}/installed/x64-windows/"
($ $(VCPKG_PATH))
IncludeDirs = /I$(SrcDir) /Ilibs/spdlog-1.14.1/include/ /I$(VCPKG_PATH)/include /Ilibs/Asio-1.30.2/include/ /Isrc/Shared/
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
CFlags += /Ot /Oi /Ox /GL  /Gy /Gw
LFLAGS += /LTCG /INCREMENTAL:NO /NODEFAULTLIB /MACHINE:x64
else
Defines += /DDIST
CFlags += /Ot /Oi /Ox /GL /Gy /Gw
LFLAGS += /LTCG /INCREMENTAL:NO /NODEFAULTLIB /OPT:REF /OPT:ICF /SUBSYSTEM:Windows /MACHINE:x64
endif
endif

#Shared
Files+= $(SrcDir)Main.cpp
Files+=$(SharedDir)Packet.cpp

ifeq ($(Type), Client)
#Client
IncludeDirs += /Ilibs/stb/include/ /Ilibs/Freetype/include/ /Ilibs/glew-2.2.0/include/ /Ilibs/GLFW3.4/x64/include/ 
LibDirs += /LIBPATH:"libs/Freetype/libs/x64" /LibPath:"libs/glew-2.2.0/libs/$(Arch)/" /LibPath:"libs/GLFW3.4/x64/lib-vc2022/"
Libs += freetype.lib glfw3.lib glew32s.lib opengl32.lib
Defines += /DGLEW_STATIC

Files += $(SrcDir)Game.cpp
Files += $(SrcDir)Networking/Client.cpp

#Core
Files += $(SrcDir)Core/Logger.cpp
Files += $(SrcDir)Core/Time.cpp

#Game
WorldSRC = $(SrcDir)World/
Files += $(WorldSRC)Chunk.cpp
Files += $(WorldSRC)Marcher.cpp
Files += $(WorldSRC)World.cpp

#Entities
Files += $(SrcDir)Entity/Player/Player.cpp

#Math
Files += $(SharedDir)Math/Frustum.cpp
Files += $(SharedDir)Math/MatrixUtils.cpp

#Rendering
Files += $(SrcDir)Rendering/Window.cpp
Files += $(SrcDir)Rendering/Shader.cpp
Files += $(SrcDir)Rendering/Textures/Texture.cpp
Files += $(SrcDir)Rendering/Gui/Font.cpp
Files += $(SrcDir)Rendering/Gui/Gui.cpp
Files += $(SrcDir)Rendering/Gui/UIDisplayManager.cpp
Files += $(SrcDir)Rendering/Gui/UI.cpp

#GUIS
UisDir = $(SrcDir)Rendering/Gui/UIS/
Files += $(UisDir)UIButton.cpp
Files += $(UisDir)UIImage.cpp
Files += $(UisDir)UITextLabel.cpp

#Meshes
MeshSrc = $(SrcDir)Rendering/Mesh/
Files += $(MeshSrc)BasicMesh.cpp
Files += $(MeshSrc)ChunkMesh.cpp
Files += $(MeshSrc)PointMesh.cpp
Files += $(MeshSrc)TexturedMesh.cpp

#Shaders
ShadersSrc = $(SrcDir)Rendering/Shaders/

#GUI Shader
Files += $(ShadersSrc)UITextShader.cpp
Files += $(ShadersSrc)UIImageShader.cpp
Files += $(ShadersSrc)UIFrameShader.cpp

#Game Shaders
Files += $(ShadersSrc)ChunkDebugShader.cpp
Files += $(ShadersSrc)ChunkShader.cpp
Files += $(ShadersSrc)PointShader.cpp

#Input
Files += $(SrcDir)Input/Keyboard.cpp
Files += $(SrcDir)Input/Mouse.cpp

#Scenes
Files += $(SrcDir)Scene/Scene.cpp
Files += $(SrcDir)Scene/SceneManager.cpp
ScenesDir = $(SrcDir)Scene/Scenes/
Files += $(ScenesDir)MainMenuScene.cpp
Files += $(ScenesDir)GameScene.cpp
else
#Server
Files += $(SrcDir)Core/Logger.cpp
Files += $(SrcDir)Server/GameServer.cpp
Files += $(SrcDir)Server/Client.cpp
endif