/* AttributeStore.cpp
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

#include "AttributeStore.h"

#include <algorithm>
#include <cstring>
#include <limits>
#include <map>

using namespace std;

namespace {
	const double EPS = 0.0000000001;

	const map<string, Attribute> ATTRIBUTE_MAPPINGS = {
			{"hull threshold", 0}
	};
}



double AttributeStore::Get(const string &attribute) const
{
	return textAttributes.Get(attribute);
}



double AttributeStore::Get(const Attribute attribute) const
{
	auto it = std::lower_bound(categorizedAttributes.begin(), categorizedAttributes.end(), attribute);
	if(it == categorizedAttributes.end() || std::bit_cast<Attribute::underlying_type>(it->first) !=
	        std::bit_cast<Attribute::underlying_type>(attribute))
		return 0.;
	return it->second;
}



void AttributeStore::Set(const std::string &attribute, double value)
{
	textAttributes[attribute] = value;
}



void AttributeStore::Set(Attribute attribute, double value)
{
	auto it = std::lower_bound(categorizedAttributes.begin(), categorizedAttributes.end(), attribute);
	if(it == categorizedAttributes.end() || std::bit_cast<Attribute::underlying_type>(it->first) !=
	        std::bit_cast<Attribute::underlying_type>(attribute))
		categorizedAttributes.insert(it, {attribute, value});
	else
		it->second = value;
}



bool AttributeStore::Empty() const
{
	return textAttributes.empty() && categorizedAttributes.empty();
}



int AttributeStore::CanAdd(const AttributeStore &other, int count) const
{
	other.ForEach([&](const variant<std::string, Attribute> &key, double otherValue)
	{
		double minimum = key.index() ? GetMinimum(get<1>(key)) : GetMinimum(get<0>(key));
		if(minimum == -numeric_limits<double>::infinity()) // no minimum value -> no need to check
			return;

		// Only automatons may have a "required crew" of 0.
		if(!key.index() && get<0>(key) == "required crew")
			minimum = !(textAttributes.Get("automaton") || other.textAttributes.Get("automaton"));

		double value = key.index() ? Get(get<1>(key)) : Get(get<0>(key));
		// Allow for rounding errors:
		if(value + otherValue * count < minimum - EPS)
			count = (value - minimum) / -otherValue + EPS;
	});

	return count;
}



void AttributeStore::Add(const AttributeStore &other, int count)
{
	other.ForEach([&](const variant<std::string, Attribute> &key, double otherValue)
	{
		if(key.index())
			Add(get<1>(key), otherValue * count);
		else
			Set(get<0>(key), Get(get<0>(key)) + otherValue * count);
	});
}



/// Adds to the value of an attribute.
void AttributeStore::Add(Attribute attribute, double valueToAdd)
{
	auto it = std::lower_bound(categorizedAttributes.begin(), categorizedAttributes.end(), attribute);
	if(it == categorizedAttributes.end() || std::bit_cast<Attribute::underlying_type>(it->first) != std::bit_cast<Attribute::underlying_type>(attribute))
		categorizedAttributes.insert(it, {attribute, valueToAdd});
	else
		it->second += valueToAdd;
}



void AttributeStore::ForEach(const std::function<void(const std::variant<std::string, Attribute> &, double)> &function) const
{
	for(const auto &[key, value] : textAttributes)
		function({key}, value);
	for(const auto &[key, value] : categorizedAttributes)
		function({key}, value);
}
