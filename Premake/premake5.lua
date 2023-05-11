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
	IncludeDir = {}
	IncludeDir["VTTAPI"] = "../Virtual-Tabletop-API/Include"
	IncludeDir["spdlog"] = "../Libraries/spdlog/include"
	IncludeDir["ImGui"] = "../Libraries/imgui"
	IncludeDir["optick"] = "../Libraries/optick/src"
	IncludeDir["yaml"] = "../Libraries/yaml-cpp/include"

	group "Client"

		project "Client"
			location "../Client"
			kind "WindowedApp"
			language "C++"
			cppdialect "C++20"

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
				"%{IncludeDir.spdlog}",
				"%{IncludeDir.VTTAPI}",
				"%{IncludeDir.ImGui}",
				"%{IncludeDir.optick}",
				"%{IncludeDir.yaml}"
			}

			links {

				"Virtual-Tabletop-API",
				"../bin/" .. output_dir .. "/ImGui/ImGui",
				"../bin/" .. output_dir .. "/yaml-cpp/yaml-cpp"
			}

			defines {

				"CLIENT"
			}

			filter "system:windows"
				systemversion "latest"
				defines {

					"PLATFORM_WINDOWS"
				}
				links {

					"Rpcrt4",
					"d3dcompiler",
					"d3d11"
				}

			filter {"system:windows", "configurations:Debug"}
				buildoptions {

					"/MTd"
				}
				links {
					
				}

			filter {"system:windows", "configurations:Release"}
				buildoptions {

					"/MT"
				}
				links {

				}

			filter "system:linux"
				defines {

					"PLATFORM_LINUX"
				}

			filter "configurations:Debug"
				defines "DEBUG"
				runtime "Debug"
				symbols "on"

			filter "configurations:Release"
				defines "RELEASE"
				runtime "Release"
				optimize "on"

			filter "configurations:Distribution"
				defines "DISTRIBUTION"
				runtime "Release"
				optimize "on"

	group "Server"

		project "Game-Server"
			location "../Server/Game-Server"
			kind "ConsoleApp"
			language "C++"
			cppdialect "C++20"
			systemversion "latest"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}/")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}/")

			files {

				"../Server/Game-Server/Include/**.h",
				"../Server/Game-Server/Source/**.cpp"
			}

			includedirs {

				"../Libraries/spdlog/include",
				"../Server/Game-Server/Include",
				"%{IncludeDir.VTTAPI}"
			}

			links {

				"Virtual-Tabletop-API"
			}

			defines {

				"SERVER"
			}

			filter "system:windows"
				defines {

					"PLATFORM_WINDOWS"
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

					"PLATFORM_LINUX"
				}

			filter "configurations:Debug"
				defines "DEBUG"
				runtime "Debug"
				symbols "on"

			filter "configurations:Release"
				defines "RELEASE"
				runtime "Release"
				optimize "on"

			filter "configurations:Distribution"
				defines "DISTRIBUTION"
				runtime "Release"
				optimize "on"

		project "Lobby-Server"
			location "../Server/Lobby-Server"
			kind "ConsoleApp"
			language "C++"
			cppdialect "C++20"
			systemversion "latest"

	group "Libraries"
		project "Virtual-Tabletop-API"
			location "../%{prj.name}"
			kind "StaticLib"
			language "C++"
			cppdialect "C++20"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}")

			files {

				"../%{prj.name}/Include/**.h",
				"../%{prj.name}/Source/**.cpp",
				"../%{prj.name}/Source/**.c++",
				"../%{prj.name}/Source/**.cc"
			}

			includedirs {

				"../%{prj.name}/Include",
				"%{IncludeDir.spdlog}",
				"%{IncludeDir.yaml}"
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
					"PLATFORM_WINDOWS"
				}

			filter {"system:windows", "configurations:Debug"}

			filter {"system:windows", "configurations:Release"}

			filter {"system:windows", "configurations:Distribution"}

			filter "system:linux"
				staticruntime "on"

				defines {

					"PLATFORM_LINUX"
				}

			filter {"system:linux", "configurations:Debug"}
			filter {"system:linux", "configurations:Release"}
			filter {"system:linux", "configurations:Distribution"}

			filter "configurations:Debug"
				defines {

					"DEBUG"
				}
				runtime "Debug"
				symbols "on"

			filter "configurations:Release"
				defines {

					"RELEASE"
				}
				runtime "Release"
				optimize "on"

			filter "configurations:Distribution"
				defines {

					"DISTRIBUTION"
				}
				runtime "Release"
				optimize "on"
		include "../Libraries/imgui"
		include "../Libraries/optick/premake-core-only"
		include "../Libraries/yaml-cpp"
	group "TTRPG Modules"