@echo off

del /s /q "%~dp0..\..\*.sln"
del /s /q "%~dp0..\..\*.vcxproj*"

echo Removed all .sln and .vcxproj files recursively.