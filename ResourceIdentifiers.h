#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

enum class EffectID
{
	AlliedGunfire,
	EnemyGunfire,
	Explosion1,
	Explosion2,
	LaunchMissile,
	CollectPickup,
	Button,
};
enum class MusicID
{
	MenuTheme,
	MissionTheme,
};

namespace Textures
{
	enum class TextureID
	{
		Eagle,
		Raptor,
		Avenger,
		Bullet,
		Missile,
		Desert,
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,

		Entities,
		Jungle,
		TitleScreen,
		Buttons,
		Explosion,
		Particle,
		FinishLine,

		Frog,
		Car1,
		Car2,
		Car3,
		Tractor,
		Truck,
		Background,
	};
}


namespace Fonts 
{
	enum class FontID
	{
		Main,
	};
}

enum class ShaderID
{
	BrightnessPass,
	DownSamplePass,
	GaussianBlurPass,
	AddPass,
};



// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder_t =  ResourceHolder<sf::Texture, Textures::TextureID>;
using FontHolder_t = ResourceHolder<sf::Font, Fonts::FontID>;
using ShaderHolder_t = ResourceHolder<sf::Shader, ShaderID>;
using SoundBufferHolder_t = ResourceHolder<sf::SoundBuffer, EffectID>;