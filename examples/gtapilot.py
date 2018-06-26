import api
import pyhookv as h
from time import time

CAMERA_FOV = 60.
DEFAULT_WEATHER_LIST = ["CLEAR", "EXTRASUNNY", "CLOUDS", "OVERCAST", "RAIN", "CLEARING", "THUNDER", "SMOG", "XMAS", "SNOWLIGHT"]#, "SNOW"]
NO_CONTROL, AI_CONTROL, EXTERNAL_CONTROL = 0, 1, 2
DEFAULT_VEHICLE_MASK = ["CAR", "BIKE", "QUADBIKE", "BICYCLE", "NONE"]
DEFAULT_MAX_SPEED = {"CAR":35, "BIKE":45, "QUADBIKE":30, "BICYCLE":25, "NONE":0}

class Vehicle:
	hash = 0
	def __init__(self, hs):
		self.hash = h.Hash(hs)
	_type = None
	@property
	def type(self):
		if self._type is None:
			self._type = "UNKNOWN"
			if h.Vehicle.is_this_model_a_plane(self.hash): self._type = "PLANE"
			if h.Vehicle.is_this_model_a_heli(self.hash): self._type = "HELI"
			if h.Vehicle.is_this_model_a_car(self.hash): self._type = "CAR"
			if h.Vehicle.is_this_model_a_train(self.hash): self._type = "TRAIN"
			if h.Vehicle.is_this_model_a_bike(self.hash): self._type = "BIKE"
			if h.Vehicle.is_this_model_a_bicycle(self.hash): self._type = "BICYCLE"
			if h.Vehicle.is_this_model_a_quadbike(self.hash): self._type = "QUADBIKE"
			if h.Vehicle.is_this_model_a_submersible(self.hash): self._type = "SUB"
		return self._type

class NoVehicle:
	type = "NONE"

