workspace "Virtual-Tabletop"
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
				"../Virtual-Tabletop-API/Include"
			}

			links {

				"Virtual-Tabletop-API"
			}

			defines {

				"VTT_CLIENT"
			}

			filter "system:windows"
				systemversion "latest"
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

		project "Game-Server"
			location "../Server/Game-Server"
			kind "ConsoleApp"
			language "C++"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}/")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}/")

			pchheader "VttGameServerPch.h"
			pchsource "../Server/Source/VttGameServerPch.cpp"

			files {

				"../Server/Game-Server/Include/**.h",
				"../Server/Game-Server/Source/**.cpp"
			}

			includedirs {

				"../Libraries/spdlog/include",
				"../Server/Game-Server/Include",
				"../Virtual-Tabletop-API/Include",
			}

			links {

				"Virtual-Tabletop-API"
			}

			defines {

				"VTT_SERVER"
			}

			filter "system:windows"
				systemversion "latest"
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
