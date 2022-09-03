##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Test
ProjectName            :=UOCAirways
ConfigurationName      :=Test
WorkspaceConfiguration :=Test
WorkspacePath          :=/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol
ProjectPath            :=/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol
IntermediateDirectory  :=./Test
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=admin
Date                   :=02/09/2022
CodeLitePath           :="/Users/admin/Library/Application Support/CodeLite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=$(IntermediateDirectory)
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="UOCAirways.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch)./include $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/src_flight.c$(ObjectSuffix) $(IntermediateDirectory)/src_passenger.c$(ObjectSuffix) $(IntermediateDirectory)/src_plane.c$(ObjectSuffix) $(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IntermediateDirectory)/src_queue.c$(ObjectSuffix) $(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IntermediateDirectory)/src_list.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Test || $(MakeDirCommand) ./Test


$(IntermediateDirectory)/.d:
	@test -d ./Test || $(MakeDirCommand) ./Test

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_flight.c$(ObjectSuffix): src/flight.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/flight.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_flight.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_flight.c$(PreprocessSuffix): src/flight.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_flight.c$(PreprocessSuffix) src/flight.c

$(IntermediateDirectory)/src_passenger.c$(ObjectSuffix): src/passenger.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/passenger.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_passenger.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_passenger.c$(PreprocessSuffix): src/passenger.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_passenger.c$(PreprocessSuffix) src/passenger.c

$(IntermediateDirectory)/src_plane.c$(ObjectSuffix): src/plane.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/plane.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_plane.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_plane.c$(PreprocessSuffix): src/plane.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_plane.c$(PreprocessSuffix) src/plane.c

$(IntermediateDirectory)/src_menu.c$(ObjectSuffix): src/menu.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/menu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_menu.c$(PreprocessSuffix): src/menu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_menu.c$(PreprocessSuffix) src/menu.c

$(IntermediateDirectory)/src_api.c$(ObjectSuffix): src/api.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/api.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_api.c$(PreprocessSuffix): src/api.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_api.c$(PreprocessSuffix) src/api.c

$(IntermediateDirectory)/src_queue.c$(ObjectSuffix): src/queue.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/queue.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_queue.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_queue.c$(PreprocessSuffix): src/queue.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_queue.c$(PreprocessSuffix) src/queue.c

$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) src/main.c

$(IntermediateDirectory)/src_test.c$(ObjectSuffix): src/test.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_test.c$(PreprocessSuffix): src/test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_test.c$(PreprocessSuffix) src/test.c

$(IntermediateDirectory)/src_list.c$(ObjectSuffix): src/list.c
	$(CC) $(SourceSwitch) "/Users/admin/Desktop/Github/MarioCode/UOC/75554_PR2_20182_S/75554_PR2_20182_S/UOCAirways_PR2_sol/src/list.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_list.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_list.c$(PreprocessSuffix): src/list.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_list.c$(PreprocessSuffix) src/list.c

##
## Clean
##
clean:
	$(RM) -r ./Test/


