#include <sstream>
#include "pybind11/pybind11.h"
#include "scripthook/natives.h"
#include "scripthook/enums.h"
#include "natives_type.h"
namespace py = pybind11;

void custom(py::class_<Py_Ai>){}
void custom(py::class_<Py_App>){}
void custom(py::class_<Py_Audio>){}
void custom(py::class_<Py_Blip>){}
void custom(py::class_<Py_Brain>){}
void custom(py::class_<Py_Cam>){}
void custom(py::class_<Py_Controls>){}
void custom(py::class_<Py_Cutscene>){}
void custom(py::class_<Py_Datafile>){}
void custom(py::class_<Py_Decisionevent>){}
void custom(py::class_<Py_Decorator>){}
void custom(py::class_<Py_Dlc1>){}
void custom(py::class_<Py_Dlc2>){}
void custom(py::class_<Py_Fire>){}
void custom(py::class_<Py_Gameplay>){}
void custom(py::class_<Py_Graphics>){}
void custom(py::class_<Py_Interior>){}
void custom(py::class_<Py_Itemset>){}
void custom(py::class_<Py_Mobile>){}
void custom(py::class_<Py_Network>){}
void custom(py::class_<Py_Networkcash>){}
void custom(py::class_<Py_Rope>){}
void custom(py::class_<Py_ScrHandle>){}
void custom(py::class_<Py_Script>){}
void custom(py::class_<Py_Socialclub>){}
void custom(py::class_<Py_Stats>){}
void custom(py::class_<Py_Streaming>){}
void custom(py::class_<Py_System>){}
void custom(py::class_<Py_Time>){}
void custom(py::class_<Py_Ui>){}
void custom(py::class_<Py_Unk>){}
void custom(py::class_<Py_Unk1>){}
void custom(py::class_<Py_Unk2>){}
void custom(py::class_<Py_Unk3>){}
void custom(py::class_<Py_Void>){}
void custom(py::class_<Py_Water>){}
void custom(py::class_<Py_Weapon>){}
void custom(py::class_<Py_Worldprobe>){}
void custom(py::class_<Py_Zone>){}
void custom(py::class_<Py_uint>){}

void custom(py::class_<Py_Any> c) {
	c.def(py::init<int>());
	py::implicitly_convertible<py::int_, Py_Any>();
}

template<typename T> T get(int handle, int offset) {
	return *(T*)(getScriptHandleBaseAddress(handle) + offset);
}
template<typename T> void set(int handle, int offset, T value) {
	*((T*)(getScriptHandleBaseAddress(handle) + offset)) = value;
}

void custom(py::class_<Py_Player> c) {
	c
		.def_property_readonly("entity_is_free_aiming_at", [](Py_Player p) {
			Entity e = 0;
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(p.id, &e))
				return Py_Entity(e);
			return Py_Entity(0);
		})
		.def_property_readonly("color", [](Py_Player p) {
			int r, g, b;
			PLAYER::GET_PLAYER_RGB_COLOUR(p.id, &r, &g, &b);
			return py::make_tuple(r, g, b);
		})
		.def_property_readonly("target_entitiy", [](Py_Player p) {
			Entity e = 0;
			if (PLAYER::GET_PLAYER_TARGET_ENTITY(p.id, &e))
				return Py_Entity(e);
			return Py_Entity(0);
		})
		.def_property("parachute_tint_index",
			[](Py_Player p) { int r = 0;  PLAYER::GET_PLAYER_PARACHUTE_TINT_INDEX(p.id, &r); return r; },
			[](Py_Player p, int id) { PLAYER::SET_PLAYER_PARACHUTE_TINT_INDEX(p.id, id); })
		.def_property("reserve_parachute_tint_index",
			[](Py_Player p) { int r = 0;  PLAYER::GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(p.id, &r); return r; },
			[](Py_Player p, int id) { PLAYER::SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(p.id, id); })
		.def_property("parachute_pack_tint_index",
			[](Py_Player p) { int r = 0;  PLAYER::GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(p.id, &r); return r; },
			[](Py_Player p, int id) { PLAYER::SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(p.id, id); })
		.def_property("parachute_smoke_trail_color",
			[](Py_Player p) { int r = 0, g = 0, b = 0;  PLAYER::GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(p.id, &r, &g, &b); return py::make_tuple(r, g, b); },
			[](Py_Player p, py::tuple c) { if (c.size() != 3) throw pybind11::value_error("Expecting tuple<int,int,int>()"); PLAYER::SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(p.id, py::cast<int>(c[0]), py::cast<int>(c[1]), py::cast<int>(c[2])); })
		;
}

