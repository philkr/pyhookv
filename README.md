# pyhookv
A python wrapper for ScriptHookV.

## Building pyhookv
Make sure to fetch all submodules in git (`git submodule update --init --recursive`) and download the scripthook SDK.
Also copy the scripthook DLL into the game directory.

For an example script see `examples/`.

## Editing the plugin
Most of the code of this plugin (`enums.cpp`, `natives.cpp`, `native_type.h`) is automatically generated from the ScriptHookV header using the script `gen.py`.
If you wish to change some wrapped functions define them in `custom.cpp` and rerun the generator. The generator automatically ignores functions that are wrapped in `custom.cpp`.

