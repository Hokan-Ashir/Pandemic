#ifndef __ABSTRACTWEATHEREFFECT_H__
#define __ABSTRACTWEATHEREFFECT_H__

namespace pan {
	class SkyColourSystem;
	class CloudsSystem;

	class AbstractWeatherEffect {
	public:
		virtual ~AbstractWeatherEffect();

		virtual void effect() = 0;
		virtual void create(CloudsSystem& cloudSystem, SkyColourSystem& skyColourSystem) final;
		virtual void destroy() final;

		bool isCreated();

	protected:
		AbstractWeatherEffect();
		void setIsCreated(bool created);
		virtual void createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) = 0;
		virtual void destroyActions() = 0;

	private:
		bool created;

	};
}

#endif