void custom(py::class_<Py_Entity> c) {
	c
		.def_static("delete", [](Py_Entity e) {Entity ee = e; ENTITY::DELETE_ENTITY(&ee); e = ee; })
		.def_static("set_no_longer_needed", [](Py_Entity e) {Entity ee = e; ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ee); e = ee; })
		.def("matrix", [](Py_Entity e) {Vector3 right, forward, up, position; ENTITY::GET_ENTITY_MATRIX(e.id, (Any*)&right, (Any*)&forward, &up, &position); return py::make_tuple(right, forward, up, position); })
		.def("quaternion", [](Py_Entity e) {float x, y, z, w; ENTITY::GET_ENTITY_QUATERNION(e.id, &x, &y, &z, &w); return py::make_tuple(x, y, z, w); })
		;
	// Ignore ENTITY::GET_ENTITY_SCRIPT
	// Ignore ENTITY::FIND_ANIM_EVENT_PHASE
	// Ignore ENTITY::PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM
	// Ignore ENTITY::SET_OBJECT_AS_NO_LONGER_NEEDED
	// Ignore ENTITY::SET_PED_AS_NO_LONGER_NEEDED
	// Ignore ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED
}
template<typename T, int (*F)(int*, int)> py::list getAll() {
	int n = 256;
	std::vector<int> all(n);
	int m =F(all.data(), n);
	while (m >= n) {
		n *= 2;
		all.resize(n);
		m = F(all.data(), n);
	}
	py::list r(m);
	for (size_t i = 0; i < m; i++)
		r[i] = T(all[i]);
	return r;
}

