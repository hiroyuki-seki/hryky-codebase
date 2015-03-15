#-------------------------------------------------------------------------------
# file:
#   pack.cmake
# brief:
#   The definition to create the installer for hryky-codebase.
# version:
#   $Id: CMakeLists.txt 215 2013-05-02 08:10:42Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
# defines the variables to create the installer of this project
#-------------------------------------------------------------------------------
hryky_include_pack()

#---------------------------------------
# defines groups of components
#---------------------------------------
cpack_add_component_group(HRYKY_LIB_COMPONENTS
	DISPLAY_NAME    
		"libraries"
	DESCRIPTION     
		"libraries of ${PROJECT_NAME}."
	EXPANDED)
cpack_add_component_group(HRYKY_EXTERNAL_COMPONENTS
	DISPLAY_NAME    
		"external products"
	DESCRIPTION     
		"The external products on which ${PROJECT_NAME} depends."
	EXPANDED)

#---------------------------------------
# defines types of installed package.
#---------------------------------------
cpack_add_install_type(HRYKY_INSTALL_TYPE_ALL
	DISPLAY_NAME
		"entire package.")
cpack_add_install_type(HRYKY_INSTALL_TYPE_NO_EXTERNAL
	DISPLAY_NAME
		"no external products.")

#---------------------------------------
# defines each component
#---------------------------------------
hryky_add_packed_component(
	ascii
	"The module to utilize ASCII characters.")

hryky_add_packed_component(
	atomic
	"The module to utilize atomic operations.")

hryky_add_packed_component(
	chrono
	"The module to utilize time duration.")

hryky_add_packed_component(
	core 
	"The Basic Common module on which each module depends.")
	
hryky_add_packed_component(
	date
	"The module to utilize date.")

hryky_add_packed_component(
	debug
	"The module to retrieve the information for depelop.")

hryky_add_packed_component(
	display
	"The module to access the information of display device."
	pixel)

hryky_add_packed_component(
	error
	"The module to handle an error.")

hryky_add_packed_component(
	exclusion
	"The module for exclusion control.")

hryky_add_packed_component(
	file
	"The module to utilize file I/O.")

hryky_add_packed_component(
	graphics
	"intermediation for low Graphics APIs.")

hryky_add_packed_component(
	http
	"reads an writes HTTP Message."
	ip uri)
	
hryky_add_packed_component(
	ip
	"reads an writes IPv4 and IPv6 Address.")
	
hryky_add_packed_component(
	log
	"writes out the log of process.")
	
hryky_add_packed_component(
	memory
	"allocates the memory.")
	
hryky_add_packed_component(
	opengl
	"low level wrapper for OpenGL API.")

hryky_add_packed_component(
	pixel
	"handles pixel formats.")
	
hryky_add_packed_component(
	task
	"processes fine grained tasks concurrently."
	thread)
	
hryky_add_packed_component(
	testing
	"framework for unit testing.")

hryky_add_packed_component(
	thread
	"manages thread resources.")
	
hryky_add_packed_component(
	type
	"The module to identify the type of variable.")
	
hryky_add_packed_component(
	uri
	"reads and writes URI.")

hryky_add_packed_component(
	win32
	"The module to utilize functions depending on Win32 API.")

hryky_add_packed_component(
	writer
	"The module to write out binary data.")

cpack_add_component(doc_hryky_codebase
	DISPLAY_NAME    
		"Documents"
	DESCRIPTION     
		"Reference Manual of this codebase"
	INSTALL_TYPES   
		HRYKY_INSTALL_TYPE_ALL 
		HRYKY_INSTALL_TYPE_NO_EXTERNAL)

cpack_add_component(HRYKY_COMPONENT_SDL
	DISPLAY_NAME    
		"Simple Directmedia Layer"
	DESCRIPTION     
		"This codebase depends on SDL in respect to Windows Management, Input Device, and Text Input. http://www.libsdl.org/"
	GROUP           
		HRYKY_EXTERNAL_COMPONENTS
	INSTALL_TYPES   
		HRYKY_INSTALL_TYPE_ALL)

cpack_add_component(HRYKY_COMPONENT_PROTOBUF
	DISPLAY_NAME    
		"Protocol Buffers"
	DESCRIPTION     
		"This codebase depends on Protocol Buffers in respect to the serialization. http://code.google.com/p/protobuf/"
	GROUP           
		HRYKY_EXTERNAL_COMPONENTS
	INSTALL_TYPES   
		HRYKY_INSTALL_TYPE_ALL)

cpack_add_component(HRYKY_COMPONENT_GL3
	DISPLAY_NAME    
		"header file for OpenGL 3.x"
	DESCRIPTION     
		"This codebase depends on OpenGL 3.x in respect to 3D Graphics. http://www.opengl.org/"
	GROUP           
		HRYKY_EXTERNAL_COMPONENTS
	INSTALL_TYPES   
		HRYKY_INSTALL_TYPE_ALL)
