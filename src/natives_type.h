// This file is auto-generated, do NOT edit!
#include "scripthook/types.h"
struct Py_Void{
	DWORD id=0;
	Py_Void(int i): id(i){}
	Py_Void(DWORD i): id(i){}
	Py_Void&operator=(int i) { id = i; return *this; }
	Py_Void&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Any{
	DWORD id=0;
	Py_Any(int i): id(i){}
	Py_Any(DWORD i): id(i){}
	Py_Any&operator=(int i) { id = i; return *this; }
	Py_Any&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_uint{
	DWORD id=0;
	Py_uint(int i): id(i){}
	Py_uint(DWORD i): id(i){}
	Py_uint&operator=(int i) { id = i; return *this; }
	Py_uint&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Hash{
	DWORD id=0;
	Py_Hash(int i): id(i){}
	Py_Hash(DWORD i): id(i){}
	Py_Hash&operator=(int i) { id = i; return *this; }
	Py_Hash&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Entity:Py_Any{

	Py_Entity(int i): Py_Any(i){}
	Py_Entity(DWORD i): Py_Any(i){}
	Py_Entity&operator=(int i) { id = i; return *this; }
	Py_Entity&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Player:Py_Any{

	Py_Player(int i): Py_Any(i){}
	Py_Player(DWORD i): Py_Any(i){}
	Py_Player&operator=(int i) { id = i; return *this; }
	Py_Player&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Ped:Py_Entity{

	Py_Ped(int i): Py_Entity(i){}
	Py_Ped(DWORD i): Py_Entity(i){}
	Py_Ped&operator=(int i) { id = i; return *this; }
	Py_Ped&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Vehicle:Py_Entity{

	Py_Vehicle(int i): Py_Entity(i){}
	Py_Vehicle(DWORD i): Py_Entity(i){}
	Py_Vehicle&operator=(int i) { id = i; return *this; }
	Py_Vehicle&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Cam:Py_Any{

	Py_Cam(int i): Py_Any(i){}
	Py_Cam(DWORD i): Py_Any(i){}
	Py_Cam&operator=(int i) { id = i; return *this; }
	Py_Cam&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Object:Py_Entity{

	Py_Object(int i): Py_Entity(i){}
	Py_Object(DWORD i): Py_Entity(i){}
	Py_Object&operator=(int i) { id = i; return *this; }
	Py_Object&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Pickup:Py_Object{

	Py_Pickup(int i): Py_Object(i){}
	Py_Pickup(DWORD i): Py_Object(i){}
	Py_Pickup&operator=(int i) { id = i; return *this; }
	Py_Pickup&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Blip:Py_Any{

	Py_Blip(int i): Py_Any(i){}
	Py_Blip(DWORD i): Py_Any(i){}
	Py_Blip&operator=(int i) { id = i; return *this; }
	Py_Blip&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_ScrHandle{
	int id=0;
	Py_ScrHandle(int i): id(i){}
	Py_ScrHandle(DWORD i): id(i){}
	Py_ScrHandle&operator=(int i) { id = i; return *this; }
	Py_ScrHandle&operator=(DWORD i) { id = i; return *this; }
	operator int() { return id; }
	operator DWORD() { return id; }
};
struct Py_Ai{};
struct Py_Gameplay{};
struct Py_Audio{};
struct Py_Cutscene{};
struct Py_Interior{};
struct Py_Weapon{};
struct Py_Itemset{};
struct Py_Streaming{};
struct Py_Script{};
struct Py_Ui{};
struct Py_Graphics{};
struct Py_Stats{};
struct Py_Brain{};
struct Py_Mobile{};
struct Py_App{};
struct Py_Time{};
struct Py_Pathfind{};
struct Py_Controls{};
struct Py_Datafile{};
struct Py_Fire{};
struct Py_Decisionevent{};
struct Py_Zone{};
struct Py_Rope{};
struct Py_Water{};
struct Py_Worldprobe{};
struct Py_Network{};
struct Py_Networkcash{};
struct Py_Dlc1{};
struct Py_Dlc2{};
struct Py_System{};
struct Py_Decorator{};
struct Py_Socialclub{};
struct Py_Unk{};
struct Py_Unk1{};
struct Py_Unk2{};
struct Py_Unk3{};
