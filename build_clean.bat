::
:: FILE          build_clean.bat
::
:: AUTHORS
::               Ilya Akkuzin <gr3yknigh1@gmail.com>
::
:: NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
::

@echo off

set project_folder=%~dp0
set configuration_folder=%project_folder%\build

pushd %project_folder%

if exist %configuration_folder% (
    echo I: Deleting configuration directory [%configuration_folder%].
    rmdir /Q /S %configuration_folder%
) else (
    echo I: Nothing to clean.
)

popd

