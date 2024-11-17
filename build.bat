::
:: FILE          build.bat
::
:: AUTHORS
::               Ilya Akkuzin <gr3yknigh1@gmail.com>
::
:: NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
::

@echo off

set project_folder=%~dp0
set configuration_folder=%project_folder%\build
set conan_folder=%project_folder%\.conan

set build_type=%1
shift

if [%build_type%]==[] set build_type=Debug

:: Detect vcvarsall for x64 build...
set vc2022_bootstrap="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
set vc2019_bootstrap="C:\Program Files (x86)\Microsoft Visual Studio\2019\Preview\VC\Auxiliary\Build\vcvarsall.bat"

if exist %vc2022_bootstrap% (
  echo I: Found VC 2022 bootstrap script!
  call %vc2022_bootstrap% amd64
) else (
  if exist %vc2019_bootstrap% (
    echo I: No script for VC 2022, but found VC 2019 bootstrap script!
    call %vc2019_bootstrap% amd64
  ) else (
    echo W: Failed to find nor VC 2019, nor VC 2022 bootstrap scripts!
  )
)

pushd %project_folder%

:: Compiling...
if "%build_type%" == "Debug" (
  echo I: Building debug
  conan build . --output-folder %configuration_folder% --build=missing --profile %conan_folder%\msvc-193-x86_64-static-debug
) else (
  if "%build_type%" == "Release" (
    echo I: Building release
    conan build . --output-folder %configuration_folder% --build=missing --profile %conan_folder%\msvc-193-x86_64-static-release
  ) else (
    echo E: Invalid build type: %build_type%
    exit 1
  )
)

if exist %configuration_folder%\compile_commands.json (
  echo I: Copying compilation database...
  copy %configuration_folder%\compile_commands.json %project_folder%\compile_commands.json
)

popd
