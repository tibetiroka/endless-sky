/* Attribute.h
Copyright (c) 2024 by tibetiroka
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

#include "AttributeCategory.h"
#include "AttributeEffect.h"
#include "Modifier.h"

#include <bit>
#include <compare>
#include <cstdint>

/// An attribute is a combination of a category and effect.
/// Categories can have their own 'category effect' to create pseudo-categories such as 'burn resistance'.
/// Effects can have a modifier to signal being over-time, relative, or multipliers.
class Attribute {
public:
	Attribute(AttributeCategory category, AttributeEffect effect, Modifier modifier = Modifier::NONE);
	Attribute(AttributeCategory category, AttributeEffect categoryEffect, AttributeEffect effect,
			Modifier modifier = Modifier::NONE);

	inline AttributeCategory Category() const;
	inline AttributeEffect CategoryEffect() const;
	inline Modifier CategoryEffectModifier() const;
	inline Modifier EffectModifier() const;
	inline AttributeEffect Effect() const;

	// To compare attributes, it is sufficient to just compare the underlying bit pattern.
	inline std::strong_ordering operator<=>(Attribute other) const;


private:
	// The declaration order of fields is significant, as we use this for efficient ordering of attributes.
	// Attributes of the same category are sorted together, ordered by their effect.

	AttributeCategory category;
	AttributeEffect categoryEffect;
	Modifier categoryEffectModifier: 4;
	Modifier effectModifier: 4;
	AttributeEffect effect;
};

inline AttributeCategory Attribute::Category() const {return category;}
inline AttributeEffect Attribute::CategoryEffect() const {return categoryEffect;}
inline Modifier Attribute::CategoryEffectModifier() const {return categoryEffectModifier;}
inline Modifier Attribute::EffectModifier() const {return effectModifier;}
inline AttributeEffect Attribute::Effect() const {return effect;}

inline std::strong_ordering Attribute::operator<=>(Attribute other) const
{
	static_assert(sizeof(Attribute) == sizeof(uint32_t));
	return std::bit_cast<uint32_t>(*this) <=> std::bit_cast<uint32_t>(other);
}
