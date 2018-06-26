#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "scripthook\main.h"
#include "scripthook\enums.h"
#include "scripthook\natives.h"
#include "pybind11/pybind11.h"
#include "pybind11/embed.h"
#include "pybind11/stl.h"

namespace py = pybind11;
void defEnums(py::module m);
void defNatives(py::module m);

py::function main_cb;

static bool running = 1;
static void scriptMain() {
	while (running) {
		if (main_cb) {
			try {
				py::gil_scoped_acquire acquire;
				main_cb();
			}
			catch (...) {
			}
		}
		WAIT(0);
	}
	TERMINATE();
}

PYBIND11_MODULE(pyhookv, m) {
	m.doc() = "Python ScriptHookV interface";
	defEnums(m);
	defNatives(m);
	m.def("main_cb", []() { return main_cb; });
	m.def("set_main_cb", [](py::object f) { main_cb = f; });
	m.def("wait", WAIT, py::call_guard<py::gil_scoped_release>());
	{
		class V {};
		py::class_<V> egv(m, "game_version");
		egv.def_property_readonly_static("Unknown", []() { return -1; });
		egv.def_property_readonly_static("current", []() { return (int)getGameVersion(); });
		const char * versions[] = { "v1_0_335_2_Steam","v1_0_335_2_NoSteam","v1_0_350_1_Steam","v1_0_350_2_NoSteam","v1_0_372_2_Steam","v1_0_372_2_NoSteam","v1_0_393_2_Steam","v1_0_393_2_NoSteam","v1_0_393_4_Steam","v1_0_393_4_NoSteam","v1_0_463_1_Steam","v1_0_463_1_NoSteam","v1_0_505_2_Steam","v1_0_505_2_NoSteam","v1_0_573_1_Steam","v1_0_573_1_NoSteam","v1_0_617_1_Steam","v1_0_617_1_NoSteam","v1_0_678_1_Steam","v1_0_678_1_NoSteam","v1_0_757_2_Steam","v1_0_757_2_NoSteam","v1_0_757_3_Steam","v1_0_757_4_NoSteam","v1_0_791_2_Steam","v1_0_791_2_NoSteam","v1_0_877_1_Steam","v1_0_877_1_NoSteam","v1_0_944_2_Steam","v1_0_944_2_NoSteam","v1_0_1011_1_Steam","v1_0_1011_1_NoSteam","v1_0_1032_1_Steam","v1_0_1032_1_NoSteam","v1_0_1103_2_Steam","v1_0_1103_2_NoSteam","v1_0_1180_2_Steam","v1_0_1180_2_NoSteam","v1_0_1290_1_Steam","v1_0_1290_1_NoSteam","v1_0_1365_1_Steam","v1_0_1365_1_NoSteam" };
		for (int i = 0; i < sizeof(versions)/sizeof(*versions); i++)
			egv.def_property_readonly_static(versions[i], [i]() { return i; });
	}
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID) {
	if (reason == DLL_PROCESS_ATTACH) {
		scriptRegister(hInst, scriptMain);
	}

	if (reason == DLL_PROCESS_DETACH) {
		running = 0;
		scriptUnregister(hInst);
	}
	return TRUE;
}


