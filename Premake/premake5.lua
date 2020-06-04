workspace "Virtual_Tabletop"
	location "../"
	architecture "x64"
	startproject "Client"

	configurations {

		"Debug",
		"Release",
		"Distribution"
	}

	output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to the premake file in root/Premake
	Include_Dir = {}

	group "Libraries"

	group "API"

		project "Virtual_Tabletop_API"
			location "../%{prj.name}"
			kind "StaticLib"
			language "C++"
			staticruntime "on"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}")

			pchheader "VTT_API_PCH.h"
			pchsource "../Virtual_Tabletop_API/Source/VTT_API_PCH.cpp"

			files {

				"../%{prj.name}/Include/**.h",
				"../%{prj.name}/Source/**.cpp"
			}

			includedirs {

				"../%{prj.name}/Include",
				"../Libraries/spdlog/include"
			}

			filter "system:windows"
				staticruntime "on"
				systemversion "latest"

				defines {
					"VTT_PLATFORM_WINDOWS"
				}

			filter "system:linux"
				staticruntime "on"

				defines {

					"VTT_PLATFORM_LINUX"
				}

			filter "configurations:Debug"
				defines "VTT_DEBUG"
				runtime "Debug"
				symbols "on"

			filter "configurations:Release"
				defines "VTT_RELEASE"
				runtime "Release"
				optimize "on"

			filter "configurations:Distribution"
				defines "VTT_DISTRIBUTION"
				runtime "Release"
				optimize "on"

	group "Client"

		project "Client"
			location "../Client"
			kind "ConsoleApp"
			language "C++"
			systemversion "latest"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}/")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}/")

			pchheader "VTT_Client_PCH.h"
			pchsource "../Client/Source/VTT_Client_PCH.cpp"

			files {

				"../Client/Include/**.h",
				"../Client/Source/**.cpp",
			}

			includedirs {

				"../Client/Include",
				"../Libraries/spdlog/include",
				"../Virtual_Tabletop_API/Include"
			}

			links {

				"Virtual_Tabletop_API"
			}

			filter "system:windows"
				defines {

					"VTT_PLATFORM_WINDOWS"
				}

			filter {"system:windows", "configurations:Debug"}
				buildoptions {

					"/MTd"
				}

			filter {"system:windows", "configurations:Release"}
				buildoptions {

					"/MT"
				}

			filter "system:linux"
				defines {

					"VTT_PLATFORM_LINUX"
				}

			filter "configurations:Debug"
				defines "VTT_DEBUG"
				runtime "Debug"
				symbols "on"

			filter "configurations:Release"
				defines "VTT_RELEASE"
				runtime "Release"
				optimize "on"

			filter "configurations:Distribution"
				defines "VTT_DISTRIBUTION"
				runtime "Release"
				optimize "on"

	group "Server"

		project "Server"
			location "../Server"
			kind "ConsoleApp"
			language "C++"
			systemversion "latest"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}/")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}/")

			pchheader "VTT_Server_PCH.h"
			pchsource "../Server/Source/VTT_Server_PCH.cpp"

			files {

				"../Server/Include/**.h",
				"../Server/Source/**.cpp"
			}

			includedirs {

				"../Libraries/spdlog/include",
				"../Server/Include",
				"../Virtual_Tabletop_API/Include"
			}

			links {

				"Virtual_Tabletop_API"
			}

			filter "system:windows"
				defines {

					"VTT_PLATFORM_WINDOWS"
				}

			filter {"system:windows", "configurations:Debug"}
				buildoptions {

					"/MTd"
				}

				filter {"system:windows", "configurations:Release"}
					buildoptions {

						"/MT"
					}

			filter "system:linux"
				defines {

					"VTT_PLATFORM_LINUX"
				}

			filter "configurations:Debug"
				defines "VTT_DEBUG"
				runtime "Debug"
				symbols "on"

			filter "configurations:Release"
				defines "VTT_RELEASE"
				runtime "Release"
				optimize "on"

			filter "configurations:Distribution"
				defines "VTT_DISTRIBUTION"
				runtime "Release"
				optimize "on"
