#ifndef __ABSTRACTWEATHEREFFECT_H__
#define __ABSTRACTWEATHEREFFECT_H__

namespace pan {
	class SkyColourSystem;
	class CloudsSystem;

	class AbstractWeatherEffect {
	public:
		virtual ~AbstractWeatherEffect();

		virtual void effect() = 0;
		virtual void create(CloudsSystem& cloudSystem, SkyColourSystem& skyColourSystem) = 0;
		virtual void destroy() = 0;

		bool isCreated();

	protected:
		AbstractWeatherEffect();
		void setIsCreated(bool created);		

	private:
		bool created;

	};
}

#endif
