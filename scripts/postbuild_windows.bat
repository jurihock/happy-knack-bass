@echo off

pushd "%~dp0"
set BASE=%CD%
popd

pushd "%BASE%\.."
set ROOT=%CD%
popd

set ARGS=--strictness-level 5 --validate-in-process --validate
set CONFIG=Release
set INPUT=%ROOT%
set OUTPUT=%ROOT%\build

set ARTEFACTS=%OUTPUT%\VintageKnackBass_artefacts\%CONFIG%
set PLUGINVAL=%OUTPUT%\_deps\pluginval-src\pluginval.exe

"%PLUGINVAL%" %ARGS% "%ARTEFACTS%\VST3\VintageKnackBass.vst3" || exit /b

del /q "%ARTEFACTS%\VintageKnackBass_SharedCode.lib"
del /q "%ARTEFACTS%\VST3\VintageKnackBass.exp"
del /q "%ARTEFACTS%\VST3\VintageKnackBass.lib"
