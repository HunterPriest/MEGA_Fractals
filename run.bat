premake5 --cc=clang --dc=ldc ninja
pushd build
ninja
popd
bin\Debug\Fractales.exe