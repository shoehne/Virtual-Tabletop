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
	Include_Dir["Poco_Foundation"] = "../Libraries/POCO/Foundation/include"
	Include_Dir["Poco_Net"] = "../Libraries/POCO/Net/include"

	-- Library directories relative to the premaket file in root/Premake
	Library_Dir = {}
	Library_Dir["POCO"] = "../Libraries/POCO/lib64"

	--group "Libraries/POCO"
		--externalproject "Poco_Foundation"
		--location "../Libraries/POCO/Foundation"
		--uuid "B01196CC-B693-4548-8464-2FF60499E73F"
		--kind "StaticLib"
		--language "C++"

		--externalproject "Poco_Net"
		--location "../Libraries/POCO/Net"
		--uuid "B057A1FE-09F7-465E-B8B5-E1B659051D76"
		--kind "StaticLib"
		--language "C++"

	group "API"

		project "Virtual_Tabletop_API"
			location "../%{prj.name}"
			kind "StaticLib"
			language "C++"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}")

			pchheader "VttApiPch.h"
			pchsource "../Virtual_Tabletop_API/Source/VttApiPch.cpp"

			files {

				"../%{prj.name}/Include/**.h",
				"../%{prj.name}/Source/**.cpp"
			}

			includedirs {

				"../%{prj.name}/Include",
				"../Libraries/spdlog/include",
			}

			links {

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
			kind "WindowedApp"
			language "C++"
			systemversion "latest"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}/")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}/")

			pchheader "VttClientPch.h"
			pchsource "../Client/Source/VttClientPch.cpp"

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

			defines {

				"VTT_CLIENT"
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

			pchheader "VttServerPch.h"
			pchsource "../Server/Source/VttServerPch.cpp"

			files {

				"../Server/Include/**.h",
				"../Server/Source/**.cpp"
			}

			includedirs {

				"../Libraries/spdlog/include",
				"../Server/Include",
				"../Virtual_Tabletop_API/Include",
			}

			links {

				"Virtual_Tabletop_API"
			}

			defines {

				"VTT_SERVER"
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