class VehiclePool:
	_vehicles, _typed_vehicles, _self = None, None, None
	@property
	def vehicles(self):
		if VehiclePool._vehicles is not None: return VehiclePool._vehicles
		# hashes = [0, 3078201489,1283517198,1560980623,1672195559,767087018,2771347558,1171614426,837858166,562680400,159274291,3087536137,2818520053,2657817814,2485144969,2487343317,2391954683,2179174271,2154536131,3895125590,3486135912,142944341,1878062887,634118882,470404958,666166960,3253274834,633712403,3471458123,1074326203,630371791,4180675781,3403504941,2053223216,1824333165,1274868363,86520421,1126868326,850991848,3945366167,4278019151,2072156101,1739845664,850565707,3089165662,2166734073,4246935337,3025077634,3854198872,2704629607,4143991942,3681241380,3950024287,1039032026,3703315515,1131912276,524108981,1069929536,2859047862,4262088844,2307837162,4061868990,121658888,444171386,682434785,2815302597,3989239879,1549126457,117401876,3463132580,3692679425,3612755468,3281516360,3990165190,736902334,237764926,1886712733,2598821281,2948279460,3387490166,2551651283,893081117,1132262048,3581397346,788747387,745926877,3334677549,1147287684,3757070668,3525819835,1876516712,2072687711,11251904,4244420235,1621617168,1394036463,2025593404,368211810,941800958,2006918058,3505073125,2983812512,223240013,6774487,349605904,2933279331,390201602,2222034228,906642318,704435172,330661258,2264796000,3690124666,3249425686,2272483501,683047626,108773431,1011753235,784565758,448402357,321739290,3650256867,3288047904,1392481335,2006142190,2890830793,822018448,4055125828,1790834270,3164157193,1682114128,1033245328,276773164,509498602,867467158,1770332643,2154757102,3410276810,3393804037,80636076,3379262425,2623969160,1177543287,3900892662,3057713523,723973206,3968823444,2164484578,2633113103,534258863,1897744184,3467805257,3982671785,970356638,196747873,3728579874,3609690755,2411965148,3053254478,1753414259,3003014393,2035069708,4289813342,3703357000,2175389151,2504420315,2255212070,2452219115,55628203,3005788552,1127131465,2647026068,627535535,3537231886,3903372712,4205676014,2299640309,2728226064,1938952078,3458454463,1353720154,1491375716,1426219628,3157435195,1030400667,184361638,920453016,240201337,642617954,3517691494,744705981,1949211328,1909141499,3205927392,499169875,2016857647,741090084,2494797253,349315417,2549763894,296357396,75131841,1234311532,1019737494,2519238556,2751205197,2186977100,884422927,1265391242,4039289119,4262731174,444583674,1518533038,387748548,2310691317,301427732,37348240,3287439187,4252008158,486987393,970385471,418536135,2889029532,3005245074,4135840458,2434067162,2071877360,2370534026,886934177,3117103977,2246633323,3812247419,3670438162,1051415893,2997294755,3188613414,1058115860,861409633,4174679674,92612664,544021352,2922118804,410882957,1269098716,3013282534,640818791,469291905,4180339789,2068293287,621481054,3080673438,482197771,2634021974,2548391185,2170765704,2771538552,3251507587,1233534620,4152024626,3663206819,2634305738,914654722,3546958660,2230595153,868868440,2531412055,165154707,3984502180,3168702960,3510150843,475220373,3545667823,1565978651,3861591579,3449006043,525509695,1896491931,1783355638,904750859,3244501995,2242229361,3660088182,1034187331,1093792632,2688780135,2351681756,433954513,2999939664,1032823388,2833484545,1036591958,3517794615,884483972,1348744438,3783366066,1987142870,569305213,3863274624,1488164764,3486509883,2287941233,3385765638,2536829930,3917501776,1830407356,2465164804,2157618379,2645431192,177270108,2199527893,1507916787,1078682497,2046537925,2667966721,1912215274,2321795001,4260343491,2758042359,2515846680,456714581,353883353,4175309224,943752001,2112052861,2844316578,741586030,3806844075,2411098011,3144368207,2254540506,356391690,2123327359,2908775872,2643899483,390902130,1645267888,1933662059,2191146052,2360515092,1737773231,2049897956,3620039993,1873600305,3627815886,3705788919,3062131285,234062309,3087195462,2249373259,4280472072,3196165219,1841130506,841808271,782665360,3089277354,3448987385,2136773105,627094268,3319621991,2589662668,3401388520,4067225593,941494461,777714999,1162065741,2518351607,1475773103,719660200,2609945748,223258115,3695398481,734217681,788045382,2841686334,1491277511,3105951696,989381445,4212341271,3039514899,2809443750,1489967196,3406724313,1922255844,3548084598,4108429845,2594165727,3902291871,3264692260,3678636260,3983945033,1221512915,1349725314,873639469,1337041428,2537130571,3080461301,819197656,2611638396,1922257928,3889340782,1044954915,729783779,833469436,1119641113,743478836,1886268224,1074745671,231083307,437538602,3484649228,728614474,400514754,1923400478,3893323758,2817386317,2594093022,1545842587,2196019706,1747439474,4080511798,1723137093,2333339779,2172210288,771711535,3228633070,970598228,3999278268,4012021193,1123216662,710198397,2623428164,384071873,699456151,2983726598,2400073108,1075432268,3955379698,1663218586,1951180813,3286105550,972671128,3223586949,3084515313,3564062519,1956216962,586013744,3338918751,2198148358,1180875963,1356124575,272929391,1836027715,48339065,3347205726,1981688531,1504306544,464687292,1531094468,1762279763,2261744861,2497353967,2736567667,1070967343,908897389,1941029835,2971866336,3852654278,2078290630,1784254509,2091594960,1641462412,2218488798,1445631933,2016027501,1502869817,3417488910,2715434129,2236089197,3194418602,712162987,2413121211,1917016601,3039269212,2942498482,1127861609,3061159916,3894672200,101905590,3631668194,290013743,1448677353,1887331236,2194326579,1043222410,408192225,3312836369,2524324030,2067820283,516990260,887537515,2132890591,338562499,4154065143,1939284556,2694714877,1543134283,2621610858,1077420264,1102544804,1341619767,3469130167,3052358707,2941886209,3796912450,3395457658,16646064,3296789504,2449479409,2672523198,989294410,2006667053,523724515,3685342204,1373123368,1777363799,2382949506,1581459400,2364918497,3676349299,917809321,1203490606,3862958888,65402552,1026149675,2891838741,3172678083,3101863448,3285698347,3724934023,758895617]
		hashes = [
			0x43779c54,0x1aba13b5,0xce23d3bf,0xf4e1aa15,0x4339cd69,0xb67597ec,0xe823fb48, # Bicycles
			0x8125bcf9,0xfd231729,0xb44f0582, # Quads
			0x63abade7,0x806b9cc3,0xf9300cc5,0xcadd5d2d,0xabb0c0,0x77934cee,0x9c669788,0x6882fa73, # Used Bikes
			# 0x30ff0190,0xf1b44f44,0x6abdf65e,0x9c669788,0x6882fa73,0x794cb30c,0x9229e4eb,0x350d1ab,0xb328b188,0x25676eaf,0xd2d5e00e,0x2c2c2324,0x4b6c568a,0xf0c2a91f,0x11f76c14,0xf683eaca,0x26321e67,0xa5325278,0xda288376,0xa0438767,0x34b82784,0xc9ceaf06,0xfdefaec3,0x6facdf31,0xcabd11e8,0x2ef89e46,0xa960b13e,0x58e316c7,0xe7d2a16e,0x2c509634,0x6d6f8f43,0xf79a00f7,0xaf599f01,0xdba9dbfc,0xdb20a373,0xc3d7c72b,0xde05fb87 # Unused bikes
			0xb779a091,0x4c80eb0e,0x5d0aac8f,0x2db8d1aa,0x45d56ada,0x94204d89,0x9441d8d5,0x8e9254fb, # Used Cars
			# 0xcfca3668,0x8852855,0x6ff0f727,0x25cbe2e2,0x1c09cf5e,0x27b4e6b0,0xc1e908d2,0x25c5af13,0xceea3f4b,0x4008eabb,0x2592b5cf,0x7a61b330,0x4bfcf28b,0x432aa566,0x32b91ae8,0xeb298297,0xfefd644f,0x7b8297c5,0x67b3f020,0x32b29a4b,0xb820ed5e,0xeb70965f,0x3dee5eda,0xdcbc1c3b,0x3fc5d440,0xaa699bb6,0x898eccea,0xf21b33be,0x7405e08,0x1a79847a,0x28ad20e1,0xa7ce1bc5,0xedc6f847,0x5c55cb39,0x6ff6914,0xce6b35a4,0xdc19d101,0xd756460c,0xc397f748,0xedd516c6,0x2bec3cbe,0xe2c013e,0x7074f39d,0x9ae6dda1,0xafbb2ca4,0xc9e8ff76,0x98171bd3,0x353b561d,0x437cf2a0,0xd577c962,0x44623884,0xdff0594c,0xd227bdbb,0x6fd95f68,0x7b8ab45f,0x3822bdfe,0x779f23aa,0xd0eb2be5,0xb1d95da0,0xd4e5f4d,0x14d69010,0xaed64a63,0x84718d34,0x360a438e,0x29fcd3e4,0x13b57d8a,0x86fe0b60,0xdbf2d57a,0xc1ae4d16,0x877358ad,0x28b67aca,0x67bc037,0x3c4e2113,0x2ec385fe,0x132d5a1a,0xc3fba120,0x52ff9437,0xbc993509,0x64430650,0x698521e3,0xcb44b1ca,0x4ce68ac,0xc96b73d9,0x462fe277,0xe882e5f6,0xb6410173,0x2b26f456,0xec8f7094,0x810369e2,0x9cf21e0f,0x1fd824af,0x711d4738,0xceb28249,0xed62bfa9,0xbba2261,0xde3d9d22,0xd7278283,0x8fc3aadc,0xb5fcf74e,0xb2fe5cf9,0xffb15b5e,0xdcbcbe48,0x81a9cddf,0x95466bdb,0x866bce26,0x432ea949,0x9dc66994,0xe8a8bda8,0xfaad85ee,0x8911b9f5,0xa29d6d10,0x73920f8e,0x50b0215a,0x58e49664,0x5502626c,0xbc32a33b,0x71cb2ffb,0xbf1691e0,0x1dc0ba53,0x7836ce2f,0x94b395c5,0x14d22159,0x97fa4f36,0x11aa0e14,0x47a6bc1,0x4992196c,0x9628879c,0xa3fc0f4d,0x825a9f4c,0x34b7390f,0xfe141da6,0x1a7fcefa,0x5a82f9ae,0x171c92c4,0x239e390,0x1d06d681,0x18f25ac7,0xac33179c,0xb3206692,0x9114eada,0x7b7e56f0,0x8d4b7a8a,0x34dd8aa1,0xb9cb3b69,0x85e8e76b,0xe33a477b,0xdac67112,0x3eab5555,0xb2a716a3,0xbe0e6126,0xf8d48e7a,0x5852838,0x206d1b68,0xae2bfe94,0x187d938d,0x4ba4e8dc,0x1bf8d381,0xf92aec4d,0x7b47a6a7,0x1cbdc10b,0x9cfffc56,0x81634188,0x49863e9c,0xf77ade32,0xda5819a3,0x36848602,0xd36a4b44,0x84f42e51,0xed7eada4,0xbcde91f0,0xd138a6bb,0x1c534995,0xe62b361b,0xcd93a7db,0x1f52a43f,0x710a2b9b,0x6a4bd8f6,0x35ed670b,0xc1632beb,0x85a5b471,0x3da47243,0x4131f378,0x8c2bd0dc,0x19dd9ed1,0x3d8fa25c,0xa8e38b01,0xd1ad4937,0x506434f6,0xe18195b2,0x767164d6,0x21eee87d,0xe644e480,0x58b3979c,0xcfcfeb3b,0x885f3671,0x9734f3ea,0xe9805550,0x6d19ccbc,0x92ef6e04,0x809aa4cb,0x9dae1398,0xa90ed5c,0x831a21d5,0x59e0fbf3,0x404b6381,0x79fbb0c5,0x9f05f101,0x71fa16ea,0x8a63c7b9,0xa46462f7,0x95f4c618,0x1b38e955,0xf8de29a8,0x38408341,0x7de35e7d,0xa988d3a2,0x2c33b46e,0x8fb66f9b,0xbb6b404f,0x86618eda,0x7e8f677f,0x9d96b45b,0x6210cbb0,0x7341576b,0x829a3c44,0x8cb29a14,0x679450af,0x7a2ef5e4,0xd7c56d39,0xd83c13ce,0xdce1d9f7,0xb6846a55,0xdf381e5,0xb802dd46,0x8612b64b,0xff22d208,0xbe819c63,0x6dbd6c0a,0x322cf98f,0x2ea68690,0xb822a1aa,0xcd935ef9,0x7f5c91f1,0x2560b2fc,0x9a5b1dcc,0xf26ceff9,0x381e10bd,0x2e5afd37,0x4543b74d,0x961afef7,0x57f682af,0x2ae524a8,0x9b909c94,0xd4ea603,0xdc434e51,0x2bc345d1,0xb9210fd0,0x3af8c345,0xb52b5113,0xa774b5a6,0x58cf185c,0xcb0e7cd9,0x72934be4,0xd37b7976,0x9a9fd3df,0x48ceced3,0x50732c82,0x3412ae2d,0x4fb1a214,0x97398a4b,0x30d3f6d8,0x9baa707c,0x72935408,0x2b7f9de3,0x31adbbfc,0x42bc5e19,0x706e2b40,0x400f5147,0xcfb3870c,0x2b6dc64a,0x72a4c31e,0xe80f67ee,0xa7ede74d,0x5c23af9b,0x82e499fa,0x6827cf72,0xf337ab36,0x66b4fc45,0x8b13f083,0x39da2754,0xee6024bc,0x42f2ed16,0x16e478c1,0x29b0da97,0xb1d80e06,0x8f0e3594,0x6322b39a,0x744ca80d,0xc3ddfdce,0x39f9c898,0xc0240885,0xb7d9f7f1,0xc703db5f,0x83051506,0x4662bcbb,0x50d4d19f,0x1044926f,0x2e19879,0xc7824e5e,0x59a9e570,0x1bb290bc,0x5b42a5c4,0x690a4153,0x86cf7cdd,0x94da98ef,0xa31cb573,0x73b1c3cb,0xb12314e0,0xe5a2d6c6,0x61d6ba8c,0x843b73de,0x562a97bd,0x72435a19,0xb527915c,0x612f4b6,0xd876dbe2,0x707e63a4,0x185484e1,0xc575df11,0x7b406efb,0x1ed0a534,0x34e6bf6b,0x7f2153df,0x142e0dc3,0x7397224c,0x41b77fa4,0xcec6b9b7,0xb5ef4c33,0xe2504942,0xca62927a,0xfdffb0,0xc4810400,0x9f4b77be,0x3af76f4a,0x779b4f2d,0x1f3766e3,0x51d83328,0x69f06b57,0x8e08ec82,0x5e4327c8,0x8cf5cae1,0x36b4a8a9,0x47bbcf2e,0xe6401328,0x3e5f6b8,0x3d29cd2b,0xac5df515,0xbd1b39c3,0xb8e2ae18,0x2d3bd401 # Unused Cars
		]
		VehiclePool._vehicles = [Vehicle(h) for h in hashes]
		return VehiclePool._vehicles
	
	@property
	def typed_vehicles(self):
		if VehiclePool._typed_vehicles is not None: return VehiclePool._typed_vehicles
		VehiclePool._typed_vehicles = {}
		for v in self.vehicles:
			if not v.type in VehiclePool._typed_vehicles: VehiclePool._typed_vehicles[v.type] = []
			VehiclePool._typed_vehicles[v.type].append(v)
		return VehiclePool._typed_vehicles
	
	def random(self, type_mask = None):
		from random import choice
		if type_mask is not None:
			valid_mask = [m for m in type_mask if m in self.typed_vehicles or m is 'NONE']
			if len(valid_mask):
				vt = choice(valid_mask)
				if vt == 'NONE': return NoVehicle()
				# api.info('# veh', len(self.typed_vehicles[vt]))
				# api.info(','.join([str(v.hash) for v in self.typed_vehicles[vt]]))
				return choice(self.typed_vehicles[vt])
		return choice(self.vehicles)

	@staticmethod
	def get():
		if VehiclePool._self is None: VehiclePool._self = VehiclePool()
		return VehiclePool._self

