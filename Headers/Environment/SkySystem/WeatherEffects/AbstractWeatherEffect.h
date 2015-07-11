#ifndef __ABSTRACTWEATHEREFFECT_H__
#define __ABSTRACTWEATHEREFFECT_H__

namespace pan {
	class SkyColourSystem;
	class CloudsSystem;

	/**
	 * Class, that describes weather effectm that can be manually created and destroyed
	 */
	class AbstractWeatherEffect {
	public:
		virtual ~AbstractWeatherEffect();

		/**
		 * Public, non-overriable wrapper-method around createActions() method. <p>
		 * This method set "created" flag after createActions() method call
		 *
		 * \param CloudSystem& reference to clouds system
		 * \param SkyColourSystem& reference to sky colour system
		 */
		virtual void create(CloudsSystem& cloudSystem, SkyColourSystem& skyColourSystem) final;

		/**
		 * Public, non-overriable wrapper-method around destroyActions() method. <p>
		 * This method unset "created" flag after destroyActions() method call
		 */
		virtual void destroy() final;

		bool isCreated();

	protected:
		AbstractWeatherEffect();
		/**
		 * \param bool is this weather effect created
		 */
		void setIsCreated(bool created);

		/**
		 * Actions, performing during creating of weather effect
		 * 
		 * \param CloudSystem& reference to clouds system
		 * \param SkyColourSystem& reference to sky colour system
		 */
		virtual void createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) = 0;

		/**
		 * Actions, performing during destruction of weather effect
		 */
		virtual void destroyActions() = 0;

	private:
		bool created;

	};
}

#endif
