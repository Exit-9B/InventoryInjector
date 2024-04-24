cmake_minimum_required(VERSION 3.24)

project(
	InventoryInjector
	VERSION 1.1.0
	LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_IGNORE_PATH "${PROJECT_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/tools/SKSE-CMakeModules/Modules"
)
include(SKSEPlugin)

set(SKSE_SUPPORT_VR ON)

SKSEPlugin_Add(
	${PROJECT_NAME}
	SOURCE_DIR src
	SOURCES
		.clang-format
		.editorconfig
		README.md
		vcpkg.json
	PRECOMPILE_HEADERS
		src/PCH/PCH.h
)

find_package(jsoncpp CONFIG REQUIRED)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		jsoncpp_static
)

file(GLOB CONFIGS
	LIST_DIRECTORIES false
	CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/data/SKSE/Plugins/${PROJECT_NAME}/*.json"
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		${CONFIGS}
)

source_group(
	"Data Files/Configs"
	FILES
		${CONFIGS}
)

install(
	FILES
		${CONFIGS}
	DESTINATION
		"SKSE/Plugins/${PROJECT_NAME}"
)

if(NOT BUILD_SKYRIMVR)
	install(
		FILES
			"${PROJECT_SOURCE_DIR}/data/SkyrimSE/I4IconAddon.esp"
		DESTINATION "."
	)
else()
	install(
		FILES
			"${PROJECT_SOURCE_DIR}/data/SkyrimVR/I4IconAddon.esp"
		DESTINATION "."
	)
endif()

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/Interface/I4IconAddon/icons.swf"
	DESTINATION "Interface/I4IconAddon"
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/Interface/Translations/I4IconAddon_ENGLISH.txt"
	DESTINATION "Interface/Translations"
)

set(CPACK_GENERATOR "7Z")
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME}-${PROJECT_VERSION})
if(BUILD_SKYRIMVR)
	string(APPEND CPACK_PACKAGE_FILE_NAME "-VR")
endif()
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)
include(CPack)
