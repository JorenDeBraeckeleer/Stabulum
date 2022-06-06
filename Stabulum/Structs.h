#pragma once

#include <SDL_stdinc.h>

struct IVec2
{
	int x, y;

	IVec2 operator+(IVec2 vec) const
	{
		return IVec2(this->x + vec.x, this->y + vec.y);
	}

	IVec2 operator-(IVec2 vec) const
	{
		return IVec2(this->x - vec.x, this->y - vec.y);
	}

	IVec2 operator*(int nr) const
	{
		return IVec2(this->x * nr, this->y * nr);
	}

	IVec2 operator/(int nr) const
	{
		return IVec2(this->x / nr, this->y / nr);
	}

	IVec2 operator*(float nr) const
	{
		return IVec2(int(this->x * nr), int(this->y * nr));
	}

	IVec2 operator/(float nr) const
	{
		return IVec2(int(this->x / nr), int(this->y / nr));
	}

	IVec2 operator*(IVec2 vec) const
	{
		return IVec2(this->x * vec.x, this->y * vec.y);
	}

	IVec2 operator/(IVec2 vec) const
	{
		return IVec2(this->x / vec.x, this->y / vec.y);
	}
};

struct IVec3
{
	int x, y, z;

	IVec3 operator+(IVec3 vec) const
	{
		return IVec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}

	IVec3 operator-(IVec3 vec) const
	{
		return IVec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	IVec3 operator*(int nr) const
	{
		return IVec3(this->x * nr, this->y * nr, this->z * nr);
	}

	IVec3 operator/(int nr) const
	{
		return IVec3(this->x / nr, this->y / nr, this->z / nr);
	}

	IVec3 operator*(float nr) const
	{
		return IVec3(int(this->x * nr), int(this->y * nr), int(this->z * nr));
	}

	IVec3 operator/(float nr) const
	{
		return IVec3(int(this->x / nr), int(this->y / nr), int(this->z / nr));
	}

	IVec3 operator*(IVec3 vec) const
	{
		return IVec3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	}

	IVec3 operator/(IVec3 vec) const
	{
		return IVec3(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	}
};

struct FVec2
{
	float x, y;

	FVec2 operator+(FVec2 vec) const
	{
		return FVec2(this->x + vec.x, this->y + vec.y);
	}

	FVec2 operator-(FVec2 vec) const
	{
		return FVec2(this->x - vec.x, this->y - vec.y);
	}

	FVec2 operator*(int nr) const
	{
		return FVec2(this->x * nr, this->y * nr);
	}

	FVec2 operator/(int nr) const
	{
		return FVec2(this->x / nr, this->y / nr);
	}

	FVec2 operator*(float nr) const
	{
		return FVec2(this->x * nr, this->y * nr);
	}

	FVec2 operator/(float nr) const
	{
		return FVec2(this->x / nr, this->y / nr);
	}

	FVec2 operator*(FVec2 vec) const
	{
		return FVec2(this->x * vec.x, this->y * vec.y);
	}

	FVec2 operator/(FVec2 vec) const
	{
		return FVec2(this->x / vec.x, this->y / vec.y);
	}
};

struct FVec3
{
	float x, y, z;

	FVec3 operator+(FVec3 vec) const
	{
		return FVec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}

	FVec3 operator-(FVec3 vec) const
	{
		return FVec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	FVec3 operator*(int nr) const
	{
		return FVec3(this->x * nr, this->y * nr, this->z * nr);
	}

	FVec3 operator/(int nr) const
	{
		return FVec3(this->x / nr, this->y / nr, this->z / nr);
	}

	FVec3 operator*(float nr) const
	{
		return FVec3(this->x * nr, this->y * nr, this->z * nr);
	}

	FVec3 operator/(float nr) const
	{
		return FVec3(this->x / nr, this->y / nr, this->z / nr);
	}

	FVec3 operator*(FVec3 vec) const
	{
		return FVec3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	}

	FVec3 operator/(FVec3 vec) const
	{
		return FVec3(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	}
};

struct RGBColor
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
};

namespace Convert
{
	inline glm::vec2 VEC2toGLM2(const FVec2& vec)
	{
		return glm::vec2{ vec.x, vec.y };
	}

	inline glm::vec3 VEC3toGLM3(const FVec3& vec)
	{
		return glm::vec3{ vec.x, vec.y, vec.z };
	}

	inline FVec2 GLM2toVEC2(const glm::vec2& vec)
	{
		return FVec2{ vec.x, vec.y };
	}

	inline FVec3 GLM3toVEC3(const glm::vec3& vec)
	{
		return FVec3{ vec.x, vec.y, vec.z };
	}

	inline SDL_Color RGBtoSDL(const RGBColor& color)
	{
		return SDL_Color{ color.r, color.g, color.b };
	}
}