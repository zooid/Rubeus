/**
 * @file		Include/master_component.h.
 *
 * @brief	Declares the master class
 */

#pragma once

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <memory>

#include <logger_component.h>
#include <message_system.h>

#define GetVariableName(x) #x

namespace Rubeus
{
	/**
	* @class		RMasterComponent
	*
	* @brief		A master component.
	* 			Serves as parent class for all components
	*/
	class RMasterComponent
	{
	protected:
		/** @brief	Identifier for this component */
		unsigned int m_ComponentID;

	public:
		/** @brief	The message system to send messages */
		static RMessageSystem m_MessageSystem;
		static RMailingList m_mailbox;

		/** @brief	The number of components initialised */
		static unsigned int componentsInitialised;

		/**
		* @fn	MasterComponent::MasterComponent();
		*
		* @brief	Default constructor
		*/
		RMasterComponent();

		/**
		* @fn	virtual MasterComponent::~MasterComponent();
		*
		* @brief	Destructor
		*/
		virtual ~RMasterComponent();

		/**
		* @fn		unsigned int MasterComponent::getComponentID();
		*
		* @brief		Gets component identifier
		*
		* @return	The component ID.
		*/
		unsigned int getComponentID() const;

		/**
		 * @fn		inline std::string getName()
		 *
		 * @brief	Gets the fully qualified name of this component
		 *
		 * @return	The name.
		 */
		inline std::string getName() { return typeid(*this).name(); }

		/**
		 * @fn		friend std::ostream & operator<<(std::ostream & stream, RMasterComponent & component)
		 *
		 * @brief	Prints the name of this component
		 *
		 * @return	The name.
		 */
		friend std::ostream & operator<<(std::ostream & stream, RMasterComponent & component);

	protected:
	};
}