const size_t MAX_NEARBY = 100;
struct NearbyEnts {
	int size = MAX_NEARBY;
	int64_t entities[MAX_NEARBY];
};
void custom(py::class_<Py_Ped> c) {
	enum PedType {
		AnyPed = -1,
		MichaelPed = 0,
		FranklinPed = 1,
		TrevorPed = 2,
		MalePed = 4,
		FemalePed = 5,
		CopPed = 6,
		ParamedicPed = 20,
		LSFDPed = 21,
		HumanPed = 26,
		SWATPed = 27,
		AnimalPed = 28,
		ArmyPed = 29
	};
	using namespace pybind11::literals;
	py::enum_<PedType>(c, "PedType")
		.value("Any", AnyPed)
		.value("Michael", MichaelPed)
		.value("Franklin", FranklinPed)
		.value("Trevor", TrevorPed)
		.value("Male", MalePed)
		.value("Female", FemalePed)
		.value("Paramedic", ParamedicPed)
		.value("LSFD", LSFDPed)
		.value("Human", HumanPed)
		.value("SWAT", SWATPed)
		.value("Animal", AnimalPed)
		.value("Army", ArmyPed);
	c
		.def_static("delete", [](Py_Ped p) {Ped pp = p; PED::DELETE_PED(&pp); p = pp; })
		.def_static("remove_elegantly", [](Py_Ped p) {Ped pp = p; PED::REMOVE_PED_ELEGANTLY(&pp); p = pp; })
		.def_property_readonly("last_damage_bone", [](Py_Ped p) {Any r = 0; if (PED::GET_PED_LAST_DAMAGE_BONE(p, &r)) return (int)r; return 0; })
		.def("nearby_peds", [](Py_Ped p, int n, int ignore_type) {NearbyEnts nb = { n }; int N = PED::GET_PED_NEARBY_PEDS(p, (int*)&nb, ignore_type); py::list r; for (int i = 0; i < N; i++) r.append(Py_Ped((int)nb.entities[i])); return r; }, "n"_a = MAX_NEARBY, "ignore_type"_a = -1)
		.def("nearby_vehicles", [](Py_Ped p, int n) {NearbyEnts nb = { n }; int N = PED::GET_PED_NEARBY_VEHICLES(p, (int*)&nb); py::list r; for (int i = 0; i < N; i++) r.append(Py_Ped((int)nb.entities[i])); return r; }, "n"_a = MAX_NEARBY)
		.def_property("parachute_tint_index",
			[](Py_Ped p) { Any r = 0;  PED::GET_PED_PARACHUTE_TINT_INDEX(p.id, &r); return r; },
			[](Py_Ped p, Any id) { PED::SET_PED_PARACHUTE_TINT_INDEX(p.id, id); })
		.def("is_evasive_driving", [](Py_Ped p) {Entity e = 0; if (PED::IS_PED_EVASIVE_DIVING(p, &e)) return Py_Entity(e); return Py_Entity(0); })
		.def_static("list", getAll<Py_Ped, worldGetAllPeds>)
		;
	// Ignore PED::SET_PED_GESTURE_GROUP
	// Ignore PED::_GET_PED_HEAD_BLEND_DATA
	// Ignore PED::SET_PED_RESERVE_PARACHUTE_TINT_INDEX
	// Ignore PED::SET_FACIAL_IDLE_ANIM_OVERRIDE
	// Ignore PED::ADD_RELATIONSHIP_GROUP
	// Ignore PED::APPLY_PED_BLOOD_BY_ZONE
	// Ignore PED::APPLY_PED_BLOOD_SPECIFIC
	// Ignore PED::GET_ANIM_INITIAL_OFFSET_POSITION
	// Ignore PED::GET_ANIM_INITIAL_OFFSET_ROTATION
	// Ignore PED::GET_CLOSEST_PED
	// Ignore PED::GET_GROUP_SIZE
	// Ignore PED::SET_PED_ALTERNATE_WALK_ANIM
}

