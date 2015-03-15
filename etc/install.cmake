#-------------------------------------------------------------------------------
# file:
#   install.cmake
# brief:
#   The definition to install hryky-codebase.
# version:
#   $Id: CMakeLists.txt 215 2013-05-02 08:10:42Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
# installation settings
#-------------------------------------------------------------------------------
install(DIRECTORY external/SDL 
	DESTINATION ./external/
	COMPONENT HRYKY_COMPONENT_SDL
	PATTERN "XTAGS" EXCLUDE
	PATTERN ".svn" EXCLUDE
)
install(DIRECTORY external/Google/protobuf 
	DESTINATION ./external/Google/
	COMPONENT HRYKY_COMPONENT_PROTOBUF
	PATTERN "XTAGS" EXCLUDE
	PATTERN ".svn" EXCLUDE
)
install(DIRECTORY external/GL3 
	DESTINATION ./external/
	COMPONENT HRYKY_COMPONENT_GL3
	PATTERN "XTAGS" EXCLUDE
	PATTERN ".svn" EXCLUDE
)

