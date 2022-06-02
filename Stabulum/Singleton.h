#pragma once

template <typename T>
class Singleton
{
public:
	virtual ~Singleton() = default;
	Singleton(const Singleton& other) = delete;
	Singleton(Singleton&& other) = delete;
	Singleton& operator=(const Singleton& other) = delete;
	Singleton& operator=(Singleton&& other) = delete;

	static T& GetInstance()
	{
		static T instance{};
		return instance;
	}

protected:
	Singleton() = default;
};