void custom(py::class_<Py_Vehicle> c) {

	c
		.def_static("delete", [](Py_Vehicle v) {Vehicle vv = v; VEHICLE::DELETE_VEHICLE(&vv); v = vv; })
		.def_property_readonly("colour", [](Py_Vehicle v) { int r = 0, g = 0, b = 0;  VEHICLE::GET_VEHICLE_COLOR(v, &r, &g, &b); return py::make_tuple(r, g, b); })
		.def_property_readonly("colours", [](Py_Vehicle v) { int p = 0, s = 0;  VEHICLE::GET_VEHICLE_COLOURS(v, &p, &s); return py::make_tuple(p, s); })
		.def_property_readonly("custom_primary_colour", [](Py_Vehicle v) { int r = 0, g = 0, b = 0;  VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(v, &r, &g, &b); return py::make_tuple(r, g, b); })
		.def_property_readonly("custom_secondary_colour", [](Py_Vehicle v) { int r = 0, g = 0, b = 0;  VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(v, &r, &g, &b); return py::make_tuple(r, g, b); })
		.def_property_readonly("extra_colours", [](Py_Vehicle v) { int p = 0, s = 0;  VEHICLE::GET_VEHICLE_EXTRA_COLOURS(v, &p, &s); return py::make_tuple(p, s); })
		.def_property_readonly("light_state", [](Py_Vehicle v) { int on = 0, hb_on = 0; VEHICLE::GET_VEHICLE_LIGHTS_STATE(v, &on, &hb_on); return py::make_tuple(on, hb_on); })
		.def_property_readonly("mod_color_1", [](Py_Vehicle v) { int p = 0, s = 0, c = 0;  VEHICLE::GET_VEHICLE_MOD_COLOR_1(v, &p, &s, &c); return py::make_tuple(p, s, c); })
		.def_property_readonly("mod_color_2", [](Py_Vehicle v) { int p = 0, s = 0;  VEHICLE::GET_VEHICLE_MOD_COLOR_2(v, &p, &s); return py::make_tuple(p, s); })
		.def_property_readonly("neon_lights_colour", [](Py_Vehicle v) { int r = 0, g = 0, b = 0;  VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(v, &r, &g, &b); return py::make_tuple(r, g, b); })
		.def_property_readonly("owner", [](Py_Vehicle v) { Entity e = 0; if (VEHICLE::_GET_VEHICLE_OWNER(v, &e)) return Py_Entity(e); return Py_Entity(0); })
		.def_property_readonly("trailer", [](Py_Vehicle v) { Vehicle vv = 0; if (VEHICLE::GET_VEHICLE_TRAILER_VEHICLE(v, &vv)) return Py_Vehicle(vv); return Py_Vehicle(0); })
		.def_property("parachute_smoke_trail_color",
			[](Py_Vehicle v) { int r = 0, g = 0, b = 0; VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(v, &r, &g, &b); return py::make_tuple(r, g, b); },
			[](Py_Vehicle v, py::tuple c) { if (c.size() != 3) throw pybind11::value_error("Expecting tuple<int,int,int>()");  VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(v, py::cast<int>(c[0]), py::cast<int>(c[1]), py::cast<int>(c[2])); })
		.def_static("list", getAll<Py_Vehicle, worldGetAllVehicles>);

	int STEERING_BASE = 0x924, GEAR_BASE = 0x812;
	if (getGameVersion() < VER_1_0_350_2_NOSTEAM) { STEERING_BASE = 0x896; GEAR_BASE = 0x792; }
	else if (getGameVersion() <= 25/*VER_1_0_791_2_NOSTEAM*/){ STEERING_BASE = 0x8AC; GEAR_BASE = 0x7A2; }
	else if (getGameVersion() <= 27/*VER_1_0_877_1_NOSTEAM*/){ STEERING_BASE = 0x8CC; GEAR_BASE = 0x7C2; }
	else if (getGameVersion() <= 33/*VER_1_0_1032_1_NOSTEAM*/){ STEERING_BASE = 0x8F4; GEAR_BASE = 0x7E2; }
	else if (getGameVersion() <= 35/*VER_1_0_1103_2_NOSTEAM*/){ STEERING_BASE = 0x904; GEAR_BASE = 0x7F2; }
	else if (getGameVersion() <= 37/*VER_1_0_1180_2_NOSTEAM*/){ STEERING_BASE = 0x924; GEAR_BASE = 0x812; }
	else if (getGameVersion() <= 39/*VER_1_0_1290_1_NOSTEAM*/){ STEERING_BASE = 0x944; GEAR_BASE = 0x832; }
	// else LOG(WARN) << "GEAR_BASE and STEERING_BASE not properly set. Unknown game version!";

	c.def_property("control",
		[STEERING_BASE](Py_Vehicle v) {
			float steering = -get<float>(v, STEERING_BASE + 0x0) / 0.6981317008f;
			float throttle = get<float>(v, STEERING_BASE + 0x8);
			float brake = get<float>(v, STEERING_BASE + 0xc);
			return py::make_tuple(steering, throttle, brake);
		},
		[GEAR_BASE](Py_Vehicle v, py::tuple c) {
			float steering = c.size() > 0 ? py::cast<float>(c[0]) : 0, throttle = c.size() > 1 ? py::cast<float>(c[1]) : 0, brake = c.size() > 2 ? py::cast<float>(c[2]) : 0;
			float current_speed = ENTITY::GET_ENTITY_SPEED_VECTOR(v, true).y;
			unsigned char gear = get<unsigned char>(v, GEAR_BASE);
			float control_throttle = 0, control_brake = 0;
			if (gear > 0) { // Forward gear
				if (throttle >= 0.f) {
					control_throttle = throttle;
					if (fabs(current_speed) > 0.5f) control_brake = brake;
					else if (brake > throttle) control_throttle = 0;
				}
				else {
					control_throttle = 0.f;
					control_brake = brake - throttle;
				}
			} else { // Back gear
				if (throttle <= 0.f) {
					control_brake = -throttle;
					if (fabs(current_speed) > 0.5f) control_throttle = brake;
					else if (brake > -throttle) control_throttle = 0;
				}
				else {
					control_brake = 0.f;
					control_throttle = throttle + brake;
				}
			}
			if (control_throttle > 0) control_throttle = 0.25 + 0.75 * control_throttle; // Get out of the deadzone
			if (control_brake > 0) control_brake = 0.25 + 0.75 * control_brake; // Get out of the deadzone
			CONTROLS::_SET_CONTROL_NORMAL(27, ControlVehicleAccelerate,control_throttle); //[0,1]
			CONTROLS::_SET_CONTROL_NORMAL(27, ControlVehicleBrake, control_brake); //[0,1]
			CONTROLS::_SET_CONTROL_NORMAL(27, ControlVehicleMoveLeftRight, steering > 0 ? (0.25 + 0.75 * steering) : (-0.25 + 0.75 * steering)); //[-1,1]
		});
		//if ( is_controlled == EXTERNAL_CONTROL) {
		//	if (vehicle) {
		//		float current_speed = ENTITY::GET_ENTITY_SPEED_VECTOR(vehicle, true).y;
		//		unsigned char gear = get<unsigned char>(vehicle, GEAR_BASE);

		//		float control_throttle = 0, control_brake = 0;
		//		if (gear > 0) { // Forward gear
		//			if (throttle >= 0.f) {
		//				control_throttle = throttle;
		//				if (fabs(current_speed) > 0.5f) control_brake = brake;
		//				else if (brake > throttle) control_throttle = 0;
		//			}
		//			else {
		//				control_throttle = 0.f;
		//				control_brake = brake - throttle;
		//			}
		//		} else { // Back gear
		//			if (throttle <= 0.f) {
		//				control_brake = -throttle;
		//				if (fabs(current_speed) > 0.5f) control_throttle = brake;
		//				else if (brake > -throttle) control_throttle = 0;
		//			}
		//			else {
		//				control_brake = 0.f;
		//				control_throttle = throttle + brake;
		//			}
		//		}
		//		if (control_throttle > 0) control_throttle = 0.25 + 0.75 * control_throttle; // Get out of the deadzone
		//		if (control_brake > 0) control_brake = 0.25 + 0.75 * control_brake; // Get out of the deadzone
		//		CONTROLS::_SET_CONTROL_NORMAL(27, ControlVehicleAccelerate,control_throttle); //[0,1]
		//		CONTROLS::_SET_CONTROL_NORMAL(27, ControlVehicleBrake, control_brake); //[0,1]
		//		CONTROLS::_SET_CONTROL_NORMAL(27, ControlVehicleMoveLeftRight, steering > 0 ? (0.25 + 0.75 * steering) : (-0.25 + 0.75 * steering)); //[-1,1]
		//	} else {
		//		CONTROLS::_SET_CONTROL_NORMAL(0, 59, steering); //[-1,1]
		//	}
		//} else /* is_controlled != EXTERNAL_CONTROL */ {
		//	if (vehicle) {
		//		steering = -get<float>(vehicle, STEERING_BASE + 0x0) / 0.6981317008f;
		//		throttle =  get<float>(vehicle, STEERING_BASE + 0x8);
		//		brake    =  get<float>(vehicle, STEERING_BASE + 0xc);
		//	}
		//	else
		//		throttle = brake = steering = 0;
		//}
	// Ignore VEHICLE::DELETE_MISSION_TRAIN
	// Ignore VEHICLE::GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME
	// Ignore VEHICLE::GET_RANDOM_VEHICLE_MODEL_IN_MEMORY
	// Ignore VEHICLE::GET_VEHICLE_RECORDING_ID
	// Ignore VEHICLE::GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME
	// Ignore VEHICLE::HAS_VEHICLE_RECORDING_BEEN_LOADED
	// Ignore VEHICLE::REMOVE_VEHICLE_RECORDING
	// Ignore VEHICLE::REQUEST_VEHICLE_RECORDING
	// Ignore VEHICLE::SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED
	// Ignore VEHICLE::START_PLAYBACK_RECORDED_VEHICLE_USING_AI
	// Ignore VEHICLE::START_PLAYBACK_RECORDED_VEHICLE
	// Ignore VEHICLE::START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS
}
// Ignore OBJECT::DELETE_OBJECT
// Ignore OBJECT::GET_STATE_OF_CLOSEST_DOOR_OF_TYPE


