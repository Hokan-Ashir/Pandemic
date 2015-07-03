#ifndef __INTROSTATE_H__
#define __INTROSTATE_H__

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/ApplicationStates/AbstractApplicationState.h>

namespace pan {
	class IntroState final : public Singleton<IntroState>, public AbstractApplicationState {
		SET_SINGLETON(IntroState)
	protected:
		IntroState();
		virtual ~IntroState() override;
	public:
		virtual Bool init() override;
		virtual void draw() override;
		virtual Bool update() override;
		virtual void shutdown() override;
		virtual void render() override;
		std::string getId() const;
	};
}

#endif