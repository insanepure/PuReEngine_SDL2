@echo off
cls
Color 1F
echo *******************************************************************************
echo *                               Clean up                                      *
echo *******************************************************************************

echo Cleaning up ...
echo.
del Build\*.ilk
del Build\*.pdb
del PuReEngine\*.sdf
del PuReEngine\*.ncb
del PuReEngine\*.opensdf
del PuReEngine\*.suo /A:H
rd  PuReEngine\ipch /Q /S
rd  PuReEngine\intermediate /Q /S
rd  PuReEngine\PuReEngine\intermediate /Q /S