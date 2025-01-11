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

#include <array>
#include <bit>
#include <compare>
#include <cstdint>
#include <utility>

/// An attribute is a combination of a category and effect.
/// Categories can have their own 'category effect' to create pseudo-categories such as 'burn resistance'.
/// Effects can have a modifier to signal being over-time, relative, or multipliers.
class Attribute {
public:
	using underlying_type = uint32_t;

	Attribute(AttributeCategory category, AttributeEffect effect, Modifier modifier = Modifier::NONE);
	Attribute(AttributeCategory category, AttributeEffect categoryEffect, Modifier categoryEffectModifier, AttributeEffect effect,
			Modifier effectModifier = Modifier::NONE);

	inline AttributeCategory Category() const;
	inline AttributeEffect CategoryEffect() const;
	inline Modifier CategoryEffectModifier() const;
	inline Modifier EffectModifier() const;
	inline AttributeEffect Effect() const;

	/// Checks if this attribute is a requirement for its category. A required attribute is
	/// consumed in order to execute an action.
	bool IsRequirement() const;

	// To compare attributes, it is sufficient to just compare the underlying bit pattern.
	inline std::strong_ordering operator<=>(Attribute other) const;
	inline std::strong_ordering operator<=>(const std::pair<Attribute, double> &other) const;
	// TODO: Define operator= here. Currently, due to a GCC bug, this would make the type not trivially copyable,
	// breaking std::bit_cast.


public:
	/// Gets the CATEGORY_BITS of state representing the given category.
	/// The minimum numerical value of an attribute of this category is the returned filter.
	/// The maximum theoretical value is filter | EFFECT_MASK, though it currently doesn't describe a valid attribute.
	static underlying_type CreateCategoryFilter(AttributeCategory category,
			AttributeEffect categoryEffect = AttributeEffect::ATTRIBUTE_EFFECT_COUNT, Modifier modifier = Modifier::NONE);

	static std::array<AttributeEffect, static_cast<std::size_t>(AttributeEffect::ATTRIBUTE_EFFECT_COUNT)> EFFECTS;
	static std::array<AttributeCategory, static_cast<std::size_t>(AttributeCategory::ATTRIBUTE_CATEGORY_COUNT)> CATEGORIES;

public:
	static constexpr unsigned int CATEGORY_BITS = 20;
	static constexpr unsigned int EFFECT_BITS = 12;
	static constexpr unsigned int EFFECT_WITHOUT_MODIFIER_BITS = 8;
	/// Has 1 where the bit is part of the category (or category effect, or its modifier).
	static constexpr underlying_type CATEGORY_MASK = (static_cast<underlying_type>(-1) >> EFFECT_BITS) << EFFECT_BITS;
	/// Has 1 where the bit is part of the effect (or its modifier)
	static constexpr underlying_type EFFECT_MASK = (static_cast<underlying_type>(-1) << CATEGORY_BITS) >> CATEGORY_BITS;
	/// Has 1 where the bit is part of the effect (but not its modifier)
	static constexpr underlying_type EFFECT_WITHOUT_MODIFIER_MASK = static_cast<underlying_type>(-1) ^
			((static_cast<underlying_type>(-1) >> EFFECT_WITHOUT_MODIFIER_BITS) << EFFECT_WITHOUT_MODIFIER_BITS);


private:
	// The declaration order of fields is significant, as we use this for efficient ordering of attributes.
	// Attributes of the same category are sorted together, ordered by their effect.

	AttributeCategory category;
	AttributeEffect categoryEffect;
	Modifier categoryEffectModifier: 4 = Modifier::NONE;
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
	static_assert(sizeof(Attribute) == sizeof(underlying_type));
	return std::bit_cast<underlying_type>(*this) <=> std::bit_cast<underlying_type>(other);
}



inline std::strong_ordering Attribute::operator<=>(const std::pair<Attribute, double> &other) const
{
	return operator<=>(other.first);
}
