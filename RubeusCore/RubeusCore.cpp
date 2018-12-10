// RubeusCore.cpp : Defines the entry point for the application.
//
#include "RubeusCore.h"

#include <nvidia_enable.h>

int main()
{
	using namespace Rubeus;
	using namespace GraphicComponents;
	using namespace AudioComponents;
	using namespace UtilityComponents;
	using namespace RML;
	using namespace Awerere;

	// Contains the entire Rubeus code base
	LOG(sizeof(*Engine));

	// Generated user file
#include "user_init.cpp"
	// End generated lines

	// startupLevel : std::string contains the startup level name. Defined in user_init.cpp
	Engine->m_StartupLevelName = startupLevel;

	// Level selection loop
	while (true)
	{
		/*
		 * Any running level should call Engine->end() at the end of the game which
		 * changes Engine->m_StartupLevelName to "" and in turn also ends the
		 * level selection loop as seen below. Setting Engine->m_StartupLevelName to
		 * "" directly will also work.
		 */
		if (Engine->m_StartupLevelName == "")
		{
			LOG("Startup level was found to be : NULL");
			break;
		}

		for (auto & item : RLevel::InstantiatedLevels)
		{
			// If level selected is the startup level
			if (item.first == Engine->m_StartupLevelName)
			{
				Engine->load(*item.second);
				Engine->run();
				Engine->getCurrentLevel()->onEnd();
				Engine->cleanUp();
			}
			// The startup level should contain the logic for when to load the next level
		}
	}
	LOG("Rubeus is now exiting");

	return 0;
}

