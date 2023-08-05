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

	-- Group directories relative to the premake file in root/Premake
	GroupDir = {}
	GroupDir["Client"] = "../Client"
	GroupDir["Server"] = "../Server"
	GroupDir["Libraries"] = "../Libraries"
	-- Include directories relative to the premake file in root/Premake
	IncludeDir = {}
	IncludeDir["Client"] = "%{GroupDir.Client}/Client/Include"
	IncludeDir["Game-Server"] = "%{GroupDir.Server}/Game-Server/Include"
	IncludeDir["VTTAPI"] = "%{GroupDir.Libraries}/Virtual-Tabletop-API/Virtual-Tabletop-API/Include"
	IncludeDir["spdlog"] = "%{GroupDir.Libraries}/spdlog/include"
	IncludeDir["ImGui"] = "%{GroupDir.Libraries}/imgui"
	IncludeDir["optick"] = "%{GroupDir.Libraries}/optick/src"
	IncludeDir["yaml"] = "%{GroupDir.Libraries}/yaml-cpp/include"
	IncludeDir["googletest"] = "%{GroupDir.Libraries}/googletest/googletest"
	

	group "Client"

		project "Client"
			location "%{GroupDir.Client}/Client"
			kind "WindowedApp"
			language "C++"
			cppdialect "c++20"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}/")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}/")

			pchheader "VttClientPch.h"
			pchsource "../Client/Client/Source/VttClientPch.cpp"

			files {

				"%{GroupDir.Client}/Client/Include/**.h",
				"%{GroupDir.Client}/Client/Source/**.cpp",
			}

			includedirs {

				"%{IncludeDir.Client}",
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
		
		project "Client-Test"
			location "%{GroupDir.Client}/Client-Test"
			kind "ConsoleApp"
			language "C++"

			targetdir ("../bin/".. output_dir .. "&{prj.name}/")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}/")

			files {

				"%{GroupDir.Client}/Client-Test/Include/**.h",
				"%{GroupDir.Client}/Client-Test/Source/**.cpp"
			}

			includedirs {

				"%{IncludeDir.Client}",
				"%{GroupDir.Client}/Client-Test/Include",
				"%{GroupDir.Client}/Client-Test/Source",
				"%{IncludeDir.googletest}",
				"%{IncludeDir.googletest}/include"
			}

			filter {"system:windows", "configurations:Debug"}
				buildoptions {

					"/MTd"
				}
				links {

					"../bin/" .. output_dir .. "/GoogleTest/GoogleTest",
				}

			filter "configurations:Debug"
				defines "DEBUG"
				runtime "Debug"
				symbols "on"

	group "Server"

		project "Game-Server"
			location "%{GroupDir.Server}/Game-Server"
			kind "ConsoleApp"
			language "C++"
			systemversion "latest"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}/")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}/")

			pchheader "VttGameServerPch.h"
			pchsource "%{GroupDir.Server}/Game-Server/Source/VttGameServerPch.cpp"

			files {

				"%{GroupDir.Server}/Game-Server/Include/**.h",
				"%{GroupDir.Server}/Server/Game-Server/Source/**.cpp"
			}

			includedirs {

				"../Libraries/spdlog/include",
				"%{IncludeDir.Server}",
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

	group "Libraries"
		project "Virtual-Tabletop-API"
			location "%{GroupDir.Libraries}/Virtual-Tabletop-API/%{prj.name}"
			kind "StaticLib"
			language "C++"

			targetdir ("../bin/" .. output_dir .. "/%{prj.name}")
			objdir ("../bin-obj/" .. output_dir .. "/%{prj.name}")

			files {

				"%{GroupDir.Libraries}/Virtual-Tabletop-API/%{prj.name}/Include/**.h",
				"%{GroupDir.Libraries}/Virtual-Tabletop-API/%{prj.name}/Source/**.cpp",
				"%{GroupDir.Libraries}/Virtual-Tabletop-API/%{prj.name}/Source/**.c++",
				"%{GroupDir.Libraries}/Virtual-Tabletop-API/%{prj.name}/Source/**.cc"
			}

			includedirs {

				"%{IncludeDir.VTTAPI}",
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

		project "Virtual-Tabletop-API-Test"
			location "%{GroupDir.Libraries}/Virtual-Tabletop-API/Virtual-Tabletop-API-Test"
			kind "ConsoleApp"
			language "C++"

		include "../Libraries/googletest"
		include "../Libraries/imgui"
		include "../Libraries/optick/premake-core-only"
		include "../Libraries/yaml-cpp"
	group "TTRPG Modules"