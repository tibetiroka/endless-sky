/* AttributeEffect.h
Copyright (c) 2023 by tibetiroka
Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.
Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <cstdint>

/// The different effects of an attribute.
enum class AttributeEffect : uint8_t {
	// These attributes have matching categories (e.g. SHIELD_GENERATION -> SHIELDS).
	// Those categories have these effects as their default effect.
	SHIELDS,
	HULL,
	THRUST,
	REVERSE_THRUST,
	TURN,
	ACTIVE_COOLING,
	RAMSCOOP,
	CLOAK,
	// These attributes don't have matching categories
	COOLING,
	FORCE,
	ENERGY,
	FUEL,
	HEAT,
	JAM,
	DISABLED,
	MINABLE,
	PIERCING,
	ATTRIBUTE_EFFECT_COUNT ///< Also used to signal "no category effect" for categories
};
