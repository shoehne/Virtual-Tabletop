workspace "Virtual_Tabletop_API"
	location "../"
	architecture "x64"
	startproject "Virtual_Tabletop_API"

	configurations {

		"Debug",
		"Release",
		"Distribution"
	}

	output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to the premake file in root/Premake
	Include_Dir = {}

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
			"../%{prj.name}/Source/**.cpp",
			"../%{prj.name}/Source/**.c++",
			"../%{prj.name}/Source/**.cc"
		}

		includedirs {

			"../%{prj.name}/Include",
			"../Libraries/spdlog/include",
			"../Libraries/yojimbo/"
		}

		links {


		}

		defines {

			
		}

		filter "system:windows"
			staticruntime "on"
			systemversion "latest"

			links {

				"winmm",
				"wldap32",
				"wsock32"
			}

			defines {
				"VTT_PLATFORM_WINDOWS"
			}

		filter {"system:windows", "configurations:Debug"}
			links {

				"../Libraries/yojimbo/bin/x64/Debug/yojimbo"
			}

		filter {"system:windows", "configurations:Release"}
			links {

				"../Libraries/yojimbo/bin/x64/Release/yojimbo"
			}

		filter {"system:windows", "configurations:Distribution"}
			links {

				"../Libraries/yojimbo/bin/x64/Release/yojimbo"
			}

		filter "system:linux"
			staticruntime "on"

			defines {

				"VTT_PLATFORM_LINUX"
			}

		filter {"system:linux", "configurations:Debug"}
		filter {"system:linux", "configurations:Release"}
		filter {"system:linux", "configurations:Distribution"}

		filter "configurations:Debug"
			defines {

				"VTT_DEBUG"
			}
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines {

				"VTT_RELEASE"
			}
			runtime "Release"
			optimize "on"

		filter "configurations:Distribution"
			defines {

				"VTT_DISTRIBUTION"
			}
			runtime "Release"
			optimize "on"

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
				"../Virtual_Tabletop_API/Include",
				"../Libraries/yojimbo/"
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
				"../Libraries/yojimbo/"
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
