#ifndef _GEN_RAND_DATA_
#define _GEN_RAND_DATA_


#include <random>
#include <stdexcept>
#include <cstdint>


namespace gen_rand_data
{
	template<typename T>
	bool checkRange(const T& min, const T& max)
	{
		return min <= max;
	}




	/////////////////////// INTEGER TYPES ///////////////////////

	template<typename T>
	class Generator
	{
	private:
		std::mt19937_64 gen{ std::random_device{}() };
		std::uniform_int_distribution<T> dist;

	public:
		Generator(const T& min, const T& max) : dist{ min, max } {}

		T getMin() noexcept(noexcept(dist.min())) { return dist.min(); }
		T getMax() noexcept(noexcept(dist.max())) { return dist.max(); }

		void setRange(const T& min, const T& max);

		T operator()() { return dist(gen); }
	};

	template<typename T>
	inline void Generator<T>::setRange(const T& min, const T& max)
	{
		if (!checkRange(min, max))
		{
			throw std::logic_error{ "min_range > max_range" };
		}

		dist = std::uniform_int_distribution<T>(min, max);
	}




	/////////////////////// DOUBLE TYPES ///////////////////////

	template<>
	class Generator<float>
	{
	private:
		std::mt19937_64 gen{ std::random_device{}() };
		std::uniform_real_distribution<float> dist;

	public:
		Generator(const float& min, const float& max) : dist{ min, max } {}

		float getMin() noexcept(noexcept(dist.min())) { return dist.min(); }
		float getMax() noexcept(noexcept(dist.max())) { return dist.max(); }

		void setRange(const float& min, const float& max);

		float operator()() { return dist(gen); }
	};

	inline void Generator<float>::setRange(const float &min, const float &max)
    {
		if (!checkRange(min, max))
		{
			throw std::logic_error{ "min_range > max_range" };
		}

		dist = std::uniform_real_distribution<float>(min, max);
	}



	template<>
	class Generator<double>
	{
	private:
		std::mt19937_64 gen{ std::random_device{}() };
		std::uniform_real_distribution<double> dist;

	public:
		Generator(const double& min, const double& max) : dist{ min, max } {}

		double getMin() noexcept(noexcept(dist.min())) { return dist.min(); }
		double getMax() noexcept(noexcept(dist.max())) { return dist.max(); }

		void setRange(const double& min, const double& max);

		double operator()() { return dist(gen); }
	};

	inline void Generator<double>::setRange(const double& min, const double& max)
    {
		if (!checkRange(min, max))
		{
			throw std::logic_error{ "min_range > max_range" };
		}

		dist = std::uniform_real_distribution<double>(min, max);
	}



	template<>
	class Generator<long double>
	{
	private:
		std::mt19937_64 gen{ std::random_device{}() };
		std::uniform_real_distribution<long double> dist;

	public:
		Generator(const long double& min, const long double& max) : dist{ min, max } {}

		long double getMin() noexcept(noexcept(dist.min())) { return dist.min(); }
		long double getMax() noexcept(noexcept(dist.max())) { return dist.max(); }

		void setRange(const long double& min, const long double& max);

		long double operator()() { return dist(gen); }
	};


	inline void Generator<long double>::setRange(const long double& min, const long double& max)
    {
		if (!checkRange(min, max))
		{
			throw std::logic_error{ "min_range > max_range" };
		}

		dist = std::uniform_real_distribution<long double>(min, max);
	}




	/////////////////////// CHAR TYPES ///////////////////////

	template<>
	class Generator <int8_t>
	{
	private:
		int8_t m_min_range;
		int8_t m_max_range;

	public:
		Generator(const int8_t& min, const int8_t& max) : m_min_range{ min }, m_max_range{ max }
		{
			if (!checkRange(min, max))
			{
				throw std::logic_error{ "min_range > max_range" };
			}
		}

		int8_t getMin() const noexcept { return m_min_range; }
		int8_t getMax() const noexcept { return m_max_range; }

		void setRange(const int8_t& min, const int8_t& max);

		int8_t operator()() { return m_min_range + rand() % (m_max_range - m_min_range + 1); }
	};

    inline void Generator<int8_t>::setRange(const int8_t& min, const int8_t& max)
    {
		if (!checkRange(min, max))
		{
			throw std::logic_error{ "minRange > maxRange" };
		}

		m_min_range = min;
		m_max_range = max;
	}



	template<>
	class Generator <uint8_t>
	{
	private:
		uint8_t m_min_range;
		uint8_t m_max_range;

	public:
		Generator(const uint8_t& min, const uint8_t& max) : m_min_range{ min }, m_max_range{ max }
		{
			if (!checkRange(min, max))
			{
				throw std::logic_error{ "minRange > maxRange" };
			}
		}

		uint8_t getMin() const noexcept { return m_min_range; }
		uint8_t getMax() const noexcept { return m_max_range; }

		void setRange(const uint8_t& min, const uint8_t& max);

		uint8_t operator()() { return m_min_range + rand() % (m_max_range - m_min_range + 1); }
	};

    inline void Generator<uint8_t>::setRange(const uint8_t& min, const uint8_t& max)
    {
		if (!checkRange(min, max))
		{
			throw std::logic_error{ "minRange > maxRange" };
		}

		m_min_range = min;
		m_max_range = max;
	}


} // namespace gen_rand_data

#endif // _GEN_RAND_DATA_