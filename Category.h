#pragma once

namespace Category
{
	enum Type
	{
		None				= 0,			// 000000000
		SceneAirLayer		= 1 << 0,		// 000000001
		PlayerAircraft		= 1 << 1,		// 000000010
		AlliedAircraft		= 1 << 2,		// 000000100
		EnemyAircraft		= 1 << 3,		// 000001000
		Pickup				= 1 << 4,
		AlliedProjectile	= 1 << 5,
		EnemyProjectile		= 1 << 6,
		ParticleSystem		= 1 << 7,
		SoundEffect			= 1 << 8,
		Frog				= 1 << 9,
		Tractor				= 1 << 10,
		Car1				= 1 << 11,
		Car2				= 1 << 12,
		Car3				= 1 << 13,
		Truck				= 1 << 14,
		Cherry				= 1 << 15,

		Actor = Frog | Tractor | Car1 | Car2 | Car3 | Tractor | Truck | Cherry,
		Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
		Projectile = AlliedProjectile | EnemyProjectile,
	};
}