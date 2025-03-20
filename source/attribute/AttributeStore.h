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
#include "../DataNode.h"
#include "../DataWriter.h"
#include "../Dictionary.h"

#include <functional>
#include <utility>
#include <variant>
#include <vector>

class AttributeStore {
	/// Performance-sensitive calls in Ship get low level access.
	friend class Ship;
public:
	/// Gets the value of the specified attribute, or 0 if not present.
	double Get(const std::string &attribute) const;
	double Get(Attribute attribute) const;

	/// Sets the value of the specified attribute. If the attribute is not present, it is added to this collection
	/// with this value.
	void Set(const std::string &attribute, double value);
	void Set(Attribute attribute, double value);

	/// Checks whether there are any attributes stored here.
	bool Empty() const;

	/// Loads data from the data node. This function can be called multiple times on an instance.
	void Load(const DataNode &node);
	/// Writes the attributes into the data writer.
	void Save(DataWriter &writer) const{}

	/// Determine whether the given number of instances of the attributes can
	/// be added to this instance. If not, return the maximum number that can be added.
	int CanAdd(const AttributeStore &other, int count) const;
	/// Adds every attribute from the given AttributeStore to this AttributeStore the specified number of times.
	void Add(const AttributeStore &other, int count);
	/// Adds to the value of an attribute.
	void Add(Attribute attribute, double value);

	/// Calls the given function on all attributes.
	void ForEach(const std::function<void(const std::variant<std::string, Attribute> &, double)> &function) const;

private:
	static double GetMinimum(const std::string &attribute);
	static double GetMinimum(Attribute attribute);


public:
	constexpr static double EPS = 0.0000000001;


private:
	/// Generic attributes that can be anything.
	Dictionary textAttributes;
	/// Categorized attributes and their values, sorted by the attribute.
	std::vector<std::pair<Attribute, double>> categorizedAttributes;
};