void custom(py::class_<Py_Pathfind> c) {
	c
		// Ignore PATHFIND::LOAD_ALL_PATH_NODES (no longer supported in newer versions)
		.def_static("load_all_path_nodes", []() { return PATHFIND::_0xF7B79A50B905A30D(-8192.0f, 8192.0f, -8192.0f, 8192.0f); })
		.def_static("closest_major_vehicle_node", [](float x, float y, float z, float u0, int u1) -> py::object { Vector3 r; if (PATHFIND::GET_CLOSEST_MAJOR_VEHICLE_NODE(x, y, z, &r, u0, u1)) return py::cast(r); return py::none(); })
		.def_static("closest_vehicle_node", [](float x, float y, float z, int node_type, float u0, float u1) -> py::object { Vector3 r; if (PATHFIND::GET_CLOSEST_VEHICLE_NODE(x, y, z, &r, node_type, u0, u1)) return py::cast(r); return py::none(); })
		.def_static("closest_vehicle_node_with_heading", [](float x, float y, float z, int node_type, float u0, int u1) -> py::object { Vector3 r; float h; if (PATHFIND::GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(x, y, z, &r, &h, node_type, u0, u1)) return py::make_tuple(r, h); return py::none(); })
		.def_static("save_coord_for_ped", [](float x, float y, float z, bool sidewalk, int flags) -> py::object { Vector3 r; if (PATHFIND::GET_SAFE_COORD_FOR_PED(x, y, z, sidewalk, &r, flags)) return py::cast(r); return py::none(); })
		.def_static("streed_name_at_coord", [](float x, float y, float z) {Hash sn, cr; PATHFIND::GET_STREET_NAME_AT_COORD(x, y, z, &sn, &cr); return py::make_tuple(sn, cr); })
		.def_static("vehicle_node_position", [](int nid) {Vector3 r; PATHFIND::GET_VEHICLE_NODE_POSITION(nid, &r); return r; })
		;
	// Ingore PATHFIND::GENERATE_DIRECTIONS_TO_COORD
	// Ingore PATHFIND::GENERATE_DIRECTIONS_TO_COORD
	// Ignore PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE
	// Ignore PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION
	// Ignore PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING
	// Ignore PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING
	// Ignore PATHFIND::GET_RANDOM_VEHICLE_NODE
	// Ignore PATHFIND::GET_VEHICLE_NODE_PROPERTIES
}

void custom(py::class_<Py_Object> c) {
	c
		.def_static("list", getAll<Py_Object, worldGetAllObjects>)
		;
}
void custom(py::class_<Py_Pickup> c) {
	c
		.def_static("list", getAll<Py_Pickup, worldGetAllPickups>)
		;
}
void custom(py::class_<Py_Hash> c) {
	c.def("__repr__", [](const Py_Hash & h) { return ((std::ostringstream&)(std::ostringstream() << "0x" << std::hex << h.id)).str();  });
	c.def("__str__", [](const Py_Hash & h) { return ((std::ostringstream&)(std::ostringstream() << "0x" << std::hex << h.id)).str();  });
}