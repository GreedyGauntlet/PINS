-- Include Directories
IncludeDir = {}
--IncludeDir["openSSL"] = "%{wks.location}/Needles/vendor/openssl/include"

-- Library Directories
LibraryDir = {}
--LibraryDir["openSSL"] = "%{wks.location}/Needles/vendor/openssl/lib"

-- Library
Library = {}
Library["WinSock"] = "Ws2_32.lib"
--Library["libssl"] = "%{LibraryDir.openSSL}/libssl.lib"
--Library["libcrypto"] = "%{LibraryDir.openSSL}/libcrypto.lib"
--Library["openSSL"] = "%{LibraryDir.openSSL}/openssl.lib"