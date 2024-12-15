/* AttributeStore.h
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

#include "Attribute.h"
#include "../Dictionary.h"

#include <utility>
#include <vector>

class AttributeStore {
public:
	// Gets the value of the specified attribute, or 0 if not present.
	double Get(const std::string &attribute) const;

	// Sets the value of the specified attribute. If the attribute is not present, it is added to this collection
	// with this value.
	void Set(const std::string &attribute, double value);

	// Checks whether there are any attributes stored here.
	bool Empty() const;


private:
	// Generic attributes that can be anything.
	Dictionary textAttributes;
	// Attributes that 
	std::vector<std::pair<Attribute, double>> categorizedAttributes;
	std::vector<std::pair<Attribute, double>> resistanceAttributes;
	std::vector<std::pair<Attribute, double>> protectionAttributes;
};
