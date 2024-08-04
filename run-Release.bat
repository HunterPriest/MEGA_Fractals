premake5 --os=windows ninja
pushd build
ninja Release && goto :run
popd
goto :eof
:run
popd
call open-Release.bat