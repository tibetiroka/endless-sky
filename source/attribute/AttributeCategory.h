/* AttributeCategory.h
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

/// Defines groupings for attributes. Many of these are situations when outfit effects are applied to a ship.
/// Categories can also be combined with an effect (categoryEffect in Attribute). This is primarily used for RESISTANCE, where
/// categories such as "burn resistance" are created this way.
enum AttributeCategory : uint8_t {
	// These categories have matching default effects.
	SHIELD_GENERATION,
	HULL_REPAIR,
	THRUSTING,
	REVERSE_THRUSTING,
	TURNING,
	ACTIVE_COOL,
	RAMSCOOPING,
	CLOAKING,
	// These don't have default effects.
	AFTERBURNING,
	FIRING,
	PROTECTION,
	RESISTANCE,
	DAMAGE,
	PASSIVE,
	ATTRIBUTE_CATEGORY_COUNT
};