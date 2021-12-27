#pragma once
#include <cmath>
#include <DirectXMath.h>

namespace Aurora
{
	constexpr float PI = 3.14159265f;
	constexpr double PI_D = 3.1415926535897932;

	template<typename T>
	constexpr auto sq(const T& x)
	{
		return x * x;
	}

	template<typename T>
	T wrap_angle(T theta)
	{
		const T modded = fmod(theta, (T)2.0 * (T)PI_D);
		return (modded > (T)PI_D) ? (modded - (T)2.0) * (T)PI_D : modded;
	}

	template<typename T>
	constexpr T interpolate(const T& src, const T& dst, float alpha)
	{
		return src + (dst - src) * alpha;
	}

	template<typename T>
	constexpr T to_rad(T deg)
	{
		return deg * PI / (T)180.0;
	}

	
	/*DirectX::XMFLOAT2 operator-(DirectX::XMFLOAT2 first, DirectX::XMFLOAT2 second)
	{
		DirectX::XMFLOAT2 res;
		res.x = first.x - second.x;
		res.y = first.y - second.y;
		return res;
	}

	DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 first, DirectX::XMFLOAT3 second)
	{
		DirectX::XMFLOAT3 res;
		res.x = first.x - second.x;
		res.y = first.y - second.y;
		res.z = first.z - second.z;
		return res;
	}

	DirectX::XMFLOAT4 operator-(DirectX::XMFLOAT4 first, DirectX::XMFLOAT4 second)
	{
		DirectX::XMFLOAT4 res;
		res.x = first.x - second.x;
		res.y = first.y - second.y;
		res.z = first.z - second.z;
		res.w = first.w - second.w;
		return res;
	}
	
	DirectX::XMFLOAT2 operator+=(DirectX::XMFLOAT2 lhs,const DirectX::XMFLOAT2 rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	DirectX::XMFLOAT3 operator+=(DirectX::XMFLOAT3 lhs,const DirectX::XMFLOAT3 rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		return lhs;
	}

	DirectX::XMFLOAT4 operator+=(DirectX::XMFLOAT4 lhs,const DirectX::XMFLOAT4 rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		lhs.w += rhs.w;
		return lhs;
	}*/

	
}