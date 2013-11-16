/**
 * Weapon.h
 * Weapon class
 *
 * Copyright (c) 2011 Dennis J. McWherter, Jr.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 * Last Update: 20 June 2011
 */

#ifndef __MICROFPS_WEAPON_H_
#define __MICROFPS_WEAPON_H_

#include "../universal.h"

namespace MicroFPS
{
	/**
	 * Weapon
	 * Abstract Base class for Weapons
	 */
	class Weapon
	{
	protected:
		class Effects; // Forward decl
	public:
		/**
		 * Constructor
		 */
		Weapon(){}

		/**
		 * Destructor
		 */
		virtual ~Weapon(){}

		/**
		 * getNode
		 * Get the weapon node
		 * @return the weapon node (based on whatever render engine you're using)
		 */
		// weapon node defined in typedef

		/**
		 * getAmmo
		 * @return u16 ammo - the amount of ammo currently available
		 */
		virtual u16 getAmmo() const = 0; // That's a lot of ammo in 16-bits <3

		/**
		 * getClip
		 * @return u16 ammo - return the amount of ammo in
		 *	the current clip
		 */
		virtual u16 getClip() const = 0;

		/**
		 * getDamage
		 * Weapon damage
		 * @return s16 damage - amount of damage done
		 */
		virtual s16 getDamage() const = 0;

		/**
		 * getMaxCapacity
		 * Weapon's max capacity
		 * @return u16 max capacity of weapon
		 */
		virtual u16 getMaxCapacity() const = 0;

		/**
		 * getMaxClipSize
		 * How many shots to reload?
		 * @return u16 max capacity of a clip
		 */
		virtual u16 getMaxClipSize() const = 0;

		/**
		 * getWeaponName
		 * Name of the Weapon
		 * @return stringw - weapon name
		 */
		virtual stringw getWeaponName() const = 0;

		/**
		 * decreaseAmmo
		 * Using ammo (i.e. shooting gun)
		 * @param u16 ammo - amount of ammo to remove
		 */
		virtual void decreaseAmmo(u16 ammo) = 0;

		/**
		 * addAmmo
		 * Gain ammo :)
		 * @param u16 ammo - ammo to add
		 */
		virtual void addAmmo(u16 ammo) = 0;

		/**
		 * setAmmo
		 * Of course, you don't need to always do math ;)
		 * @return u16 ammo - where to set ammo
		 */
		virtual void setAmmo(u16 ammo) = 0;

		/**
		 * getEffects
		 * Weapon effects pointer
		 * @return Effects*
		 */
		virtual Effects * getEffects() const = 0;

	protected:
		/** TODO: Add Functions for animations, sounds, etc. */
		/**
		 * Effects class
		 */
		class Effects
		{
		public:
			/**
			 * Constructor
			 */
			Effects(){}

			/**
			 * Destructor
			 */
			virtual ~Effects(){}

			/**
			 * getAnimation
			 * Retrieves an std::pair<u32,u32> with key frames
			 */
			virtual std::pair<u32,u32> getAnimation(std::string name) const = 0;

			/**
			 * getSound
			 * -- Not yet implemented; need to integrate audio engine
			 */
			virtual void getSound() const = 0;

			/**
			 * addAnimation
			 * @param std::string name
			 * @param u32 start frame
			 * @param u32 end
			 */
			virtual void addAnimation(std::string, u32 start, u32 end) = 0;

			/**
			 * addSound
			 * -- Not implemented yet; need to integrate audio engine
			 */
			virtual void addSound() = 0;

			/**
			 * shoot
			 */
			virtual void shoot() = 0;
		};
	};
}

#endif // __MICROFPS_WEAPON_H_
