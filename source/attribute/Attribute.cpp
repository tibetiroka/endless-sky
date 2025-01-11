/* Attribute.cpp
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

#include "Attribute.h"

using enum AttributeCategory;
using enum AttributeEffect;
using namespace std;



Attribute::Attribute(AttributeCategory category, AttributeEffect effect, Modifier modifier)
	: category(category), categoryEffect(AttributeEffect::ATTRIBUTE_EFFECT_COUNT), effectModifier(modifier), effect(effect)
{
}



Attribute::Attribute(AttributeCategory category, AttributeEffect categoryEffect, Modifier categoryEffectModifier,
		AttributeEffect effect, Modifier effectModifier)
		: category(category), categoryEffect(categoryEffect), categoryEffectModifier(categoryEffectModifier),
		effectModifier(effectModifier), effect(effect)
{
}



/// Checks if this attribute is a requirement for its category. A required attribute is
/// consumed in order to execute an action.
bool Attribute::IsRequirement() const
{
	if(category == PASSIVE || category == DAMAGE || category == PROTECTION)
		return false;
	if(effectModifier == Modifier::OVER_TIME)
		return false;
	if(static_cast<int>(category) == static_cast<int>(effect) && category <= CLOAKING)
		return false;
	if(effect <= HULL || effect == ENERGY || effect == FUEL)
		return true;
	return false;
}



/// Gets the CATEGORY_BITS of state representing the given category.
Attribute::underlying_type Attribute::CreateCategoryFilter(AttributeCategory category, AttributeEffect categoryEffect,
		Modifier modifier)
{
	// Create an attribute with a dummy effect, then extract the category bits.
	Attribute a{category, categoryEffect, modifier, static_cast<AttributeEffect>(0)};
	return std::bit_cast<underlying_type>(a);
}



array<AttributeEffect, static_cast<size_t>(AttributeEffect::ATTRIBUTE_EFFECT_COUNT)> Attribute::EFFECTS = []()
{
	array<AttributeEffect, static_cast<size_t>(AttributeEffect::ATTRIBUTE_EFFECT_COUNT)> array{};
	for(int i = 0; i < static_cast<int>(ATTRIBUTE_EFFECT_COUNT); i++)
		array[i] = static_cast<AttributeEffect>(i);
	return array;
}();



std::array<AttributeCategory, static_cast<std::size_t>(AttributeCategory::ATTRIBUTE_CATEGORY_COUNT)> Attribute::CATEGORIES = []()
{
	std::array<AttributeCategory, static_cast<std::size_t>(AttributeCategory::ATTRIBUTE_CATEGORY_COUNT)> array{};
	for(int i = 0; i < static_cast<int>(ATTRIBUTE_CATEGORY_COUNT); i++)
		array[i] = static_cast<AttributeCategory>(i);
	return array;
}();