def random_vehicle(type_mask=None):
	return VehiclePool.get().random(type_mask)

class DrivingStyle:
	Normal = 786603
	IgnoreLights = 2883621
	SometimesOvertakeTraffic = 5
	Rushed = 1074528293
	AvoidTraffic = 786468
	AvoidTrafficExtremely = 6

def bad_stuff():
	player = h.Player.id()
	ped = h.Player.ped_id()
	if not ped.does_exist: return True
	if not player.is_control_on: return True
	if ped.is_dead: return True
	if player.is_being_arrested(True): return True
	return False

class BaseScenario:
	def __init__(self, **params):
		from random import choice, randint, uniform
		vehicle_mask = params.get('vehicle_mask', DEFAULT_VEHICLE_MASK)
		self.vehicle = params.get('vehicle', random_vehicle(vehicle_mask))
		weather_list = params.get('weather_list', DEFAULT_WEATHER_LIST)
		self.weather = params.get('weather', choice(weather_list))
		self.seed    = int(params.get('seed', randint(0,1000000)))
		self.x       = float(params.get('x', uniform(-2500, 2500)))
		self.y       = float(params.get('y', uniform(-2000, 6000)))
		self.timeout = int(params.get('timeout', 30))
		self.safety_timout = int(params.get('safety_timout', 1))
		self.time    = int(params.get('time', randint(0,24*60)))
		self.running = False
	
	def start(self):
		api.info("Starting new scenario", self.params())
		while bad_stuff(): h.wait(0)
		# Basic map setup
		h.Gameplay.set_random_seed(self.seed)
		while not h.Pathfind.load_all_path_nodes(): h.wait(0)
		api.info("Starting")
		
		# Start the timeout
		self.start_time = time()
		self.last_safety = time()
		
		# Setup the weather
		h.Gameplay.set_weather_type_now_persist(self.weather)
		
		# Set the time
		h.Time.set_clock_time(self.time // 60, self.time % 60, 0)
		
		# Disable the control
		h.Controls.disable_control_action(0, h.eControl.control_next_camera, True)
		h.Controls.disable_control_action(0, h.eControl.control_look_left_right, True)
		h.Controls.disable_control_action(0, h.eControl.control_look_up_down, True)
		h.Controls.disable_control_action(0, h.eControl.control_look_up_only, True)
		h.Controls.disable_control_action(0, h.eControl.control_look_down_only, True)
		h.Controls.disable_control_action(0, h.eControl.control_look_left_only, True)
		h.Controls.disable_control_action(0, h.eControl.control_look_right_only, True)
	
	def setup_cam(self):
		h.Cam.destroy_all_cams(True)
		h.Cam.render_script_cams(False, False, 0, False, False)
		if h.Cam.get_follow_ped_view_mode() != 4:
			h.Cam.set_follow_ped_view_mode(4)
		if h.Cam.get_follow_vehicle_view_mode() != 4:
			h.Cam.set_follow_vehicle_view_mode(4)

		# First person CAM
		#self.cam = h.Cam.create_camera(h.Hash(0xA70102CA), True)#h.Cam.create_cam("DEFAULT_SCRIPTED_CAMERA", True)
		#api.info(self.cam.fov)
		#self.cam.fov = 60.
		#api.info(self.cam.fov)
		#self.cam.set_active(True)
		#o = self.ped.get_offset_from_given_world_coords(x.x, x.y, x.z)
		#self.cam.attach_to_entity(self.ped, o.x, o.y, o.z, True)
		#api.info(o.x, o.y, o.z)
		
		#self.update_cam()
		#h.Cam.render_script_cams(True, False, self.cam, True, True)
	
	def update_cam(self):
		#self.cam.fov = 60.
		if h.Cam.get_follow_ped_view_mode() != 4:
			h.Cam.set_follow_ped_view_mode(4)
		if h.Cam.get_follow_vehicle_view_mode() != 4:
			h.Cam.set_follow_vehicle_view_mode(4)
		#h.Cam.set_gameplay_relative_pitch(0., 0.)
		#h.Cam.set_gameplay_relative_heading(0.)
		
		#x = h.Cam.get_gameplay_coord()
		#o = self.ped.get_offset_from_given_world_coords(x.x, x.y, x.z)
		#api.info(o.x, o.y, o.z)
		#r = self.ped.get_rotation(1)
		#r = h.Cam.get_gameplay_rot(1)
		# self.cam.set_rot(r.x, r.y, r.z, 1)
		#api.info('fov ', self.cam.fov, h.Cam.get_gameplay_fov())
	
	def stop(self):
		h.Controls.enable_control_action(0, h.eControl.control_next_camera, True)
		h.Controls.enable_control_action(0, h.eControl.control_look_left_right, True)
		h.Controls.enable_control_action(0, h.eControl.control_look_up_down, True)
		h.Controls.enable_control_action(0, h.eControl.control_look_up_only, True)
		h.Controls.enable_control_action(0, h.eControl.control_look_down_only, True)
		h.Controls.enable_control_action(0, h.eControl.control_look_left_only, True)
		h.Controls.enable_control_action(0, h.eControl.control_look_right_only, True)
		
		h.Cam.destroy_all_cams(True)
		h.Cam.render_script_cams(False, False, 0, False, False)
	
	def safety_check(self):
		player = h.Player.id()
		player.set_everyone_ignore_player(True)
		player.set_dispatch_cops_for_player(False)
		player.set_can_be_hassled_by_gangs(False)
		player.set_police_ignore_player(True)
		player.clear_wanted_level()
		player.remove_helmet(1)
		player.invincible = True
		ped = h.Player.ped_id()
		ped.set_helmet(False)
		
	
	def update(self):
		t0 = time()
		if t0 - self.start_time > self.timeout:
			self.running = False
			return False
		if t0 - self.last_safety > self.safety_timout:
			self.last_safety = t0
			self.safety_check()
		
		self.update_cam()
		self.running = not bad_stuff()
		return self.running
	
	def is_running(self):
		return self.running
	
	def params(self):
		return dict(weather=self.weather, vehicle_type=self.vehicle.type, seed=self.seed, x=self.x, y=self.y, time=self.time, vehicle=self.vehicle)
		

class WalkingScenario(BaseScenario):
	def __init__(self, **params):
		super().__init__(**params)

	def start(self):
		super().start()
		# Find a spawn location
		ped_pos = h.Pathfind.save_coord_for_ped(self.x, self.y, 0, False, 0)
		if ped_pos is None:
			pos, heading = h.Pathfind.closest_vehicle_node_with_heading(self.x, self.y, 0, 0, 0, 0)
			ped_pos = h.Pathfind.save_coord_for_ped(pos.x, pos.y, 0, False, 0)
			if ped_pos is None:
				ped_pos = pos
		
		# Teleport player
		ped = h.Player.ped_id()
		while not ped.does_exist():
			h.wait(0)
			ped = h.Player.ped_id()
		ped.set_coords(ped_pos.x, ped_pos.y, ped_pos.z, 0, 0, 0, 1)
		ped.heading = heading
		for it in range(45): h.wait(0)
		ped.set_keep_task(False)
		h.Ai.clear_ped_tasks(ped)
		h.Ai.task_wander_in_area(ped, pos.x, pos.y, pos.z, 15, 0.01, 1)
		ped.set_keep_task(True)
		self.safety_check()
		
		self.setup_cam()
		
		# Reset the start time
		self.start_time = time()

	def update(self):
		rval = super().update()
		if h.Cam.get_follow_ped_view_mode() != 4:
			h.Cam.set_follow_ped_view_mode(4)
		h.Cam.set_gameplay_relative_pitch(0., 0.)
		h.Cam.set_gameplay_relative_heading(0.)
		return rval
	
	def stop(self):
		super().stop()
		h.Ai.clear_ped_tasks(h.Player.ped_id())
		
		

class DrivingScenario(BaseScenario):
	def __init__(self, **params):
		from random import choice, randint, uniform
		super().__init__(**params)
		self.driving_style = int(params.get('driving_style', DrivingStyle.Normal))
		self.max_speed = float(params.get('max_speed', uniform(15, DEFAULT_MAX_SPEED[self.vehicle.type])))
		self.last_control = None

	def _remove_vehicles_in_radius(self, x, y, z, r):
		# Get all vehicles and remove them (Entity.remove doesn't work for some reason)
		for c in h.Vehicle.list():
			p = c.get_coords(True)
			if h.Gameplay.get_distance_between_coords(x, y, z, p.x, p.y, p.z, 1) < r:
				api.info(h.Gameplay.get_distance_between_coords(x, y, z, p.x, p.y, p.z, 1))
				h.Entity.delete(c)
	def _remove_all_vehicles(self):
		# Get all vehicles and remove them (Entity.remove doesn't work for some reason)
		for c in h.Vehicle.list():
			h.Vehicle.delete(c)
	
	def start(self):
		super().start()
		# Find a spawn location
		pos, heading = h.Pathfind.closest_vehicle_node_with_heading(self.x, self.y, 0, 0, 0, 0)
		
		# Remove nearby vehicles (3m radius)
		# self._remove_vehicles_in_radius(pos.x, pos.y, pos.z, 3)
		self._remove_all_vehicles()
		
		# Teleport player
		ped = h.Player.ped_id()
		while not ped.does_exist():
			h.wait(0)
			ped = h.Player.ped_id()
		ped.set_coords(pos.x, pos.y, pos.z, 0, 0, 0, 1)
		ped.heading = heading
		h.wait(500)
		# Create the vehicle
		h.Streaming.request_model(self.vehicle.hash)
		while not h.Streaming.has_model_loaded(self.vehicle.hash):
			h.wait(100)
		
		for it in range(10):
			v = h.Vehicle.create_vehicle(self.vehicle.hash, pos.x, pos.y, pos.z, heading, False, False)
			h.wait(100)
			if v.does_exist(): break
		h.Streaming.set_model_as_no_longer_needed(self.vehicle.hash)
		v.set_on_ground_properly()
		h.wait(500)
		ped.set_into_vehicle(v, -1)
		
		# TODO: Setup the camera
#		if h.Cam.get_follow_ped_view_mode() != 4:
#			h.Cam.set_follow_ped_view_mode(4)
#		if h.Cam.get_follow_vehicle_view_mode() != 4:
#			h.Cam.set_follow_vehicle_view_mode(4)
#		h.Cam.set_gameplay_relative_pitch(0., 0.)
#		h.Cam.set_gameplay_relative_heading(0.)
		h.wait(100)
		
		# Setup the autopilot
		ped.set_driver_ability(100)
		ped.set_driver_aggressiveness(50)
		#ped.set_keep_task(False)
		h.Ai.clear_ped_tasks(ped)
		h.Ai.task_vehicle_drive_wander(ped, v, self.max_speed, self.driving_style)
		#ped.set_keep_task(True)
		
		# Make the vehicle invincible
		ped.set_config_flag(32, False)
		v.tyres_can_burst = False
		v.set_wheels_can_break(False)
		v.set_has_strong_axles(True)
		v.set_can_be_visibly_damaged(False)
		v.set_invincible(True)
		v.set_proofs(1,1,1,1,1,1,1,1)
		
		self.v = v
		self.ped = ped
		
		self.safety_check()
		h.wait(500)

		self.setup_cam()
		
		# Reset the start time
		self.start_time = time()
		self.last_control = self.v.control
		
	def update(self):
		rval = super().update()
		if not self.v.does_exist():
			api.warn("Bad vehicle", self.vehicle.hash, h.Vehicle.get_display_name_from_model(self.vehicle.hash))
		self.last_control = self.v.control
		return rval and self.v.does_exist()
	
	def stop(self):
		super().stop()
		h.Ai.clear_ped_tasks(h.Player.ped_id())

	def params(self):
		p = super().params()
		p.update( dict(max_speed = self.max_speed, driving_style=self.driving_style, vehicle_hash=self.vehicle.hash, control=self.last_control) )
		return p

class Scenario:
	def __init__(self, **params):
		self.base = BaseScenario(**params)
		params.update(self.base.params())
		if self.base.vehicle.type == 'NONE':
			self.base = WalkingScenario(**params)
		else:
			self.base = DrivingScenario(**params)
		self.start = self.base.start
		self.stop = self.base.stop
		self.update = self.base.update
		self.params = self.base.params
		self.is_running = self.base.is_running
	

class PyPilot(api.BaseController):
	scenario = None
	first_frame = True
	last_capture_time = 0
	scenario_params = {'driving_style': DrivingStyle.IgnoreLights, 'vehicle_mask':['NONE', 'CAR','BIKE', 'QUADBIKE', 'BICYCLE'], 'timeout':30} # ['BIKE', 'QUADBIKE', 'BICYCLE']
	fps = 6
	def ph_loop_no_except(self):
		try:
			self.ph_loop()
		except Exception as e:
			import traceback, io
			f = io.StringIO()
			traceback.print_exc(file=f)
			api.warn('CB failed', e)
			api.warn(f.getvalue())
	
	def ph_loop(self):
		if self.running:
			self.scenario = Scenario(**self.scenario_params)
			self.scenario.start()
			self.first_frame = True
			self.last_capture_time = 0
			try:
				while self.running:
					h.wait(0)
					if not self.scenario.update():
						break
			finally:
				self.scenario.stop()
				self.scenario = None
	
	def key_down(self, key, special):
		if key == 0x79: # F10
			self.running = not self.running
		return False
	
	def game_state(self):
		if self.scenario is not None:
			return str(self.scenario.params())
		return "{}"
	
	def __init__(self, *args, **kwargs):
		super().__init__(*args, **kwargs)
		self.running = False
		h.set_main_cb(self.ph_loop_no_except)
	
	# def start_draw(self, *args):
		# self.cnt += 1
		# return api.DrawType.DEFAULT
	
	def record_frame(self, frame_id):
		if self.scenario is not None and self.scenario.is_running():
			if time() - self.last_capture_time < 1./self.fps:
				return api.RecordingType.NONE
			self.last_capture_time = time()
			if self.first_frame:
				self.first_frame = False
				return api.RecordingType.DRAW_FIRST
			return api.RecordingType.DRAW
		return api.RecordingType.NONE
			
		# self.cnt = 0
		# api.info('start_frame', args)

	# def start_frame(self, *args, **kwargs):
#		pass

	# def end_frame(self, *args, **kwargs):
		# api.info('end_frame', args, self.cnt)
#		pass
	
	def unload(self):
		self.running = False
		if h.main_cb() == self.ph_loop:
			h.set_main_cb(None)
