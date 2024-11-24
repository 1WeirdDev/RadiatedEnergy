#Type Client | Server
#Arch can be [x64]
Platform = Windows
Type = Client
#Type = Server
Configuration = Dist
TargetName = RadiatedEnergy
Arch = x64

OUTPUT_DIR = bin/$(Configuration)-$(Platform)/$(Type)/
INT_DIR = bin-int/$(Configuration)-$(Platform)/$(Type)/
SrcDir=src/$(Type)/
SharedDir=src/Shared/
MF =
RF = 
CC = 
LK = 
Files =
Defines =
CFlags = 
LFlags = 
Files = 

ifeq ($(Platform), Windows)
include WindowsMake.mk
else
$(error Invalid Platform)
endif

default: build

clean:
	$(RF) bin-int
make_folders:
	$(MF) $(INT_DIR)
	$(MF) $(OUTPUT_DIR)
buildpch:
	$(CC) $(CFlags) $(Defines) $(IncludeDirs) /Ycpch.h /Fp$(INT_DIR)pch.pch $(SrcDir)/pch.cpp
build:
	$(CC) $(Files) $(CFlags) $(Defines) $(IncludeDirs) /Yupch.h /Fp$(INT_DIR)pch.pch 
	$(LK) $(LFlags) $(LibDirs) $(Libs)
run:
ifneq ($(Configuration), Dist)
	gdb -ex run -ex quit -ex "set args $(ProgramArgs)" $(OUTPUT_DIR)$(TargetName).exe
else
	$(OUTPUT_DIR)$(TargetName).exe
endif
buildnrun: make_folders build run
rebuild:make_folders buildpch build
rebuildnrun:make_folders buildpch build run

push:
	Push.bat
pull:
	Pull.bat