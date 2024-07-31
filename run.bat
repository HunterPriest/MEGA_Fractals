premake5 --cc=clang --dc=ldc ninja
pushd build
ninja && goto :run
popd
goto :eof
:run
popd
build\bin\Debug\Fractales.exe